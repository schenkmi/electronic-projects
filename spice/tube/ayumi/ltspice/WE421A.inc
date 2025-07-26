*
* Generic triode model: WE421A
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:13 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT WE421A A G K
BGG   GG   0 V=V(G,K)+0.99947463
BM1   M1   0 V=(0.16037928*(URAMP(V(A,K))+1e-10))**-1.9202159
BM2   M2   0 V=(0.4385688*(URAMP(V(GG)+URAMP(V(A,K))/3.5006467)+1e-10))**3.4202159
BP    P    0 V=0.0067402387*(URAMP(V(GG)+URAMP(V(A,K))/7.9819784)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.010830172*V(M1)*V(M2)
BIG   IG   0 V=0.0033701193*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0046756479*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 8.6p
CGK   G    K 6p
CAK   A    K 2.2p
.ENDS
