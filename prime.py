#!/usr/bin/env python3

# prime.py: calculate prime numbers

# $Id: prime.py,v 1.2 2025/08/04 03:42:55 scott Exp scott $

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

#        # try to divide (odd) number by all lower odd numbers
#        #my_range = list(range(i - 2, 2, -2))
#        ###print(f"my_range {my_range}")
#        for down in range(i - 2, 2, -2):
#            ###print(f"i {i} down {down}")
#            if i % down == 0:
#                ###print(f"i {i} mod down {down} is not prime")
#                is_prime = False
#                break

        # try to divide (odd) number by all lower odd numbers, count up
        # instead of down as we are more likely to be able to divide by
        # lower (odd) numbers, this is more readable too!
        for up in range(3, i - 1, +2):
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

num_primes = prime(1, 1000000)
#num_primes = prime(1, 100)
print(f"num_primes = {num_primes}")
