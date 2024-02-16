#! /usr/bin/env python3

# O(n) solution

# Runs out of recursion stack, so RTEs on most large test groups.
# Haven't fiddled with sys.setrecursionlimit because it's machine-
# and compiler-dependent.

# @EXPECTED_GRADES@ RTE RTE AC AC RTE



n = int(input())
g = [[] for _ in range(n)]
for _ in range(n-1):
    a, b = map(int, input().split())
    a -= 1
    b -= 1
    g[a].append(b)
    g[b].append(a)

ans = [None] * n
size = [1] * n
def dfs_1(u, p=None):
    ret = 0
    for e in g[u]:
        if e != p:
            ret += dfs_1(e, u)
            ret += size[e] * (2*size[u] - 1)
            size[u] += size[e]
    return ret

ans[0] = dfs_1(0)

def dfs_2(u, p = None):
    for e in g[u]:
        if e != p:
            ans[e] = ans[u] - (n-size[e]) + size[e]
            dfs_2(e, u)

dfs_2(0)
print(min(ans))

