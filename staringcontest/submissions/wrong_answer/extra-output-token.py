#! /usr/bin/env python3

# Exactly like th.py put prints extra ouput

from random import shuffle

query = lambda x, y: int(input(f"? {x+1} {y+1}\n"))

n = int(input())
res = [0] * n
ids = list(range(n))
shuffle(ids)
j, k = ids[:2]
min_jk = query(j, k)
for i in ids[2:]:
    min_ij = query(i, j)
    if min_ij < min_jk:
        res[i] = min_ij
    else:
        if min_ij == min_jk:
            res[j] = min_ij
            j = i
        else:
            res[k] = min_jk
            k = i
        min_jk = query(j, k)
res[j] = res[k] = min_jk
print("!", *res, "spam", flush=True)
