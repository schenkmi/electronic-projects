# Docker

This directory contains Dockerfiles for building One ROM in a consistent environment.

* `Dockerfile.build` - creates `one-rom-build` container for building One ROM.
* `Dockerfile` - creates `one-rom` tooling and firmware, using `one-rom-build` container.

Uses:

* Ubuntu 24.04
* arm-gnu-toolchain-14.3.rel1-x86_64-arm-none
* Latest Rust and probe-rs versions

## Building One ROM

Either build via the [`one-rom` container](#building-one-rom-via-one-rom-container) or use the `one-rom-build` container directly, like this:

```bash
docker run --name one-rom-builder piersfinlayson/one-rom-build:latest sh -c '
git clone https://github.com/piersfinlayson/one-rom.git && \
cd one-rom && \
MCU=f401re HW_REV=24-f CONFIG=config/vic20-pal.mk make test info-detail
'
docker cp one-rom-builder:/home/build/one-rom/sdrr/build/sdrr-stm32f401re.elf /tmp/
docker rm one-rom-builder
```

Change the `MCU=f401re HW_REV=24-f CONFIG=config/vic20-pal.mk` values to the appropriate ones for your firmware.

You can build additional configurations using the same container (i.e. not running `docker rm one-rom-builder`, but running further commands in `one-rom-builder`).  This avoids re-cloning the repo, and also avoids rebuilding all of the Rust tooling, which takes most of the build time.

## Building `one-rom-build` Container

To create the one-rom-build container, from the repo root:

```bash
docker buildx build \
    --platform linux/amd64 \
    --build-arg BUILD_DATE=$(date -u +'%Y-%m-%dT%H:%M:%SZ') \
    --build-arg VERSION=$(git describe --tags --always --dirty 2>/dev/null || echo "dev") \
    --build-arg VCS_REF=$(git rev-parse HEAD 2>/dev/null || echo "unknown") \
    -t piersfinlayson/one-rom-build:latest \
    -f ci/docker/Dockerfile.build .
```

Then tag with the correct version number and push:

```bash
docker tag piersfinlayson/one-rom-build:latest piersfinlayson/one-rom-build:x.y.z
docker push piersfinlayson/one-rom-build:latest
docker push piersfinlayson/one-rom-build:x.y.z
```

## Building One ROM via `one-rom` Container

To build One ROM, create the one-rom container, from the repo root:

```bash
docker build \
    -f ci/docker/Dockerfile \
    -t piersfinlayson/one-rom:latest .
```

To use non-default build configuration, pass in build arguments.  For example:

```bash
docker build \
    --build-arg MCU=f401re \
    --build-arg CONFIG=vic20-pal.mk \
    --build-arg HW_REV=24-f \
    -f ci/docker/Dockerfile \
    -t piersfinlayson/sdrr-f401re-24-f-vic20-pal:latest .
```
