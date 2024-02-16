#! /usr/bin/env python3

# Solution in time O(zm) using dynamic programming
# @EXPECTED_GRADES@ RTE AC AC RTE RTE RTE RTE
# The RTE/TLE behaviour (does it run out of memory before
# it runs out of time?) is funky and differs between pypy/cpython

import math

z, m, c, n = map(int, input().split())
a = set(int(input()) for _ in range(n))
a.add(z) # assume goal position is safe

best = [[math.inf] * m for _ in range(z + 2)]

# best[p][t] = min number of seconds to be at
#              position p at a time that is t mod m
# Can be computed in space O(m) instead of O(zm)

best[0][0] = 0
for p in range(z + 1):
    for t in range(m):
        t_ = (t + 1) % m
        for p_ in [p, p + 1]:
            best[p_][t_] = min(
                best[p_][t_],
                best[p][t] + 1 + (c if t_ == 0 and p_ not in a else 0)
                )

print(min(best[z][t] for t in range(m)))
