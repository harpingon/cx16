# game of life for Commander X16 


* gol1.asm

 > Main routine, defines zero page addrs etc

* readlist.inc

 > read the actions list and implement into VERA

* makelist.inc

 > add an order to a list 'storeaction'
 > also 'initlist' resets the action list

* algo.inc

 > The Life algorithm. Read all cells, compute
 > neighbor count and, if cell changes state
 > use 'storeaction' to implement the change
   
* grid.grid

 > starting grid pattern

* grid.py

 > convert grid.grid to grid.inc

* runit

 > run python, compile, and run program

### grid.inc format:

[CHR] character to store (space or *), X, Y
So the grid.py computes the "on" orders and stores the coordinates to use use
List is terminated with FF FF FF
