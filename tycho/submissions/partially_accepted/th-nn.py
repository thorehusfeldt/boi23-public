#! /usr/bin/env python3

# Solution in time O(n*n) using dynamic programming
# using Lucas's formulas and notation from the original analysis

# @EXPECTED_GRADES@ TLE AC AC AC TLE TLE TLE

import math

z, m, c, n = map(int, input().split())
a = [0] + list(int(input()) for _ in range(n))

def f(d):
    return (c + m) * math.ceil(d / m) - c

damage = [0]
for i in range(1, n + 1):
    damage.append(min(damage[j] + f(a[i] - a[j]) for j in range(i)))

def g(d):
    return d + c * (math.ceil(d/m) - 1)

print(min(damage[i] + g(z - a[i]) for i in range(n + 1)))
