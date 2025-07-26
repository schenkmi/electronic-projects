*
* Generic triode model: 25E5T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:19 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 25E5T A G K
BGG   GG   0 V=V(G,K)+1
BM1   M1   0 V=(0.081561717*(URAMP(V(A,K))+1e-10))**-0.79980677
BM2   M2   0 V=(0.65222871*(URAMP(V(GG)+URAMP(V(A,K))/4.2639035)+1e-10))**2.2998068
BP    P    0 V=0.0042185857*(URAMP(V(GG)+URAMP(V(A,K))/6.5374361)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0025511424*V(M1)*V(M2)
BIG   IG   0 V=0.0021092928*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00311336*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 7.7p
CGK   G    K 9.9p
CAK   A    K 7p
.ENDS
