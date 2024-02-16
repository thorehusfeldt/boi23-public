#! /usr/bin/env python3
# @EXPECTED_GRADES@ WA AC TLE WA WA WA WA

from itertools import combinations
import sys

k, n, s, t = map(int, input().split())
stars = [tuple(map(int, input().split())) for _ in range(n)]


def dist(p, q):
    return ((p[0] - q[0])**2 + (p[1] - q[1])**2 ) ** .5

def circle(p, q, r):
    """
    Returns the center and radius of the circle passing the given 3 points.
    In case the 3 points form a line, returns (None, infinity).
    """
    temp = q[0] * q[0] + q[1] * q[1]
    bc = (p[0] * p[0] + p[1] * p[1] - temp) / 2
    cd = (temp - r[0] * r[0] - r[1] * r[1]) / 2
    det = (p[0] - q[0]) * (q[1] - r[1]) - (q[0] - r[0]) * (p[1] - q[1])

    if abs(det) < 1.0e-6:
        return (None, None)

    x = (bc*(q[1] - r[1]) - cd*(p[1] - q[1])) / det
    y = ((p[0] - q[0]) * cd - (q[0] - r[0]) * bc) / det

    radius = ((x - p[0])**2 + (y - p[1])**2) ** .5
    return ((x, y), radius)

def main():
    costs = set()
    for p in stars:
        for q in stars:
            # The assumption about optimal center is wrong
            center = (p[0] + q[0]) / 2, (p[1] + q[1]) / 2 
            radius = dist(p, q) / 2
            if sum(1 for star in stars if dist(star, center) <= radius) >= k:
                costs.add((t * radius + s * dist((0,0), center), center, radius, "2"))
    for p in stars:
        for q in stars:
            for r in stars:
                center, radius = circle(p, q, r)
                if center is None:
                    continue
                if sum(1 for star in stars if dist(star, center) <= radius) >= k:
                    costs.add((t * radius + s * dist((0,0), center), center, radius, "3"))
    cost, center, radius, three = min(costs)
    print(f"position={center}, radius={radius}, [{three}]", file=sys.stderr)
    print(cost)

main()
