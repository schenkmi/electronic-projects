FROM piersfinlayson/one-rom-build:latest

# Metadata
LABEL org.opencontainers.image.title="One ROM"
LABEL org.opencontainers.image.description="One ROM firmware and tooling container"
LABEL org.opencontainers.image.authors="Piers Finlayson <piers@piers.rocks>"
LABEL org.opencontainers.image.url="https://piers.rocks"
LABEL org.opencontainers.image.source="https://github.com/piersfinlayson/one-rom"
LABEL org.opencontainers.image.licenses="MIT"
LABEL org.opencontainers.image.vendor="piers.rocks"

# One ROM build args
ARG CONFIG
ARG MCU
ARG HW_REV
ARG ROM_CONFIGS
ARG SWD
ARG BOOT_LOGGING
ARG MAIN_LOOP_LOGGING
ARG MAIN_LOOP_ONE_SHOT
ARG DEBUG_LOGGING
ARG MCO
ARG MCO2
ARG OSC
ARG FREQ
ARG OVERCLOCK
ARG STATUS_LED
ARG BOOTLOADER
ARG DISABLE_PRELOAD_TO_RAM
ARG SERVE_ALG
ARG GEN_OUTPUT_DIR
ARG CARGO_PROFILE
ARG EXTRA_C_FLAGS
ARG COUNT_ROM_ACCESS

# Clone the repository
RUN git clone https://github.com/piersfinlayson/one-rom.git
COPY config/docker/ /home/build/one-rom/config/docker/

# Build One ROM
WORKDIR /home/build/one-rom
WORKDIR /home/build/one-rom
RUN env \
    ${CONFIG:+CONFIG=$CONFIG} \
    ${MCU:+MCU=$MCU} \
    ${HW_REV:+HW_REV=$HW_REV} \
    ${ROM_CONFIGS:+ROM_CONFIGS="$ROM_CONFIGS"} \
    ${SWD:+SWD=$SWD} \
    ${BOOT_LOGGING:+BOOT_LOGGING=$BOOT_LOGGING} \
    ${MAIN_LOOP_LOGGING:+MAIN_LOOP_LOGGING=$MAIN_LOOP_LOGGING} \
    ${MAIN_LOOP_ONE_SHOT:+MAIN_LOOP_ONE_SHOT=$MAIN_LOOP_ONE_SHOT} \
    ${DEBUG_LOGGING:+DEBUG_LOGGING=$DEBUG_LOGGING} \
    ${MCO:+MCO=$MCO} \
    ${MCO2:+MCO2=$MCO2} \
    ${OSC:+OSC=$OSC} \
    ${FREQ:+FREQ=$FREQ} \
    ${OVERCLOCK:+OVERCLOCK=$OVERCLOCK} \
    ${STATUS_LED:+STATUS_LED=$STATUS_LED} \
    ${BOOTLOADER:+BOOTLOADER=$BOOTLOADER} \
    ${DISABLE_PRELOAD_TO_RAM:+DISABLE_PRELOAD_TO_RAM=$DISABLE_PRELOAD_TO_RAM} \
    ${SERVE_ALG:+SERVE_ALG=$SERVE_ALG} \
    ${GEN_OUTPUT_DIR:+GEN_OUTPUT_DIR=$GEN_OUTPUT_DIR} \
    ${CARGO_PROFILE:+CARGO_PROFILE=$CARGO_PROFILE} \
    ${EXTRA_C_FLAGS:+EXTRA_C_FLAGS=$EXTRA_C_FLAGS} \
    ${COUNT_ROM_ACCESS:+COUNT_ROM_ACCESS=$COUNT_ROM_ACCESS} \
    make test info-detail

# Copy build artifacts to output directory
RUN cp -r sdrr/build /home/build/output/

# Output detailed firmware information
RUN ELF_FILE=$(basename $(find sdrr/build -name "sdrr-stm32*.elf" -type f)) && \
    /home/build/one-rom/rust/target/release/one-rom-info info -d /home/build/output/build/$ELF_FILE >> /home/build/output/one-rom-info.txt

# Default to staying in the project directory
WORKDIR /home/build/one-rom
VOLUME ["/home/build/output"]
