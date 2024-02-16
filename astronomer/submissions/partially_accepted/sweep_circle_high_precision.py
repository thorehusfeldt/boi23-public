#! /usr/bin/env python3
# @EXPECTED_GRADES@ AC AC AC AC AC AC AC

from math import sqrt,atan2,pi
import sys
import random

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

def err(a,b):
    d = abs(b-a)
    m = max(1,max(abs(a),abs(b)))
    return d/m

k,n,s,t = map(int,input().split())
if(s == 0 and t == 0):
    print(0)
    sys.exit(0)
s = s
t = t
ot = t
s /= t
t = 1

ps = []

for i in range(n):
    x,y = map(int, input().split())
    ps.append(Point(x,y))

cb = [[0 for _ in range(n)] for _ in range(n)]  
cmp = [[0 for _ in range(n)] for _ in range(n)]  

random.shuffle(ps)

eps = 10**-15

if t <= s:
    d = list(map(lambda x: x.dist(), ps))
    d.sort()
    print("%.20f" % (d[k-1] * ot))
    sys.exit(0)

for i in range(n):
    for j in range(i):
        mp = (ps[j]+ps[i])/2
        dir = (ps[j]-ps[i]).unit().perp()
        mi = -10**9
        ma = 10**9
        while(err(mi,ma) > eps):
            md1 = (mi*2 + ma)/3
            md2 = (mi + ma*2)/3
            
            cs1 = (dir*md1 + mp).dist()*s + (dir*md1 + mp-ps[i]).dist()*t
            cs2 = (dir*md2 + mp).dist()*s + (dir*md2 + mp-ps[i]).dist()*t
            if(cs1 <= cs2):
                ma = md2
            else:
                mi = md1

        cmp[i][j] = (mi + ma)/2
        cb[i][j] = cb[j][i] = (dir*cmp[i][j] + mp).dist()*s + (dir*cmp[i][j] + mp-ps[i]).dist()*t
        cmp[j][i] = -cmp[i][j]

def sweep(u,cst):
    if(ps[u].dist()*s > cst): return False
    e = []
    for v in range(n):
        if u == v: continue
        if cb[u][v] > cst: continue

        mp = (ps[u]+ps[v])/2
        dir = (ps[v]-ps[u]).unit().perp()

        lmi = -10**18
        lma = cmp[u][v]
        rmi = cmp[u][v]
        rma = 10**18

        while(err(lmi,lma) > eps):
            md = (lmi + lma)/2
            cs = (dir*md + mp).dist()*s + (dir*md + mp-ps[u]).dist()*t
            if cs < cst:
                lma = md
            else:
                lmi = md
        
        while(err(rmi,rma) > eps):
            md = (rmi + rma)/2
            cs = (dir*md + mp).dist()*s + (dir*md + mp-ps[u]).dist()*t
            if cs < cst:
                rmi = md
            else:
                rma = md


        langle = (mp + dir*(lmi + lma)/2-ps[u]).angle()
        rangle = (mp + dir*(rmi + rma)/2-ps[u]).angle()
        e.append((langle,1))
        e.append((rangle,-1))

        if langle > rangle:
            e.append((-pi,1))
            e.append((pi,-1))
    #print(u,cst)
    e.sort()
    cr = 1
    if cr >= k:
        return True
    for v in e:
        cr += v[1]
        if cr >= k: return True
    return False


best = 10**20

for i in range(n):
    better = best - eps
    if not sweep(i,better): continue

    mi = 0
    ma = better
    while(err(ma,mi) > eps):
        md = (ma+mi)/2
        if sweep(i,md):
            ma = md
        else:
            mi = md
    best = (ma+mi)/2

print(best*ot)