#!/usr/bin/env python3

# prime.py: calculate prime numbers

# $Id: prime.py,v 1.7 2026/01/04 05:45:46 scott Exp scott $

import sys
import math

def prime(min_val, max_val):
    num_primes = 0 

    if min_val > max_val:
        return num_primes

    if max_val < 2:
        return num_primes
    
    if min_val < 3:
        num_primes += 1
        
    for i in range(3, max_val + 1):
        if i % 2 == 0:
            continue

        is_prime = True

        for up in range(3, int(math.sqrt(i)) + 1, +2):
            if i % up == 0:
                is_prime = False
                break

        if is_prime:
            num_primes += 1

    return num_primes

def main():
    min_val = 1
    max_val = 50000000

    argc = len(sys.argv)
    if argc == 3:
        min_val = int(sys.argv[1])
        max_val = int(sys.argv[2])
    elif argc == 2:
        max_val = int(sys.argv[1])

    if min_val > max_val:
        print(f"ERROR: min {min_val} must be <= max {max_val}", file=sys.stderr)
        sys.exit(1)

    num_primes = prime(min_val, max_val)
    print(f"min = {min_val}, max = {max_val}, num_primes = {num_primes}")

if __name__ == "__main__":
    main()
