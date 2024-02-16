#! /usr/bin/env python3
# @EXPECTED_GRADES@ AC WA WA WA WA AC WA
from math import sqrt,atan2,pi
import sys
import random
eps = 1e-4
class Point:
    def __init__(self,x,y):
        self.x = x
        self.y = y
    def dist(self):
        return sqrt(self.x**2 + self.y**2)
    def __add__(self, other):
        return Point(self.x + other.x, self.y + other.y)
    def __sub__(self, other):
        return Point(self.x - other.x, self.y - other.y)
    def __mul__(self, other):
        return Point(self.x * other, self.y * other)
    def __truediv__(self,other):
        return Point(self.x/other,self.y/other)
    def perp(self):
        return Point(-self.y,self.x)
    def unit(self):
        return self/self.dist()
    def angle(self):
        return atan2(self.y, self.x)

k,n,s,t = map(int,input().split())

ps = []

for i in range(n):
    x,y = map(int, input().split())
    ps.append(Point(x,y))

def sweep(u,cst):
    if(ps[u].dist()*s > cst): return False
    e = []
    for v in range(n):
        if v == u: continue
        md = (ps[u] + ps[v]) / 2
        dir = (ps[v]-ps[u]).perp().unit()
        lmn = -1e9
        lmx = 1e9
        rmn = -1e9
        rmx = 1e9
        mcost = 1e18
        while lmn + abs(lmn*eps) < lmx and lmn + eps < lmx:
            lmd1 = (2*lmn + lmx) / 3
            lmd2 = (lmn + 2*lmx) / 3

            #print(lmn,lmx)
            cs1 = (Point(md.x + dir.x*lmd1 - ps[u].x,md.y + dir.y*lmd1 - ps[u].y)).dist()*t + (Point(md.x + dir.x*lmd1,md.y + dir.y*lmd1)).dist()*s
            cs2 = (Point(md.x + dir.x*lmd2 - ps[u].x,md.y + dir.y*lmd2 - ps[u].y)).dist()*t + (Point(md.x + dir.x*lmd2,md.y + dir.y*lmd2)).dist()*s
            dcst = cs2-cs1
            mcost = min(mcost,cs1)
            if cs1 <= cst or dcst > 0:
                lmx = lmd2
                if cs2 > cst: rmx = lmd2
            else:
                lmn = lmd1
        rmn = lmn

        while rmn + abs(rmn*eps) < rmx and rmn + eps < rmx:
            rmd1 = (2*rmn + rmx) / 3
            rmd2 = (rmn + 2*rmx) / 3

            cs1 = (Point(md.x + dir.x*rmd1 - ps[u].x,md.y + dir.y*rmd1 - ps[u].y)).dist()*t + (Point(md.x + dir.x*rmd1,md.y + dir.y*rmd1)).dist()*s
            cs2 = (Point(md.x + dir.x*rmd2 - ps[u].x,md.y + dir.y*rmd2 - ps[u].y)).dist()*t + (Point(md.x + dir.x*rmd2,md.y + dir.y*rmd2)).dist()*s
            dcst = cs2-cs1
            mcost = min(mcost,cs1)

            if cs2 <= cst or dcst < 0:
                rmn = rmd1
            else:
                rmx = rmd2
        if mcost > cst:
            continue

        langle = (md + dir*lmn-ps[u]).angle()
        rangle = (md + dir*rmn-ps[u]).angle()
        e.append((langle,1))
        e.append((rangle,-1))

        if langle > rangle:
            e.append((-pi,1))
            e.append((pi,-1))
    e.sort()
    cr = 1
    if cr >= k:
        return True
    for v in e:
        cr += v[1]
        if cr >= k: return True
    return False

def construct(cst):
    for i in range(n):
        if sweep(i,cst): return True
    return False

def main():
    if t <= s:
        d = list(map(lambda x: x.dist(), ps))
        d.sort()
        print(d[k-1] * t)
        return

    mic = 0
    mac = 1e18
    while mic + abs(mic*eps) < mac and mic + eps < mac:
        md = (mic + mac) / 2
        r = construct(md)
        #print(md,r)
        if(r):
            mac = md
        else:
            mic = md
    best = (mic + mac) / 2 
            
    print(best)

main()
