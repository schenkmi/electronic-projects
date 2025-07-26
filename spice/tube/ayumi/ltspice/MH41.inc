*
* Generic triode model: MH41
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:42:59 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT MH41 A G K
BGG   GG   0 V=V(G,K)+0.69037329
BM1   M1   0 V=(0.016743849*(URAMP(V(A,K))+1e-10))**-2.3893886
BM2   M2   0 V=(0.38566473*(URAMP(V(GG)+URAMP(V(A,K))/36.690206)+1e-10))**3.8893886
BP    P    0 V=0.0031372081*(URAMP(V(GG)+URAMP(V(A,K))/95.134979)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0095426065*V(M1)*V(M2)
BIG   IG   0 V=0.0015686041*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0016181984*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 3.2p
CGK   G    K 8.5p
CAK   A    K 4.1p
.ENDS
