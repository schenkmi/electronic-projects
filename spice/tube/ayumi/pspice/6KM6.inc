*
* Generic pentode model: 6KM6
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:37 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 6KM6 A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.57761874
BM1   M1   0 V=(0.52339318*(URAMP(V(G2,K))+1e-10))^-5.2554363
BM2   M2   0 V=(0.22204339*(URAMP(V(GG)+URAMP(V(G2,K))/1.4863713)))^6.7554363
BP    P    0 V=0.006536245*(URAMP(V(GG)+URAMP(V(G2,K))/6.6940577))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*4.7534114*V(M1)*V(M2)
BIG   IG   0 V=0.0032681225*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.987878393*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.012121607)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+1060)/(URAMP(V(G2,K))+1060)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0047861683*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0047861683*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  1.2p
CGK   G1  K  12.6p
C12   G1  G2 8.4p
CAK   A   K  7.9p
.ENDS
