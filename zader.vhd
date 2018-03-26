library IEEE;
use IEEE.std_logic_1164.all;

entity zader is
  port(
	x1: in STD_LOGIC;
	clk: in STD_LOGIC;
	res: in STD_LOGIC;
	z1: out STD_LOGIC
  );
end zader;

architecture Automat of zader is
signal e: STD_LOGIC_VECTOR(5 downto 1);
begin
pe1:process(clk, res)
  begin
	if(res = '1') then
		e(1) <= '0';
	elsif(clk'event and clk = '1') then
		e(1) <= (e(2)  and e(3)  and e(4)  and e(5)  and x1) or (e(1)  and not e(5) ) or (e(1)  and not e(4) ) or (e(1)  and not e(3) ) or (e(1)  and not e(2) );
	end if;
  end process;
pe2:process(clk, res)
  begin
	if(res = '1') then
		e(2) <= '0';
	elsif(clk'event and clk = '1') then
		e(2) <= (not e(1)  and e(2)  and not x1) or (not e(1)  and not e(5)  and x1) or (not e(1)  and not e(4)  and x1) or (not e(1)  and not e(3)  and x1) or (not e(1)  and not e(2)  and x1) or (e(1)  and not e(5)  and not x1) or (e(1)  and not e(4)  and not x1) or (e(1)  and not e(3)  and not x1) or (e(1)  and not e(2)  and not x1);
	end if;
  end process;
pe3:process(clk, res)
  begin
	if(res = '1') then
		e(3) <= '0';
	elsif(clk'event and clk = '1') then
		e(3) <= (not e(1)  and e(2)  and e(3)  and not x1) or (not e(1)  and e(2)  and not e(5)  and x1) or (not e(1)  and e(2)  and not e(4)  and x1) or (not e(1)  and e(2)  and not e(3)  and x1) or (e(1)  and e(2)  and not e(5)  and not x1) or (e(1)  and e(2)  and not e(4)  and not x1) or (e(1)  and e(2)  and not e(3)  and not x1);
	end if;
  end process;
pe4:process(clk, res)
  begin
	if(res = '1') then
		e(4) <= '0';
	elsif(clk'event and clk = '1') then
		e(4) <= (not e(1)  and e(2)  and e(3)  and e(4)  and not x1) or (not e(1)  and e(2)  and e(3)  and not e(5)  and x1) or (not e(1)  and e(2)  and e(3)  and not e(4)  and x1) or (e(1)  and e(2)  and e(3)  and not e(5)  and not x1) or (e(1)  and e(2)  and e(3)  and not e(4)  and not x1);
	end if;
  end process;
pe5:process(clk, res)
  begin
	if(res = '1') then
		e(5) <= '0';
	elsif(clk'event and clk = '1') then
		e(5) <= (not e(1)  and e(2)  and e(3)  and e(4)  and e(5)  and not x1) or (not e(1)  and e(2)  and e(3)  and e(4)  and not e(5)  and x1) or (e(1)  and e(2)  and e(3)  and e(4)  and not e(5)  and not x1);
	end if;
  end process;

pz:process(e)
  begin
	z1 <= e(1);
  end process;
end Automat;
