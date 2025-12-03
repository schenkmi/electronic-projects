//! One ROM Lab firmware

// Copyright (c) 2025 Piers Finlayson <piers@piers.rocks>
//
// MIT licence

#[allow(unused_imports)]
use log::{debug, error, info, trace, warn};

use airfrog_rpc::channel::{ChannelActor, RamChannel, RamChannelIo};
use alloc::vec;
use embassy_time::{Duration, Timer};
use static_cell::make_static;

use onerom_protocol::lab::{Command, LabRomEntry, Response};

use crate::Rom;
use crate::info::LAB_RAM_INFO;

// Buffers used as command channels for Airfrog comms
const RPC_CHANNEL_SIZE_U16: u16 = 512;
const RPC_CHANNEL_SIZE: usize = RPC_CHANNEL_SIZE_U16 as usize;
static mut RPC_CMD_CHANNEL: [u8; RPC_CHANNEL_SIZE] = [0; RPC_CHANNEL_SIZE];
static mut RPC_RSP_CHANNEL: [u8; RPC_CHANNEL_SIZE] = [0; RPC_CHANNEL_SIZE];

// Check every so often for commands
const CONTROL_POLL_INTERVAL: Duration = Duration::from_millis(250);

pub(crate) struct Control {
    rpc_cmd_ch: RamChannel,
    rpc_rsp_ch: RamChannel,
    rom: Rom,
}

impl Control {
    /// Create the Control object.
    pub fn new(rom: Rom) -> Self {
        // Get RPC channel pointers used to control One ROM Lab.  This involves
        // unsafe code, as we have to get a pointer to statically allocated
        // buffers, write them to our info structure (so the host can find
        // them) and pass them to the channel.
        #[allow(static_mut_refs)]
        let (cmd_ptr, rsp_ptr) = unsafe {
            LAB_RAM_INFO.rpc_cmd_channel = &RPC_CMD_CHANNEL as *const _ as *const core::ffi::c_void;
            LAB_RAM_INFO.rpc_rsp_channel = &RPC_RSP_CHANNEL as *const _ as *const core::ffi::c_void;
            LAB_RAM_INFO.rpc_cmd_channel_size = RPC_CHANNEL_SIZE_U16;
            LAB_RAM_INFO.rpc_rsp_channel_size = RPC_CHANNEL_SIZE_U16;

            let rpc_cmd_channel_ptr = &raw mut RPC_CMD_CHANNEL as *mut u8 as u32;
            let rpc_rsp_channel_ptr = &raw mut RPC_RSP_CHANNEL as *mut u8 as u32;
            debug!(
                "RPC Command Channel address:  {rpc_cmd_channel_ptr:#010X} size: {RPC_CHANNEL_SIZE_U16} bytes"
            );
            debug!(
                "RPC Response Channel address: {rpc_rsp_channel_ptr:#010X} size: {RPC_CHANNEL_SIZE_U16} bytes"
            );
            (rpc_cmd_channel_ptr, rpc_rsp_channel_ptr)
        };

        // Two mutably static RamChannel instances.  These store nothing, so
        // are "free".  They are simply wrappers implementing (unsafe) volatile
        // reads and writes to RAM
        let ram_cmd_ch_io = make_static!(RamChannelIo::new());
        let ram_rsp_ch_io = make_static!(RamChannelIo::new());

        // Create the channels
        let rpc_cmd_ch = RamChannel::new(
            ram_cmd_ch_io,
            ChannelActor::Consumer,
            cmd_ptr,
            RPC_CHANNEL_SIZE,
        )
        .expect("Failed to create RPC Command Channel");
        let rpc_rsp_ch = RamChannel::new(
            ram_rsp_ch_io,
            ChannelActor::Producer,
            rsp_ptr,
            RPC_CHANNEL_SIZE,
        )
        .expect("Failed to create RPC Response Channel");

        Self {
            rpc_cmd_ch,
            rpc_rsp_ch,
            rom,
        }
    }

    /// Run the Control handler.  Call from within a task.
    pub async fn run(&mut self) -> ! {
        info!("Control task started");
        loop {
            // Wait for a command.  Target only returns errors if it can't read
            // RAM - so we're OK to expect().
            let data_size = loop {
                if let Some(size) = self
                    .rpc_cmd_ch
                    .data_available()
                    .expect("RPC Channel error getting command size")
                {
                    if size >= Command::size() {
                        break size;
                    } else {
                        warn!("Received under-sized command, ignoring");
                    }
                }
                Timer::after(CONTROL_POLL_INTERVAL).await;
            };

            // Read the command from the channel - this marks the data as
            // "consumed" so the producer can send another command.
            assert!(data_size >= Command::size());
            debug!("Reading command of size {data_size}");
            let mut data = vec![0u8; data_size];
            let received = self
                .rpc_cmd_ch
                .consume_bytes(&mut data)
                .expect("RPC Channel error reading data");
            assert!(received == data_size);
            debug!("Read command bytes: {received}");

            // Convert the command bytes into a Command enum
            let command_u32 = u32::from_le_bytes(data[..Command::size()].try_into().unwrap());
            let command = Command::from(command_u32);
            if command == Command::Unknown {
                warn!("Received unknown command 0x{command_u32:#0910X}, ignoring");
                continue;
            }

            // Handle the command including sending a response
            self.handle_command(command, &data[Command::size()..]).await;
        }
    }

    async fn handle_command(&mut self, command: Command, _data: &[u8]) {
        debug!("Handling command: {command:?}");
        match command {
            Command::Ping => {
                debug!("Ping command received");
                self.send_response_no_data(Response::Pong);
            }
            Command::ReadRom => {
                debug!("ReadRom command received");
                // Read the ROM
                if let Some(rom) = self.rom.read_rom().await {
                    // Found a ROM - build the response from the metadata
                    let rom_metadata: LabRomEntry = rom.into();
                    match rom_metadata.to_buffer() {
                        Ok(buf) => self.send_response_data(&buf),
                        Err(e) => {
                            error!("Failed to build ROM metadata response: {e:?}");
                            self.send_response_no_data(Response::RomNotRecognised);
                        }
                    }
                } else {
                    self.send_response_no_data(Response::NoRom);
                }
                debug!("ReadRom command complete");
            }
            Command::GetRawData => {
                debug!("GetRawData command received");
                // Not implemented
                self.send_response_no_data(Response::Error);
                todo!();
            }
            Command::Unknown => info!("Unknown command received, ignoring"),
        }
    }

    fn send_response_no_data(&mut self, response: Response) {
        let mut buf = [0u8; Response::size()];
        response.to_bytes(&mut buf);
        self.rpc_rsp_ch
            .publish_bytes(&buf)
            .expect("RPC Channel error sending response (no data)");
    }

    fn send_response_data(&mut self, data: &[u8]) {
        self.rpc_rsp_ch
            .publish_bytes(data)
            .expect("RPC Channel error sending response (with data)");
    }
}
