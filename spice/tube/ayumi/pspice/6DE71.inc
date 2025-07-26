*
* Generic triode model: 6DE71
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:46 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6DE71 A G K
BGG   GG   0 V=V(G,K)+0.97660212
BM1   M1   0 V=(0.012940444*(URAMP(V(A,K))+1e-10))^-0.39564264
BM2   M2   0 V=(0.79128838*(URAMP(V(GG)+URAMP(V(A,K))/16.128628)+1e-10))^1.8956426
BP    P    0 V=0.00091559181*(URAMP(V(GG)+URAMP(V(A,K))/20.382743)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00054039164*V(M1)*V(M2)
BIG   IG   0 V=0.00045779591*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00052599563*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 2.2p
CAK   A    K 0.5p
.ENDS
