*
* Generic pentode model: ECL85P
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Wed Oct 22 16:34:56 2008
*              Plate
*              | Screen Grid
*              | | Control Grid
*              | | | Cathode
*              | | | |
.SUBCKT ECL85P A G2 G1 K
BGG   GG   0 V=V(G1,K)+0.61401316
BM1   M1   0 V=(0.075869075*(URAMP(V(G2,K))+1e-10))**-1.148877
BM2   M2   0 V=(0.56627772*(URAMP(V(GG)+URAMP(V(G2,K))/5.7167203)))**2.648877
BP    P    0 V=0.0037731888*(URAMP(V(GG)+URAMP(V(G2,K))/10.095259))**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0027774625*V(M1)*V(M2)
BIG   IG   0 V=0.0018865944*URAMP(V(G1,K))**1.5*(URAMP(V(G1,K))/(URAMP(V(A,K))+URAMP(V(G1,K)))*1.2+0.4)
BIK2  IK2  0 V=V(IK,IG)*(1-0.4*(EXP(-URAMP(V(A,K))/URAMP(V(G2,K))*15)-EXP(-15)))
BIG2T IG2T 0 V=V(IK2)*(0.935445718*(1-URAMP(V(A,K))/(URAMP(V(A,K))+10))**1.5+0.064554282)
BIK3  IK3  0 V=V(IK2)*(URAMP(V(A,K))+4320)/(URAMP(V(G2,K))+4320)
BIK4  IK4  0 V=V(IK3)-URAMP(V(IK3)-(0.0024608947*(URAMP(V(A,K))+URAMP(URAMP(V(G2,K))-URAMP(V(A,K))))**1.5))
BIP   IP   0 V=URAMP(V(IK4,IG2T)-URAMP(V(IK4,IG2T)-(0.0024608947*URAMP(V(A,K))**1.5)))
BIAK  A    K I=V(IP)+1e-10*V(A,K)
BIG2  G2   K I=URAMP(V(IK4,IP))
BIGK  G1   K I=V(IG)
* CAPS
CGA   G1  A  1p
CGK   G1  K  5.1p
C12   G1  G2 3.4p
CAK   A   K  7.1p
.ENDS
