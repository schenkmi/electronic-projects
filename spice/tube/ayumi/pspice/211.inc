*
* Generic triode model: 211
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:51 2008
*           Plate
*           | Grid
*           | | Cathode
*           | | |
.SUBCKT 211 A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.0021297199*(URAMP(V(A,K))+1e-10))^-0.038461562
BM2   M2   0 V=(0.97499998*(URAMP(V(GG)+URAMP(V(A,K))/11.73864)+1e-10))^1.5384616
BP    P    0 V=0.00045306372*(URAMP(V(GG)+URAMP(V(A,K))/12.039631)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00039351788*V(M1)*V(M2)
BIG   IG   0 V=0.00011014965*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00041468102*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 14p
CGK   G    K 5.4p
CAK   A    K 4.8p
.ENDS
