#! /usr/bin/env python3

# Nonrecursive DFS from every vertex

n = int(input())
edges = {u: [] for u in range(n)}
for _ in range(n - 1):
    u, v = map(lambda x: int(x) - 1, input().split())
    edges[u].append(v)
    edges[v].append(u)


# Compute dfs traversal from (arbitrarily chosen) node 0.
# Nonrecursive DFS to keep the Python gods happy.
traversal = []
visited = set()
S = [0]
while S:
    u = S.pop()
    traversal.append(u)
    if u not in visited:
        visited.add(u)
        for v in edges[u]:
            if v not in visited:
                S.append(u)
                S.append(v)


# Compute total cost corresponding to any
# traversal from 0. While we're
# here, we also compute the size of the
# subtree rooted at each node.

cost = 0
checked = set()
subtree_size = {}
for time, u in enumerate(traversal):
    if u not in checked:
        cost += time
        subtree_size[u] = 1
        checked.add(u)
    else:
        subtree_size[u] += childsize
    childsize = subtree_size[u]

# Comput answer for other starting nodes than 0

parentcost = cost
res = {0: parentcost}
for v in traversal:
    if v not in res:
        # Consider traversal that goes v, T_v, v, u, T_u
        res[v] = parentcost # a priori same as starting at u, v, T_v,...
        # but all of T_v is visisted one time step earlier:
        res[v] -= subtree_size[v]
        # u itself is now visited at time 2|E(T_v)| + 1 (rather than time 0)
        res[v] += 2 * (subtree_size[v] - 1) + 1
        # Each vertex in T_u - T_v - {u} is visited one time step earlier
        res[v] -= (n - subtree_size[v] - 1)
    parentcost = res[v]

print(min(res.values()))
