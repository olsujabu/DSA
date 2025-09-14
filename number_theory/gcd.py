# author : Buyandelger.J
# date : 20/08/2025 19:20
# title :  Greatest Common Divisor
# resource : https://www.geeksforgeeks.org/maths/greatest-common-divisor-gcd/

# 10 jild zaasan math-iin argaar
first = int(input())
second = int(input())
arr_1, arr_2 = [], []

for i in range(1, first + 1):
    if first % i == 0:
        arr_1.append(i)
for i in range(1, second + 1):
    if second % i == 0:
        arr_2.append(i)
if first == 0 and second == 0:
    print("GCD is undefined")
elif first == 0:
    print("GCD:", abs(second))
elif second == 0:
    print("GCD:", abs(first))
else:
    gcd = max(set(arr_1) & set(arr_2))
    print("GCD:", gcd)

# zaaval ingej zovooj bhin orond python-d shuud oldog library baigaa.

import math 
print("GCD :", math.gcd(first, second))
# ene library-nii tsaadah code, minii bichsen code-noos hamaagui hurdan.
# def gcd(a, b):
#     while b != 0:
#         a, b = b, a % b
#     return a