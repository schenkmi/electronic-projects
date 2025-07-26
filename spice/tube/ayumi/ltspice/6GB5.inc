*
* Generic pentode model: 6GB5
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:07 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 6GB5 A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.84509256
BM1   M1   0 V=(0.074600608*(URAMP(V(G2,K))+1e-10))**-0.78902807
BM2   M2   0 V=(0.65529996*(URAMP(V(GG)+URAMP(V(G2,K))/4.6206063)))**2.2890281
BP    P    0 V=0.0051497371*(URAMP(V(GG)+URAMP(V(G2,K))/7.0511317))**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0031020384*V(M1)*V(M2)
BIG   IG   0 V=0.0025748686*URAMP(V(G1,K))**1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.963603604*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))**1.5+0.036396396)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+4658)/(URAMP(V(G2,K))+4658)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0037083507*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))**1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0037083507*URAMP(V(A,K))**1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  1.75p
CGK   G1  K  12.9p
C12   G1  G2 8.6p
CAK   A   K  9.4p
.ENDS
