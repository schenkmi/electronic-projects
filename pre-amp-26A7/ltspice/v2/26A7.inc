*
*
* 26A7.lib spice models:
*
* 26A7_SA_triode	parallel sections
* 26A7_SA_G2		parallel sections
* 26A7_rca_triode	single section
* 26A7_PM_triode	parallel sections
*
* indirect heating 26V / 600mA
* Va max=Vg2 max=50V
* Pa=2W			each section
* Pg2=0.5W		each section
* Ia max=20mA		each section
* Ig2 max=1.9mA		each section
*
*
*
**** 26A7 triode ******************************************
* Created on 12/19/2025 01:17 using paint_kit.jar 3.1 
* www.dmitrynizh.com/tubeparams_image.htm
* Plate Curves image file: SmokingAmp measurements
* Data source link: diyaudio forum 
*----------------------------------------------------------------------------------
.SUBCKT 26A7_SA_triode 1 2 3 ; Plate Grid Cathode
+ PARAMS: CCG=32P  CGP=2.4P CCP=26P RGI=2000
+ MU=3.6 KG1=495 KP=10.09 KVB=15 VCT=0.19 EX=1.736 
* Vp_MAX=110 Ip_MAX=90 Vg_step=2.5 Vg_start=2.5 Vg_count=16
* Rp=2000 Vg_ac=3 P_max=5 Vg_qui=-12 Vp_qui=50
* X_MIN=60 Y_MIN=36 X_SIZE=845 Y_SIZE=664 FSZ_X=1694 FSZ_Y=776 XYGrid=true
* showLoadLine=y showIp=y isDHT=n isPP=n isAsymPP=n showDissipLimit=y 
* showIg1=n gridLevel2=n isInputSnapped=n  
* XYProjections=y harmonicPlot=y dissipPlot=y 
*----------------------------------------------------------------------------------
E1 7 0 VALUE={V(1,3)/KP*LOG(1+EXP(KP*(1/MU+(VCT+V(2,3))/SQRT(KVB+V(1,3)*V(1,3)))))} 
RE1 7 0 1G  ; TO AVOID FLOATING NODES
G1 1 3 VALUE={(PWR(V(7),EX)+PWRS(V(7),EX))/KG1} 
RCP 1 3 1G   ; TO AVOID FLOATING NODES
C1 2 3 {CCG} ; CATHODE-GRID 
C2 2 1 {CGP} ; GRID=PLATE 
C3 1 3 {CCP} ; CATHODE-PLATE 
D3 5 3 DX ; POSITIVE GRID CURRENT 
R1 2 5 {RGI} ; POSITIVE GRID CURRENT 
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N) 
.ENDS 26A7_SA_triode
*$
*
*
*
**** 26A7 G2 input ******************************************
* Created on 12/19/2025 01:32 using paint_kit.jar 3.1 
* www.dmitrynizh.com/tubeparams_image.htm
* Plate Curves image file: SmokingAmp measurements
* Data source link: diyaudio forum
* Capacitances left as in triode mode BUT in this G2 input mode Cs are different!!!
*----------------------------------------------------------------------------------
.SUBCKT 26A7_SA_G2 1 2 3 ; Plate Grid Cathode
+ PARAMS: CCG=32P  CGP=2.4P CCP=26P RGI=2000
+ MU=17.71 KG1=618.75 KP=174 KVB=43.5 VCT=1.011 EX=1.111 
* Vp_MAX=130 Ip_MAX=20 Vg_step=1 Vg_start=1 Vg_count=16
* Rp=6000 Vg_ac=1 P_max=5 Vg_qui=-2 Vp_qui=50
* X_MIN=59 Y_MIN=-11 X_SIZE=1000 Y_SIZE=740 FSZ_X=1694 FSZ_Y=843 XYGrid=true
* showLoadLine=y showIp=y isDHT=n isPP=n isAsymPP=n showDissipLimit=y 
* showIg1=n gridLevel2=n isInputSnapped=n  
* XYProjections=y harmonicPlot=y dissipPlot=y 
*----------------------------------------------------------------------------------
E1 7 0 VALUE={V(1,3)/KP*LOG(1+EXP(KP*(1/MU+(VCT+V(2,3))/SQRT(KVB+V(1,3)*V(1,3)))))} 
RE1 7 0 1G  ; TO AVOID FLOATING NODES
G1 1 3 VALUE={(PWR(V(7),EX)+PWRS(V(7),EX))/KG1} 
RCP 1 3 1G   ; TO AVOID FLOATING NODES
C1 2 3 {CCG} ; CATHODE-GRID 
C2 2 1 {CGP} ; GRID=PLATE 
C3 1 3 {CCP} ; CATHODE-PLATE 
D3 5 3 DX ; POSITIVE GRID CURRENT 
R1 2 5 {RGI} ; POSITIVE GRID CURRENT 
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N) 
.ENDS 26A7_SA_G2
*$
*
*
*
**** 26A7 rca riode ******************************************
* Created on 12/23/2025 20:05 using paint_kit.jar 3.1 
* www.dmitrynizh.com/tubeparams_image.htm
* Plate Curves image file: rca triode chrs
* Data source link: frank 
*----------------------------------------------------------------------------------
.SUBCKT 26A7_rca_triode 1 2 3 ; Plate Grid Cathode
+ PARAMS: CCG=16P  CGP=1.2P CCP=13P RGI=2000
+ MU=3.95 KG1=451.05 KP=13.77 KVB=58.8 VCT=0.512 EX=1.305 
* Vp_MAX=55 Ip_MAX=70 Vg_step=3 Vg_start=3 Vg_count=11
* Rp=1000 Vg_ac=2.85 P_max=2.5 Vg_qui=-3 Vp_qui=35
* X_MIN=50 Y_MIN=110 X_SIZE=821 Y_SIZE=525 FSZ_X=1636 FSZ_Y=733 XYGrid=true
* showLoadLine=y showIp=y isDHT=n isPP=n isAsymPP=n showDissipLimit=y 
* showIg1=n gridLevel2=n isInputSnapped=n  
* XYProjections=y harmonicPlot=y dissipPlot=y 
*----------------------------------------------------------------------------------
E1 7 0 VALUE={V(1,3)/KP*LOG(1+EXP(KP*(1/MU+(VCT+V(2,3))/SQRT(KVB+V(1,3)*V(1,3)))))} 
RE1 7 0 1G  ; TO AVOID FLOATING NODES
G1 1 3 VALUE={(PWR(V(7),EX)+PWRS(V(7),EX))/KG1} 
RCP 1 3 1G   ; TO AVOID FLOATING NODES
C1 2 3 {CCG} ; CATHODE-GRID 
C2 2 1 {CGP} ; GRID=PLATE 
C3 1 3 {CCP} ; CATHODE-PLATE 
D3 5 3 DX ; POSITIVE GRID CURRENT 
R1 2 5 {RGI} ; POSITIVE GRID CURRENT 
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N) 
.ENDS 26A7_rca_triode
*$
*
*
**** P. Millett MEASUREMENTS ******************************************
* Created on 12/28/2025 11:33 using paint_kit.jar 3.1 
* www.dmitrynizh.com/tubeparams_image.htm
* Plate Curves image file: P.Millett measurements, parallel sections
* Data source link: 
*----------------------------------------------------------------------------------
.SUBCKT 26A7_PM_triode 1 2 3 ; Plate Grid Cathode
+ PARAMS: CCG=32P  CGP=2.4P CCP=26P RGI=2000
+ MU=3.78 KG1=450.45 KP=11.02 KVB=62.4 VCT=1 EX=1.58 
* Vp_MAX=100 Ip_MAX=100 Vg_step=5 Vg_start=5 Vg_count=16
* Rp=2000 Vg_ac=2.86 P_max=5 Vg_qui=-12 Vp_qui=50
* X_MIN=110 Y_MIN=45 X_SIZE=672 Y_SIZE=639 FSZ_X=1570 FSZ_Y=786 XYGrid=true
* showLoadLine=y showIp=y isDHT=n isPP=n isAsymPP=n showDissipLimit=y 
* showIg1=n gridLevel2=n isInputSnapped=n  
* XYProjections=y harmonicPlot=y dissipPlot=y 
*----------------------------------------------------------------------------------
E1 7 0 VALUE={V(1,3)/KP*LOG(1+EXP(KP*(1/MU+(VCT+V(2,3))/SQRT(KVB+V(1,3)*V(1,3)))))} 
RE1 7 0 1G  ; TO AVOID FLOATING NODES
G1 1 3 VALUE={(PWR(V(7),EX)+PWRS(V(7),EX))/KG1} 
RCP 1 3 1G   ; TO AVOID FLOATING NODES
C1 2 3 {CCG} ; CATHODE-GRID 
C2 2 1 {CGP} ; GRID=PLATE 
C3 1 3 {CCP} ; CATHODE-PLATE 
D3 5 3 DX ; POSITIVE GRID CURRENT 
R1 2 5 {RGI} ; POSITIVE GRID CURRENT 
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N) 
.ENDS 26A7_PM_triode
*$
*
*

