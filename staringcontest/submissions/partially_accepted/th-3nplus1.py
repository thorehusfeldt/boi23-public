#! /usr/bin/env python3

# Very preliminary AC submission to use for development.
# Will end up solving just test group 1 (and thus has to move to submissions/PAC).

n = int(input())
j, k = 0, 1
res = [0] * n
for i in range(2, n):
    # invariant:  sorted([a[j], a[k]) == sorted(a[:i])[-2:]
    ij = int(input(f"? {i+1} {j+1}\n"))
    ik = int(input(f"? {i+1} {k+1}\n"))
    jk = int(input(f"? {j+1} {k+1}\n"))
    if ij == ik: # a[i] < a[j] and a[i] < a[k]
        res[i] = ij
    if ij == jk: # a[j] < a[i] and a[j] < a[k]
        res[j] = ij
        j = i
    if ik == jk: # a[k] < a[i] and a[k] < a[j]
        res[k] = ik
        k = i
res[j] = res[k] = int(input(f"? {j+1} {k+1}\n"))
print("!", *res, flush=True)
