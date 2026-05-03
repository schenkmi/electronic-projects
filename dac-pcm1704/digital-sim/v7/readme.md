iverilog -o sim tb_i2s_to_pcm.v i2s_to_pcm.v
vvp sim
gtkwave i2s_pcm.vcd

iverilog -o sim tb_verification_i2s_to_pcm.v i2s_to_pcm.v
vvp sim
gtkwave i2s_pcm.vcd