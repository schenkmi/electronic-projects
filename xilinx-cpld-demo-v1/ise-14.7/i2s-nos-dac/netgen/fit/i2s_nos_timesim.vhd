--------------------------------------------------------------------------------
-- Copyright (c) 1995-2013 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____
--  /   /\/   /
-- /___/  \  /    Vendor: Xilinx
-- \   \   \/     Version: P.20131013
--  \   \         Application: netgen
--  /   /         Filename: i2s_nos_timesim.vhd
-- /___/   /\     Timestamp: Mon Apr 19 18:10:51 2021
-- \   \  /  \ 
--  \___\/\___\
--             
-- Command	: -intstyle ise -rpw 100 -ar Structure -tm i2s_nos -w -dir netgen/fit -ofmt vhdl -sim i2s_nos.nga i2s_nos_timesim.vhd 
-- Device	: XC2C64A-5-VQ44 (Speed File: Version 14.0 Advance Product Specification)
-- Input file	: i2s_nos.nga
-- Output file	: C:\Users\schenk\Documents\GitHub\electronic-projects\xilinx-cpld-demo-v1\ise-14.7\i2s-nos-dac\netgen\fit\i2s_nos_timesim.vhd
-- # of Entities	: 1
-- Design Name	: i2s_nos.nga
-- Xilinx	: C:\Xilinx\14.7\ISE_DS\ISE\
--             
-- Purpose:    
--     This VHDL netlist is a verification model and uses simulation 
--     primitives which may not represent the true implementation of the 
--     device, however the netlist is functionally correct and should not 
--     be modified. This file cannot be synthesized and should only be used 
--     with supported simulation tools.
--             
-- Reference:  
--     Command Line Tools User Guide, Chapter 23
--     Synthesis and Simulation Design Guide, Chapter 6
--             
--------------------------------------------------------------------------------

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
library SIMPRIM;
use SIMPRIM.VCOMPONENTS.ALL;
use SIMPRIM.VPACKAGE.ALL;

entity i2s_nos is
  port (
    BCK : in STD_LOGIC := 'X'; 
    LRCK : in STD_LOGIC := 'X'; 
    DATAIN : in STD_LOGIC := 'X'; 
    CLKOUTL : out STD_LOGIC; 
    CLKOUTR : out STD_LOGIC; 
    DATAOUTL : out STD_LOGIC; 
    DATAOUTR : out STD_LOGIC; 
    LEOUTL : out STD_LOGIC; 
    LEOUTR : out STD_LOGIC 
  );
end i2s_nos;

architecture Structure of i2s_nos is
  signal BCK_II_UIM_1 : STD_LOGIC; 
  signal BCK_II_FCLK_2 : STD_LOGIC; 
  signal LRCK_II_UIM_4 : STD_LOGIC; 
  signal DATAIN_II_IREG_6 : STD_LOGIC; 
  signal Gnd_7 : STD_LOGIC; 
  signal Vcc_8 : STD_LOGIC; 
  signal CLKOUTL_MC_Q_11 : STD_LOGIC; 
  signal CLKOUTR_MC_Q_13 : STD_LOGIC; 
  signal DATAOUTL_MC_Q_15 : STD_LOGIC; 
  signal DATAOUTR_MC_Q_17 : STD_LOGIC; 
  signal LEOUTL_MC_Q_19 : STD_LOGIC; 
  signal LEOUTR_MC_Q_21 : STD_LOGIC; 
  signal CLKOUTL_MC_Q_tsimrenamed_net_Q_22 : STD_LOGIC; 
  signal CLKOUTL_MC_D_23 : STD_LOGIC; 
  signal CLKOUTL_MC_D1_24 : STD_LOGIC; 
  signal CLKOUTL_MC_D2_25 : STD_LOGIC; 
  signal CLKOUTR_MC_Q_tsimrenamed_net_Q_26 : STD_LOGIC; 
  signal CLKOUTR_MC_D_27 : STD_LOGIC; 
  signal CLKOUTR_MC_D1_28 : STD_LOGIC; 
  signal CLKOUTR_MC_D2_29 : STD_LOGIC; 
  signal DATAOUTL_MC_Q_tsimrenamed_net_Q : STD_LOGIC; 
  signal DATAOUTL_MC_D_31 : STD_LOGIC; 
  signal DATAOUTL_MC_D1_32 : STD_LOGIC; 
  signal DATAOUTL_MC_D2_33 : STD_LOGIC; 
  signal sr_left_30_MC_Q : STD_LOGIC; 
  signal sr_left_30_MC_D_36 : STD_LOGIC; 
  signal sr_left_30_MC_D1_37 : STD_LOGIC; 
  signal sr_left_30_MC_D2_38 : STD_LOGIC; 
  signal sr_left_29_MC_Q : STD_LOGIC; 
  signal sr_left_29_MC_D_41 : STD_LOGIC; 
  signal sr_left_29_MC_D1_42 : STD_LOGIC; 
  signal sr_left_29_MC_D2_43 : STD_LOGIC; 
  signal sr_left_28_MC_Q : STD_LOGIC; 
  signal sr_left_28_MC_D_46 : STD_LOGIC; 
  signal sr_left_28_MC_D1_47 : STD_LOGIC; 
  signal sr_left_28_MC_D2_48 : STD_LOGIC; 
  signal sr_left_27_MC_Q : STD_LOGIC; 
  signal sr_left_27_MC_D_51 : STD_LOGIC; 
  signal sr_left_27_MC_D1_52 : STD_LOGIC; 
  signal sr_left_27_MC_D2_53 : STD_LOGIC; 
  signal sr_left_26_MC_Q : STD_LOGIC; 
  signal sr_left_26_MC_D_56 : STD_LOGIC; 
  signal sr_left_26_MC_D1_57 : STD_LOGIC; 
  signal sr_left_26_MC_D2_58 : STD_LOGIC; 
  signal sr_left_25_MC_Q : STD_LOGIC; 
  signal sr_left_25_MC_D_61 : STD_LOGIC; 
  signal sr_left_25_MC_D1_62 : STD_LOGIC; 
  signal sr_left_25_MC_D2_63 : STD_LOGIC; 
  signal sr_left_24_MC_Q : STD_LOGIC; 
  signal sr_left_24_MC_D_66 : STD_LOGIC; 
  signal sr_left_24_MC_D1_67 : STD_LOGIC; 
  signal sr_left_24_MC_D2_68 : STD_LOGIC; 
  signal sr_left_23_MC_Q : STD_LOGIC; 
  signal sr_left_23_MC_D_71 : STD_LOGIC; 
  signal sr_left_23_MC_D1_72 : STD_LOGIC; 
  signal sr_left_23_MC_D2_73 : STD_LOGIC; 
  signal sr_left_22_MC_Q : STD_LOGIC; 
  signal sr_left_22_MC_D_76 : STD_LOGIC; 
  signal sr_left_22_MC_D1_77 : STD_LOGIC; 
  signal sr_left_22_MC_D2_78 : STD_LOGIC; 
  signal sr_left_21_MC_Q : STD_LOGIC; 
  signal sr_left_21_MC_D_81 : STD_LOGIC; 
  signal sr_left_21_MC_D1_82 : STD_LOGIC; 
  signal sr_left_21_MC_D2_83 : STD_LOGIC; 
  signal sr_left_20_MC_Q : STD_LOGIC; 
  signal sr_left_20_MC_D_86 : STD_LOGIC; 
  signal sr_left_20_MC_D1_87 : STD_LOGIC; 
  signal sr_left_20_MC_D2_88 : STD_LOGIC; 
  signal sr_left_19_MC_Q : STD_LOGIC; 
  signal sr_left_19_MC_D_91 : STD_LOGIC; 
  signal sr_left_19_MC_D1_92 : STD_LOGIC; 
  signal sr_left_19_MC_D2_93 : STD_LOGIC; 
  signal sr_left_18_MC_Q : STD_LOGIC; 
  signal sr_left_18_MC_D_96 : STD_LOGIC; 
  signal sr_left_18_MC_D1_97 : STD_LOGIC; 
  signal sr_left_18_MC_D2_98 : STD_LOGIC; 
  signal sr_left_17_MC_Q : STD_LOGIC; 
  signal sr_left_17_MC_D_101 : STD_LOGIC; 
  signal sr_left_17_MC_D1_102 : STD_LOGIC; 
  signal sr_left_17_MC_D2_103 : STD_LOGIC; 
  signal sr_left_16_MC_Q : STD_LOGIC; 
  signal sr_left_16_MC_D_106 : STD_LOGIC; 
  signal sr_left_16_MC_D1_107 : STD_LOGIC; 
  signal sr_left_16_MC_D2_108 : STD_LOGIC; 
  signal sr_left_15_MC_Q : STD_LOGIC; 
  signal sr_left_15_MC_D_111 : STD_LOGIC; 
  signal sr_left_15_MC_D1_112 : STD_LOGIC; 
  signal sr_left_15_MC_D2_113 : STD_LOGIC; 
  signal sr_left_14_MC_Q : STD_LOGIC; 
  signal sr_left_14_MC_D_116 : STD_LOGIC; 
  signal sr_left_14_MC_D1_117 : STD_LOGIC; 
  signal sr_left_14_MC_D2_118 : STD_LOGIC; 
  signal sr_left_13_MC_Q : STD_LOGIC; 
  signal sr_left_13_MC_D_121 : STD_LOGIC; 
  signal sr_left_13_MC_D1_122 : STD_LOGIC; 
  signal sr_left_13_MC_D2_123 : STD_LOGIC; 
  signal sr_left_12_MC_Q : STD_LOGIC; 
  signal sr_left_12_MC_D_126 : STD_LOGIC; 
  signal sr_left_12_MC_D1_127 : STD_LOGIC; 
  signal sr_left_12_MC_D2_128 : STD_LOGIC; 
  signal sr_left_11_MC_Q : STD_LOGIC; 
  signal sr_left_11_MC_D_131 : STD_LOGIC; 
  signal sr_left_11_MC_D1_132 : STD_LOGIC; 
  signal sr_left_11_MC_D2_133 : STD_LOGIC; 
  signal sr_left_10_MC_Q : STD_LOGIC; 
  signal sr_left_10_MC_D_136 : STD_LOGIC; 
  signal sr_left_10_MC_D1_137 : STD_LOGIC; 
  signal sr_left_10_MC_D2_138 : STD_LOGIC; 
  signal sr_left_9_MC_Q : STD_LOGIC; 
  signal sr_left_9_MC_D_141 : STD_LOGIC; 
  signal sr_left_9_MC_D1_142 : STD_LOGIC; 
  signal sr_left_9_MC_D2_143 : STD_LOGIC; 
  signal sr_left_8_MC_Q : STD_LOGIC; 
  signal sr_left_8_MC_D_146 : STD_LOGIC; 
  signal sr_left_8_MC_D1_147 : STD_LOGIC; 
  signal sr_left_8_MC_D2_148 : STD_LOGIC; 
  signal sr_left_7_MC_Q : STD_LOGIC; 
  signal sr_left_7_MC_D_151 : STD_LOGIC; 
  signal sr_left_7_MC_D1_152 : STD_LOGIC; 
  signal sr_left_7_MC_D2_153 : STD_LOGIC; 
  signal sr_left_6_MC_Q : STD_LOGIC; 
  signal sr_left_6_MC_D_156 : STD_LOGIC; 
  signal sr_left_6_MC_D1_157 : STD_LOGIC; 
  signal sr_left_6_MC_D2_158 : STD_LOGIC; 
  signal sr_left_5_MC_Q : STD_LOGIC; 
  signal sr_left_5_MC_D_161 : STD_LOGIC; 
  signal sr_left_5_MC_D1_162 : STD_LOGIC; 
  signal sr_left_5_MC_D2_163 : STD_LOGIC; 
  signal sr_left_4_MC_Q : STD_LOGIC; 
  signal sr_left_4_MC_D_166 : STD_LOGIC; 
  signal sr_left_4_MC_D1_167 : STD_LOGIC; 
  signal sr_left_4_MC_D2_168 : STD_LOGIC; 
  signal sr_left_3_MC_Q : STD_LOGIC; 
  signal sr_left_3_MC_D_171 : STD_LOGIC; 
  signal sr_left_3_MC_D1_172 : STD_LOGIC; 
  signal sr_left_3_MC_D2_173 : STD_LOGIC; 
  signal sr_left_2_MC_Q : STD_LOGIC; 
  signal sr_left_2_MC_D_176 : STD_LOGIC; 
  signal sr_left_2_MC_D1_177 : STD_LOGIC; 
  signal sr_left_2_MC_D2_178 : STD_LOGIC; 
  signal sr_left_1_MC_Q : STD_LOGIC; 
  signal sr_left_1_MC_D_181 : STD_LOGIC; 
  signal sr_left_1_MC_D1_182 : STD_LOGIC; 
  signal sr_left_1_MC_D2_183 : STD_LOGIC; 
  signal sr_left_0_MC_Q : STD_LOGIC; 
  signal sr_left_0_MC_D_186 : STD_LOGIC; 
  signal sr_left_0_MC_D1_187 : STD_LOGIC; 
  signal sr_left_0_MC_D2_188 : STD_LOGIC; 
  signal DATAOUTR_MC_UIM_189 : STD_LOGIC; 
  signal DATAOUTR_MC_Q_tsimrenamed_net_Q : STD_LOGIC; 
  signal DATAOUTR_MC_D_191 : STD_LOGIC; 
  signal DATAOUTR_MC_D1_192 : STD_LOGIC; 
  signal DATAOUTR_MC_D2_193 : STD_LOGIC; 
  signal sr_right_10_MC_Q : STD_LOGIC; 
  signal sr_right_10_MC_D_196 : STD_LOGIC; 
  signal sr_right_10_MC_D1_197 : STD_LOGIC; 
  signal sr_right_10_MC_D2_198 : STD_LOGIC; 
  signal sr_right_9_MC_Q : STD_LOGIC; 
  signal sr_right_9_MC_D_201 : STD_LOGIC; 
  signal sr_right_9_MC_D1_202 : STD_LOGIC; 
  signal sr_right_9_MC_D2_203 : STD_LOGIC; 
  signal sr_right_8_MC_Q : STD_LOGIC; 
  signal sr_right_8_MC_D_206 : STD_LOGIC; 
  signal sr_right_8_MC_D1_207 : STD_LOGIC; 
  signal sr_right_8_MC_D2_208 : STD_LOGIC; 
  signal sr_right_7_MC_Q : STD_LOGIC; 
  signal sr_right_7_MC_D_211 : STD_LOGIC; 
  signal sr_right_7_MC_D1_212 : STD_LOGIC; 
  signal sr_right_7_MC_D2_213 : STD_LOGIC; 
  signal sr_right_6_MC_Q : STD_LOGIC; 
  signal sr_right_6_MC_D_216 : STD_LOGIC; 
  signal sr_right_6_MC_D1_217 : STD_LOGIC; 
  signal sr_right_6_MC_D2_218 : STD_LOGIC; 
  signal sr_right_5_MC_Q : STD_LOGIC; 
  signal sr_right_5_MC_D_221 : STD_LOGIC; 
  signal sr_right_5_MC_D1_222 : STD_LOGIC; 
  signal sr_right_5_MC_D2_223 : STD_LOGIC; 
  signal sr_right_4_MC_Q : STD_LOGIC; 
  signal sr_right_4_MC_D_226 : STD_LOGIC; 
  signal sr_right_4_MC_D1_227 : STD_LOGIC; 
  signal sr_right_4_MC_D2_228 : STD_LOGIC; 
  signal sr_right_3_MC_Q : STD_LOGIC; 
  signal sr_right_3_MC_D_231 : STD_LOGIC; 
  signal sr_right_3_MC_D1_232 : STD_LOGIC; 
  signal sr_right_3_MC_D2_233 : STD_LOGIC; 
  signal sr_right_2_MC_Q : STD_LOGIC; 
  signal sr_right_2_MC_D_236 : STD_LOGIC; 
  signal sr_right_2_MC_D1_237 : STD_LOGIC; 
  signal sr_right_2_MC_D2_238 : STD_LOGIC; 
  signal sr_right_1_MC_Q : STD_LOGIC; 
  signal sr_right_1_MC_D_241 : STD_LOGIC; 
  signal sr_right_1_MC_D1_242 : STD_LOGIC; 
  signal sr_right_1_MC_D2_243 : STD_LOGIC; 
  signal LEOUTL_MC_Q_tsimrenamed_net_Q_244 : STD_LOGIC; 
  signal LEOUTL_MC_D_245 : STD_LOGIC; 
  signal LEOUTL_MC_D1_246 : STD_LOGIC; 
  signal LEOUTL_MC_D2_247 : STD_LOGIC; 
  signal LEOUTR_MC_Q_tsimrenamed_net_Q_248 : STD_LOGIC; 
  signal LEOUTR_MC_D_249 : STD_LOGIC; 
  signal LEOUTR_MC_D1_250 : STD_LOGIC; 
  signal LEOUTR_MC_D2_251 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_0_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_0_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTL_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTL_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTL_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTL_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTR_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTR_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTR_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_CLKOUTR_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTL_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTL_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTL_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTL_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTL_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTL_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_30_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_30_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_30_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_30_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_30_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_30_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_29_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_29_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_29_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_29_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_29_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_29_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_28_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_28_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_28_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_28_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_28_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_28_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_27_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_27_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_27_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_27_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_27_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_27_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_26_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_26_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_26_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_26_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_26_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_26_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_25_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_25_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_25_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_25_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_25_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_25_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_24_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_24_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_24_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_24_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_24_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_24_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_23_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_23_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_23_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_23_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_23_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_23_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_22_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_22_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_22_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_22_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_22_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_22_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_21_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_21_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_21_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_21_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_21_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_21_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_20_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_20_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_20_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_20_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_20_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_20_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_19_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_19_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_19_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_19_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_19_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_19_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_18_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_18_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_18_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_18_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_18_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_18_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_17_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_17_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_17_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_17_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_17_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_17_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_16_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_16_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_16_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_16_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_16_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_16_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_15_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_15_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_15_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_15_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_15_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_15_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_14_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_14_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_14_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_14_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_14_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_14_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_13_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_13_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_13_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_13_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_13_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_13_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_12_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_12_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_12_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_12_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_12_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_12_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_11_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_11_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_11_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_11_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_11_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_11_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_10_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_10_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_10_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_10_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_10_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_10_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_9_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_9_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_9_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_9_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_9_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_9_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_8_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_8_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_8_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_8_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_8_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_8_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_7_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_7_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_7_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_7_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_7_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_7_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_6_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_6_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_6_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_6_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_6_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_6_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_5_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_5_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_5_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_5_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_5_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_5_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_4_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_4_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_4_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_4_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_4_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_4_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_3_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_3_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_3_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_3_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_3_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_3_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_2_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_2_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_2_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_2_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_2_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_2_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_1_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_1_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_1_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_1_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_1_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_1_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_0_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_0_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_0_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_0_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_0_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_left_0_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTR_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTR_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTR_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTR_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTR_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_DATAOUTR_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_10_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_10_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_10_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_10_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_10_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_10_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_9_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_9_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_9_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_9_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_9_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_9_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_8_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_8_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_8_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_8_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_8_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_8_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_7_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_7_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_7_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_7_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_7_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_7_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_6_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_6_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_6_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_6_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_6_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_6_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_5_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_5_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_5_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_5_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_5_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_5_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_4_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_4_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_4_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_4_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_4_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_4_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_3_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_3_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_3_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_3_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_3_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_3_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_2_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_2_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_2_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_2_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_2_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_2_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_1_MC_REG_IN : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_1_MC_REG_CLK : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_1_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_1_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_1_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_sr_right_1_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTL_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTL_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTL_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTL_MC_D1_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTR_MC_D_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTR_MC_D_IN1 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTR_MC_D1_IN0 : STD_LOGIC; 
  signal NlwBufferSignal_LEOUTR_MC_D1_IN1 : STD_LOGIC; 
  signal sr_right : STD_LOGIC_VECTOR ( 10 downto 0 ); 
  signal sr_left : STD_LOGIC_VECTOR ( 30 downto 0 ); 
begin
  BCK_II_UIM : X_BUF
    port map (
      I => BCK,
      O => BCK_II_UIM_1
    );
  BCK_II_FCLK : X_BUF
    port map (
      I => BCK,
      O => BCK_II_FCLK_2
    );
  LRCK_II_UIM : X_BUF
    port map (
      I => LRCK,
      O => LRCK_II_UIM_4
    );
  DATAIN_II_IREG : X_BUF
    port map (
      I => DATAIN,
      O => DATAIN_II_IREG_6
    );
  sr_right_0_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_0_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_0_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right(0)
    );
  Gnd : X_ZERO
    port map (
      O => Gnd_7
    );
  Vcc : X_ONE
    port map (
      O => Vcc_8
    );
  CLKOUTL_12 : X_BUF
    port map (
      I => CLKOUTL_MC_Q_11,
      O => CLKOUTL
    );
  CLKOUTR_14 : X_BUF
    port map (
      I => CLKOUTR_MC_Q_13,
      O => CLKOUTR
    );
  DATAOUTL_16 : X_BUF
    port map (
      I => DATAOUTL_MC_Q_15,
      O => DATAOUTL
    );
  DATAOUTR_18 : X_BUF
    port map (
      I => DATAOUTR_MC_Q_17,
      O => DATAOUTR
    );
  LEOUTL_20 : X_BUF
    port map (
      I => LEOUTL_MC_Q_19,
      O => LEOUTL
    );
  LEOUTR_22 : X_BUF
    port map (
      I => LEOUTR_MC_Q_21,
      O => LEOUTR
    );
  CLKOUTL_MC_Q : X_BUF
    port map (
      I => CLKOUTL_MC_Q_tsimrenamed_net_Q_22,
      O => CLKOUTL_MC_Q_11
    );
  CLKOUTL_MC_Q_tsimrenamed_net_Q : X_BUF
    port map (
      I => CLKOUTL_MC_D_23,
      O => CLKOUTL_MC_Q_tsimrenamed_net_Q_22
    );
  CLKOUTL_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_CLKOUTL_MC_D_IN0,
      I1 => NlwBufferSignal_CLKOUTL_MC_D_IN1,
      O => CLKOUTL_MC_D_23
    );
  CLKOUTL_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_CLKOUTL_MC_D1_IN0,
      I1 => NlwBufferSignal_CLKOUTL_MC_D1_IN1,
      O => CLKOUTL_MC_D1_24
    );
  CLKOUTL_MC_D2 : X_ZERO
    port map (
      O => CLKOUTL_MC_D2_25
    );
  CLKOUTR_MC_Q : X_BUF
    port map (
      I => CLKOUTR_MC_Q_tsimrenamed_net_Q_26,
      O => CLKOUTR_MC_Q_13
    );
  CLKOUTR_MC_Q_tsimrenamed_net_Q : X_BUF
    port map (
      I => CLKOUTR_MC_D_27,
      O => CLKOUTR_MC_Q_tsimrenamed_net_Q_26
    );
  CLKOUTR_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_CLKOUTR_MC_D_IN0,
      I1 => NlwBufferSignal_CLKOUTR_MC_D_IN1,
      O => CLKOUTR_MC_D_27
    );
  CLKOUTR_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_CLKOUTR_MC_D1_IN0,
      I1 => NlwBufferSignal_CLKOUTR_MC_D1_IN1,
      O => CLKOUTR_MC_D1_28
    );
  CLKOUTR_MC_D2 : X_ZERO
    port map (
      O => CLKOUTR_MC_D2_29
    );
  DATAOUTL_MC_Q : X_BUF
    port map (
      I => DATAOUTL_MC_Q_tsimrenamed_net_Q,
      O => DATAOUTL_MC_Q_15
    );
  DATAOUTL_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_DATAOUTL_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_DATAOUTL_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => DATAOUTL_MC_Q_tsimrenamed_net_Q
    );
  DATAOUTL_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_DATAOUTL_MC_D_IN0,
      I1 => NlwBufferSignal_DATAOUTL_MC_D_IN1,
      O => DATAOUTL_MC_D_31
    );
  DATAOUTL_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_DATAOUTL_MC_D1_IN0,
      I1 => NlwBufferSignal_DATAOUTL_MC_D1_IN1,
      O => DATAOUTL_MC_D1_32
    );
  DATAOUTL_MC_D2 : X_ZERO
    port map (
      O => DATAOUTL_MC_D2_33
    );
  sr_left_30_Q : X_BUF
    port map (
      I => sr_left_30_MC_Q,
      O => sr_left(30)
    );
  sr_left_30_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_30_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_30_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_30_MC_Q
    );
  sr_left_30_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_30_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_30_MC_D_IN1,
      O => sr_left_30_MC_D_36
    );
  sr_left_30_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_30_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_30_MC_D1_IN1,
      O => sr_left_30_MC_D1_37
    );
  sr_left_30_MC_D2 : X_ZERO
    port map (
      O => sr_left_30_MC_D2_38
    );
  sr_left_29_Q : X_BUF
    port map (
      I => sr_left_29_MC_Q,
      O => sr_left(29)
    );
  sr_left_29_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_29_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_29_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_29_MC_Q
    );
  sr_left_29_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_29_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_29_MC_D_IN1,
      O => sr_left_29_MC_D_41
    );
  sr_left_29_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_29_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_29_MC_D1_IN1,
      O => sr_left_29_MC_D1_42
    );
  sr_left_29_MC_D2 : X_ZERO
    port map (
      O => sr_left_29_MC_D2_43
    );
  sr_left_28_Q : X_BUF
    port map (
      I => sr_left_28_MC_Q,
      O => sr_left(28)
    );
  sr_left_28_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_28_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_28_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_28_MC_Q
    );
  sr_left_28_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_28_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_28_MC_D_IN1,
      O => sr_left_28_MC_D_46
    );
  sr_left_28_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_28_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_28_MC_D1_IN1,
      O => sr_left_28_MC_D1_47
    );
  sr_left_28_MC_D2 : X_ZERO
    port map (
      O => sr_left_28_MC_D2_48
    );
  sr_left_27_Q : X_BUF
    port map (
      I => sr_left_27_MC_Q,
      O => sr_left(27)
    );
  sr_left_27_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_27_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_27_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_27_MC_Q
    );
  sr_left_27_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_27_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_27_MC_D_IN1,
      O => sr_left_27_MC_D_51
    );
  sr_left_27_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_27_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_27_MC_D1_IN1,
      O => sr_left_27_MC_D1_52
    );
  sr_left_27_MC_D2 : X_ZERO
    port map (
      O => sr_left_27_MC_D2_53
    );
  sr_left_26_Q : X_BUF
    port map (
      I => sr_left_26_MC_Q,
      O => sr_left(26)
    );
  sr_left_26_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_26_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_26_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_26_MC_Q
    );
  sr_left_26_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_26_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_26_MC_D_IN1,
      O => sr_left_26_MC_D_56
    );
  sr_left_26_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_26_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_26_MC_D1_IN1,
      O => sr_left_26_MC_D1_57
    );
  sr_left_26_MC_D2 : X_ZERO
    port map (
      O => sr_left_26_MC_D2_58
    );
  sr_left_25_Q : X_BUF
    port map (
      I => sr_left_25_MC_Q,
      O => sr_left(25)
    );
  sr_left_25_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_25_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_25_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_25_MC_Q
    );
  sr_left_25_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_25_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_25_MC_D_IN1,
      O => sr_left_25_MC_D_61
    );
  sr_left_25_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_25_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_25_MC_D1_IN1,
      O => sr_left_25_MC_D1_62
    );
  sr_left_25_MC_D2 : X_ZERO
    port map (
      O => sr_left_25_MC_D2_63
    );
  sr_left_24_Q : X_BUF
    port map (
      I => sr_left_24_MC_Q,
      O => sr_left(24)
    );
  sr_left_24_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_24_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_24_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_24_MC_Q
    );
  sr_left_24_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_24_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_24_MC_D_IN1,
      O => sr_left_24_MC_D_66
    );
  sr_left_24_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_24_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_24_MC_D1_IN1,
      O => sr_left_24_MC_D1_67
    );
  sr_left_24_MC_D2 : X_ZERO
    port map (
      O => sr_left_24_MC_D2_68
    );
  sr_left_23_Q : X_BUF
    port map (
      I => sr_left_23_MC_Q,
      O => sr_left(23)
    );
  sr_left_23_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_23_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_23_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_23_MC_Q
    );
  sr_left_23_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_23_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_23_MC_D_IN1,
      O => sr_left_23_MC_D_71
    );
  sr_left_23_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_23_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_23_MC_D1_IN1,
      O => sr_left_23_MC_D1_72
    );
  sr_left_23_MC_D2 : X_ZERO
    port map (
      O => sr_left_23_MC_D2_73
    );
  sr_left_22_Q : X_BUF
    port map (
      I => sr_left_22_MC_Q,
      O => sr_left(22)
    );
  sr_left_22_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_22_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_22_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_22_MC_Q
    );
  sr_left_22_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_22_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_22_MC_D_IN1,
      O => sr_left_22_MC_D_76
    );
  sr_left_22_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_22_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_22_MC_D1_IN1,
      O => sr_left_22_MC_D1_77
    );
  sr_left_22_MC_D2 : X_ZERO
    port map (
      O => sr_left_22_MC_D2_78
    );
  sr_left_21_Q : X_BUF
    port map (
      I => sr_left_21_MC_Q,
      O => sr_left(21)
    );
  sr_left_21_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_21_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_21_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_21_MC_Q
    );
  sr_left_21_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_21_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_21_MC_D_IN1,
      O => sr_left_21_MC_D_81
    );
  sr_left_21_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_21_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_21_MC_D1_IN1,
      O => sr_left_21_MC_D1_82
    );
  sr_left_21_MC_D2 : X_ZERO
    port map (
      O => sr_left_21_MC_D2_83
    );
  sr_left_20_Q : X_BUF
    port map (
      I => sr_left_20_MC_Q,
      O => sr_left(20)
    );
  sr_left_20_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_20_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_20_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_20_MC_Q
    );
  sr_left_20_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_20_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_20_MC_D_IN1,
      O => sr_left_20_MC_D_86
    );
  sr_left_20_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_20_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_20_MC_D1_IN1,
      O => sr_left_20_MC_D1_87
    );
  sr_left_20_MC_D2 : X_ZERO
    port map (
      O => sr_left_20_MC_D2_88
    );
  sr_left_19_Q : X_BUF
    port map (
      I => sr_left_19_MC_Q,
      O => sr_left(19)
    );
  sr_left_19_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_19_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_19_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_19_MC_Q
    );
  sr_left_19_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_19_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_19_MC_D_IN1,
      O => sr_left_19_MC_D_91
    );
  sr_left_19_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_19_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_19_MC_D1_IN1,
      O => sr_left_19_MC_D1_92
    );
  sr_left_19_MC_D2 : X_ZERO
    port map (
      O => sr_left_19_MC_D2_93
    );
  sr_left_18_Q : X_BUF
    port map (
      I => sr_left_18_MC_Q,
      O => sr_left(18)
    );
  sr_left_18_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_18_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_18_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_18_MC_Q
    );
  sr_left_18_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_18_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_18_MC_D_IN1,
      O => sr_left_18_MC_D_96
    );
  sr_left_18_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_18_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_18_MC_D1_IN1,
      O => sr_left_18_MC_D1_97
    );
  sr_left_18_MC_D2 : X_ZERO
    port map (
      O => sr_left_18_MC_D2_98
    );
  sr_left_17_Q : X_BUF
    port map (
      I => sr_left_17_MC_Q,
      O => sr_left(17)
    );
  sr_left_17_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_17_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_17_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_17_MC_Q
    );
  sr_left_17_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_17_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_17_MC_D_IN1,
      O => sr_left_17_MC_D_101
    );
  sr_left_17_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_17_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_17_MC_D1_IN1,
      O => sr_left_17_MC_D1_102
    );
  sr_left_17_MC_D2 : X_ZERO
    port map (
      O => sr_left_17_MC_D2_103
    );
  sr_left_16_Q : X_BUF
    port map (
      I => sr_left_16_MC_Q,
      O => sr_left(16)
    );
  sr_left_16_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_16_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_16_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_16_MC_Q
    );
  sr_left_16_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_16_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_16_MC_D_IN1,
      O => sr_left_16_MC_D_106
    );
  sr_left_16_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_16_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_16_MC_D1_IN1,
      O => sr_left_16_MC_D1_107
    );
  sr_left_16_MC_D2 : X_ZERO
    port map (
      O => sr_left_16_MC_D2_108
    );
  sr_left_15_Q : X_BUF
    port map (
      I => sr_left_15_MC_Q,
      O => sr_left(15)
    );
  sr_left_15_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_15_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_15_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_15_MC_Q
    );
  sr_left_15_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_15_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_15_MC_D_IN1,
      O => sr_left_15_MC_D_111
    );
  sr_left_15_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_15_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_15_MC_D1_IN1,
      O => sr_left_15_MC_D1_112
    );
  sr_left_15_MC_D2 : X_ZERO
    port map (
      O => sr_left_15_MC_D2_113
    );
  sr_left_14_Q : X_BUF
    port map (
      I => sr_left_14_MC_Q,
      O => sr_left(14)
    );
  sr_left_14_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_14_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_14_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_14_MC_Q
    );
  sr_left_14_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_14_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_14_MC_D_IN1,
      O => sr_left_14_MC_D_116
    );
  sr_left_14_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_14_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_14_MC_D1_IN1,
      O => sr_left_14_MC_D1_117
    );
  sr_left_14_MC_D2 : X_ZERO
    port map (
      O => sr_left_14_MC_D2_118
    );
  sr_left_13_Q : X_BUF
    port map (
      I => sr_left_13_MC_Q,
      O => sr_left(13)
    );
  sr_left_13_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_13_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_13_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_13_MC_Q
    );
  sr_left_13_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_13_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_13_MC_D_IN1,
      O => sr_left_13_MC_D_121
    );
  sr_left_13_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_13_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_13_MC_D1_IN1,
      O => sr_left_13_MC_D1_122
    );
  sr_left_13_MC_D2 : X_ZERO
    port map (
      O => sr_left_13_MC_D2_123
    );
  sr_left_12_Q : X_BUF
    port map (
      I => sr_left_12_MC_Q,
      O => sr_left(12)
    );
  sr_left_12_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_12_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_12_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_12_MC_Q
    );
  sr_left_12_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_12_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_12_MC_D_IN1,
      O => sr_left_12_MC_D_126
    );
  sr_left_12_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_12_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_12_MC_D1_IN1,
      O => sr_left_12_MC_D1_127
    );
  sr_left_12_MC_D2 : X_ZERO
    port map (
      O => sr_left_12_MC_D2_128
    );
  sr_left_11_Q : X_BUF
    port map (
      I => sr_left_11_MC_Q,
      O => sr_left(11)
    );
  sr_left_11_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_11_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_11_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_11_MC_Q
    );
  sr_left_11_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_11_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_11_MC_D_IN1,
      O => sr_left_11_MC_D_131
    );
  sr_left_11_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_11_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_11_MC_D1_IN1,
      O => sr_left_11_MC_D1_132
    );
  sr_left_11_MC_D2 : X_ZERO
    port map (
      O => sr_left_11_MC_D2_133
    );
  sr_left_10_Q : X_BUF
    port map (
      I => sr_left_10_MC_Q,
      O => sr_left(10)
    );
  sr_left_10_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_10_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_10_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_10_MC_Q
    );
  sr_left_10_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_10_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_10_MC_D_IN1,
      O => sr_left_10_MC_D_136
    );
  sr_left_10_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_10_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_10_MC_D1_IN1,
      O => sr_left_10_MC_D1_137
    );
  sr_left_10_MC_D2 : X_ZERO
    port map (
      O => sr_left_10_MC_D2_138
    );
  sr_left_9_Q : X_BUF
    port map (
      I => sr_left_9_MC_Q,
      O => sr_left(9)
    );
  sr_left_9_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_9_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_9_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_9_MC_Q
    );
  sr_left_9_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_9_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_9_MC_D_IN1,
      O => sr_left_9_MC_D_141
    );
  sr_left_9_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_9_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_9_MC_D1_IN1,
      O => sr_left_9_MC_D1_142
    );
  sr_left_9_MC_D2 : X_ZERO
    port map (
      O => sr_left_9_MC_D2_143
    );
  sr_left_8_Q : X_BUF
    port map (
      I => sr_left_8_MC_Q,
      O => sr_left(8)
    );
  sr_left_8_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_8_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_8_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_8_MC_Q
    );
  sr_left_8_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_8_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_8_MC_D_IN1,
      O => sr_left_8_MC_D_146
    );
  sr_left_8_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_8_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_8_MC_D1_IN1,
      O => sr_left_8_MC_D1_147
    );
  sr_left_8_MC_D2 : X_ZERO
    port map (
      O => sr_left_8_MC_D2_148
    );
  sr_left_7_Q : X_BUF
    port map (
      I => sr_left_7_MC_Q,
      O => sr_left(7)
    );
  sr_left_7_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_7_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_7_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_7_MC_Q
    );
  sr_left_7_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_7_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_7_MC_D_IN1,
      O => sr_left_7_MC_D_151
    );
  sr_left_7_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_7_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_7_MC_D1_IN1,
      O => sr_left_7_MC_D1_152
    );
  sr_left_7_MC_D2 : X_ZERO
    port map (
      O => sr_left_7_MC_D2_153
    );
  sr_left_6_Q : X_BUF
    port map (
      I => sr_left_6_MC_Q,
      O => sr_left(6)
    );
  sr_left_6_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_6_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_6_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_6_MC_Q
    );
  sr_left_6_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_6_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_6_MC_D_IN1,
      O => sr_left_6_MC_D_156
    );
  sr_left_6_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_6_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_6_MC_D1_IN1,
      O => sr_left_6_MC_D1_157
    );
  sr_left_6_MC_D2 : X_ZERO
    port map (
      O => sr_left_6_MC_D2_158
    );
  sr_left_5_Q : X_BUF
    port map (
      I => sr_left_5_MC_Q,
      O => sr_left(5)
    );
  sr_left_5_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_5_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_5_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_5_MC_Q
    );
  sr_left_5_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_5_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_5_MC_D_IN1,
      O => sr_left_5_MC_D_161
    );
  sr_left_5_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_5_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_5_MC_D1_IN1,
      O => sr_left_5_MC_D1_162
    );
  sr_left_5_MC_D2 : X_ZERO
    port map (
      O => sr_left_5_MC_D2_163
    );
  sr_left_4_Q : X_BUF
    port map (
      I => sr_left_4_MC_Q,
      O => sr_left(4)
    );
  sr_left_4_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_4_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_4_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_4_MC_Q
    );
  sr_left_4_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_4_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_4_MC_D_IN1,
      O => sr_left_4_MC_D_166
    );
  sr_left_4_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_4_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_4_MC_D1_IN1,
      O => sr_left_4_MC_D1_167
    );
  sr_left_4_MC_D2 : X_ZERO
    port map (
      O => sr_left_4_MC_D2_168
    );
  sr_left_3_Q : X_BUF
    port map (
      I => sr_left_3_MC_Q,
      O => sr_left(3)
    );
  sr_left_3_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_3_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_3_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_3_MC_Q
    );
  sr_left_3_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_3_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_3_MC_D_IN1,
      O => sr_left_3_MC_D_171
    );
  sr_left_3_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_3_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_3_MC_D1_IN1,
      O => sr_left_3_MC_D1_172
    );
  sr_left_3_MC_D2 : X_ZERO
    port map (
      O => sr_left_3_MC_D2_173
    );
  sr_left_2_Q : X_BUF
    port map (
      I => sr_left_2_MC_Q,
      O => sr_left(2)
    );
  sr_left_2_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_2_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_2_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_2_MC_Q
    );
  sr_left_2_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_2_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_2_MC_D_IN1,
      O => sr_left_2_MC_D_176
    );
  sr_left_2_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_2_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_2_MC_D1_IN1,
      O => sr_left_2_MC_D1_177
    );
  sr_left_2_MC_D2 : X_ZERO
    port map (
      O => sr_left_2_MC_D2_178
    );
  sr_left_1_Q : X_BUF
    port map (
      I => sr_left_1_MC_Q,
      O => sr_left(1)
    );
  sr_left_1_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_1_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_1_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_1_MC_Q
    );
  sr_left_1_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_1_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_1_MC_D_IN1,
      O => sr_left_1_MC_D_181
    );
  sr_left_1_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_1_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_1_MC_D1_IN1,
      O => sr_left_1_MC_D1_182
    );
  sr_left_1_MC_D2 : X_ZERO
    port map (
      O => sr_left_1_MC_D2_183
    );
  sr_left_0_Q : X_BUF
    port map (
      I => sr_left_0_MC_Q,
      O => sr_left(0)
    );
  sr_left_0_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_left_0_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_left_0_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_left_0_MC_Q
    );
  sr_left_0_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_left_0_MC_D_IN0,
      I1 => NlwBufferSignal_sr_left_0_MC_D_IN1,
      O => sr_left_0_MC_D_186
    );
  sr_left_0_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_left_0_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_left_0_MC_D1_IN1,
      O => sr_left_0_MC_D1_187
    );
  sr_left_0_MC_D2 : X_ZERO
    port map (
      O => sr_left_0_MC_D2_188
    );
  DATAOUTR_MC_Q : X_BUF
    port map (
      I => DATAOUTR_MC_Q_tsimrenamed_net_Q,
      O => DATAOUTR_MC_Q_17
    );
  DATAOUTR_MC_UIM : X_BUF
    port map (
      I => DATAOUTR_MC_Q_tsimrenamed_net_Q,
      O => DATAOUTR_MC_UIM_189
    );
  DATAOUTR_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_DATAOUTR_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_DATAOUTR_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => DATAOUTR_MC_Q_tsimrenamed_net_Q
    );
  DATAOUTR_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_DATAOUTR_MC_D_IN0,
      I1 => NlwBufferSignal_DATAOUTR_MC_D_IN1,
      O => DATAOUTR_MC_D_191
    );
  DATAOUTR_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_DATAOUTR_MC_D1_IN0,
      I1 => NlwBufferSignal_DATAOUTR_MC_D1_IN1,
      O => DATAOUTR_MC_D1_192
    );
  DATAOUTR_MC_D2 : X_ZERO
    port map (
      O => DATAOUTR_MC_D2_193
    );
  sr_right_10_Q : X_BUF
    port map (
      I => sr_right_10_MC_Q,
      O => sr_right(10)
    );
  sr_right_10_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_10_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_10_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_10_MC_Q
    );
  sr_right_10_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_10_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_10_MC_D_IN1,
      O => sr_right_10_MC_D_196
    );
  sr_right_10_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_10_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_10_MC_D1_IN1,
      O => sr_right_10_MC_D1_197
    );
  sr_right_10_MC_D2 : X_ZERO
    port map (
      O => sr_right_10_MC_D2_198
    );
  sr_right_9_Q : X_BUF
    port map (
      I => sr_right_9_MC_Q,
      O => sr_right(9)
    );
  sr_right_9_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_9_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_9_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_9_MC_Q
    );
  sr_right_9_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_9_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_9_MC_D_IN1,
      O => sr_right_9_MC_D_201
    );
  sr_right_9_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_9_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_9_MC_D1_IN1,
      O => sr_right_9_MC_D1_202
    );
  sr_right_9_MC_D2 : X_ZERO
    port map (
      O => sr_right_9_MC_D2_203
    );
  sr_right_8_Q : X_BUF
    port map (
      I => sr_right_8_MC_Q,
      O => sr_right(8)
    );
  sr_right_8_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_8_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_8_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_8_MC_Q
    );
  sr_right_8_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_8_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_8_MC_D_IN1,
      O => sr_right_8_MC_D_206
    );
  sr_right_8_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_8_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_8_MC_D1_IN1,
      O => sr_right_8_MC_D1_207
    );
  sr_right_8_MC_D2 : X_ZERO
    port map (
      O => sr_right_8_MC_D2_208
    );
  sr_right_7_Q : X_BUF
    port map (
      I => sr_right_7_MC_Q,
      O => sr_right(7)
    );
  sr_right_7_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_7_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_7_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_7_MC_Q
    );
  sr_right_7_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_7_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_7_MC_D_IN1,
      O => sr_right_7_MC_D_211
    );
  sr_right_7_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_7_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_7_MC_D1_IN1,
      O => sr_right_7_MC_D1_212
    );
  sr_right_7_MC_D2 : X_ZERO
    port map (
      O => sr_right_7_MC_D2_213
    );
  sr_right_6_Q : X_BUF
    port map (
      I => sr_right_6_MC_Q,
      O => sr_right(6)
    );
  sr_right_6_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_6_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_6_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_6_MC_Q
    );
  sr_right_6_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_6_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_6_MC_D_IN1,
      O => sr_right_6_MC_D_216
    );
  sr_right_6_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_6_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_6_MC_D1_IN1,
      O => sr_right_6_MC_D1_217
    );
  sr_right_6_MC_D2 : X_ZERO
    port map (
      O => sr_right_6_MC_D2_218
    );
  sr_right_5_Q : X_BUF
    port map (
      I => sr_right_5_MC_Q,
      O => sr_right(5)
    );
  sr_right_5_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_5_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_5_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_5_MC_Q
    );
  sr_right_5_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_5_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_5_MC_D_IN1,
      O => sr_right_5_MC_D_221
    );
  sr_right_5_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_5_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_5_MC_D1_IN1,
      O => sr_right_5_MC_D1_222
    );
  sr_right_5_MC_D2 : X_ZERO
    port map (
      O => sr_right_5_MC_D2_223
    );
  sr_right_4_Q : X_BUF
    port map (
      I => sr_right_4_MC_Q,
      O => sr_right(4)
    );
  sr_right_4_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_4_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_4_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_4_MC_Q
    );
  sr_right_4_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_4_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_4_MC_D_IN1,
      O => sr_right_4_MC_D_226
    );
  sr_right_4_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_4_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_4_MC_D1_IN1,
      O => sr_right_4_MC_D1_227
    );
  sr_right_4_MC_D2 : X_ZERO
    port map (
      O => sr_right_4_MC_D2_228
    );
  sr_right_3_Q : X_BUF
    port map (
      I => sr_right_3_MC_Q,
      O => sr_right(3)
    );
  sr_right_3_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_3_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_3_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_3_MC_Q
    );
  sr_right_3_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_3_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_3_MC_D_IN1,
      O => sr_right_3_MC_D_231
    );
  sr_right_3_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_3_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_3_MC_D1_IN1,
      O => sr_right_3_MC_D1_232
    );
  sr_right_3_MC_D2 : X_ZERO
    port map (
      O => sr_right_3_MC_D2_233
    );
  sr_right_2_Q : X_BUF
    port map (
      I => sr_right_2_MC_Q,
      O => sr_right(2)
    );
  sr_right_2_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_2_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_2_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_2_MC_Q
    );
  sr_right_2_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_2_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_2_MC_D_IN1,
      O => sr_right_2_MC_D_236
    );
  sr_right_2_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_2_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_2_MC_D1_IN1,
      O => sr_right_2_MC_D1_237
    );
  sr_right_2_MC_D2 : X_ZERO
    port map (
      O => sr_right_2_MC_D2_238
    );
  sr_right_1_Q : X_BUF
    port map (
      I => sr_right_1_MC_Q,
      O => sr_right(1)
    );
  sr_right_1_MC_REG : X_FF
    generic map(
      INIT => '0'
    )
    port map (
      I => NlwBufferSignal_sr_right_1_MC_REG_IN,
      CE => Vcc_8,
      CLK => NlwBufferSignal_sr_right_1_MC_REG_CLK,
      SET => Gnd_7,
      RST => Gnd_7,
      O => sr_right_1_MC_Q
    );
  sr_right_1_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_sr_right_1_MC_D_IN0,
      I1 => NlwBufferSignal_sr_right_1_MC_D_IN1,
      O => sr_right_1_MC_D_241
    );
  sr_right_1_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_sr_right_1_MC_D1_IN0,
      I1 => NlwBufferSignal_sr_right_1_MC_D1_IN1,
      O => sr_right_1_MC_D1_242
    );
  sr_right_1_MC_D2 : X_ZERO
    port map (
      O => sr_right_1_MC_D2_243
    );
  LEOUTL_MC_Q : X_BUF
    port map (
      I => LEOUTL_MC_Q_tsimrenamed_net_Q_244,
      O => LEOUTL_MC_Q_19
    );
  LEOUTL_MC_Q_tsimrenamed_net_Q : X_BUF
    port map (
      I => LEOUTL_MC_D_245,
      O => LEOUTL_MC_Q_tsimrenamed_net_Q_244
    );
  LEOUTL_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_LEOUTL_MC_D_IN0,
      I1 => NlwBufferSignal_LEOUTL_MC_D_IN1,
      O => LEOUTL_MC_D_245
    );
  LEOUTL_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_LEOUTL_MC_D1_IN0,
      I1 => NlwBufferSignal_LEOUTL_MC_D1_IN1,
      O => LEOUTL_MC_D1_246
    );
  LEOUTL_MC_D2 : X_ZERO
    port map (
      O => LEOUTL_MC_D2_247
    );
  LEOUTR_MC_Q : X_BUF
    port map (
      I => LEOUTR_MC_Q_tsimrenamed_net_Q_248,
      O => LEOUTR_MC_Q_21
    );
  LEOUTR_MC_Q_tsimrenamed_net_Q : X_BUF
    port map (
      I => LEOUTR_MC_D_249,
      O => LEOUTR_MC_Q_tsimrenamed_net_Q_248
    );
  LEOUTR_MC_D : X_XOR2
    port map (
      I0 => NlwBufferSignal_LEOUTR_MC_D_IN0,
      I1 => NlwBufferSignal_LEOUTR_MC_D_IN1,
      O => LEOUTR_MC_D_249
    );
  LEOUTR_MC_D1 : X_AND2
    port map (
      I0 => NlwBufferSignal_LEOUTR_MC_D1_IN0,
      I1 => NlwBufferSignal_LEOUTR_MC_D1_IN1,
      O => LEOUTR_MC_D1_250
    );
  LEOUTR_MC_D2 : X_ZERO
    port map (
      O => LEOUTR_MC_D2_251
    );
  NlwBufferBlock_sr_right_0_MC_REG_IN : X_BUF
    port map (
      I => DATAIN_II_IREG_6,
      O => NlwBufferSignal_sr_right_0_MC_REG_IN
    );
  NlwBufferBlock_sr_right_0_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_0_MC_REG_CLK
    );
  NlwBufferBlock_CLKOUTL_MC_D_IN0 : X_BUF
    port map (
      I => CLKOUTL_MC_D1_24,
      O => NlwBufferSignal_CLKOUTL_MC_D_IN0
    );
  NlwBufferBlock_CLKOUTL_MC_D_IN1 : X_BUF
    port map (
      I => CLKOUTL_MC_D2_25,
      O => NlwBufferSignal_CLKOUTL_MC_D_IN1
    );
  NlwBufferBlock_CLKOUTL_MC_D1_IN0 : X_BUF
    port map (
      I => BCK_II_UIM_1,
      O => NlwBufferSignal_CLKOUTL_MC_D1_IN0
    );
  NlwBufferBlock_CLKOUTL_MC_D1_IN1 : X_BUF
    port map (
      I => BCK_II_UIM_1,
      O => NlwBufferSignal_CLKOUTL_MC_D1_IN1
    );
  NlwBufferBlock_CLKOUTR_MC_D_IN0 : X_BUF
    port map (
      I => CLKOUTR_MC_D1_28,
      O => NlwBufferSignal_CLKOUTR_MC_D_IN0
    );
  NlwBufferBlock_CLKOUTR_MC_D_IN1 : X_BUF
    port map (
      I => CLKOUTR_MC_D2_29,
      O => NlwBufferSignal_CLKOUTR_MC_D_IN1
    );
  NlwBufferBlock_CLKOUTR_MC_D1_IN0 : X_BUF
    port map (
      I => BCK_II_UIM_1,
      O => NlwBufferSignal_CLKOUTR_MC_D1_IN0
    );
  NlwBufferBlock_CLKOUTR_MC_D1_IN1 : X_BUF
    port map (
      I => BCK_II_UIM_1,
      O => NlwBufferSignal_CLKOUTR_MC_D1_IN1
    );
  NlwBufferBlock_DATAOUTL_MC_REG_IN : X_BUF
    port map (
      I => DATAOUTL_MC_D_31,
      O => NlwBufferSignal_DATAOUTL_MC_REG_IN
    );
  NlwBufferBlock_DATAOUTL_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_DATAOUTL_MC_REG_CLK
    );
  NlwBufferBlock_DATAOUTL_MC_D_IN0 : X_BUF
    port map (
      I => DATAOUTL_MC_D1_32,
      O => NlwBufferSignal_DATAOUTL_MC_D_IN0
    );
  NlwBufferBlock_DATAOUTL_MC_D_IN1 : X_BUF
    port map (
      I => DATAOUTL_MC_D2_33,
      O => NlwBufferSignal_DATAOUTL_MC_D_IN1
    );
  NlwBufferBlock_DATAOUTL_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(30),
      O => NlwBufferSignal_DATAOUTL_MC_D1_IN0
    );
  NlwBufferBlock_DATAOUTL_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(30),
      O => NlwBufferSignal_DATAOUTL_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_30_MC_REG_IN : X_BUF
    port map (
      I => sr_left_30_MC_D_36,
      O => NlwBufferSignal_sr_left_30_MC_REG_IN
    );
  NlwBufferBlock_sr_left_30_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_30_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_30_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_30_MC_D1_37,
      O => NlwBufferSignal_sr_left_30_MC_D_IN0
    );
  NlwBufferBlock_sr_left_30_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_30_MC_D2_38,
      O => NlwBufferSignal_sr_left_30_MC_D_IN1
    );
  NlwBufferBlock_sr_left_30_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(29),
      O => NlwBufferSignal_sr_left_30_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_30_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(29),
      O => NlwBufferSignal_sr_left_30_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_29_MC_REG_IN : X_BUF
    port map (
      I => sr_left_29_MC_D_41,
      O => NlwBufferSignal_sr_left_29_MC_REG_IN
    );
  NlwBufferBlock_sr_left_29_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_29_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_29_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_29_MC_D1_42,
      O => NlwBufferSignal_sr_left_29_MC_D_IN0
    );
  NlwBufferBlock_sr_left_29_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_29_MC_D2_43,
      O => NlwBufferSignal_sr_left_29_MC_D_IN1
    );
  NlwBufferBlock_sr_left_29_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(28),
      O => NlwBufferSignal_sr_left_29_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_29_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(28),
      O => NlwBufferSignal_sr_left_29_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_28_MC_REG_IN : X_BUF
    port map (
      I => sr_left_28_MC_D_46,
      O => NlwBufferSignal_sr_left_28_MC_REG_IN
    );
  NlwBufferBlock_sr_left_28_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_28_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_28_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_28_MC_D1_47,
      O => NlwBufferSignal_sr_left_28_MC_D_IN0
    );
  NlwBufferBlock_sr_left_28_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_28_MC_D2_48,
      O => NlwBufferSignal_sr_left_28_MC_D_IN1
    );
  NlwBufferBlock_sr_left_28_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(27),
      O => NlwBufferSignal_sr_left_28_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_28_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(27),
      O => NlwBufferSignal_sr_left_28_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_27_MC_REG_IN : X_BUF
    port map (
      I => sr_left_27_MC_D_51,
      O => NlwBufferSignal_sr_left_27_MC_REG_IN
    );
  NlwBufferBlock_sr_left_27_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_27_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_27_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_27_MC_D1_52,
      O => NlwBufferSignal_sr_left_27_MC_D_IN0
    );
  NlwBufferBlock_sr_left_27_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_27_MC_D2_53,
      O => NlwBufferSignal_sr_left_27_MC_D_IN1
    );
  NlwBufferBlock_sr_left_27_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(26),
      O => NlwBufferSignal_sr_left_27_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_27_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(26),
      O => NlwBufferSignal_sr_left_27_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_26_MC_REG_IN : X_BUF
    port map (
      I => sr_left_26_MC_D_56,
      O => NlwBufferSignal_sr_left_26_MC_REG_IN
    );
  NlwBufferBlock_sr_left_26_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_26_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_26_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_26_MC_D1_57,
      O => NlwBufferSignal_sr_left_26_MC_D_IN0
    );
  NlwBufferBlock_sr_left_26_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_26_MC_D2_58,
      O => NlwBufferSignal_sr_left_26_MC_D_IN1
    );
  NlwBufferBlock_sr_left_26_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(25),
      O => NlwBufferSignal_sr_left_26_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_26_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(25),
      O => NlwBufferSignal_sr_left_26_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_25_MC_REG_IN : X_BUF
    port map (
      I => sr_left_25_MC_D_61,
      O => NlwBufferSignal_sr_left_25_MC_REG_IN
    );
  NlwBufferBlock_sr_left_25_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_25_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_25_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_25_MC_D1_62,
      O => NlwBufferSignal_sr_left_25_MC_D_IN0
    );
  NlwBufferBlock_sr_left_25_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_25_MC_D2_63,
      O => NlwBufferSignal_sr_left_25_MC_D_IN1
    );
  NlwBufferBlock_sr_left_25_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(24),
      O => NlwBufferSignal_sr_left_25_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_25_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(24),
      O => NlwBufferSignal_sr_left_25_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_24_MC_REG_IN : X_BUF
    port map (
      I => sr_left_24_MC_D_66,
      O => NlwBufferSignal_sr_left_24_MC_REG_IN
    );
  NlwBufferBlock_sr_left_24_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_24_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_24_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_24_MC_D1_67,
      O => NlwBufferSignal_sr_left_24_MC_D_IN0
    );
  NlwBufferBlock_sr_left_24_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_24_MC_D2_68,
      O => NlwBufferSignal_sr_left_24_MC_D_IN1
    );
  NlwBufferBlock_sr_left_24_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(23),
      O => NlwBufferSignal_sr_left_24_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_24_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(23),
      O => NlwBufferSignal_sr_left_24_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_23_MC_REG_IN : X_BUF
    port map (
      I => sr_left_23_MC_D_71,
      O => NlwBufferSignal_sr_left_23_MC_REG_IN
    );
  NlwBufferBlock_sr_left_23_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_23_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_23_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_23_MC_D1_72,
      O => NlwBufferSignal_sr_left_23_MC_D_IN0
    );
  NlwBufferBlock_sr_left_23_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_23_MC_D2_73,
      O => NlwBufferSignal_sr_left_23_MC_D_IN1
    );
  NlwBufferBlock_sr_left_23_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(22),
      O => NlwBufferSignal_sr_left_23_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_23_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(22),
      O => NlwBufferSignal_sr_left_23_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_22_MC_REG_IN : X_BUF
    port map (
      I => sr_left_22_MC_D_76,
      O => NlwBufferSignal_sr_left_22_MC_REG_IN
    );
  NlwBufferBlock_sr_left_22_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_22_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_22_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_22_MC_D1_77,
      O => NlwBufferSignal_sr_left_22_MC_D_IN0
    );
  NlwBufferBlock_sr_left_22_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_22_MC_D2_78,
      O => NlwBufferSignal_sr_left_22_MC_D_IN1
    );
  NlwBufferBlock_sr_left_22_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(21),
      O => NlwBufferSignal_sr_left_22_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_22_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(21),
      O => NlwBufferSignal_sr_left_22_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_21_MC_REG_IN : X_BUF
    port map (
      I => sr_left_21_MC_D_81,
      O => NlwBufferSignal_sr_left_21_MC_REG_IN
    );
  NlwBufferBlock_sr_left_21_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_21_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_21_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_21_MC_D1_82,
      O => NlwBufferSignal_sr_left_21_MC_D_IN0
    );
  NlwBufferBlock_sr_left_21_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_21_MC_D2_83,
      O => NlwBufferSignal_sr_left_21_MC_D_IN1
    );
  NlwBufferBlock_sr_left_21_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(20),
      O => NlwBufferSignal_sr_left_21_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_21_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(20),
      O => NlwBufferSignal_sr_left_21_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_20_MC_REG_IN : X_BUF
    port map (
      I => sr_left_20_MC_D_86,
      O => NlwBufferSignal_sr_left_20_MC_REG_IN
    );
  NlwBufferBlock_sr_left_20_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_20_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_20_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_20_MC_D1_87,
      O => NlwBufferSignal_sr_left_20_MC_D_IN0
    );
  NlwBufferBlock_sr_left_20_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_20_MC_D2_88,
      O => NlwBufferSignal_sr_left_20_MC_D_IN1
    );
  NlwBufferBlock_sr_left_20_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(19),
      O => NlwBufferSignal_sr_left_20_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_20_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(19),
      O => NlwBufferSignal_sr_left_20_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_19_MC_REG_IN : X_BUF
    port map (
      I => sr_left_19_MC_D_91,
      O => NlwBufferSignal_sr_left_19_MC_REG_IN
    );
  NlwBufferBlock_sr_left_19_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_19_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_19_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_19_MC_D1_92,
      O => NlwBufferSignal_sr_left_19_MC_D_IN0
    );
  NlwBufferBlock_sr_left_19_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_19_MC_D2_93,
      O => NlwBufferSignal_sr_left_19_MC_D_IN1
    );
  NlwBufferBlock_sr_left_19_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(18),
      O => NlwBufferSignal_sr_left_19_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_19_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(18),
      O => NlwBufferSignal_sr_left_19_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_18_MC_REG_IN : X_BUF
    port map (
      I => sr_left_18_MC_D_96,
      O => NlwBufferSignal_sr_left_18_MC_REG_IN
    );
  NlwBufferBlock_sr_left_18_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_18_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_18_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_18_MC_D1_97,
      O => NlwBufferSignal_sr_left_18_MC_D_IN0
    );
  NlwBufferBlock_sr_left_18_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_18_MC_D2_98,
      O => NlwBufferSignal_sr_left_18_MC_D_IN1
    );
  NlwBufferBlock_sr_left_18_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(17),
      O => NlwBufferSignal_sr_left_18_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_18_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(17),
      O => NlwBufferSignal_sr_left_18_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_17_MC_REG_IN : X_BUF
    port map (
      I => sr_left_17_MC_D_101,
      O => NlwBufferSignal_sr_left_17_MC_REG_IN
    );
  NlwBufferBlock_sr_left_17_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_17_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_17_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_17_MC_D1_102,
      O => NlwBufferSignal_sr_left_17_MC_D_IN0
    );
  NlwBufferBlock_sr_left_17_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_17_MC_D2_103,
      O => NlwBufferSignal_sr_left_17_MC_D_IN1
    );
  NlwBufferBlock_sr_left_17_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(16),
      O => NlwBufferSignal_sr_left_17_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_17_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(16),
      O => NlwBufferSignal_sr_left_17_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_16_MC_REG_IN : X_BUF
    port map (
      I => sr_left_16_MC_D_106,
      O => NlwBufferSignal_sr_left_16_MC_REG_IN
    );
  NlwBufferBlock_sr_left_16_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_16_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_16_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_16_MC_D1_107,
      O => NlwBufferSignal_sr_left_16_MC_D_IN0
    );
  NlwBufferBlock_sr_left_16_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_16_MC_D2_108,
      O => NlwBufferSignal_sr_left_16_MC_D_IN1
    );
  NlwBufferBlock_sr_left_16_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(15),
      O => NlwBufferSignal_sr_left_16_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_16_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(15),
      O => NlwBufferSignal_sr_left_16_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_15_MC_REG_IN : X_BUF
    port map (
      I => sr_left_15_MC_D_111,
      O => NlwBufferSignal_sr_left_15_MC_REG_IN
    );
  NlwBufferBlock_sr_left_15_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_15_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_15_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_15_MC_D1_112,
      O => NlwBufferSignal_sr_left_15_MC_D_IN0
    );
  NlwBufferBlock_sr_left_15_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_15_MC_D2_113,
      O => NlwBufferSignal_sr_left_15_MC_D_IN1
    );
  NlwBufferBlock_sr_left_15_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(14),
      O => NlwBufferSignal_sr_left_15_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_15_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(14),
      O => NlwBufferSignal_sr_left_15_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_14_MC_REG_IN : X_BUF
    port map (
      I => sr_left_14_MC_D_116,
      O => NlwBufferSignal_sr_left_14_MC_REG_IN
    );
  NlwBufferBlock_sr_left_14_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_14_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_14_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_14_MC_D1_117,
      O => NlwBufferSignal_sr_left_14_MC_D_IN0
    );
  NlwBufferBlock_sr_left_14_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_14_MC_D2_118,
      O => NlwBufferSignal_sr_left_14_MC_D_IN1
    );
  NlwBufferBlock_sr_left_14_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(13),
      O => NlwBufferSignal_sr_left_14_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_14_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(13),
      O => NlwBufferSignal_sr_left_14_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_13_MC_REG_IN : X_BUF
    port map (
      I => sr_left_13_MC_D_121,
      O => NlwBufferSignal_sr_left_13_MC_REG_IN
    );
  NlwBufferBlock_sr_left_13_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_13_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_13_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_13_MC_D1_122,
      O => NlwBufferSignal_sr_left_13_MC_D_IN0
    );
  NlwBufferBlock_sr_left_13_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_13_MC_D2_123,
      O => NlwBufferSignal_sr_left_13_MC_D_IN1
    );
  NlwBufferBlock_sr_left_13_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(12),
      O => NlwBufferSignal_sr_left_13_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_13_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(12),
      O => NlwBufferSignal_sr_left_13_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_12_MC_REG_IN : X_BUF
    port map (
      I => sr_left_12_MC_D_126,
      O => NlwBufferSignal_sr_left_12_MC_REG_IN
    );
  NlwBufferBlock_sr_left_12_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_12_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_12_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_12_MC_D1_127,
      O => NlwBufferSignal_sr_left_12_MC_D_IN0
    );
  NlwBufferBlock_sr_left_12_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_12_MC_D2_128,
      O => NlwBufferSignal_sr_left_12_MC_D_IN1
    );
  NlwBufferBlock_sr_left_12_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(11),
      O => NlwBufferSignal_sr_left_12_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_12_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(11),
      O => NlwBufferSignal_sr_left_12_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_11_MC_REG_IN : X_BUF
    port map (
      I => sr_left_11_MC_D_131,
      O => NlwBufferSignal_sr_left_11_MC_REG_IN
    );
  NlwBufferBlock_sr_left_11_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_11_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_11_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_11_MC_D1_132,
      O => NlwBufferSignal_sr_left_11_MC_D_IN0
    );
  NlwBufferBlock_sr_left_11_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_11_MC_D2_133,
      O => NlwBufferSignal_sr_left_11_MC_D_IN1
    );
  NlwBufferBlock_sr_left_11_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(10),
      O => NlwBufferSignal_sr_left_11_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_11_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(10),
      O => NlwBufferSignal_sr_left_11_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_10_MC_REG_IN : X_BUF
    port map (
      I => sr_left_10_MC_D_136,
      O => NlwBufferSignal_sr_left_10_MC_REG_IN
    );
  NlwBufferBlock_sr_left_10_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_10_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_10_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_10_MC_D1_137,
      O => NlwBufferSignal_sr_left_10_MC_D_IN0
    );
  NlwBufferBlock_sr_left_10_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_10_MC_D2_138,
      O => NlwBufferSignal_sr_left_10_MC_D_IN1
    );
  NlwBufferBlock_sr_left_10_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(9),
      O => NlwBufferSignal_sr_left_10_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_10_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(9),
      O => NlwBufferSignal_sr_left_10_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_9_MC_REG_IN : X_BUF
    port map (
      I => sr_left_9_MC_D_141,
      O => NlwBufferSignal_sr_left_9_MC_REG_IN
    );
  NlwBufferBlock_sr_left_9_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_9_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_9_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_9_MC_D1_142,
      O => NlwBufferSignal_sr_left_9_MC_D_IN0
    );
  NlwBufferBlock_sr_left_9_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_9_MC_D2_143,
      O => NlwBufferSignal_sr_left_9_MC_D_IN1
    );
  NlwBufferBlock_sr_left_9_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(8),
      O => NlwBufferSignal_sr_left_9_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_9_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(8),
      O => NlwBufferSignal_sr_left_9_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_8_MC_REG_IN : X_BUF
    port map (
      I => sr_left_8_MC_D_146,
      O => NlwBufferSignal_sr_left_8_MC_REG_IN
    );
  NlwBufferBlock_sr_left_8_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_8_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_8_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_8_MC_D1_147,
      O => NlwBufferSignal_sr_left_8_MC_D_IN0
    );
  NlwBufferBlock_sr_left_8_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_8_MC_D2_148,
      O => NlwBufferSignal_sr_left_8_MC_D_IN1
    );
  NlwBufferBlock_sr_left_8_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(7),
      O => NlwBufferSignal_sr_left_8_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_8_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(7),
      O => NlwBufferSignal_sr_left_8_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_7_MC_REG_IN : X_BUF
    port map (
      I => sr_left_7_MC_D_151,
      O => NlwBufferSignal_sr_left_7_MC_REG_IN
    );
  NlwBufferBlock_sr_left_7_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_7_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_7_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_7_MC_D1_152,
      O => NlwBufferSignal_sr_left_7_MC_D_IN0
    );
  NlwBufferBlock_sr_left_7_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_7_MC_D2_153,
      O => NlwBufferSignal_sr_left_7_MC_D_IN1
    );
  NlwBufferBlock_sr_left_7_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(6),
      O => NlwBufferSignal_sr_left_7_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_7_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(6),
      O => NlwBufferSignal_sr_left_7_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_6_MC_REG_IN : X_BUF
    port map (
      I => sr_left_6_MC_D_156,
      O => NlwBufferSignal_sr_left_6_MC_REG_IN
    );
  NlwBufferBlock_sr_left_6_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_6_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_6_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_6_MC_D1_157,
      O => NlwBufferSignal_sr_left_6_MC_D_IN0
    );
  NlwBufferBlock_sr_left_6_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_6_MC_D2_158,
      O => NlwBufferSignal_sr_left_6_MC_D_IN1
    );
  NlwBufferBlock_sr_left_6_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(5),
      O => NlwBufferSignal_sr_left_6_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_6_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(5),
      O => NlwBufferSignal_sr_left_6_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_5_MC_REG_IN : X_BUF
    port map (
      I => sr_left_5_MC_D_161,
      O => NlwBufferSignal_sr_left_5_MC_REG_IN
    );
  NlwBufferBlock_sr_left_5_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_5_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_5_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_5_MC_D1_162,
      O => NlwBufferSignal_sr_left_5_MC_D_IN0
    );
  NlwBufferBlock_sr_left_5_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_5_MC_D2_163,
      O => NlwBufferSignal_sr_left_5_MC_D_IN1
    );
  NlwBufferBlock_sr_left_5_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(4),
      O => NlwBufferSignal_sr_left_5_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_5_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(4),
      O => NlwBufferSignal_sr_left_5_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_4_MC_REG_IN : X_BUF
    port map (
      I => sr_left_4_MC_D_166,
      O => NlwBufferSignal_sr_left_4_MC_REG_IN
    );
  NlwBufferBlock_sr_left_4_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_4_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_4_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_4_MC_D1_167,
      O => NlwBufferSignal_sr_left_4_MC_D_IN0
    );
  NlwBufferBlock_sr_left_4_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_4_MC_D2_168,
      O => NlwBufferSignal_sr_left_4_MC_D_IN1
    );
  NlwBufferBlock_sr_left_4_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(3),
      O => NlwBufferSignal_sr_left_4_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_4_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(3),
      O => NlwBufferSignal_sr_left_4_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_3_MC_REG_IN : X_BUF
    port map (
      I => sr_left_3_MC_D_171,
      O => NlwBufferSignal_sr_left_3_MC_REG_IN
    );
  NlwBufferBlock_sr_left_3_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_3_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_3_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_3_MC_D1_172,
      O => NlwBufferSignal_sr_left_3_MC_D_IN0
    );
  NlwBufferBlock_sr_left_3_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_3_MC_D2_173,
      O => NlwBufferSignal_sr_left_3_MC_D_IN1
    );
  NlwBufferBlock_sr_left_3_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(2),
      O => NlwBufferSignal_sr_left_3_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_3_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(2),
      O => NlwBufferSignal_sr_left_3_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_2_MC_REG_IN : X_BUF
    port map (
      I => sr_left_2_MC_D_176,
      O => NlwBufferSignal_sr_left_2_MC_REG_IN
    );
  NlwBufferBlock_sr_left_2_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_2_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_2_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_2_MC_D1_177,
      O => NlwBufferSignal_sr_left_2_MC_D_IN0
    );
  NlwBufferBlock_sr_left_2_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_2_MC_D2_178,
      O => NlwBufferSignal_sr_left_2_MC_D_IN1
    );
  NlwBufferBlock_sr_left_2_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(1),
      O => NlwBufferSignal_sr_left_2_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_2_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(1),
      O => NlwBufferSignal_sr_left_2_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_1_MC_REG_IN : X_BUF
    port map (
      I => sr_left_1_MC_D_181,
      O => NlwBufferSignal_sr_left_1_MC_REG_IN
    );
  NlwBufferBlock_sr_left_1_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_1_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_1_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_1_MC_D1_182,
      O => NlwBufferSignal_sr_left_1_MC_D_IN0
    );
  NlwBufferBlock_sr_left_1_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_1_MC_D2_183,
      O => NlwBufferSignal_sr_left_1_MC_D_IN1
    );
  NlwBufferBlock_sr_left_1_MC_D1_IN0 : X_BUF
    port map (
      I => sr_left(0),
      O => NlwBufferSignal_sr_left_1_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_1_MC_D1_IN1 : X_BUF
    port map (
      I => sr_left(0),
      O => NlwBufferSignal_sr_left_1_MC_D1_IN1
    );
  NlwBufferBlock_sr_left_0_MC_REG_IN : X_BUF
    port map (
      I => sr_left_0_MC_D_186,
      O => NlwBufferSignal_sr_left_0_MC_REG_IN
    );
  NlwBufferBlock_sr_left_0_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_left_0_MC_REG_CLK
    );
  NlwBufferBlock_sr_left_0_MC_D_IN0 : X_BUF
    port map (
      I => sr_left_0_MC_D1_187,
      O => NlwBufferSignal_sr_left_0_MC_D_IN0
    );
  NlwBufferBlock_sr_left_0_MC_D_IN1 : X_BUF
    port map (
      I => sr_left_0_MC_D2_188,
      O => NlwBufferSignal_sr_left_0_MC_D_IN1
    );
  NlwBufferBlock_sr_left_0_MC_D1_IN0 : X_BUF
    port map (
      I => DATAOUTR_MC_UIM_189,
      O => NlwBufferSignal_sr_left_0_MC_D1_IN0
    );
  NlwBufferBlock_sr_left_0_MC_D1_IN1 : X_BUF
    port map (
      I => DATAOUTR_MC_UIM_189,
      O => NlwBufferSignal_sr_left_0_MC_D1_IN1
    );
  NlwBufferBlock_DATAOUTR_MC_REG_IN : X_BUF
    port map (
      I => DATAOUTR_MC_D_191,
      O => NlwBufferSignal_DATAOUTR_MC_REG_IN
    );
  NlwBufferBlock_DATAOUTR_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_DATAOUTR_MC_REG_CLK
    );
  NlwBufferBlock_DATAOUTR_MC_D_IN0 : X_BUF
    port map (
      I => DATAOUTR_MC_D1_192,
      O => NlwBufferSignal_DATAOUTR_MC_D_IN0
    );
  NlwBufferBlock_DATAOUTR_MC_D_IN1 : X_BUF
    port map (
      I => DATAOUTR_MC_D2_193,
      O => NlwBufferSignal_DATAOUTR_MC_D_IN1
    );
  NlwBufferBlock_DATAOUTR_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(10),
      O => NlwBufferSignal_DATAOUTR_MC_D1_IN0
    );
  NlwBufferBlock_DATAOUTR_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(10),
      O => NlwBufferSignal_DATAOUTR_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_10_MC_REG_IN : X_BUF
    port map (
      I => sr_right_10_MC_D_196,
      O => NlwBufferSignal_sr_right_10_MC_REG_IN
    );
  NlwBufferBlock_sr_right_10_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_10_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_10_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_10_MC_D1_197,
      O => NlwBufferSignal_sr_right_10_MC_D_IN0
    );
  NlwBufferBlock_sr_right_10_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_10_MC_D2_198,
      O => NlwBufferSignal_sr_right_10_MC_D_IN1
    );
  NlwBufferBlock_sr_right_10_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(9),
      O => NlwBufferSignal_sr_right_10_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_10_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(9),
      O => NlwBufferSignal_sr_right_10_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_9_MC_REG_IN : X_BUF
    port map (
      I => sr_right_9_MC_D_201,
      O => NlwBufferSignal_sr_right_9_MC_REG_IN
    );
  NlwBufferBlock_sr_right_9_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_9_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_9_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_9_MC_D1_202,
      O => NlwBufferSignal_sr_right_9_MC_D_IN0
    );
  NlwBufferBlock_sr_right_9_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_9_MC_D2_203,
      O => NlwBufferSignal_sr_right_9_MC_D_IN1
    );
  NlwBufferBlock_sr_right_9_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(8),
      O => NlwBufferSignal_sr_right_9_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_9_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(8),
      O => NlwBufferSignal_sr_right_9_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_8_MC_REG_IN : X_BUF
    port map (
      I => sr_right_8_MC_D_206,
      O => NlwBufferSignal_sr_right_8_MC_REG_IN
    );
  NlwBufferBlock_sr_right_8_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_8_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_8_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_8_MC_D1_207,
      O => NlwBufferSignal_sr_right_8_MC_D_IN0
    );
  NlwBufferBlock_sr_right_8_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_8_MC_D2_208,
      O => NlwBufferSignal_sr_right_8_MC_D_IN1
    );
  NlwBufferBlock_sr_right_8_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(7),
      O => NlwBufferSignal_sr_right_8_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_8_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(7),
      O => NlwBufferSignal_sr_right_8_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_7_MC_REG_IN : X_BUF
    port map (
      I => sr_right_7_MC_D_211,
      O => NlwBufferSignal_sr_right_7_MC_REG_IN
    );
  NlwBufferBlock_sr_right_7_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_7_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_7_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_7_MC_D1_212,
      O => NlwBufferSignal_sr_right_7_MC_D_IN0
    );
  NlwBufferBlock_sr_right_7_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_7_MC_D2_213,
      O => NlwBufferSignal_sr_right_7_MC_D_IN1
    );
  NlwBufferBlock_sr_right_7_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(6),
      O => NlwBufferSignal_sr_right_7_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_7_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(6),
      O => NlwBufferSignal_sr_right_7_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_6_MC_REG_IN : X_BUF
    port map (
      I => sr_right_6_MC_D_216,
      O => NlwBufferSignal_sr_right_6_MC_REG_IN
    );
  NlwBufferBlock_sr_right_6_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_6_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_6_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_6_MC_D1_217,
      O => NlwBufferSignal_sr_right_6_MC_D_IN0
    );
  NlwBufferBlock_sr_right_6_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_6_MC_D2_218,
      O => NlwBufferSignal_sr_right_6_MC_D_IN1
    );
  NlwBufferBlock_sr_right_6_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(5),
      O => NlwBufferSignal_sr_right_6_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_6_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(5),
      O => NlwBufferSignal_sr_right_6_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_5_MC_REG_IN : X_BUF
    port map (
      I => sr_right_5_MC_D_221,
      O => NlwBufferSignal_sr_right_5_MC_REG_IN
    );
  NlwBufferBlock_sr_right_5_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_5_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_5_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_5_MC_D1_222,
      O => NlwBufferSignal_sr_right_5_MC_D_IN0
    );
  NlwBufferBlock_sr_right_5_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_5_MC_D2_223,
      O => NlwBufferSignal_sr_right_5_MC_D_IN1
    );
  NlwBufferBlock_sr_right_5_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(4),
      O => NlwBufferSignal_sr_right_5_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_5_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(4),
      O => NlwBufferSignal_sr_right_5_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_4_MC_REG_IN : X_BUF
    port map (
      I => sr_right_4_MC_D_226,
      O => NlwBufferSignal_sr_right_4_MC_REG_IN
    );
  NlwBufferBlock_sr_right_4_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_4_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_4_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_4_MC_D1_227,
      O => NlwBufferSignal_sr_right_4_MC_D_IN0
    );
  NlwBufferBlock_sr_right_4_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_4_MC_D2_228,
      O => NlwBufferSignal_sr_right_4_MC_D_IN1
    );
  NlwBufferBlock_sr_right_4_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(3),
      O => NlwBufferSignal_sr_right_4_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_4_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(3),
      O => NlwBufferSignal_sr_right_4_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_3_MC_REG_IN : X_BUF
    port map (
      I => sr_right_3_MC_D_231,
      O => NlwBufferSignal_sr_right_3_MC_REG_IN
    );
  NlwBufferBlock_sr_right_3_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_3_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_3_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_3_MC_D1_232,
      O => NlwBufferSignal_sr_right_3_MC_D_IN0
    );
  NlwBufferBlock_sr_right_3_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_3_MC_D2_233,
      O => NlwBufferSignal_sr_right_3_MC_D_IN1
    );
  NlwBufferBlock_sr_right_3_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(2),
      O => NlwBufferSignal_sr_right_3_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_3_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(2),
      O => NlwBufferSignal_sr_right_3_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_2_MC_REG_IN : X_BUF
    port map (
      I => sr_right_2_MC_D_236,
      O => NlwBufferSignal_sr_right_2_MC_REG_IN
    );
  NlwBufferBlock_sr_right_2_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_2_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_2_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_2_MC_D1_237,
      O => NlwBufferSignal_sr_right_2_MC_D_IN0
    );
  NlwBufferBlock_sr_right_2_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_2_MC_D2_238,
      O => NlwBufferSignal_sr_right_2_MC_D_IN1
    );
  NlwBufferBlock_sr_right_2_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(1),
      O => NlwBufferSignal_sr_right_2_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_2_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(1),
      O => NlwBufferSignal_sr_right_2_MC_D1_IN1
    );
  NlwBufferBlock_sr_right_1_MC_REG_IN : X_BUF
    port map (
      I => sr_right_1_MC_D_241,
      O => NlwBufferSignal_sr_right_1_MC_REG_IN
    );
  NlwBufferBlock_sr_right_1_MC_REG_CLK : X_BUF
    port map (
      I => BCK_II_FCLK_2,
      O => NlwBufferSignal_sr_right_1_MC_REG_CLK
    );
  NlwBufferBlock_sr_right_1_MC_D_IN0 : X_BUF
    port map (
      I => sr_right_1_MC_D1_242,
      O => NlwBufferSignal_sr_right_1_MC_D_IN0
    );
  NlwBufferBlock_sr_right_1_MC_D_IN1 : X_BUF
    port map (
      I => sr_right_1_MC_D2_243,
      O => NlwBufferSignal_sr_right_1_MC_D_IN1
    );
  NlwBufferBlock_sr_right_1_MC_D1_IN0 : X_BUF
    port map (
      I => sr_right(0),
      O => NlwBufferSignal_sr_right_1_MC_D1_IN0
    );
  NlwBufferBlock_sr_right_1_MC_D1_IN1 : X_BUF
    port map (
      I => sr_right(0),
      O => NlwBufferSignal_sr_right_1_MC_D1_IN1
    );
  NlwBufferBlock_LEOUTL_MC_D_IN0 : X_BUF
    port map (
      I => LEOUTL_MC_D1_246,
      O => NlwBufferSignal_LEOUTL_MC_D_IN0
    );
  NlwBufferBlock_LEOUTL_MC_D_IN1 : X_BUF
    port map (
      I => LEOUTL_MC_D2_247,
      O => NlwBufferSignal_LEOUTL_MC_D_IN1
    );
  NlwBufferBlock_LEOUTL_MC_D1_IN0 : X_BUF
    port map (
      I => LRCK_II_UIM_4,
      O => NlwBufferSignal_LEOUTL_MC_D1_IN0
    );
  NlwBufferBlock_LEOUTL_MC_D1_IN1 : X_BUF
    port map (
      I => LRCK_II_UIM_4,
      O => NlwBufferSignal_LEOUTL_MC_D1_IN1
    );
  NlwBufferBlock_LEOUTR_MC_D_IN0 : X_BUF
    port map (
      I => LEOUTR_MC_D1_250,
      O => NlwBufferSignal_LEOUTR_MC_D_IN0
    );
  NlwBufferBlock_LEOUTR_MC_D_IN1 : X_BUF
    port map (
      I => LEOUTR_MC_D2_251,
      O => NlwBufferSignal_LEOUTR_MC_D_IN1
    );
  NlwBufferBlock_LEOUTR_MC_D1_IN0 : X_BUF
    port map (
      I => LRCK_II_UIM_4,
      O => NlwBufferSignal_LEOUTR_MC_D1_IN0
    );
  NlwBufferBlock_LEOUTR_MC_D1_IN1 : X_BUF
    port map (
      I => LRCK_II_UIM_4,
      O => NlwBufferSignal_LEOUTR_MC_D1_IN1
    );
  NlwBlockROC : X_ROC
    generic map (ROC_WIDTH => 100 ns)
    port map (O => PRLD);

end Structure;

