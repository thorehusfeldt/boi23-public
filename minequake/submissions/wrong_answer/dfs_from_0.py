#! /usr/bin/env python3

# Single DFS from first vertex
# Fails on a path unless the first vertex is an endpoint

# @EXPECTED_GRADES@ WA WA WA WA WA

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



cost = 0
checked = set()
for time, u in enumerate(dfs(0)):
    if u not in checked:
        cost += time
        checked.add(u)

print(cost)
