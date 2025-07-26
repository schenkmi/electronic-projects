*
* Generic triode model: 6RA3
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:45 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6RA3 A G K
BGG   GG   0 V=V(G,K)+0.99999995
BM1   M1   0 V=(0.17083943*(URAMP(V(A,K))+1e-10))^-1.0578391
BM2   M2   0 V=(0.5864325*(URAMP(V(GG)+URAMP(V(A,K))/2.4207966)+1e-10))^2.5578391
BP    P    0 V=0.0037228747*(URAMP(V(GG)+URAMP(V(A,K))/4.1280055)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0025729671*V(M1)*V(M2)
BIG   IG   0 V=0.0018614373*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0032931125*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5.2p
CGK   G    K 6.9p
CAK   A    K 5.4p
.ENDS
