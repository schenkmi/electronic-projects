*
* Generic pentode model: 6JB5
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:15 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 6JB5 A G2 G1 K
BGG   GG   0 V=V(G1,K)+1
BM1   M1   0 V=(0.16129088*(URAMP(V(G2,K))+1e-10))^-2.7283665
BM2   M2   0 V=(0.35474692*(URAMP(V(GG)+URAMP(V(G2,K))/4.0005552)))^4.2283665
BP    P    0 V=0.0020818822*(URAMP(V(GG)+URAMP(V(G2,K))/11.277209))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0106492*V(M1)*V(M2)
BIG   IG   0 V=0.0010409411*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.931759377*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.068240623)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+3620)/(URAMP(V(G2,K))+3620)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0013239066*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0013239066*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.49p
CGK   G1  K  5.4p
C12   G1  G2 3.6p
CAK   A   K  6p
.ENDS
