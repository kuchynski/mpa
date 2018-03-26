library IEEE;
use IEEE.std_logic_1164.all;

entity indicate2 is
  port(
	x1: in STD_LOGIC;
	clk: in STD_LOGIC;
	res: in STD_LOGIC;
	z1: out STD_LOGIC;
	z2: out STD_LOGIC;
	y1: out STD_LOGIC;
	y2: out STD_LOGIC;
	y3: out STD_LOGIC;
	y4: out STD_LOGIC;
	y5: out STD_LOGIC;
	y6: out STD_LOGIC;
	y7: out STD_LOGIC
  );
end indicate2;

architecture Automat of indicate2 is
signal e: STD_LOGIC_VECTOR(2 downto 1);
begin
pe1:process(clk, res)
  begin
	if(res = '1') then
		e(1) <= '0';
	elsif(clk'event and clk = '1') then
		e(1) <= (not e(1) );
	end if;
  end process;
pe2:process(clk, res)
  begin
	if(res = '1') then
		e(2) <= '0';
	elsif(clk'event and clk = '1') then
		e(2) <= (e(1)  and not e(2) ) or (not e(1)  and e(2) );
	end if;
  end process;

pz:process(e)
  begin
	z1 <= e(1);
	z2 <= e(2);
  end process;
 y6 <= '0';
py1:process(e, x1)
  begin
	y1 <= (not e(2) );
	y2 <= (e(1) ) or (e(2) );
	y3 <= (e(1) );
	y4 <= (e(1)  and not e(2) );
	y5 <= (not e(1)  and e(2) );
	y7 <= (e(1)  and not e(2) );
  end process;
end Automat;
