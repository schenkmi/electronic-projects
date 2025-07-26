*
* Generic triode model: 6SN7
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:58 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6SN7 A G K
BGG   GG   0 V=V(G,K)+0.54900933
BM1   M1   0 V=(0.020494606*(URAMP(V(A,K))+1e-10))**-0.76277031
BM2   M2   0 V=(0.66290422*(URAMP(V(GG)+URAMP(V(A,K))/16.448024)+1e-10))**2.2627703
BP    P    0 V=0.0012465111*(URAMP(V(GG)+URAMP(V(A,K))/24.812067)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00074417047*V(M1)*V(M2)
BIG   IG   0 V=0.0003834058*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0006816103*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 3p
CAK   A    K 1.2p
.ENDS
