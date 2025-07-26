*
* Generic triode model: 350BT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:53 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 350BT A G K
BGG   GG   0 V=V(G,K)+0.99999998
BM1   M1   0 V=(0.060793226*(URAMP(V(A,K))+1e-10))^-0.90421858
BM2   M2   0 V=(0.62390334*(URAMP(V(GG)+URAMP(V(A,K))/6.1864896)+1e-10))^2.4042186
BP    P    0 V=0.0019265247*(URAMP(V(GG)+URAMP(V(A,K))/9.9157821)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0012190211*V(M1)*V(M2)
BIG   IG   0 V=0.00096326237*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0012619241*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 6.7p
CGK   G    K 9.3p
CAK   A    K 7.5p
.ENDS
