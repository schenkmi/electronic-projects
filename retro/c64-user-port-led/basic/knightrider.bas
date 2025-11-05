10 rem knight-rider on user port pb0..pb7
20 data 56577,56579 : rem addrs $dd01,$dd03 (port b data, ddrb)
30 read a,b : dp=a : dd=b
40 poke dd,255 : rem set port b to output
50 p=1 : d=1 : rem start at bit 0, moving right
60 poke dp,p
70 for t=1 to 200 : next t
80 if d=1 then p=p*2 : if p=128 then d=-1 : goto 100
90 if d=-1 then p=p/2 : if p=1 then d=1 : goto 100
100 goto 60
