----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    11:01:23 04/18/2021 
-- Design Name: 
-- Module Name:    i2s-nos - Behavioral 
-- Project Name: 
-- Target Devices: 
-- Tool versions: 
-- Description: 
--
-- Dependencies: 
--
-- Revision: 
-- Revision 0.01 - File Created
-- Additional Comments: 
--
----------------------------------------------------------------------------------
library IEEE;
use IEEE.STD_LOGIC_1164.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity i2s_nos is
    Port ( MCLK : in  STD_LOGIC;
           BCK : in  STD_LOGIC;
           LRCK : in  STD_LOGIC;
           DATAIN : in  STD_LOGIC;
           CLKOUT : out  STD_LOGIC;
           LEOUT : out  STD_LOGIC;
           DATAOUTL : out  STD_LOGIC;
           DATAOUTR : out  STD_LOGIC);
end i2s_nos;

architecture Behavioral of i2s_nos is
	signal D0, D1, D2, D3, D4, D5, D6, D7, D8, D9, D10, D11 : STD_LOGIC;
	signal DA0, DA1, DA2, DA3, DA4, DA5, DA6, DA7, DA8, DA9, DA10, DA11 : STD_LOGIC;
	begin
	SHIFT : process (BCK)
		begin
			if (BCK'event and BCK='1') then
				D0 <= DATAIN; D1 <= D0; D2 <= D1; D3 <= D2;
				D4 <= D3; D5 <= D4; D6 <= D5; D7 <= D6; 
				D8 <= D7; D9 <= D8; D10 <= D9; D11 <= D10;
			end if;
		end process;
		
			SHIFT2 : process (BCK)
		begin
			if (BCK'event and BCK='1') then
				DA0 <= D11; DA1 <= DA0; DA2 <= DA1; DA3 <= DA2;
				DA4 <= DA3; DA5 <= DA4; DA6 <= DA5; DA7 <= DA6; 
				DA8 <= DA7; DA9 <= DA8; DA10 <= DA9; DA11 <= DA10;
			end if;
		end process;
		
		
		DATAOUTL <= D11;
		DATAOUTR <= DA11;
		CLKOUT <= BCK;
		LEOUT <= LRCK;

end Behavioral;

