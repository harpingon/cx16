# Address = 0 + CursorY * 8 * 320 + CursorX * 8
f = open("grid.grid", "r")
print(".actions")
y=0
m=f.readline()
m=f.readline()
for line in f:
    l=line.strip()
    x=0
    for c in l:
        if ("*" == c):
            a=0+y*320+x*8
            ha="%0.6X" % a
            hx="%0.2X" % x
            hy="%0.2X" % y
            # print("!byte $1,${},${},${}".format(ha[0:2],ha[2:4],ha[4:6]))
            print("!byte $1,${},${},${}".format('10',hy,hx))
        x+=2
    y+=1
print("!byte $FF,$FF,$FF")
