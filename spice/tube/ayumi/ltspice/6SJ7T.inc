*
* Generic triode model: 6SJ7T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:55 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6SJ7T A G K
BGG   GG   0 V=V(G,K)+0.40161932
BM1   M1   0 V=(0.02462593*(URAMP(V(A,K))+1e-10))**-0.84287662
BM2   M2   0 V=(0.64023858*(URAMP(V(GG)+URAMP(V(A,K))/14.609049)+1e-10))**2.3428766
BP    P    0 V=0.0011655656*(URAMP(V(GG)+URAMP(V(A,K))/22.818133)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00071703729*V(M1)*V(M2)
BIG   IG   0 V=0.00068041382*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00044226898*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.4p
CGK   G    K 3.6p
CAK   A    K 7p
.ENDS
