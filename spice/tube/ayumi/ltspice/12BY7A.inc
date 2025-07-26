*
* Generic pentode model: 12BY7A
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:15 2008
*              Plate
*              | Screen Grid
*              | | Control Grid
*              | | | Cathode
*              | | | |
.SUBCKT 12BY7A A G2 G1 K
BGG   GG   0 V=V(G1,K)+-0.02185341
BM1   M1   0 V=(0.014593712*(URAMP(V(G2,K))+1e-10))**-0.7027291
BM2   M2   0 V=(0.68097344*(URAMP(V(GG)+URAMP(V(G2,K))/21.860549)))**2.2027291
BP    P    0 V=0.0061475247*(URAMP(V(GG)+URAMP(V(G2,K))/32.101912))**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0036081888*V(M1)*V(M2)
BIG   IG   0 V=0.0030737623*URAMP(V(G1,K))**1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.82512147*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))**1.5+0.17487853)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+4890)/(URAMP(V(G2,K))+4890)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0033632383*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))**1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0033632383*URAMP(V(A,K))**1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.063p
CGK   G1  K  6.1p
C12   G1  G2 4.1p
CAK   A   K  3.4p
.ENDS
