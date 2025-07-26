*
* Generic pentode model: 7591
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:23 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 7591 A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.99926889
BM1   M1   0 V=(0.013694604*(URAMP(V(G2,K))+1e-10))^-0.39656351
BM2   M2   0 V=(0.79090417*(URAMP(V(GG)+URAMP(V(G2,K))/15.268483)))^1.8965635
BP    P    0 V=0.0034491916*(URAMP(V(GG)+URAMP(V(G2,K))/19.305098))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0020351267*V(M1)*V(M2)
BIG   IG   0 V=0.0017245958*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.88749484*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.11250516)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+2850)/(URAMP(V(G2,K))+2850)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0019960381*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0019960381*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.25p
CGK   G1  K  5.9p
C12   G1  G2 3.9p
CAK   A   K  4.8p
.ENDS
