*
* Generic triode model: 6J7T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:14 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6J7T A G K
BGG   GG   0 V=V(G,K)+0.75953915
BM1   M1   0 V=(0.0057490544*(URAMP(V(A,K))+1e-10))^-0.20145614
BM2   M2   0 V=(0.8815978*(URAMP(V(GG)+URAMP(V(A,K))/20.595073)+1e-10))^1.7014561
BP    P    0 V=0.00080605414*(URAMP(V(GG)+URAMP(V(A,K))/23.361076)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00053791349*V(M1)*V(M2)
BIG   IG   0 V=0.00040302707*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00045533328*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.8p
CGK   G    K 4.2p
CAK   A    K 12p
.ENDS
