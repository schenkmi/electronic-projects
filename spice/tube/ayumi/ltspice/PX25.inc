*
* Generic triode model: PX25
* Copyright 2003--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 22:43:05 2008
*            Plate
*            | Grid
*            | | Cathode
*            | | |
.SUBCKT PX25 A G K
BGG   GG   0 V=V(G,K)+-1
BM1   M1   0 V=(0.042915161*(URAMP(V(A,K))+1e-10))**-0.71624142
BM2   M2   0 V=(0.67682157*(URAMP(V(GG)+URAMP(V(A,K))/7.5306353)+1e-10))**2.2162414
BP    P    0 V=0.0019818048*(URAMP(V(GG)+URAMP(V(A,K))/11.126471)+1e-10)**1.5
BIK   IK   0 V=U(V(GG))*V(P)+(1-U(V(GG)))*0.0011671444*V(M1)*V(M2)
BIG   IG   0 V=0.00099090241*URAMP(V(G,K))**1.5*(URAMP(V(G,K))/(URAMP(V(A,K))+URAMP(V(G,K)))*1.2+0.4)
BIAK  A    K I=URAMP(V(IK,IG)-URAMP(V(IK,IG)-(0.0012639928*URAMP(V(A,K))**1.5)))+1e-10*V(A,K)
BIGK  G    K I=V(IG)
* CAPS
CGA   G    A 14.8p
CGK   G    K 11.4p
CAK   A    K 8.3p
.ENDS
