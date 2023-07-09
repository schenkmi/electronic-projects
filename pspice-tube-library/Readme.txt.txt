

# Pin numbering Transistors

The usual pin order in SPICE is C B E.

Q1 C VBB E 0 npn_ideal_transistor

The node order for transistor (Q) models is C B E. So if pin 1 is E, pin 2 is B, and pin 3 is C you’d use node order 3 2 1. But the BC556 is C B E, which matches the spice default and should be fine as is. (This is for parameter style .model models, not subckt models… those can have any order and you need to check the model source to see what it needs.)


BC850C

Q^@REFDES %c %b %e @MODEL ?AREA/@AREA/

*              C B E
.SUBCKT BC850C 1 2 3 
Q1 1 2 3 Transistor 0.9342
Q2 11 2 3 Transistor 0.0658
RQ 1 11 662.1
D1 2 1 Diode
