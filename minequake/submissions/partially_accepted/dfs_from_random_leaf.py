#! /usr/bin/env python3

# One nonrandom DFS from random leaf. This works well for paths

# @EXPECTED_GRADES@ AC WA WA WA WA

import random
random.seed(42)

n = int(input())

if n == 1:
    print(0)
    exit()

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


leaves = [u for u in range(n) if len(edges[u]) == 1]

start = random.choice(leaves)
for u in range(n):
    random.shuffle(edges[u])
cost = 0
checked = set()
for time, u in enumerate(dfs(start)):
    if u not in checked:
        cost += time
        checked.add(u)

print(cost)
