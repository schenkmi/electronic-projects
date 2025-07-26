*
* Generic triode model: 6K7T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Wed Jun 30 20:54:56 2010
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6K7T A G K
BGG   GG   0 V=V(G,K)+-1
BM1   M1   0 V=(2.3738651*(URAMP(V(A,K))+1e-10))**-38.694622
BM2   M2   0 V=(0.037318425*(URAMP(V(GG)+URAMP(V(A,K))/0.40553339)+1e-10))**40.194622
BP    P    0 V=0.00060436625*(URAMP(V(GG)+URAMP(V(A,K))/10.866841)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*2.5180035e+51*V(M1)*V(M2)
BIG   IG   0 V=0.00030218313*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00038749733*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.8p
CGK   G    K 4.2p
CAK   A    K 12p
.ENDS
