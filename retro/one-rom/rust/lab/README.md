# One ROM Lab

One ROM Lab firmware reads ROM images from external ROM chips (originals, One ROMs, and other replacements), by using the One ROM hardware with female socket placed on top of the ROM socket pins.  It can also be used to instrument the performance of these external ROM chips, by using additional equipment, such as logic analyzers or oscilloscopes.

<div class="video-container">
    <iframe 
        width="560" 
        height="315" 
        src="https://www.youtube.com/embed/9QBlPToP_BQ" 
        frameborder="0" 
        allow="accelerometer; autoplay; encrypted-media; gyroscope; picture-in-picture" 
        allowfullscreen>
    </iframe>
</div>

You need female headers on the top of your One ROM PCB in order to use the Lab firmware. 

One ROM Lab currently only support STM32F4 based One ROMs - a RP2350 is viable, with the appropriate changes to support `embassy-rp`.

## Modes

There are three modes of operation:
- **Control** - **default** - is controlled via an external device using SWD.  When paired with `Airfrog` this allows the user to manually trigger ROM Reads using Airfrog's web UI.
- **One-shot** - reads a ROM image once at startup and then stops.  This is useful for automated testing, or for use in environments where SWD is not available.  In this mode, ROM information is output via RTT.
- **Continuous** - continuously reads a ROM image in a loop, with a brief pause between reads.

These three modes are mutually exclusive, and are selected at [build](#building) time using Cargo features.

## Building

There are different features to support:
- Different STM32F4 variants
- Different [modes](#modes)

Supported STM32F4 variants:
- `f401re`
- `f405rg` - **default**
- `f411re`
- `f446re`

Modes:
- `control` - **default** - controlled via SWD (e.g. Airfrog UI)
- `oneshot` - reads a ROM image once at startup and then stops
- `repeat` - continuously reads an attached ROM image in a loop

Example build commands:

```bash
cargo build --release --no-default-features --features f405rg,control
cargo build --release --no-default-features --features f411re,oneshot
cargo build --release --no-default-features --features f446re,repeat
```

## Flashing

If using `probe-rs` use `cargo run` instead of `cargo build` to automatically flash the firmware after building:

```bash
cargo build --release --no-default-features --features f405rg,control
cargo build --release --no-default-features --features f411re,oneshot
cargo build --release --no-default-features --features f446re,repeat
```
