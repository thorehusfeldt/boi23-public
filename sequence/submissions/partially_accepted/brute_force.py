#! /usr/bin/env python3

# Generate all good sequences of length n,
# but restrict attention to nondecreasing
# sequences, so that “containing i” is
# the same as “ends in i”.

# @EXPECTED_GRADES@ AC TLE TLE TLE TLE TLE

n = int(input())
w = [int(input()) for _ in range(n)]

sequences = set([(1,)])
best = {i: float("inf") for i in range(1, n + 1)}
best[1] = w[1 - 1]
for _ in range(n - 1):
    extended_sequences = set()
    for s in sequences:
        ws = sum(w[j - 1] for j in s)
        for x in set([s[-1] + 1] if s[-1] < n else []) | set(
            a * b for a in set(s) for b in set(s) if s[-1] <= a * b <= n
        ):
            sx = s + (x,)
            extended_sequences.add(sx)
            best[x] = min(best[x], ws + w[x - 1])
    sequences = extended_sequences
print(*(best[i] for i in range(1, n + 1)), sep="\n")
