*
* Generic triode model: 6AU6T
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:39:10 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 6AU6T A G K
BGG   GG   0 V=V(G,K)+0.24107953
BM1   M1   0 V=(0.014176045*(URAMP(V(A,K))+1e-10))**-0.93570358
BM2   M2   0 V=(0.61583848*(URAMP(V(GG)+URAMP(V(A,K))/27.099343)+1e-10))**2.4357036
BP    P    0 V=0.0032162308*(URAMP(V(GG)+URAMP(V(A,K))/44.003978)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0020681021*V(M1)*V(M2)
BIG   IG   0 V=0.0016081154*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0017183702*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.2p
CGK   G    K 3.3p
CAK   A    K 5p
.ENDS
