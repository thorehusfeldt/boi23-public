#! /usr/bin/env python3

# Best of many random traversals.

# This works as soon as the random start node is correctly chosen,
# which is quite certain with n^2 trails.
# (Shuffling the edges turns out to be irrelevant.)
# 
# Much too slow for large instances (cubic time),
# but works whp for small enough graphs

# @EXPECTED_GRADES@ TLE TLE AC TLE TLE

import random
random.seed(42)

n = int(input())
edges = {u: [] for u in range(n)}
for _ in range(n - 1):
    u, v = map(lambda x: int(x) - 1, input().split())
    edges[u].append(v)
    edges[v].append(u)


def dfs(r):
    # yield vertices in some dfs order from r
    visited = set()
    S = [r]
    while S:
        u = S.pop()
        yield u
        if u not in visited:
            visited.add(u)
            for v in edges[u]:
                if v not in visited:
                    S.append(u)
                    S.append(v)


costs = set()
num_trails = n * n

for _ in range(num_trails):
    start = random.randrange(n)
    for u in range(n):
        random.shuffle(edges[u])
    cost = 0
    checked = set()
    for time, u in enumerate(dfs(start)):
        if u not in checked:
            cost += time
            checked.add(u)
    costs.add(cost)

print(min(costs))
