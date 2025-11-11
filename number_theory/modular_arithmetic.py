# 
# author : Buyandelger.J
# date : 20/08/2025 18:48
# title : Modular Arithmetic
# resource : https://www.geeksforgeeks.org/engineering-mathematics/modular-arithmetic/

def modular_arithmetic():
    a = 38
    b = 14
    divisor = 12
    r1 = 38 % divisor
    r2 = 14 % divisor

    if r1 == r2 : # 2 == 2
        print(a % divisor) # => remainder (38 ≡ 14 (mod 12))
# 2 natural toog adilhan toon huvaagaad adilhan remainder garch 
# baival 2 natural toogoo hoorond ni module avahad remainder mun garna. 
modular_arithmetic()

def addition_modular_arithmetic():
    # Compute (27 + 19) mod 7
    # 27 = 7 * 3 + 6
    # 19 = 7 * 2 + 5
    # (27 + 19) mod 7 => (6 + 5) mod 7 = 4
    return

def multiplication_modular_arithmetic():
    # Compute (23 × 17) mod 5
    # 23 = 5 * 4 + 3
    # 17 = 5 * 3 + 2
    # 2 * 3 mod 5 = 1
    return 

def modular_exponentiation():
    # euler's theorem
    return 