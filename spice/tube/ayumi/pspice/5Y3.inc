*
* Generic diode model: 5Y3
* Copyright 2007--2008 by Ayumi Nakabayashi, All rights reserved.
* Version 3.10, Generated on Sat Mar  8 23:08:31 2008
.SUBCKT 5Y3 A K
BIA A K I=URAMP(V(A,K))^1.5 * 0.00035355339
.ENDS
