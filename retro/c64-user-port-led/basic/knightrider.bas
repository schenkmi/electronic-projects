10 rem knight-rider on user port pb0..pb7
20 data 56577,56579 : rem addrs $dd01,$dd03 (port b data, ddrb)
30 read a,b : dp=a : dd=b
40 rem set ddrb to all outputs (255)
50 poke dd,255
60 rem start pattern (one led at a time)
70 p=1 : d=1 : rem p holds bit pattern, d is direction (1 right, -1 left)
80 poke dp,p : rem write pattern to pb0..pb7
90 for t=1 to 200 : next t : rem delay loop (tune for speed)
100 if d=1 then gosub 200
110 if d=-1 then gosub 300
120 goto 80
200 rem shift right
210 if p>=128 then d=-1 : return
220 p=p*2 : return
300 rem shift left
310 if p<=1 then d=1 : return
320 p=p/2 : return
