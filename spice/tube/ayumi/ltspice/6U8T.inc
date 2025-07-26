*
* Generic triode model: 6U8T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:00 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6U8T A G K
BGG   GG   0 V=V(G,K)+0.99995916
BM1   M1   0 V=(0.035181787*(URAMP(V(A,K))+1e-10))**-2.5690962
BM2   M2   0 V=(0.36863223*(URAMP(V(GG)+URAMP(V(A,K))/17.94587)+1e-10))**4.0690962
BP    P    0 V=0.0033085897*(URAMP(V(GG)+URAMP(V(A,K))/48.682314)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.013182953*V(M1)*V(M2)
BIG   IG   0 V=0.0016542949*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0017567609*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 1.8p
CGK   G    K 2.8p
CAK   A    K 2p
.ENDS
