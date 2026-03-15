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
TB_SIMPLE = i2s_to_pcm_tb_simple.v
TB_FULL = i2s_to_pcm_tb.v

# Output
OUT_SIMPLE = i2s_to_pcm_simple
OUT_FULL   = i2s_to_pcm_full

# Waveform output
VCD_SIMPLE = i2s_to_pcm_simple.vcd
VCD_FULL   = i2s_to_pcm_tb.vcd

# Simulation flags
FLAGS   = -Wall -g2012

# =============================================================================
# Targets
# =============================================================================

.PHONY: all simple full clean wave-simple wave-full help

# Default target
all: simple

# Compile and run simple testbench
simple: compile-simple run-simple

# Compile and run full testbench
full: compile-full run-full

# Compile simple testbench
compile-simple:
	@echo "==> Compiling simple testbench..."
	$(VLOGAN) $(FLAGS) -o $(OUT_SIMPLE) $(SRC) $(TB_SIMPLE)

# Run simple testbench
run-simple: compile-simple
	@echo "==> Running simple testbench..."
	$(VVP) $(OUT_SIMPLE)

# Compile full testbench
compile-full:
	@echo "==> Compiling full testbench..."
	$(VLOGAN) $(FLAGS) -o $(OUT_FULL) $(SRC) $(TB_FULL)

# Run full testbench
run-full: compile-full
	@echo "==> Running full testbench..."
	$(VVP) $(OUT_FULL)

# View waveforms - simple
wave-simple:
	@echo "==> Opening waveforms in GTKWave..."
	$(WAVEFORM) $(VCD_SIMPLE)

# View waveforms - full
wave-full:
	@echo "==> Opening waveforms in GTKWave..."
	$(WAVEFORM) $(VCD_FULL)

# Clean build artifacts
clean:
	@echo "==> Cleaning build artifacts..."
	rm -f $(OUT_SIMPLE) $(OUT_FULL)
	rm -f $(VCD_SIMPLE) $(VCD_FULL)
	rm -f *.vcd

# Help
help:
	@echo "I2S to PCM Converter - Simulation Makefile"
	@echo ""
	@echo "Targets:"
	@echo "  make simple      - Compile and run simple testbench (default)"
	@echo "  make full        - Compile and run full testbench"
	@echo "  make wave-simple - Open simple testbench waveforms in GTKWave"
	@echo "  make wave-full   - Open full testbench waveforms in GTKWave"
	@echo "  make clean       - Remove all build artifacts"
	@echo "  make help        - Show this help message"
	@echo ""
	@echo "Quick start:"
	@echo "  make simple      - Run simulation and verify output"
	@echo "  make wave-simple - View waveforms after simulation"
