*
* Generic triode model: 6SQ7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:59 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6SQ7 A G K
BGG   GG   0 V=V(G,K)+0.73774817
BM1   M1   0 V=(0.0014361986*(URAMP(V(A,K))+1e-10))^-0.21629832
BM2   M2   0 V=(0.87397394*(URAMP(V(GG)+URAMP(V(A,K))/87.749749)+1e-10))^1.7162983
BP    P    0 V=0.00075255807*(URAMP(V(GG)+URAMP(V(A,K))/100.40316)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00049502244*V(M1)*V(M2)
BIG   IG   0 V=0.00037627904*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00038755003*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.7p
CGK   G    K 1.7p
CAK   A    K 3.8p
.ENDS
