*
* Generic triode model: 6BM8PT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:18 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 6BM8PT A G K
BGG   GG   0 V=V(G,K)+0.90753334
BM1   M1   0 V=(0.058205333*(URAMP(V(A,K))+1e-10))^-0.96337515
BM2   M2   0 V=(0.60892065*(URAMP(V(GG)+URAMP(V(A,K))/6.7189608)+1e-10))^2.4633752
BP    P    0 V=0.0032859022*(URAMP(V(GG)+URAMP(V(A,K))/11.034214)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0021448732*V(M1)*V(M2)
BIG   IG   0 V=0.0016429511*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.002099612*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3.9p
CGK   G    K 5.4p
CAK   A    K 7.7p
.ENDS
