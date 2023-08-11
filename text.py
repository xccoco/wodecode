from random import randint
import sys
sys.stdout = open("1006.in","w")
n = 1000000
m = 5000
print(n,m)
for i in range(n):
	print(randint(1,1e9),end = ' ')
print()
for i in range(m):
	l = randint(1,n - 1)
	r = randint(l + 1,n)
	print(l,r)
