#!/usr/bin/env python3

# Pythonification of Lucas' simple segment tree solution. Slooooow...
import sys
INF = 10**18

class RMQ:
    def __init__(self, size):
        cap = 1
        while cap < size + 1:
            cap *= 2
        self.cap = cap
        self.seg = [INF] * (2 * cap)

    def update(self, idx, v):
        idx += self.cap
        self.seg[idx] = v
        while idx >= 1:
            idx //= 2
            self.seg[idx] = min(self.seg[2 * idx], self.seg[2 * idx + 1])

    def query(self, l, r, a=0, b=None, idx=1):
        if b is None:
            b = self.cap - 1
        if l <= a and b <= r:
            return self.seg[idx]
        if b < l or r < a:
            return INF
        mid = (a + b) // 2
        return min(
            self.query(l, r, a, mid, 2 * idx), self.query(l, r, mid + 1, b, 2 * idx + 1)
        )


base, m, d, n = map(int, input().split())
shelters = [0] + [int(line) for line in sys.stdin]
dp = [0] * len(shelters)
comp = {v: i for i, v in enumerate(sorted(set(a % m for a in shelters)))}
rmq = RMQ(n)
rmq.update(0, 0)


for i in range(1, n + 1):
    p = comp[shelters[i] % m]
    x = (shelters[i] // m) * (d + m)
    dp[i] = x + min(rmq.query(0, p - 1) + d + m, rmq.query(p, n)) - d
    rmq.update(p, dp[i] - x)

print(
    min(
        dp[i] + base - a + d * ((base - a + m - 1) // m - 1)
        for i, a in enumerate(shelters)
    )
)
