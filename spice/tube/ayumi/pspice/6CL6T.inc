*
* Generic triode model: 6CL6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:43 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6CL6T A G K
BGG   GG   0 V=V(G,K)+0.23313833
BM1   M1   0 V=(0.023688975*(URAMP(V(A,K))+1e-10))^-0.93652529
BM2   M2   0 V=(0.6156308*(URAMP(V(GG)+URAMP(V(A,K))/16.225658)+1e-10))^2.4365253
BP    P    0 V=0.0060982027*(URAMP(V(GG)+URAMP(V(A,K))/26.356151)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0039229723*V(M1)*V(M2)
BIG   IG   0 V=0.0030491014*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0033994382*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4.5p
CGK   G    K 6.5p
CAK   A    K 5.4p
.ENDS
