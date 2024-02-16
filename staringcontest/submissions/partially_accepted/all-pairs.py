#! /usr/bin/env python3

# Iteratively identify and remove the weakest player
# still undetermined by running everybody against everybody


n = int(input())
a = [0] * n

undetermined = list(range(n))
result = [ [None] * n for _ in range(n)]
for i in range(n):
    for j in range(n):
        if j == i:
            continue
        result[i][j] = int(input(f"? {i + 1} {j + 1}\n"))

while len(undetermined) > 1:
    for i in undetermined:
        outcomes = set(result[i][j] for j in undetermined if j != i)
        if len(outcomes) == 1:
            a[i] = outcomes.pop()
            undetermined.remove(i)
            break
a[undetermined.pop()] = max(a)
print("!", *a, flush=True)
