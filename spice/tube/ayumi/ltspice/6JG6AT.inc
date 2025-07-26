*
* Generic triode model: 6JG6AT
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:17 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 6JG6AT A G K
BGG   GG   0 V=V(G,K)+0.99372841
BM1   M1   0 V=(0.20443422*(URAMP(V(A,K))+1e-10))**-2.1006356
BM2   M2   0 V=(0.41659311*(URAMP(V(GG)+URAMP(V(A,K))/2.8537634)+1e-10))**3.6006356
BP    P    0 V=0.0069256204*(URAMP(V(GG)+URAMP(V(A,K))/6.8502415)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.014050654*V(M1)*V(M2)
BIG   IG   0 V=0.0034628102*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0050333831*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.2p
CGK   G    K 12.8p
CAK   A    K 8.3p
.ENDS
