library IEEE;
use IEEE.std_logic_1164.all;

entity NewAutomat is
  port(
	x1: in STD_LOGIC;
	x2: in STD_LOGIC;
	x3: in STD_LOGIC;
	clk: in STD_LOGIC;
	res: in STD_LOGIC;
	y1: out STD_LOGIC;
	y2: out STD_LOGIC;
	y3: out STD_LOGIC;
	y4: out STD_LOGIC;
	y5: out STD_LOGIC
  );
end NewAutomat;

architecture Automat of NewAutomat is
begin
py3:process(x1, x2, x3)
  begin
	y1 <= (x2);
	y2 <= (not x1 and not x2 and x3);
	y3 <= (not x1 and not x2 and x3) or (x2 and not x3);
	y4 <= (x1) or (x2) or (x3);
	y5 <= (not x1) or (x2) or (x3);
  end process;
end Automat;
