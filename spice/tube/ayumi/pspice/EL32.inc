*
* Generic pentode model: EL32
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:47 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT EL32 A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.99999999
BM1   M1   0 V=(0.12471331*(URAMP(V(G2,K))+1e-10))^-1.9909547
BM2   M2   0 V=(0.42968188*(URAMP(V(GG)+URAMP(V(G2,K))/4.5730334)))^3.4909547
BP    P    0 V=0.0011713028*(URAMP(V(GG)+URAMP(V(G2,K))/10.642835))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0020582453*V(M1)*V(M2)
BIG   IG   0 V=0.00058565141*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.87143806*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.12856194)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+3110)/(URAMP(V(G2,K))+3110)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.00075455382*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.00075455382*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  4p
CGK   G1  K  2.4p
C12   G1  G2 1.6p
CAK   A   K  4p
.ENDS
