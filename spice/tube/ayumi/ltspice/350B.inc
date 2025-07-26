*
* Generic pentode model: 350B
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:53 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 350B A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.99999998
BM1   M1   0 V=(0.060793226*(URAMP(V(G2,K))+1e-10))**-0.90421858
BM2   M2   0 V=(0.62390334*(URAMP(V(GG)+URAMP(V(G2,K))/6.1864896)))**2.4042186
BP    P    0 V=0.0019265247*(URAMP(V(GG)+URAMP(V(G2,K))/9.9157821))**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0012190211*V(M1)*V(M2)
BIG   IG   0 V=0.00096326237*URAMP(V(G1,K))**1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.946533574*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))**1.5+0.053466426)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+4981.25)/(URAMP(V(G2,K))+4981.25)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0012619241*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))**1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0012619241*URAMP(V(A,K))**1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.5p
CGK   G1  K  9.3p
C12   G1  G2 6.2p
CAK   A   K  7.5p
.ENDS
