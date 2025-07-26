*
* Generic pentode model: E83F
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:32 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT E83F A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.67775811
BM1   M1   0 V=(0.012440248*(URAMP(V(G2,K))+1e-10))^-0.83377528
BM2   M2   0 V=(0.6427354*(URAMP(V(GG)+URAMP(V(G2,K))/28.718446)))^2.3337753
BP    P    0 V=0.0069226192*(URAMP(V(GG)+URAMP(V(G2,K))/44.6816))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0042425066*V(M1)*V(M2)
BIG   IG   0 V=0.0034613096*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.81925243*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.18074757)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+9975)/(URAMP(V(G2,K))+9975)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0036950034*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0036950034*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.015p
CGK   G1  K  4.8p
C12   G1  G2 3.2p
CAK   A   K  3.5p
.ENDS
