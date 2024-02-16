#! /usr/bin/env python3

# Iteratively identify and remove the weakest player
# still undetermined by running everybody against everybody

# Too slow; also uses too many queries

n = int(input())
a = [0] * n

undetermined = list(range(n))

while len(undetermined) > 1:
    for i in undetermined:
        outcomes = set()
        for j in undetermined:
            if j == i:
                continue
            outcomes.add(int(input(f"? {i + 1} {j + 1}\n")))
        if len(outcomes) == 1:
            a[i] = outcomes.pop()
            undetermined.remove(i)
            break
a[undetermined.pop()] = max(a)
print("!", *a, flush=True)
