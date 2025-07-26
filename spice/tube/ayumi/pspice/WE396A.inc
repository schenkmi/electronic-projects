*
* Generic triode model: WE396A
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:12 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT WE396A A G K
BGG   GG   0 V=V(G,K)+0.052879817
BM1   M1   0 V=(0.014753653*(URAMP(V(A,K))+1e-10))^-0.87734793
BM2   M2   0 V=(0.63095518*(URAMP(V(GG)+URAMP(V(A,K))/25.013793)+1e-10))^2.3773479
BP    P    0 V=0.0026962883*(URAMP(V(GG)+URAMP(V(A,K))/39.644326)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0016842826*V(M1)*V(M2)
BIG   IG   0 V=0.0013481441*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0014508027*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.3p
CGK   G    K 2.2p
CAK   A    K 1p
.ENDS
