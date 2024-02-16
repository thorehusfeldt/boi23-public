#! /usr/bin/env python3

# Pythonified version of Wojciech's solution,
# uses frozenset(A) as hashable for memoisation.

import functools

n = int(input())
w = [int(input()) for _ in range(n)]


@functools.lru_cache(maxsize=None)
def F(A):
    a = max(A)
    if a == 1:
        return w[0]
    B = A - set([a])
    best = F(frozenset(B | set([a - 1])))
    for ij in divisors[a]:
        best = min(best, F(frozenset(B | set(ij))))
    return best + w[a - 1]


divisors = {i + 1: [] for i in range(n)}
for i in range(2, n):
    for j in range(i, n):
        if i * j > n:
            break
        divisors[i * j].append((i, j))

print(*(F(frozenset([i])) for i in range(1, n + 1)))
