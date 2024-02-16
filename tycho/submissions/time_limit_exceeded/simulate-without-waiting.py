#! /usr/bin/env python3

# @EXPECTED_GRADES@ TLE WA WA TLE TLE TLE TLE

""" Wrong solution that stoically drives home,
    taking whatever damage the pulsar throws at you.
"""

b, p, d, n = map(int, input().split())
shelters = set(map(int, (input() for _ in range(n))))

damage = pos = time = 0
while pos != b:
    if time > 0 and time % p == 0 and pos not in shelters:
        damage += d
    time += 1
    pos += 1
    damage += 1
print(damage)
