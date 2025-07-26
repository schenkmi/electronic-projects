*
* Generic pentode model: 6JS6
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:19 2008
*            Plate
*            | Screen Grid
*            | | Control Grid
*            | | | Cathode
*            | | | |
.SUBCKT 6JS6 A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.9999936
BM1   M1   0 V=(0.21913245*(URAMP(V(G2,K))+1e-10))^-1.3747601
BM2   M2   0 V=(0.52178266*(URAMP(V(GG)+URAMP(V(G2,K))/2.1823209)))^2.8747601
BP    P    0 V=0.0035536558*(URAMP(V(GG)+URAMP(V(G2,K))/4.1824327))^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0031522524*V(M1)*V(M2)
BIG   IG   0 V=0.0017768279*URAMP(V(G1,K))^1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.9913745766*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))^1.5+0.0086254234)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+1435)/(URAMP(V(G2,K))+1435)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0031247106*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))^1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0031247106*URAMP(V(A,K))^1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  0.7p
CGK   G1  K  14p
C12   G1  G2 9.3p
CAK   A   K  9.3p
.ENDS
