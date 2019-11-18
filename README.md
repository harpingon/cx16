** game of life for X16 ** 

(maybe, evenutally)

gol1.asm	:	the main routine


readlist.inc	:	read the list of orders and execute them

makelist.inc	: 	long but pointless route to illustrate error
			eventually this will compute the new orders

grid.grid	:	dots are emtpy space, stars are filled space

grid.py		:	turn grid.grid into grid.inc


grid.inc format:

[0,1] off or on, vera high, vera mid, vera lo

So the grid.py computes the "on" orders and stores the vera addresses that will be used

List is terminated with FF FF FF
