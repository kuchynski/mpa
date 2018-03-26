library IEEE;
use IEEE.std_logic_1164.all;

entity BelKoleso is
  port(
	BK1: in STD_LOGIC;
	BK2: in STD_LOGIC;
	clk: in STD_LOGIC;
	res: in STD_LOGIC;
	BK_PLUS: out STD_LOGIC;
	BK_MINUS: out STD_LOGIC;
	NEW_KOORDINAT: out STD_LOGIC
  );
end BelKoleso;

architecture Automat of BelKoleso is
signal e: STD_LOGIC_VECTOR(5 downto 1);
begin
pe1:process(clk, res)
  begin
	if(res = '1') then
		e(1) <= '0';
	elsif(clk'event and clk = '1') then
		e(1) <= (e(2) and not e(3) and e(4) and not BK1and BK2) or (not e(2) and not e(4) and BK1and not BK2) or (e(1) and not e(3) and e(4) and not BK1) or (e(1) and not e(4) and BK1) or (e(1) and e(3) and BK1) or (e(1) and e(3) and not e(4) ) or (e(1) and BK2);
	end if;
  end process;
pe2:process(clk, res)
  begin
	if(res = '1') then
		e(2) <= '0';
	elsif(clk'event and clk = '1') then
		e(2) <= (not e(1) and e(2) and not e(3) and e(4) and not BK2) or (e(1) and not e(3) and e(4) and BK1and not BK2) or (not e(1) and not e(4) and not BK1and BK2) or (not e(1) and e(2) and e(3) and BK2) or (not e(1) and e(2) and e(3) and not e(4) ) or (not e(1) and e(2) and BK1);
	end if;
  end process;
pe3:process(clk, res)
  begin
	if(res = '1') then
		e(3) <= '0';
	elsif(clk'event and clk = '1') then
		e(3) <= (e(1) and not e(3) and not e(4) and BK1and BK2) or (e(2) and not e(3) and not e(4) and BK1and BK2) or (e(1) and e(4) and BK1and not BK2) or (e(1) and e(4) and not BK1and BK2) or (e(2) and e(4) and BK1and not BK2) or (e(2) and e(4) and not BK1and BK2);
	end if;
  end process;
pe4:process(clk, res)
  begin
	if(res = '1') then
		e(4) <= '0';
	elsif(clk'event and clk = '1') then
		e(4) <= (e(1) and e(4) ) or (e(1) and e(3) ) or (e(2) and e(4) ) or (e(2) and e(3) );
	end if;
  end process;
pe5:process(clk, res)
  begin
	if(res = '1') then
		e(5) <= '0';
	elsif(clk'event and clk = '1') then
		e(5) <= (not e(1) and e(2) and e(3) and e(4) and not BK1and not BK2);
	end if;
  end process;

pz:process(e)
  begin
	BK_PLUS <= e(1);
	BK_MINUS <= e(2);
	NEW_KOORDINAT <= e(3);
  end process;
end Automat;
