*
* Generic triode model: ECC99_AN
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sun Jan 12 18:46:10 2014
*                Plate
*                | Grid
*                | | Cathode
*                | | |
.SUBCKT ECC99_AN A G K
BGG   GG   0 V=V(G,K)+0.042958289
BM1   M1   0 V=(0.02038404*(URAMP(V(A,K))+1e-10))**-0.86570009
BM2   M2   0 V=(0.63406177*(URAMP(V(GG)+URAMP(V(A,K))/17.952193)+1e-10))**2.3657001
BP    P    0 V=0.005978906*(URAMP(V(GG)+URAMP(V(A,K))/28.313003)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0037149974*V(M1)*V(M2)
BIG   IG   0 V=0.002989453*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0033089913*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 5.8p
CGK   G    K 5.1p
CAK   A    K 0.8p
.ENDS

