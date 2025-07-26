*
* Generic triode model: 300B
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:52 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 300B A G K
BGG   GG   0 V=V(G,K)+0.99996017
BM1   M1   0 V=(0.038949013*(URAMP(V(A,K))+1e-10))**-0.25159159
BM2   M2   0 V=(0.85636401*(URAMP(V(GG)+URAMP(V(A,K))/3.6877954)+1e-10))**1.7515916
BP    P    0 V=0.0011156138*(URAMP(V(GG)+URAMP(V(A,K))/4.3063409)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00071191966*V(M1)*V(M2)
BIG   IG   0 V=0.00055780691*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00096815606*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 15p
CGK   G    K 8.5p
CAK   A    K 4.1p
.ENDS
