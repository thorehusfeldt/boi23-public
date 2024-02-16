#!/usr/bin/env python3
# @EXPECTED_GRADES@ AC WA WA WA WA WA WA

b, p, d, n = map(int, input().split())
a = [int(input()) for _ in range(n)]

shelter_cnt = [0]*p
for i in a:
    shelter_cnt[i % p] += 1

def damage(start):
    total = b + start
    first_shelter = p - start
    pulse_cnt = (b - first_shelter + p - 1) // p
    total += d * (pulse_cnt - shelter_cnt[first_shelter % p])
    return total

best = 2 * 10**18
for i in range(0, p):
    best = min(best, damage(i))

print(best)