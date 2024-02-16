#!/usr/bin/env python3
# @EXPECTED_GRADES@ AC AC AC AC WA WA WA
import random

b, k, _ = map(int, input().split())


def query(px, py):
    return map(int, input(f"? {px} {py}\n").split())


def distance(p, q):
    return abs(p[0] - q[0]) + abs(p[1] - q[1])

def candidate(sw, se):
    y = (sw + se - 4 * b) // 2
    x = y + 2 * b - se
    return (x, y) if -b <= x <= b and -b <= y <= b else None

distances_sw = list(query(-b, -b))
distances_se = list(query(b, -b))
candidates = set(
        candidate(sw, se) for sw in distances_sw for se in distances_se
)
candidates.discard(None)

candidates = list(candidates)
deposits = []
while len(candidates) > 0:
    r = random.choice(candidates)
    distances = set(query(*r))
    if 0 in distances:
        deposits.append(r)
        candidates.remove(r)
    candidates = [p for p in candidates if distance(p, r) in distances]

print("!", " ".join(f"{d[0]} {d[1]}" for d in deposits), flush=True)
