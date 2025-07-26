*
* Generic pentode model: KT66
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:54 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT KT66 A G2 G1 K
BGG   GG   0 V=V(G1,K)+1
BM1   M1   0 V=(0.051887963*(URAMP(V(G2,K))+1e-10))^-0.76669755
BM2   M2   0 V=(0.66175569*(URAMP(V(GG)+URAMP(V(G2,K))/6.5187433)))^2.2666975
BP    P    0 V=0.0018223197*(URAMP(V(GG)+URAMP(V(G2,K))/9.8506796))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0010893248*V(M1)*V(M2)
BIG   IG   0 V=0.00091115984*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.938072528*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.061927472)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+2300)/(URAMP(V(G2,K))+2300)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0011955789*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0011955789*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  1.1p
CGK   G1  K  8.1p
C12   G1  G2 5.4p
CAK   A   K  9p
.ENDS
