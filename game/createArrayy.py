' '
width = 21
height = 16
o = 'x'
n = ' '
mylist = [
            
            [n,n,n,n,n,n,n,n,o,n,n,n,n,n,o,n,n,n,n,n,n],
            [n,o,o,n,o,o,n,n,o,n,o,o,n,o,o,o,n,o,o,o,n],
            [n,n,n,n,n,n,n,n,n,n,o,n,n,n,n,n,n,n,o,n,n],
            [n,o,o,o,o,o,n,o,o,o,o,n,n,o,n,o,o,o,o,o,n],
            [n,n,n,n,n,n,n,n,n,o,o,o,n,o,n,n,n,n,n,n,n],
            [o,o,o,n,n,n,o,o,o,o,n,n,n,o,o,o,o,o,n,o,o],
            [o,n,o,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,o,n],
            [o,n,n,n,o,n,o,n,o,o,n,o,o,n,n,o,n,n,n,n,n],
            [o,n,o,n,o,o,o,n,o,n,n,n,o,n,n,o,n,n,o,o,o],
            [o,o,o,n,o,n,o,n,o,o,o,o,o,n,n,o,n,n,n,n,n],
            [n,n,n,n,n,n,n,n,n,o,o,o,n,n,n,o,n,o,o,o,n],
            [n,n,n,o,o,o,o,n,n,n,n,n,n,n,n,o,n,o,n,n,n],
            [o,o,n,n,o,o,n,n,o,o,o,o,o,n,n,o,n,o,n,o,o],
            [n,n,n,n,n,n,n,n,n,n,o,n,n,n,n,n,n,n,n,n,n],
            [n,o,o,o,o,o,o,o,o,n,o,n,o,o,o,o,o,o,o,o,n],
            [n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n,n],
         ]

for x in range(width):
	for y in range(height):
		if mylist[y][x] == o:
			print 'gameBoard[' + str(x) + '][' + str(y) + '] = obstacleBlock;'
