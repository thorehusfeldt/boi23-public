#! /usr/bin/env python3

n = int(input())
edges = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v = map(lambda x: int(x) - 1, input().split())
    edges[u].append(v)
    edges[v].append(u)


traversal = []
visited = set()
S = [0]
cost = time = 0
while S:
    u = S.pop()
    traversal.append(u)
    if u not in visited:
        cost += time
        visited.add(u)
        for v in edges[u]:
            if v not in visited:
                S.append(u)
                S.append(v)
    time += 1

sz = {}
for u in traversal:
    prev = sz[u] = 1 if u not in sz else sz[u] + prev

res = {0: cost}
for v in traversal:
    if v not in res:
        res[v] = cost + 2 * sz[v] - n
    cost = res[v]

print(min(res.values()))
