*
* Generic pentode model: 6JR6
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:20 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 6JR6 A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.99994363
BM1   M1   0 V=(0.13323481*(URAMP(V(G2,K))+1e-10))**-1.5275541
BM2   M2   0 V=(0.49544944*(URAMP(V(GG)+URAMP(V(G2,K))/3.7869273)))**3.0275541
BP    P    0 V=0.0072054321*(URAMP(V(GG)+URAMP(V(G2,K))/7.6434182))**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0074085952*V(M1)*V(M2)
BIG   IG   0 V=0.003602716*URAMP(V(G1,K))**1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.986575754*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))**1.5+0.013424246)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+1900)/(URAMP(V(G2,K))+1900)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0050620509*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))**1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0050620509*URAMP(V(A,K))**1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.7p
CGK   G1  K  12.8p
C12   G1  G2 8.5p
CAK   A   K  8.3p
.ENDS
