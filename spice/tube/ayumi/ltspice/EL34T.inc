*
* Generic triode model: EL34T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:48 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT EL34T A G K
BGG   GG   0 V=V(G,K)+0.29360503
BM1   M1   0 V=(0.040003405*(URAMP(V(A,K))+1e-10))**-0.73308055
BM2   M2   0 V=(0.67171782*(URAMP(V(GG)+URAMP(V(A,K))/8.2063559)+1e-10))**2.2330806
BP    P    0 V=0.0033402929*(URAMP(V(GG)+URAMP(V(A,K))/12.216969)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0019762451*V(M1)*V(M2)
BIG   IG   0 V=0.0016701465*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0020885491*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.2p
CGK   G    K 9.1p
CAK   A    K 8.4p
.ENDS
