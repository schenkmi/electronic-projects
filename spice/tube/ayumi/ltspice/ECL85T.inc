*
* Generic triode model: ECL85T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Wed Oct 22 16:34:55 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT ECL85T A G K
BGG   GG   0 V=V(G,K)+0.53083873
BM1   M1   0 V=(0.0093163171*(URAMP(V(A,K))+1e-10))**-0.90408466
BM2   M2   0 V=(0.6239381*(URAMP(V(GG)+URAMP(V(A,K))/40.365941)+1e-10))**2.4040847
BP    P    0 V=0.0035136299*(URAMP(V(GG)+URAMP(V(A,K))/64.695426)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0022231252*V(M1)*V(M2)
BIG   IG   0 V=0.0017568149*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0018385944*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 2.7p
CAK   A    K 4p
.ENDS
