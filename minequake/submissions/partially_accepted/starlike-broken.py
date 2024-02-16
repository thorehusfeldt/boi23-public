#! /usr/bin/env python3

# Starlike trees consist of k disjoint paths P[i] = (s[i], ..., t[i])
# connected to a single core vertex w as w--s_[1], ..., w--s[k]
# Visit such a graph by sorting the paths by length, with
# P1 is longest, and then following the unique tour
# starting in t[1] and ending in t[2].

# Broken version that sorts in the wrong direction
# This still works for path graphs

# # @EXPECTED_GRADES@ AC WA WA WA WA

n = int(input())
if n == 1:
    print(0)
    exit()
edges = [[] for _ in range(n)]
for _ in range(n - 1):
    u, v =  map(lambda x: int(x) - 1, input().split())
    edges[u].append(v)
    edges[v].append(u)

_, core = max((len(edges[u]), u) for u in range(n))
allpaths = set() # all paths from the core (minus the core)
for u in edges[core]:
    parent = core
    path = [u]
    while True:
        for v in edges[u]:
            if v != parent:
                path.append(v)
                parent = u
                u = v
                break
        else:
            break
    allpaths.add(tuple(path))

sortedpaths = sorted(allpaths, key=len)
cost = time = 0
# Travel along longest path to core
for v in sortedpaths[0]:
    cost += time
    time += 1
# visit core:
cost += time
# visit shorter paths
for path in sortedpaths[1:-1]:
    for v in path:
        time += 1 # traverse tunnel to v
        cost += time # inspect v
    for v in reversed(path):
        time += 1 # traverse tunnel from v
# finally visit shortest path (if it exists)
if len(sortedpaths) > 1:
    for v in sortedpaths[-1]:
        time += 1
        cost += time

print(cost)
