# author : Buyandelger.J
# date : 21/08/2025 15:20
# title :  Fermit's little Theorem 
# resource : https://www.geeksforgeeks.org/dsa/fermats-little-theorem/


p = 859
a = 8
exponent = a ** (p - 1)
equation = exponent % p # => 1

print(equation)
print((exponent - 1) % p)
# hervee exponent deer -1 hiivel p toond huvaagdana. 

# example : 3^100,000 by 53.
p2 = 53
b = 3
exponent = b ** (p2 - 1)
equation = exponent % p2

print(equation)