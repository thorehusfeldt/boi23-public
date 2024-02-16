#!/usr/bin/env python3

# Pedestrian pythonification of lucas_imp_seg.cpp
# @EXPECTED_GRADES@ AC AC AC AC AC TLE TLE
# TODO expected grade for group 6 is not clear to me... TLE/AC?

MAX = (1 << 40) - 1
INF = 2 * 10**18

seg = [INF]
lazy = [0]
L = [-1]
R = [-1]


def push(i):
    if L[i] != -1:
        seg[L[i]] += lazy[i]
        lazy[L[i]] += lazy[i]
    if R[i] != -1:
        seg[R[i]] += lazy[i]
        lazy[R[i]] += lazy[i]
    lazy[i] = 0


def upd(p, v, a=0, b=MAX, i=0):
    if a == b:
        seg[i] = v
    else:
        push(i)
        m = (a + b) // 2
        if p <= m:
            if L[i] == -1:
                L[i] = len(seg)
                seg.append(INF)
                lazy.append(0)
                L.append(-1)
                R.append(-1)
            upd(p, v, a, m, L[i])
        else:
            if R[i] == -1:
                R[i] = len(seg)
                seg.append(INF)
                lazy.append(0)
                L.append(-1)
                R.append(-1)
            upd(p, v, m + 1, b, R[i])
        seg[i] = INF
        if L[i] != -1:
            seg[i] = min(seg[i], seg[L[i]])
        if R[i] != -1:
            seg[i] = min(seg[i], seg[R[i]])


def add(l, r, v, a=0, b=MAX, i=0):
    if l <= a and b <= r:
        seg[i] += v
        lazy[i] += v
    elif b < l or r < a:
        return
    else:
        push(i)
        m = (a + b) // 2
        if L[i] != -1:
            add(l, r, v, a, m, L[i])
        if R[i] != -1:
            add(l, r, v, m + 1, b, R[i])
        seg[i] = INF
        if L[i] != -1:
            seg[i] = min(seg[i], seg[L[i]])
        if R[i] != -1:
            seg[i] = min(seg[i], seg[R[i]])


def circ_add(l, r, v):
    if l <= r:
        add(l, r, v)
    else:
        add(l, MAX, v)
        add(0, r, v)


def qry(p, a=0, b=MAX, i=0):
    if a == b:
        return seg[i]
    push(i)
    m = (a + b) // 2
    return qry(p, a, m, L[i]) if p <= m else qry(p, m + 1, b, R[i])


def main():
    z, m, c, n = map(int, input().split())
    n += 1  # add imaginary hiding spot at 0 to make implementation easier
    a = [0]
    for i in range(1, n):
        a.append(int(input()))

    upd(0, -c - m)
    to_add = 0
    last = 0
    for i in range(1, n):
        d = a[i] - last
        to_add += (c + m) * ((d - 1) // m)
        l, r = last % m, (a[i] - 1) % m
        circ_add(l, r, c + m)
        dp = seg[0] + m
        upd(a[i] % m, dp - c - m)
        last = a[i]
    d = z - last
    to_add += (c + m) * ((d - 1) // m)
    l, r = last % m, (z - 1) % m
    circ_add(l, r, c + m)
    answers = []
    for i in range(n):
        x = qry(a[i] % m)
        x += (z - a[i]) % m
        if (z - a[i]) % m == 0:
            x += m
        answers.append(x)
    print(min(answers) + to_add)


main()
