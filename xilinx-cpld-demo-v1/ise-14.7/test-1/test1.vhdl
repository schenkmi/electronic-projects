----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    19:19:46 04/14/2021 
-- Design Name: 
-- Module Name:    test1 - Behavioral 
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


entity test1 is 
  port(C, SI : in  std_logic; 
        SO : out std_logic); 
		  
--    attribute pin_assign : string;
--    attribute pin_assign of C : signal is "38";
--    attribute pin_assign of SI : signal is "37";
--	 attribute pin_assign of SO : signal is "36";
		  
		  
end test1; 
architecture Behavioral of test1 is 
  signal tmp: std_logic_vector(7 downto 0); 
  begin 
    process (C) 
      begin 
        if (C'event and C='1') then 
          for i in 0 to 6 loop 
            tmp(i+1) <= tmp(i); 
          end loop; 
          tmp(0) <= SI; 
        end if; 
    end process; 
    SO <= tmp(7); 
end Behavioral; 



