#! /usr/bin/env python3

# Assumes graph is a path without even looking at the input.

# # @EXPECTED_GRADES@ AC WA WA WA WA

n = int(input())
print(n * (n - 1) // 2)
