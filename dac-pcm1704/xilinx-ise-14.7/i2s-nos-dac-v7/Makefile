# =============================================================================
# Makefile for I2S to PCM Converter Simulation
# =============================================================================
# Prerequisites:
#   - Icarus Verilog (iverilog) for compilation
#   - vvp for simulation execution
#   - GTKWave for waveform viewing
#
# Install on macOS:   brew install icarus-verilog gtkwave
# Install on Ubuntu:  sudo apt-get install iverilog gtkwave
# =============================================================================

# Simulator
VLOGAN  = iverilog
VVP     = vvp
WAVEFORM = gtkwave

# Source files
SRC     = i2s_to_pcm.v
TB_FULL = i2s_to_pcm_tb.v

# Output
OUT_FULL   = i2s_to_pcm_full

# Waveform output
VCD_FULL   = i2s_to_pcm_tb.vcd

# Simulation flags
FLAGS   = -Wall -g2012

# =============================================================================
# Targets
# =============================================================================

.PHONY: all simple full clean wave-simple wave-full help

# Default target
all: full

# Compile and run full testbench
full: compile-full run-full

# Compile full testbench
compile-full:
	@echo "==> Compiling full testbench..."
	$(VLOGAN) $(FLAGS) -o $(OUT_FULL) $(SRC) $(TB_FULL)

# Run full testbench
run-full: compile-full
	@echo "==> Running full testbench..."
	$(VVP) $(OUT_FULL)

# View waveforms - full
wave-full:
	@echo "==> Opening waveforms in GTKWave..."
	$(WAVEFORM) $(VCD_FULL)

# Clean build artifacts
clean:
	@echo "==> Cleaning build artifacts..."
	rm -f $(OUT_FULL)
	rm -f $(VCD_FULL)
	rm -f *.vcd

# Help
help:
	@echo "I2S to PCM Converter - Simulation Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  make full        - Compile and run full testbench"
	@echo "  make wave-full   - Open full testbench waveforms in GTKWave"
	@echo "  make clean       - Remove all build artifacts"
	@echo "  make help        - Show this help message"
	@echo ""
	@echo "Quick start:"
	@echo "  make full        - Run simulation and verify output"
	@echo "  make wave-full   - View waveforms after simulation"
