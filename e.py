inp = input()

p = int(inp.split()[0])
q = int(inp.split()[1])

l = 0
r = 1e18 + 1


def f(xx):
	ff = 0
	res = 0
	for i in range(1,8):
		ff += i ** 5
		now=ff
		for j in range(1,8):
			if j==i:
				continue
			now*=(xx-j)

		for j in range(1,8):
			if j==i:
				continue
			now//=(i-j)

		res+=now
	return res - p * xx

# print("{} {}".format(p, q))
while (r - l > 1):
	mid = (l + r) // 2 
	tmp = mid
	ok = 1
	for d in range(1, 10001):
		tmp -= p
		if (tmp < 0):
			ok = 0
			break
		tmp += (q * (d ** 5))
	# print("{} {}".format(mid,tmp))
	if (ok):
		r = mid
	else:
		l = mid


x = r
l = 0
r = 1e18

big = 1e99

while (r - l > 1):
	# print(mid)
	mid = (l + r) // 2
	if (f(mid) >= big - x):
		r = mid
	else:
		l = mid

print("{}\n{}".format(int(x), r))
