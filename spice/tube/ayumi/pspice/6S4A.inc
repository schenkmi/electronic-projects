*
* Generic triode model: 6S4A
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:40:51 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6S4A A G K
BGG   GG   0 V=V(G,K)+0.32778768
BM1   M1   0 V=(0.034282937*(URAMP(V(A,K))+1e-10))^-1.0247707
BM2   M2   0 V=(0.59411337*(URAMP(V(GG)+URAMP(V(A,K))/11.839319)+1e-10))^2.5247707
BP    P    0 V=0.0017432762*(URAMP(V(GG)+URAMP(V(A,K))/19.92771)+1e-10)^1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0011797852*V(M1)*V(M2)
BIG   IG   0 V=0.00087163808*URAMP(V(G,K))^1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0010044908*URAMP(V(A,K))^1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 2.4p
CGK   G    K 4.2p
CAK   A    K 0.6p
.ENDS
