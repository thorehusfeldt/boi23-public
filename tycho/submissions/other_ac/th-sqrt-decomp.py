#!/usr/bin/env python3

import sys

INF = 2 * 10**18 # less clean than float("inf"), but avoids type mismatch (thus faster)

class RMQ:
    def __init__(self, size):
        self.block_size = 1 + int(size ** (1 / 2))
        num_blocks = 1 + size // self.block_size
        self.values = [INF] * size
        self.minima = [INF] * num_blocks

    def update(self, idx, v):
        assert 0 <= idx < len(self.values), (idx, self.values)
        self.values[idx] = v
        B = self.block_size
        j = idx // B
        assert j * B <= idx < (j + 1) * B
        self.minima[j] = min(self.values[j * B : (j + 1) * B])

    def query(self, lo, hi):
        B = self.block_size
        j_lo = lo // B
        j_hi = hi // B
        return min(
                min(self.values[lo : (j_lo + 1) * B], default=INF),
                min(self.minima[j_lo + 1 : j_hi], default=INF),
                min(self.values[j_hi * B : hi + 1], default=INF),
            ) if j_lo < j_hi else min(self.values[lo : hi + 1], default=INF)

def main():
    base, m, d, n = map(int, input().split())
    shelters = [0] + [int(line) for line in sys.stdin]
    dp = [0] * len(shelters)
    ranks = {v: i for i, v in enumerate(sorted(set(a % m for a in shelters)))}
    rmq = RMQ(n + 1)

    rmq.update(0, 0)

    for i in range(1, n + 1):
        p = ranks[shelters[i] % m]
        x = (shelters[i] // m) * (d + m)
        dp[i] = x + min(rmq.query(0, p - 1) + d + m, rmq.query(p, n)) - d
        rmq.update(p, dp[i] - x)

    print(
        min(
            dp[i] + base - a + d * ((base - a + m - 1) // m - 1)
            for i, a in enumerate(shelters)
        )
    )


main()
