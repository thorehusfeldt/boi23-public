#! /usr/bin/env python3

# Solution in time O(n*m) using dynamic programming,
# using Lucas's formulas and notation from the original analysis

# @EXPECTED_GRADES@ TLE AC AC TLE AC TLE TLE

z, m, c, n = map(int, input().split())
a = [0] + list(int(input()) for _ in range(n))

f = lambda d: -(c + m) * (-d // m) - c
g = lambda d: d + c * (-(-d // m) - 1)

damage = [0]

s = [None] * m # want s[k] = max (j : j < i and a[j] = k)
i = 0
s[a[i] % m] = i # effect is a[0] = 0 because we put a cave at 0
for i in range(1, n + 1):
    # this can be one-linered, but let's do it slowly:
    damages = set()
    for k in range(m):
        if s[k] is None:
            continue
        j = s[k]
        damages.add(damage[j] + f(a[i] - a[j]))
    damage.append(min(damages))
    s[a[i] % m] = i

print(min(damage[i] + g(z - a[i]) for i in range(n + 1)))
