#! /usr/bin/env python3
# @EXPECTED_GRADES@ AC RTE RTE RTE RTE RTE RTE
""" Works for k = 1 (i.e., a single hidden point) """

b, k, _ = map(int,input().split())
assert k == 1
print(f"? {-b} {-b} {-b} {b}", flush=True)
da, db = map(int, input().split())
print(f"? {-b} {-b}", flush=True)
d = int(input())
if d == db:
    da, db = db, da
x = (da + db - 2*b)//2-b
y = da - (b + x) - b
print(f"! {x} {y}", flush=True)
