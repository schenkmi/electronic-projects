// Copyright (C) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT License

//! One ROM generation Builder objects and functions

use alloc::collections::{BTreeMap, BTreeSet};
use alloc::format;
use alloc::string::{String, ToString};
use alloc::vec;
use alloc::vec::Vec;

use onerom_config::fw::FirmwareProperties;
use onerom_config::rom::RomType;

use crate::image::{CsConfig, CsLogic, Location, Rom, RomSet, RomSetType, SizeHandling};
use crate::meta::Metadata;
use crate::{Error, FIRMWARE_SIZE, MAX_METADATA_LEN, Result};

/// Main Builder object
///
/// Model is to create the builder from a JSON config, retrieve the list of
/// files that need to be loaded, call `add_file` for each file once loaded,
/// then call `build` to generate the metadata and ROM images.
///
/// # Example
/// ```no_run
/// use onerom_config::fw::{FirmwareProperties, FirmwareVersion, ServeAlg};
/// use onerom_config::hw::Board;
/// use onerom_config::mcu::Variant as McuVariant;
/// # use onerom_gen::Error;
/// use onerom_gen::builder::{Builder, FileData, License};
///
/// # fn fetch_file(url: &str) -> Result<Vec<u8>, Error> {
/// #     // Dummy implementation for doc test
/// #     Ok(vec![0u8; 8192])
/// # }
/// #
/// # fn accept_license(license: &License) -> Result<(), Error> {
/// #     // Dummy implementation for doc test
/// #     Ok(())
/// # }
/// #
/// let json = r#"{
///     "version": 1,
///     "description": "Example ROM configuration",
///     "rom_sets": [{
///         "type": "single",
///         "roms": [{
///             "file": "http://example.com/kernal.bin",
///             "type": "2764",
///             "cs1": 0
///         }]
///     }]
/// }"#;
///
/// // Create builder from JSON
/// let mut builder = Builder::from_json(json)?;
///
/// // Get list of licenses to be validated
/// let licenses = builder.licenses();
///
/// // Accept licenses as required
/// for license in licenses {
///     accept_license(&license)?; // Your implementation
///
///     builder.accept_license(&license)?; // Mark as validated
/// }
///
/// // Get list of files to load
/// let file_specs = builder.file_specs();
///
/// // Load each file (fetch or read from disk)
/// for spec in file_specs {
///     let data = fetch_file(&spec.source)?; // Your implementation
///     
///     builder.add_file(FileData {
///         id: spec.id,
///         data,
///     })?;
/// }
///
/// // Get config description (optional)
/// let description = builder.description();
///
/// // Define firmware properties
/// let props = FirmwareProperties::new(
///     FirmwareVersion::new(0, 5, 1, 0),
///     Board::Ice24UsbH,
///     McuVariant::F411RE,
///     ServeAlg::Default,
///     false,
/// ).unwrap();
///
/// // Validate ready to build (optional)
/// builder.build_validation(&props)?;
///
/// // Build metadata and ROM images
/// let (metadata_buf, rom_images_buf) = builder.build(props)?;
/// // Buffers ready to flash at appropriate offsets
/// # Ok::<(), onerom_gen::Error>(())
/// ```
#[derive(Debug, serde::Serialize, serde::Deserialize)]
pub struct Builder {
    config: Config,
    files: BTreeMap<usize, Vec<u8>>,
    licenses: BTreeMap<usize, License>,
    file_id_map: BTreeMap<usize, usize>,
}

impl Builder {
    /// Create from JSON config
    pub fn from_json(json: &str) -> Result<Self> {
        let config: Config = serde_json::from_str(json).map_err(|e| Error::InvalidConfig {
            error: e.to_string(),
        })?;

        Self::validate_config(&config)?;

        let mut builder = Self {
            config,
            files: BTreeMap::new(),
            licenses: BTreeMap::new(),
            file_id_map: BTreeMap::new(),
        };

        builder.build_file_id_map();

        Ok(builder)
    }

    /// Get a reference to the config
    pub fn config(&self) -> &Config {
        &self.config
    }

    fn validate_config(config: &Config) -> Result<()> {
        // Validate version
        if config.version != 1 {
            return Err(Error::UnsupportedConfigVersion {
                version: config.version,
            });
        }

        // Validate each rom set has roms
        let mut rom_num = 0;
        for set in config.rom_sets.iter() {
            if set.roms.is_empty() {
                return Err(Error::NoRoms);
            }

            if set.roms.len() > 1 {
                if set.set_type == RomSetType::Single {
                    return Err(Error::TooManyRoms {
                        expected: 1,
                        actual: set.roms.len(),
                    });
                }

                if set.roms.len() > 3 && set.set_type == RomSetType::Multi {
                    return Err(Error::TooManyRoms {
                        expected: 3,
                        actual: set.roms.len(),
                    });
                }

                if set.roms.len() > 4 && set.set_type == RomSetType::Banked {
                    return Err(Error::TooManyRoms {
                        expected: 4,
                        actual: set.roms.len(),
                    });
                }
            }

            for rom in set.roms.iter() {
                let rom0 = &set.roms[0];

                // Check filename specified
                if rom.file.is_empty() {
                    return Err(Error::InvalidConfig {
                        error: format!("ROM {} file name is empty", rom_num),
                    });
                }

                // Check all ROMs in a bank are same type
                if set.set_type == RomSetType::Banked && rom.rom_type != rom0.rom_type {
                    return Err(Error::InvalidConfig {
                        error: format!(
                            "All ROMs in a banked set must be of the same type ({} != {})",
                            rom.rom_type.name(),
                            rom0.rom_type.name()
                        ),
                    });
                }

                // Check that required CS lines are specified
                for line in rom.rom_type.control_lines() {
                    if line.name != "ce" && line.name != "oe" {
                        let cs = match line.name {
                            "cs1" => &rom.cs1,
                            "cs2" => &rom.cs2,
                            "cs3" => &rom.cs3,
                            _ => {
                                return Err(Error::InvalidConfig {
                                    error: format!("Unknown control line {}", line.name),
                                });
                            }
                        };
                        if cs.is_none() {
                            return Err(Error::MissingCsConfig { line: line.name });
                        }
                    }
                }

                // Check that invalid CS lines are NOT specified
                let has_cs2 = rom
                    .rom_type
                    .control_lines()
                    .iter()
                    .any(|line| line.name == "cs2");
                let has_cs3 = rom
                    .rom_type
                    .control_lines()
                    .iter()
                    .any(|line| line.name == "cs3");

                if rom.cs2.is_some() && !has_cs2 {
                    return Err(Error::InvalidConfig {
                        error: format!(
                            "CS2 specified for ROM type {} which does not use CS2",
                            rom.rom_type.name()
                        ),
                    });
                }

                if rom.cs3.is_some() && !has_cs3 {
                    return Err(Error::InvalidConfig {
                        error: format!(
                            "CS3 specified for ROM type {} which does not use CS3",
                            rom.rom_type.name()
                        ),
                    });
                }

                // Check that at least one CS line is active (not all ignore)
                let cs1_active = rom.cs1.is_some() && rom.cs1.unwrap() != CsLogic::Ignore;
                let cs2_active = rom.cs2.is_some() && rom.cs2.unwrap() != CsLogic::Ignore;
                let cs3_active = rom.cs3.is_some() && rom.cs3.unwrap() != CsLogic::Ignore;

                if !cs1_active && !cs2_active && !cs3_active {
                    return Err(Error::InvalidConfig {
                        error: format!(
                            "ROM type {} must have at least one active CS line (not all ignore)",
                            rom.rom_type.name()
                        ),
                    });
                }

                // Check that CS1 cannot be ignore if other CS lines are active
                if !cs1_active && (cs2_active || cs3_active) {
                    return Err(Error::InvalidConfig {
                        error: format!("CS1 cannot be ignore when CS2 or CS3 are active"),
                    });
                }

                // Validate location if present
                if let Some(location) = &rom.location {
                    // Check length is non-zero
                    if location.length == 0 {
                        return Err(Error::InvalidConfig {
                            error: format!("ROM {} location length must be non-zero", rom_num),
                        });
                    }

                    // Check for overflowing a usize (!)
                    if location.start.checked_add(location.length).is_none() {
                        return Err(Error::InvalidConfig {
                            error: format!("ROM {} location start + length overflows", rom_num),
                        });
                    }
                }

                rom_num += 1;
            }

            // After the loop: validate CS consistency for multi/banked sets
            if set.set_type == RomSetType::Multi || set.set_type == RomSetType::Banked {
                if set.roms.len() > 1 {
                    // Get CS configuration from first ROM
                    let first_cs1 = set.roms[0].cs1;
                    let first_cs2 = set.roms[0].cs2;
                    let first_cs3 = set.roms[0].cs3;

                    // Check all other ROMs have the same CS configuration
                    for (idx, rom) in set.roms.iter().enumerate().skip(1) {
                        if rom.cs1 != first_cs1 || rom.cs2 != first_cs2 || rom.cs3 != first_cs3 {
                            if (rom.cs2 != first_cs2) && let Some(cs) = rom.cs2 && (cs == CsLogic::Ignore) {
                                // Ignore difference if cs2 is ignore
                                // If there are 3 CS lines on ROM 1, cs2 must
                                // be the same, but we don't support that yet
                                continue;
                            }
                            // Should do a similar test for CS3, but we don't support that yet
                            return Err(Error::InvalidConfig {
                                error: format!(
                                    "{:?} set requires all ROMs to have identical CS configuration. ROM 0 has cs1={:?}/cs2={:?}/cs3={:?}, but ROM {} has cs1={:?}/cs2={:?}/cs3={:?}",
                                    set.set_type,
                                    first_cs1,
                                    first_cs2,
                                    first_cs3,
                                    idx,
                                    rom.cs1,
                                    rom.cs2,
                                    rom.cs3
                                ),
                            });
                        }
                    }
                }
            }
        }

        Ok(())
    }

    fn build_file_id_map(&mut self) {
        let mut seen_files: BTreeMap<(String, Option<String>), usize> = BTreeMap::new();
        let mut file_id = 0;
        let mut rom_id = 0;

        for rom_set in self.config.rom_sets.iter() {
            for rom in &rom_set.roms {
                let key = (rom.file.clone(), rom.extract.clone());
                
                let assigned_file_id = if let Some(&existing_id) = seen_files.get(&key) {
                    existing_id
                } else {
                    seen_files.insert(key, file_id);
                    let id = file_id;
                    file_id += 1;
                    id
                };
                
                self.file_id_map.insert(rom_id, assigned_file_id);
                rom_id += 1;
            }
        }
    }

    /// Get list of files that need to be loaded
    pub fn file_specs(&self) -> Vec<FileSpec> {
        let mut specs = Vec::new();
        let mut seen_files: BTreeMap<(String, Option<String>), usize> = BTreeMap::new();
        let mut rom_id = 0;

        for (rom_set_num, rom_set) in self.config.rom_sets.iter().enumerate() {
            for rom in &rom_set.roms {
                let key = (rom.file.clone(), rom.extract.clone());
                let file_id = *self.file_id_map.get(&rom_id).unwrap();
                
                if !seen_files.contains_key(&key) {
                    specs.push(FileSpec {
                        id: file_id,
                        description: rom.description.clone(),
                        source: rom.file.clone(),
                        extract: rom.extract.clone(),
                        size_handling: rom.size_handling.clone(),
                        rom_type: rom.rom_type.clone(),
                        rom_size: rom.rom_type.size_bytes(),
                        cs1: rom.cs1,
                        cs2: rom.cs2,
                        cs3: rom.cs3,
                        set_id: rom_set_num,
                        set_type: rom_set.set_type.clone(),
                        set_description: rom_set.description.clone(),
                    });
                    seen_files.insert(key, file_id);
                }
                
                rom_id += 1;
            }
        }

        specs
    }

    /// Add a loaded file - called multiple times, once for each file that
    /// has been loaded
    pub fn add_file(&mut self, file: FileData) -> Result<()> {
        // Check if already added
        if self.files.contains_key(&file.id) {
            return Err(Error::DuplicateFile { id: file.id });
        }

        // Validate id is in range
        let total_files = self.total_file_count();
        if file.id >= total_files {
            return Err(Error::InvalidFile {
                id: file.id,
                total: total_files,
            });
        }

        self.files.insert(file.id, file.data);
        Ok(())
    }

    /// Get list of licenses that need to be validated
    pub fn licenses(&mut self) -> Vec<License> {
        let mut licenses = Vec::new();

        let mut license_id = 0;
        let mut rom_id = 0;
        for rom_set in self.config.rom_sets.iter() {
            for rom in &rom_set.roms {
                if let Some(ref url) = rom.license {
                    let license = License::new(license_id, rom_id, url.clone());
                    licenses.push(license.clone());
                    self.licenses.insert(license_id, license);
                    license_id += 1;
                }
                rom_id += 1;
            }
        }

        licenses
    }

    /// Mark a license as validated
    pub fn accept_license(&mut self, license: &License) -> Result<()> {
        // Check license id is valid
        let own_license = self.licenses.remove(&license.id);
        if own_license.is_some() {
            self.licenses.insert(license.id, own_license.unwrap());
            Ok(())
        } else {
            Err(Error::InvalidLicense { id: license.id })
        }
    }

    fn total_file_count(&self) -> usize {
        self.file_id_map.values().collect::<BTreeSet<_>>().len()
    }

    /// Validate whether ready to build
    pub fn build_validation(&self, props: &FirmwareProperties) -> Result<()> {
        // Check all files loaded
        for ii in 0..self.total_file_count() {
            if !self.files.contains_key(&ii) {
                return Err(Error::MissingFile { id: ii });
            }
        }

        // Check all licenses validated
        for (id, license) in self.licenses.iter() {
            if !license.validated {
                return Err(Error::UnvalidatedLicense { id: *id });
            }
        }

        // Validate all ROM types are supported by this board
        let board = props.board();
        for set in self.config.rom_sets.iter() {
            for rom in set.roms.iter() {
                if !board.supports_rom_type(rom.rom_type) {
                    return Err(Error::UnsupportedRomType {
                        rom_type: rom.rom_type.clone(),
                    });
                }
            }
        }

        Ok(())
    }

    /// Generate metadata and ROM images once all files loaded
    ///
    /// Returns (metadata, Rom images)
    pub fn build(&self, props: FirmwareProperties) -> Result<(Vec<u8>, Vec<u8>)> {
        // Validate ready to build
        self.build_validation(&props)?;

        // Build Rom and RomSet objects together
        let mut rom_sets = Vec::new();
        let mut rom_id = 0;

        for (set_id, rom_set_config) in self.config.rom_sets.iter().enumerate() {
            let mut set_roms = Vec::new();

            for rom_config in &rom_set_config.roms {
                let file_id = self.file_id_map.get(&rom_id).unwrap();
                let data = self.files.get(file_id).unwrap();

                let filename = rom_config.filename();

                let rom = Rom::from_raw_rom_image(
                    rom_id,
                    filename,
                    rom_config.label.clone(),
                    data,
                    vec![0u8; rom_config.rom_type.size_bytes()],
                    &rom_config.rom_type,
                    CsConfig::new(rom_config.cs1, rom_config.cs2, rom_config.cs3),
                    &rom_config.size_handling,
                    rom_config.location,
                )?;
                set_roms.push(rom);
                rom_id += 1;
            }

            let rom_set = RomSet::new(
                set_id,
                rom_set_config.set_type.clone(),
                props.serve_alg(),
                set_roms,
            )?;
            rom_sets.push(rom_set);
        }

        // Build Metadata
        let metadata = Metadata::new(props.board(), rom_sets, props.boot_logging());

        // Get buffer sizes
        let metadata_size = metadata.metadata_len();
        let rom_data_size: usize = metadata.rom_images_size();
        let set_count = metadata.total_set_count();

        // Check the board has enough space
        let mcu_variant = props.mcu_variant();
        let flash_size = mcu_variant.flash_storage_bytes();
        let rom_space = flash_size - FIRMWARE_SIZE - MAX_METADATA_LEN;
        assert!(rom_space > 0);

        // Figure out the ROM data size
        if rom_data_size > rom_space {
            return Err(Error::BufferTooSmall {
                location: "Flash",
                expected: rom_data_size,
                actual: rom_space,
            });
        }

        // Allocate buffers
        let mut metadata_buf = vec![0u8; metadata_size];
        let mut rom_data_buf = vec![0u8; rom_data_size];
        let mut rom_data_ptrs = vec![0u32; set_count];

        // Write metadata
        metadata.write_all(&mut metadata_buf, &mut rom_data_ptrs)?;
        // Note rom_data_ptrs unused here - absolute flash addresses.

        // Write ROM data
        metadata.write_roms(&mut rom_data_buf)?;

        // Done - return the two buffers
        Ok((metadata_buf, rom_data_buf))
    }

    fn num_rom_sets(&self) -> usize {
        self.config.rom_sets.len()
    }

    fn num_roms(&self) -> usize {
        self.config.rom_sets.iter().map(|set| set.roms.len()).sum()
    }

    /// Build config description
    ///
    /// Returns a string like:
    ///
    /// No multi-set/banked ROMS:
    ///
    /// ```text
    /// Name of config
    /// --------------
    /// 
    /// Description of config
    ///
    /// Detailed description
    ///
    /// Images:
    /// 0: Image 0
    /// 1: Image 1
    ///
    /// Notes```
    ///
    /// Multi-set/banked ROMs:
    ///
    /// ```text
    /// Description of config
    ///
    /// Detailed description
    ///
    /// Sets:
    /// 0: Image 0
    /// 1: Image 1
    ///
    /// Notes```
    pub fn description(&self) -> String {
        let mut desc = String::new();

        if let Some(name) = self.config.name.as_ref() {
            desc.push_str(name);
            desc.push_str("\n");
            desc.push_str(&"-".repeat(name.len()));
            desc.push_str("\n\n");
        }

        desc.push_str(&self.config.description);
        desc.push_str("\n\n");

        if let Some(detail) = &self.config.detail {
            desc.push_str(detail);
            desc.push_str("\n\n");
        }

        let multi_rom_sets = if self.num_rom_sets() == self.num_roms() {
            desc.push_str("Images:");
            false
        } else {
            desc.push_str("Sets:");
            true
        };
        desc.push_str("\n");

        let mut none = true;
        for (ii, set) in self.config.rom_sets.iter().enumerate() {
            none = false;
            desc.push_str(&format!("{ii}:"));
            if multi_rom_sets {
                desc.push_str(&format!(" {:?}", set.set_type));
                if let Some(ref set_desc) = set.description {
                    desc.push_str(&format!(", {set_desc}"));
                }
                desc.push_str("\n");
            } else {
                desc.push_str(" ");
            }

            for (jj, rom) in set.roms.iter().enumerate() {
                if multi_rom_sets {
                    desc.push_str(&format!("  {jj}: "));
                }
                if let Some(rom_desc) = &rom.description {
                    desc.push_str(rom_desc);
                } else {
                    desc.push_str(&rom.file);
                }
                desc.push_str("\n");
            }
        }

        if none {
            desc.push_str("  None\n");
        }

        if let Some(notes) = &self.config.notes {
            desc.push_str("\n");
            desc.push_str(notes);
        } else {
            // Strip trailing \n
            desc.pop();
        }

        desc
    }

    /// Get categories for this config
    pub fn categories(&self) -> Vec<String> {
        let mut categories = Vec::new();
        if let Some(cats) = &self.config.categories {
            for cat in cats {
                categories.push(cat.clone());
            }
        }
        categories
    }
}

/// License details for validation by caller
#[derive(Debug, Clone, serde::Serialize, serde::Deserialize)]
pub struct License {
    /// License ID provided for information only. 
    pub id: usize,

    /// File ID that this license applies to, provided for information only.
    pub file_id: usize,

    /// License URL/identifier.  Used by caller to retrieve and present to user
    /// for acceptance.
    pub url: String,

    // Whether this license has been validated by the caller
    validated: bool,
}

impl License {
    /// Create new license
    pub fn new(id: usize, file_id: usize, url: String) -> Self {
        Self {
            id,
            file_id,
            url,
            validated: false,
        }
    }
}

/// Details about a file to be loaded by the caller
#[derive(Debug, Clone, serde::Serialize, serde::Deserialize)]
pub struct FileSpec {
    /// File ID to be used when adding the loaded file to the builder
    pub id: usize,

    /// Optional description for this file.  Provided for information only.
    pub description: Option<String>,

    /// Filename or URL of the ROM image to be loaded
    pub source: String,

    /// Optional extract path within an archive (zip/tar) if the file pointed
    /// to is an archive.  If extract is present, the file at that path within
    /// the archive should be extracted before returning the data to the
    /// builder. 
    pub extract: Option<String>,

    /// Size handling configuration for this ROM.  Provided for information
    /// only.
    pub size_handling: SizeHandling,

    /// Type of ROM.  Provided for information only.
    pub rom_type: RomType,

    /// Size of the ROM in bytes.  Provided for information only.
    pub rom_size: usize,

    /// Optional Chip Select 1 logic - only valid for ROM Types that have CS1.
    /// Provided for information only.
    pub cs1: Option<CsLogic>,

    /// Optional Chip Select 2 logic - only valid for ROM Types that have CS2.
    /// Provided for information only.
    pub cs2: Option<CsLogic>,

    /// Optional Chip Select 3 logic - only valid for ROM Types that have CS3.
    /// Provided for information only.
    pub cs3: Option<CsLogic>,

    /// ROM Set ID that this file belongs to.  Provided for information only.
    pub set_id: usize,

    /// ROM Set type that this file belongs to.  Provided for information only.
    pub set_type: RomSetType,

    /// Optional ROM Set description that this file belongs to.  Provided for
    /// information only.
    pub set_description: Option<String>,
}

/// File data loaded by the caller, passed back to the builder.
#[derive(Debug, serde::Serialize, serde::Deserialize)]
pub struct FileData {
    /// File ID as per FileSpec
    pub id: usize,

    /// File data
    pub data: Vec<u8>,
}

/// Top level configuration structure
#[derive(Debug, Clone, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
pub struct Config {
    /// Configuration format version.
    #[cfg_attr(feature = "schemars", schemars(schema_with = "version_schema"))]
    pub version: u32,

    /// Optional name for this configuration.  Is included in the description
    /// output by the builder.
    pub name: Option<String>,

    /// Mandatory description for this configuration.  This is included in the
    /// description output by the builder, following the name.
    pub description: String,

    /// Optional detailed description for this configuration.  This is included
    /// in the description output by the builder, following name and
    /// description.
    pub detail: Option<String>,

    /// Array of ROM set configurations.  Note that even if not using complex
    /// features like dynamic banking and multi-ROM sets, each ROM image is in
    /// its own set.
    /// The builder description output lists either "Images" or "Sets"
    /// depending on whether there are any multi-set or banked sets in use.
    pub rom_sets: Vec<RomSetConfig>,

    /// Optional notes for this configuration.  This is included in the
    /// description output by the builder, following the list of images/sets.
    pub notes: Option<String>,

    /// Optional categories for this configuration, to aid in grouping,
    /// sorting, and searching of configurations.
    pub categories: Option<Vec<String>>,
}

#[cfg(feature = "schemars")]
fn version_schema(_gen: &mut schemars::SchemaGenerator) -> schemars::Schema {
    schemars::json_schema!({
        "const": 1
    })
}

/// ROM Set configuration structure
#[derive(Debug, Default, Clone, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
pub struct RomSetConfig {
    /// Type of ROM set
    #[serde(rename = "type")]
    #[cfg_attr(feature = "schemars", schemars(default))]
    pub set_type: RomSetType,

    /// Optional description for this ROM set.  This is included in the
    /// description output by the builder.
    pub description: Option<String>,

    /// Array of ROM configurations in this set.  Contains 1 member for single
    /// ROM sets, and multiple members for multi-ROM and banked ROM sets.
    pub roms: Vec<RomConfig>,
}

/// ROM configuration structure
#[derive(Debug, Clone, serde::Serialize, serde::Deserialize)]
#[cfg_attr(feature = "schemars", derive(schemars::JsonSchema))]
pub struct RomConfig {
    /// Filename or URL of the ROM image - filename is only valid if using a
    /// generator tool with local file access.  This is passed to the generator
    /// tool to retrieve the ROM image.
    pub file: String,

    /// Optional license URL/identifier for the ROM.  This is passed to the
    /// generator tool to retrieve and ask the user to accept before building.
    pub license: Option<String>,

    /// Optional description for this configuration.  This is included in the
    /// description output by the builder.
    pub description: Option<String>,

    /// Type of ROM
    #[serde(rename = "type")]
    pub rom_type: RomType,

    /// Optional Chip Select 1 logic - only valid for ROM Types that have CS1
    pub cs1: Option<CsLogic>,

    /// Optional Chip Select 2 logic - only valid for ROM Types that have CS2
    pub cs2: Option<CsLogic>,

    /// Optional Chip Select 3 logic - only valid for ROM Types that have CS3
    pub cs3: Option<CsLogic>,

    /// Optional size handling configuration for this ROM.  Used to specify
    /// handling when the image supplied isn't the correct size for this ROM
    /// type.
    #[serde(default)]
    pub size_handling: SizeHandling,

    /// Optional extract path within an archive (zip/tar) if the file pointed
    /// to is an archive.
    pub extract: Option<String>,

    /// Optional label for this ROM image.  If specified, this is used in
    /// metadata instead of the filename (which itself can be complex if
    /// extracting a file from an image and providing location information)
    pub label: Option<String>,

    /// Optional location within a larger image file.  Used to specify start
    /// offset and length within the file.  Useful when multiple ROM images
    /// are concatenated into a single file and one needs to be extracted.
    pub location: Option<Location>,
}

impl RomConfig {
    // Constructs the filename string for metadata.  Note label will be used
    // in metadata instead if specified.
    fn filename(&self) -> String {
        if let Some(label) = &self.label {
            // Return label if we have one
            return label.clone();
        }

        // Base of filename is "file|extract" or just "file"
        let filename_base = if let Some(extract) = &self.extract {
            format!("{}|{}", self.file, extract)
        } else {
            self.file.clone()
        };

        // If location specified, append "|start=0x...,length=0x..."
        if let Some(location) = &self.location {
            format!(
                "{}|start={:#X},length={:#X}",
                filename_base, location.start, location.length
            )
        } else {
            filename_base
        }
    }
}