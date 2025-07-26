*
* Generic triode model: 41MXP
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:41:30 2008
*             Plate
*             | Grid
*             | | Cathode
*             | | |
.SUBCKT 41MXP A G K
BGG   GG   0 V=V(G,K)+0.99999047
BM1   M1   0 V=(0.24250237*(URAMP(V(A,K))+1e-10))**-4.0569457
BM2   M2   0 V=(0.26993246*(URAMP(V(GG)+URAMP(V(A,K))/3.0105584)+1e-10))**5.5569457
BP    P    0 V=0.0015885113*(URAMP(V(GG)+URAMP(V(A,K))/11.153006)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.089955716*V(M1)*V(M2)
BIG   IG   0 V=0.00079425566*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0010126188*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 4p
CAK   A    K 4p
.ENDS
