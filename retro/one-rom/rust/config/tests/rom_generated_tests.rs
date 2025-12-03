// config/tests/generated_tests.rs

use onerom_config::rom::{ControlLineType, ProgrammingPinState, RomType};

#[test]
fn test_rom_2316_specs() {
    let rom = RomType::Rom2316;
    assert_eq!(rom.name(), "2316");
    assert_eq!(rom.size_bytes(), 2048);
    assert_eq!(rom.rom_pins(), 24);
    assert_eq!(rom.num_addr_lines(), 11);
    assert_eq!(rom.address_pins().len(), 11);
    assert_eq!(rom.data_pins().len(), 8);

    let control = rom.control_lines();
    assert_eq!(control.len(), 3);
    assert!(control.iter().any(|c| c.name == "cs1"));
    assert!(
        control
            .iter()
            .all(|c| c.line_type == ControlLineType::Configurable)
    );
}

#[test]
fn test_rom_2364_specs() {
    let rom = RomType::Rom2364;
    assert_eq!(rom.name(), "2364");
    assert_eq!(rom.size_bytes(), 8192);
    assert_eq!(rom.rom_pins(), 24);
    assert_eq!(rom.num_addr_lines(), 13);

    let control = rom.control_lines();
    assert_eq!(control.len(), 1);
    assert_eq!(control[0].name, "cs1");
    assert_eq!(control[0].pin, 20);
}

#[test]
fn test_rom_27128_specs() {
    let rom = RomType::Rom27128;
    assert_eq!(rom.name(), "27128");
    assert_eq!(rom.size_bytes(), 16384);
    assert_eq!(rom.rom_pins(), 28);
    assert_eq!(rom.num_addr_lines(), 14);

    let control = rom.control_lines();
    assert_eq!(control.len(), 2);
    assert!(
        control
            .iter()
            .any(|c| c.name == "ce" && c.line_type == ControlLineType::FixedActiveLow)
    );
    assert!(
        control
            .iter()
            .any(|c| c.name == "oe" && c.line_type == ControlLineType::FixedActiveLow)
    );

    let prog = rom.programming_pins().unwrap();
    assert_eq!(prog.len(), 2);
    let vpp = prog.iter().find(|p| p.name == "vpp").unwrap();
    assert_eq!(vpp.read_state, ProgrammingPinState::Vcc);
}

#[test]
fn test_rom_27512_specs() {
    let rom = RomType::Rom27512;
    assert_eq!(rom.size_bytes(), 65536);
    assert_eq!(rom.num_addr_lines(), 16);

    // Pin 1 is A15
    assert!(!rom.programming_pins().is_none());

    let addr = rom.address_pins();
    assert_eq!(addr[15], 1); // A15 on pin 1
}

#[test]
fn test_try_from_str() {
    assert_eq!(RomType::try_from_str("2364"), Some(RomType::Rom2364));
    assert_eq!(RomType::try_from_str("27128"), Some(RomType::Rom27128));
    assert_eq!(RomType::try_from_str("27512"), Some(RomType::Rom27512));
    assert_eq!(RomType::try_from_str("invalid"), None);
}

#[test]
fn test_all_rom_types_parse() {
    let types = ["2316", "2332", "2364", "23128", "27128", "27256", "27512"];
    for type_name in types {
        assert!(
            RomType::try_from_str(type_name).is_some(),
            "Failed to parse {}",
            type_name
        );
    }
}
