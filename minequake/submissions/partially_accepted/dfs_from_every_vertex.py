#! /usr/bin/env python3

# Nonrecursive DFS from every vertex

# Quadratic time, fine for instances up to 1000 halls or so

# @EXPECTED_GRADES@ TLE TLE AC AC TLE

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
for start in range(n):
    cost = 0
    checked = set()
    for time, u in enumerate(dfs(start)):
        if u not in checked:
            cost += time
            checked.add(u)
    costs.add(cost)
print(min(costs))
