*
* Generic triode model: 6BL8PT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:14 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 6BL8PT A G K
BGG   GG   0 V=V(G,K)+0.57453871
BM1   M1   0 V=(0.0091087169*(URAMP(V(A,K))+1e-10))**-0.67124576
BM2   M2   0 V=(0.69084764*(URAMP(V(GG)+URAMP(V(A,K))/33.940276)+1e-10))**2.1712458
BP    P    0 V=0.0040028722*(URAMP(V(GG)+URAMP(V(A,K))/49.128454)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0023332764*V(M1)*V(M2)
BIG   IG   0 V=0.0020014361*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0021242724*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.1p
CGK   G    K 3.1p
CAK   A    K 3.4p
.ENDS
