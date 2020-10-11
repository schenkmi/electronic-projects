* 6SN7GTB Triode PSpice Model                    8/96, Rev. 1.0  (fp)
*
* -------------------------------------------------------------------
*  This model is provided "as is", with no warranty of any kind,
*  either expressed or implied, about the suitability or fitness
*  of this model for any particular purpose.  Use of this model
*  shall be entirely at the user's own risk.
*
*  For a discussion about vacuum tube modeling please refer to:
*  W. Marshall Leach, jr: "SPICE Models for Vacuum-Tube Amplifiers";
*  J. Audio Eng. Soc., Vol 43, No 3, March 1995.
* -------------------------------------------------------------------
*
* This model is valid for the following tubes:
* 6SN7GTB, ECC32, 6FQ7/6CG7, 5692;
* at the following conditions:
*  Plate voltage  : 0..450V
*  Grid voltage   : 0..-18V
*  Cathode current: 0..30mA
*
*
*  Connections: Plate
*               | Grid
*               | | Cathode
*               | | |
.SUBCKT 6SN7GTB P G K
E1  2  0  VALUE={V(P,K)+20.43*V(G,K)}
R1  2  0  1.0K
Gp  P  K  VALUE={10.89E-6*(PWR(V(2),1.5)+PWRS(V(2),1.5))/2}
Cgk G  K  2.4P
Cgp G  P  4.0P
Cpk P  K  0.7P
.ENDS 6SN7GTB

* 6SN7 Triode PSpice Model
* copyright (c) 1998 Mithat Konar -- all rights reserved
* copyright (c) 2001 Teodoro Marinucci  -- all rights reserved
*
* Model used: "Improved VT Models for SPICE Simulations,"
*     Norman Koren, Glass Audio 5/96.
* Plate parameters determined by computerized optimization using Excel XP and Solver, Aug 13, 2001.
* Plate data from http://www.mclink.it/com/audiomatica/sofia/.
* Interelectrode capacitances are based on data found on http://www.duncanamps.co.uk/cgi-bin/tdsl3.exe/;
* however, the reliability of the HF characteristics for this model is probably
* not very high. It is likely that that additional complexity will be required
* to better model the HF behavior--including the inclusion of heater terminals
* in order to explicitly incorporate grid, plate, and cathode to heater
* capacitances. And don't forget to add parasitic capacitances of ~0.7 pF
* for adjacent pins and ~0.5 pF for others (see Koren's article) as well as for
* the effects of a shield (if used).
* No guarantees of any kind are made regarding the accuracy or suitability
* of any part of this model. Use at your own risk.
*
* Connections: Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 6SN7   1 2 3
+ PARAMS: MU=22.23 EX=1.31 KG1=668.85 KP=179.77 KVB=243.78
+ RGI=2000
+ CCG=2.6P CGP=4.1P CCP=0.8P

E1	7 	0	VALUE={V(1,3)/KP*LOG(1+EXP(KP*(1/MU+V(2,3)/SQRT(KVB+V(1,3)*V(1,3)))))}
RE1	7	0	1G
G1	1	3	VALUE={ (PWR(V(7),EX)+PWRS(V(7), EX))/(2*KG1) }
RCP	1	3	1G	; TO AVOID FLOATING NODES IN MU-FOLLOWER
C1	2	3	{CCG}	; CATHODE GRID
C2	2	1	{CGP}	; GRID-PLATE
C3	1	3	{CCP}	; CATHODE-PLATE
D3	5	3	DX	; FOR GRID CURRENT
R1	2	5	{RGI}	; FOR GRID CURRENT
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N)
.ENDS



**********************
.subckt 6sn7i 1 2 3 ; placca griglia catodo
+ params: mu=21 ex=1.36 kg1=1460 kp=150 kvb=400 rgi=300
+ ccg=2.4p cgp=4p ccp=.7p
e1 7 0 value=
+{v(1,3)/kp*log(1+exp(kp*(1/mu+v(2,3)/sqrt(kvb+v(1,3)*v(1,3)))))}
re1 7 0 1g
g1 1 3 value= {(pwr(v(7),ex)+pwrs(v(7),ex))/kg1}
rcp 1 3 1g
c1 2 3 {ccg}
c2 1 2 {cgp}
c3 1 3 {ccp}
r1 2 5 {rgi}
d3 5 3 dx
.model dx d(is=1n rs=1 cjo=10pf tt=1n)
.ends

.subckt 6sn7ii 1 2 3 ; placca griglia catodo   
+ params: mu=22.004 ex=1.2128 kg1=1213.7 kp=203.06 kvb=355 rgi=2k
+ ccg=2.4p cgp=4p ccp=.7p
e1 7 0 value=
+{v(1,3)/kp*log(1+exp(kp*(1/mu+v(2,3)/sqrt(kvb+v(1,3)*v(1,3)))))}
re1 7 0 1g
g1 1 3 value= {(pwr(v(7),ex)+pwrs(v(7),ex))/kg1}
rcp 1 3 1g
c1 2 3 {ccg}
c2 1 2 {cgp}
c3 1 3 {ccp}
r1 2 5 {rgi}
d3 5 3 dx
.model dx d(is=1n rs=1 cjo=10pf tt=1n)
.ends


********************************************
* Duncan's Models
************************************************************************
.SUBCKT TRIODENH A G K
+PARAMS: LIP=1 LIF=3.7E-3 RAF=18E-3 RAS=1 CDO=0 RAP=4E-3
+ ERP=1.5 ERI=0
+ MU0=17.3 MUR=19E-3 EMC=9.6E-6 GCO=0 GCF=213E-6
+ CGA=3.9p CGK=2.4p CAK=0.7p
************************************************************************
*
* Anode/grid model
*
* Models reduction in mu at large negative grid voltages
* Models change in Ra with negative grid voltages
* Models limit in Ia with high +Vg and low Va
*
* PARAMETERS
*
* LIP Conduction limit exponent
* LIF Conduction limit factor
* CDO Conduction offset
* RAF Anode resistance factor for neg grid voltages
* RAP Anode resistance factor for positive grid voltages
* ERP Emission power
* ERI Emission power increase
* MU0 Mu between grid and anode at Vg=0
* MUR Mu reduction factor for large negative grid voltages
* EMC Emission coefficient
* GCO Grid current offset in volts
* GCF Grid current scale factor
*
************************************************************************
Elim LI 0 VALUE {PWR(LIMIT{V(A,K),0,1E6},{LIP})*{LIF}}
Egg GG 0 VALUE {V(G,K)-{CDO}}
Erpf RP 0 VALUE {1-PWR(LIMIT{-V(GG)*{RAF},0,0.999},{RAS})+LIMIT{V(GG),0,1E6}*{RAP}}
Egr GR 0 VALUE {LIMIT{V(GG),0,1E6}+LIMIT{(V(GG))*(1+V(GG)*{MUR}),0,-1E6}}
Eem EM 0 VALUE {LIMIT{V(A,K)+V(GR)*{MU0},0,1E6}}
Eep EP 0 VALUE {PWR(V(EM),ERP-LIMIT{V(G,K),0,-1E6}*ERI)*{EMC}*V(RP)}
Eel EL 0 VALUE {LIMIT{V(EP),0,V(LI)}}
Eld LD 0 VALUE {LIMIT{V(EP)-V(LI),0,1E6}}
Ga A K VALUE {V(EL)}
************************************************************************
*
* Grid current model
*
* Models grid current, along with rise in grid current at low Va
*
************************************************************************
Egf GF 0 VALUE {PWR(LIMIT{V(GG),0,1E6},1.5)*{GCF}}
Gg G K VALUE {(V(GF)+V(LD))}
*
* Capacitances and anti-float resistors
*
CM1 G K {CGK}
CM2 A G {CGA}
CM3 A K {CAK}
RF1 A 0 1000MEG
RF2 G 0 1000MEG
RF3 K 0 1000MEG
.ENDS
**********************************************************************
* GENERIC: 2A3
* MODEL: NH2A3
* NOTES: No heater model (virtual cathode)
**********************************************************************
.SUBCKT NH2A3 A G K
XV1 A G K TRIODENH
+PARAMS: LIP= 1.5 LIF= 0.003 RAF= 0.0045 RAS= 1 CDO= 0
+ RAP= 0.005 ERP= 1.6247 ERI=-0.000019
+ MU0= 3.7731 MUR= 0.004685 EMC= 0.0000615
+ GCO= 0 GCF= 0.0001
+ CGA=1.65E-11 CGK=7.50E-12 CAK=5.50E-12
.ENDS
**********************************************************************
* GENERIC: 3CX300
* MODEL: NH3CX300
* NOTES: No heater model
**********************************************************************
.SUBCKT NH3CX300 A G K
XV1 A G K TRIODENH
+PARAMS: LIP= 1.5 LIF= 10 RAF= 0.00473 RAS= 1 CDO= 0
+ RAP= 0.005 ERP= 1.25 ERI=-0.00053
+ MU0= 8.321 MUR= 0.0012 EMC= 0.000533
+ GCO= 0 GCF= 0.0001
+ CGA=1.00E-11 CGK=2.50E-11 CAK=1.00E-12
.ENDS
**********************************************************************
* GENERIC: SV6AS7
* MODEL: NHSV6AS7
* NOTES: No heater model
**********************************************************************
.SUBCKT NHSV6AS7 A G K
XV1 A G K TRIODENH
+PARAMS: LIP= 1 LIF= 0.01 RAF= 0.0058 RAS= 0.7 CDO= 0
+ RAP= 0.035 ERP= 1.5 ERI= 0
+ MU0= 2.05 MUR= 0.0017 EMC= 0.0005
+ GCO= 0 GCF= 0
+ CGA=1.10E-11 CGK=8.00E-12 CAK=3.00E-12
.ENDS
**********************************************************************
* GENERIC: 6SN7GTB
* MODEL: NH6SN7GTB
* NOTES: No heater model
**********************************************************************
.SUBCKT NH6SN7GTB A G K
XV1 A G K TRIODENH
+PARAMS: LIP= 1 LIF= 0.0037 RAF= 0.03 RAS= 2 CDO= 0
+ RAP= 0.002 ERP= 1.4 ERI= 0.007
+ MU0= 19.2642 MUR= 0.007677 EMC= 0.0000189
+ GCO= 0 GCF= 0.000213
+ CGA=3.90E-12 CGK=2.40E-12 CAK=7.00E-13
.ENDS

* GL211 Triode PSpice Model                      9/96, Rev. 1.0  (fp)
*
* -------------------------------------------------------------------
*  This model is provided "as is", with no warranty of any kind,
*  either expressed or implied, about the suitability or fitness
*  of this model for any particular purpose.  Use of this model
*  shall be entirely at the user's own risk.
*
*  For a discussion about vacuum tube modeling please refer to:
*  W. Marshall Leach, jr: "SPICE Models for Vacuum-Tube Amplifiers";
*  J. Audio Eng. Soc., Vol 43, No 3, March 1995.
* -------------------------------------------------------------------
*
* This model is valid for the following tubes:
* GL211, VT4C;
* at the following conditions:
*  Plate voltage  :  0..2200V (grid negative),
*                   100..700V (grid positive) (1)
*  Grid voltage   : +50..-180V (2)
*  Cathode current: 0..200mA
*
* (1) Plate current decrease and grid current increase at low plate
*     voltage are not modeled.
* (2) Since no data was available, grid current modeling is only 
*     approximate. Adjust Gg if required.
*
*
* Connections: Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT GL211  P G K
E1  2  0  VALUE={V(P,K)+12.11*V(G,K)}
R1  2  0  1.0K
Gp  P  K  VALUE={9.39E-6*(PWR(V(2),1.5)+PWRS(V(2),1.5))/2}
Gg  G  K  VALUE={358E-6*(PWR(V(G,K),1.5)+PWRS(V(G,K),1.5))/2}
Cgk G  K  6.0P
Cgp G  P  14.5P
Cpk P  K  5.5P
.ENDS GL211

.subckt VT4C 1 3 4 ; TRIODO DI POTENZA D.H.T. ( G.E.)
g1 2 4 value = {(exp(1.5*(log((v(2,4)/12)+v(3,4)))))/3010}
c1 3 4 6p
c2 3 1 14.5p
c3 1 4 5.5p
r1 3 5 10k
d1 1 2 dx
d2 4 2 dx2
d3 5 4 dx
.model dx d(is=1p rs=1)
.model dx2 d(is=1n rs=1)
.ends VT4C ; eq. 211A

* E88CC Triode PSpice Model
* copyright (c) 1998 Mithat Konar -- all rights reserved
* copyright (c) 2001 Teodoro Marinucci  -- all rights reserved
*
* Model used: "Improved VT Models for SPICE Simulations,"
*     Norman Koren, Glass Audio 5/96.
* Plate parameters determined by computerized optimization using Excel XP and Solver, Aug 13, 2001.
* Plate data from http://www.mclink.it/com/audiomatica/sofia/.
* Interelectrode capacitances are based on data found on http://www.duncanamps.co.uk/cgi-bin/tdsl3.exe/;
* however, the reliability of the HF characteristics for this model is probably
* not very high. It is likely that that additional complexity will be required
* to better model the HF behavior--including the inclusion of heater terminals
* in order to explicitly incorporate grid, plate, and cathode to heater
* capacitances. And don't forget to add parasitic capacitances of ~0.7 pF
* for adjacent pins and ~0.5 pF for others (see Koren's article) as well as for
* the effects of a shield (if used).
* No guarantees of any kind are made regarding the accuracy or suitability
* of any part of this model. Use at your own risk.
*
* Connections: Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT E88CC  1 2 3
+ PARAMS: MU=36.34 EX=1.35 KG1=129.3 KP=292.92 KVB=217.61
+ RGI=2000
+ CCG=3.1P CGP=1.4P CCP=0.18P ; http://www.jj-electronic.sk/tube_e88cc.htm

E1	7 	0	VALUE={V(1,3)/KP*LOG(1+EXP(KP*(1/MU+V(2,3)/SQRT(KVB+V(1,3)*V(1,3)))))}
RE1	7	0	1G
G1	1	3	VALUE={ (PWR(V(7),EX)+PWRS(V(7), EX))/(2*KG1) }
RCP	1	3	1G	; TO AVOID FLOATING NODES IN MU-FOLLOWER
C1	2	3	{CCG}	; CATHODE GRID
C2	2	1	{CGP}	; GRID-PLATE
C3	1	3	{CCP}	; CATHODE-PLATE
D3	5	3	DX	; FOR GRID CURRENT
R1	2	5	{RGI}	; FOR GRID CURRENT
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N)
.ENDS

.SUBCKT EL34 1 2 3 4 ;  P G1 C G2
+ PARAMS: MU=11 EX=1.35 KG1=650 KG2=4200 KP=60 KVB=24
+         CCG=15P CPG1=1P CCP=8P RGI=1K 
RE1  7 0  1MEG    ; DUMMY SO NODE 7 HAS 2 CONNECTIONS
E1   7 0  VALUE=  ; E1 BREAKS UP LONG EQUATION FOR G1.
+{V(4,3)/KP*LOG(1+EXP((1/MU+V(2,3)/V(4,3))*KP))}
G1   1 3  VALUE={(PWR(V(7),EX)+PWRS(V(7),EX))/KG1*ATAN(V(1,3)/KVB)}
G2     4 3  VALUE={(EXP(EX*(LOG((V(4,3)/MU)+V(2,3)))))/KG2}
RCP  1 3  1G      ; FOR CONVERGENCE
C1   2 3  {CCG}   ; CATHODE-GRID 1
C2   1 2  {CPG1}  ; GRID 1-PLATE
C3   1 3  {CCP}   ; CATHODE-PLATE
R1   2 5  {RGI}   ; FOR GRID CURRENT
D3   5 3  DX      ; FOR GRID CURRENT
.MODEL DX D(IS=1N RS=1 CJO=10PF TT=1N)
.ENDS

