#! /usr/bin/env python3

# Solution in time O(n* min(n, p)) using dynamic programming,
# using Lucas's formulas and notation from the original analysis,
# and observing that s[k] has at most min(n, p) elements.

# @EXPECTED_GRADES@ TLE AC AC AC AC TLE TLE

b, m, d, n = map(int, input().split())
a = [0] + list(int(input()) for _ in range(n))

f = lambda x: -(d + m) * (-x // m) - d
g = lambda x: x + d * (-(-x // m) - 1)

s = {} # want s[k] = max (j : j < i and a[j] % m == k)
damage = []
for i in range(n + 1):
    damage += [min((damage[j] + f(a[i] - a[j]) for j in s.values()), default=0)]
    s[a[i] % m] = i

print(min(damage[i] + g(b - a[i]) for i in range(n + 1)))
