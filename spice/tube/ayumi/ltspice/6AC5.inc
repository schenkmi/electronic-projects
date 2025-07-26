*
* Generic triode model: 6AC5
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:38:59 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT 6AC5 A G K
BGG   GG   0 V=V(G,K)+0.64401885
BM1   M1   0 V=(0.0088089263*(URAMP(V(A,K))+1e-10))**-1.3738592
BM2   M2   0 V=(0.52194624*(URAMP(V(GG)+URAMP(V(A,K))/54.269243)+1e-10))**2.8738592
BP    P    0 V=0.0005490772*(URAMP(V(GG)+URAMP(V(A,K))/103.97478)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.00048665592*V(M1)*V(M2)
BIG   IG   0 V=0.00015454249*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.00037669733*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 4p
CGK   G    K 4p
CAK   A    K 4p
.ENDS
