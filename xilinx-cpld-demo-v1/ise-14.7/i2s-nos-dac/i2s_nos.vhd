--------------------------------------------------------------------------------
-- Company: 
-- Engineer:
--
-- Create Date:   18:21:03 04/19/2021
-- Design Name:   
-- Module Name:   C:/Users/schenk/Documents/GitHub/electronic-projects/xilinx-cpld-demo-v1/ise-14.7/i2s-nos-dac/i2s_nos.vhd
-- Project Name:  i2s-nos-dac
-- Target Device:  
-- Tool versions:  
-- Description:   
-- 
-- VHDL Test Bench Created by ISE for module: i2s_nos
-- 
-- Dependencies:
-- 
-- Revision:
-- Revision 0.01 - File Created
-- Additional Comments:
--
-- Notes: 
-- This testbench has been automatically generated using types std_logic and
-- std_logic_vector for the ports of the unit under test.  Xilinx recommends
-- that these types always be used for the top-level I/O of a design in order
-- to guarantee that the testbench will bind correctly to the post-implementation 
-- simulation model.
--------------------------------------------------------------------------------
LIBRARY ieee;
USE ieee.std_logic_1164.ALL;
 
-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--USE ieee.numeric_std.ALL;
 
ENTITY i2s_nos IS
END i2s_nos;
 
ARCHITECTURE behavior OF i2s_nos IS 
 
    -- Component Declaration for the Unit Under Test (UUT)
 
    COMPONENT i2s_nos
    PORT(
         MCLK : IN  std_logic;
         BCK : IN  std_logic;
         LRCK : IN  std_logic;
         DATAIN : IN  std_logic;
         CLKOUTR : OUT  std_logic;
         LEOUTR : OUT  std_logic;
         DATAOUTR : OUT  std_logic;
         CLKOUTL : OUT  std_logic;
         LEOUTL : OUT  std_logic;
         DATAOUTL : OUT  std_logic
        );
    END COMPONENT;
    

   --Inputs
   signal MCLK : std_logic := '0';
   signal BCK : std_logic := '0';
   signal LRCK : std_logic := '0';
   signal DATAIN : std_logic := '0';

 	--Outputs
   signal CLKOUTR : std_logic;
   signal LEOUTR : std_logic;
   signal DATAOUTR : std_logic;
   signal CLKOUTL : std_logic;
   signal LEOUTL : std_logic;
   signal DATAOUTL : std_logic;

   -- Clock period definitions
   constant MCLK_period : time := 10 ns;
   constant CLKOUTR_period : time := 10 ns;
   constant CLKOUTL_period : time := 10 ns;
 
BEGIN
 
	-- Instantiate the Unit Under Test (UUT)
   uut: i2s_nos PORT MAP (
          MCLK => MCLK,
          BCK => BCK,
          LRCK => LRCK,
          DATAIN => DATAIN,
          CLKOUTR => CLKOUTR,
          LEOUTR => LEOUTR,
          DATAOUTR => DATAOUTR,
          CLKOUTL => CLKOUTL,
          LEOUTL => LEOUTL,
          DATAOUTL => DATAOUTL
        );

   -- Clock process definitions
   MCLK_process :process
   begin
		MCLK <= '0';
		wait for MCLK_period/2;
		MCLK <= '1';
		wait for MCLK_period/2;
   end process;
 
   CLKOUTR_process :process
   begin
		CLKOUTR <= '0';
		wait for CLKOUTR_period/2;
		CLKOUTR <= '1';
		wait for CLKOUTR_period/2;
   end process;
 
   CLKOUTL_process :process
   begin
		CLKOUTL <= '0';
		wait for CLKOUTL_period/2;
		CLKOUTL <= '1';
		wait for CLKOUTL_period/2;
   end process;
 

   -- Stimulus process
   stim_proc: process
   begin		
      -- hold reset state for 100 ns.
      wait for 100 ns;	

      wait for MCLK_period*10;

      -- insert stimulus here 

      wait;
   end process;

END;
