#!/usr/bin/env python3

# prime.py: calculate prime numbers

# $Id: prime.py,v 1.5 2025/08/26 16:06:28 scott Exp scott $

import math

def prime(min, max):
    num_primes = 0 

    # check for min > max
    if min > max:
        # TODO: stderr
        print(f"ERROR: min {min} must be <= max {max}")
        return -1

    # if all negative numbers, nothing to do
    if max < 2:
        return num_primes
    
    # special case < 3: 2 is prime
    if min < 3:
        ###print("2")
        num_primes += 1
        
    for i in range(3, max + 1):
        ###print(f"CHECKING {i}")

        # special case: even number
        if i % 2 == 0:
            ###print(f"  {i} EVEN NOT PRIME")
            continue

        is_prime = True

        for up in range(3, int(math.sqrt(i)) + 1, +2):
            ###print(f"i {i} up {up}")
            if i % up == 0:
                ###print(f"i {i} mod up {up} is not prime")
                is_prime = False
                break

        if is_prime:
            ###print(f"{i}")
            num_primes += 1
        #else:
            ###print(f"  {i}: NOT PRIME")

    return num_primes

###print("Entering main.")

# TODO: command-line arguments

min = 1
max = 50000000
num_primes = prime(min, max)
#num_primes = prime(1, 100)
print(f"min = {min}, max = {max}, num_primes = {num_primes}")
