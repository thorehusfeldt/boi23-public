#!/usr/bin/env python3
# @EXPECTED_GRADES@ AC AC AC AC AC AC TLE

INF = 2 * 10**18

def update(idx, v):
    idx += cap
    seg[idx] = v
    while idx >= 1:
        idx //= 2
        seg[idx] = min(seg[2 * idx], seg[2 * idx + 1])


def query(l, r, a=0, b=None, idx=1):
    if b is None:
        b = cap - 1
    if l <= a and b <= r:
        return seg[idx]
    if b < l or r < a:
        return INF
    mid = (a + b) // 2
    return min(query(l, r, a, mid, 2 * idx), query(l, r, mid + 1, b, 2 * idx + 1))


base, m, d, n = map(int, input().split())
shelters = [0] + [int(input()) for _ in range(n)]
dp = [0] * len(shelters)
a_mod_m = sorted(set(a % m for a in shelters))
comp = {v: i for i, v in enumerate(a_mod_m)}

cap = 1
while cap < n + 1:
    cap *= 2
seg = [INF] * (2 * cap)

update(0, 0)

for i in range(1, n + 1):
    p = comp[shelters[i] % m]
    x = (shelters[i] // m) * (d + m)
    dp[i] = x + min(query(0, p - 1) + d + m, query(p, n)) - d
    update(p, dp[i] - x)

print(min(dp[i] + base - a + d * ((base - a + m - 1) // m - 1) for i, a in enumerate(shelters)))
