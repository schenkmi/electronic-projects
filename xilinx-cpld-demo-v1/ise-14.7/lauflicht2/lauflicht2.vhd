----------------------------------------------------------------------------------
-- Company: 
-- Engineer: 
-- 
-- Create Date:    06:52:09 05/06/2021 
-- Design Name: 
-- Module Name:    lauflicht2 - Behavioral 
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

library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.NUMERIC_STD.ALL;

entity Lauflicht is
    Port ( clk : in  STD_LOGIC;
           leds : out  STD_LOGIC_VECTOR (7 downto 0));
end Lauflicht;

architecture Behavioral of Lauflicht is
  constant fclk    : integer := 50000;
  signal clkdiv    : integer range 0 to fclk/2000 := 0;-- PWM Frequenz: 2000 Hz / 16 Schritte = 125 Hz
  signal nextled   : integer range 0 to 5000/3 := 0;   -- Weiterschalten mit 3Hz
  signal idx       : integer range 0 to 13 := 0;       -- Index
  signal pwmcnt    : integer range 0 to 15 := 0;       -- PWM Zähler
  signal ledbright : std_logic_vector( 7 downto 0); -- die hellen LEDs
  signal leddimmed : std_logic_vector( 7 downto 0); -- die etwas dunkler nachleuchtenden LEDs
  signal ledglow   : std_logic_vector( 7 downto 0); -- die gerade noch so nachleuchtenden LEDs
  
begin
   
   process
     type Rom is array (0 to 13) of std_logic_vector(7 downto 0); 
     constant ledarray : Rom := ("10000000",
                                 "01000000",
                                 "00100000",
                                 "00010000",
                                 "00001000",
                                 "00000100",
                                 "00000010",
                                 "00000001",
                                 "00000010",
                                 "00000100",
                                 "00001000",
                                 "00010000",
                                 "00100000",
                                 "01000000");
   begin
      wait until rising_edge(clk);
      if (clkdiv<fclk/5000) then  -- Taktteiler 
         clkdiv<=clkdiv+1;
      else
         clkdiv<=0;
         if (nextled<5000/3) then -- Bitmuster verwalten
            nextled <= nextled+1;
         else
            nextled <= 0;
            if (idx<13) then idx<=idx+1;
            else             idx<=0;
            end if;
            ledglow   <= leddimmed;
            leddimmed <= ledbright;
            ledbright <= ledarray(idx);
         end if;
         if (pwmcnt<15) then      -- PWM für gedimmte LEDs
            pwmcnt <= pwmcnt+1;
         else
            pwmcnt <= 0;
         end if;
      end if;
   end process;
      
   leds <= ledbright or leddimmed or ledglow when pwmcnt < 4 else
           ledbright or leddimmed            when pwmcnt < 8 else
           ledbright;
           
end Behavioral;
