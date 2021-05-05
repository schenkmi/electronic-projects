----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:48:33 05/05/2021 
-- Design Name: 
-- Module Name:    lauflicht - Behavioral 
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
use IEEE.STD_LOGIC_UNSIGNED.ALL;

-- Uncomment the following library declaration if using
-- arithmetic functions with Signed or Unsigned values
--use IEEE.NUMERIC_STD.ALL;

-- Uncomment the following library declaration if instantiating
-- any Xilinx primitives in this code.
--library UNISIM;
--use UNISIM.VComponents.all;

entity knight_top is
    Port ( CLK : in  STD_LOGIC;
           LED : out  STD_LOGIC_VECTOR (7 downto 0));
end knight_top;

architecture Behavioral of knight_top is

signal clk_div   : std_logic_vector(4 downto 0);
signal shift_reg : std_logic_vector(7 downto 0) := X"01";
signal fwd       : std_logic := '1';

begin

    -- clock divider
	process (CLK)
    begin
        if (CLK'Event and CLK = '1') then
            clk_div <= clk_div + '1';
        end if;
    end process;

	-- knight rider display
    process (clk_div(4))
    begin
        if (clk_div(4)'Event and clk_div(4) = '1') then
            if (fwd = '1') then
                shift_reg <= shift_reg(6 downto 0) & '0';
                if (shift_reg = X"40") then
                    fwd <= '0';
                end if;
            else
                shift_reg <= '0' & shift_reg(7 downto 1);
                if (shift_reg = X"02") then
                    fwd <= '1';
                end if;
            end if;
        end if;
    end process;

	 -- display the result on the LEDs
	 LED <= not shift_reg;

end Behavioral;
