*
* Generic pentode model: 6U8P
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:03 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 6U8P A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.65071871
BM1   M1   0 V=(0.046006989*(URAMP(V(G2,K))+1e-10))^-2.7651713
BM2   M2   0 V=(0.35168575*(URAMP(V(GG)+URAMP(V(G2,K))/14.091647)))^4.2651713
BP    P    0 V=0.003445744*(URAMP(V(GG)+URAMP(V(G2,K))/40.068859))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.018698107*V(M1)*V(M2)
BIG   IG   0 V=0.001722872*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.74580496*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.25419504)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+6302.5)/(URAMP(V(G2,K))+6302.5)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0018526668*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0018526668*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.007p
CGK   G1  K  3p
C12   G1  G2 2p
CAK   A   K  3.5p
.ENDS
