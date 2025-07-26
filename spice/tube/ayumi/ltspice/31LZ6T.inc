*
* Generic triode model: 31LZ6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:20 2008
*              Plate
*              | Grid
*              | | Cathode
*              | | |
.SUBCKT 31LZ6T A G K
BGG   GG   0 V=V(G,K)+-0.11976616
BM1   M1   0 V=(0.21025804*(URAMP(V(A,K))+1e-10))**-1.445676
BM2   M2   0 V=(0.50922098*(URAMP(V(GG)+URAMP(V(A,K))/2.3341748)+1e-10))**2.945676
BP    P    0 V=0.0061264796*(URAMP(V(GG)+URAMP(V(A,K))/4.5838151)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0058083241*V(M1)*V(M2)
BIG   IG   0 V=0.0030632398*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0051737191*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 9.2p
CGK   G    K 12.9p
CAK   A    K 10.4p
.ENDS
