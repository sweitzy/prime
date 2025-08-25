// prime.c: calculate prime numbers

// $Id: prime.c,v 1.10 2025/08/25 01:00:27 scott Exp scott $

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// https://www.mathsisfun.com/prime_numbers.html

//#define DEBUG(...) printf(__VA_ARGS__)
#define DEBUG(...)

//#define OUTPUT(...) printf(__VA_ARGS__)
#define OUTPUT(...)

// wow, have to actually do  something, or -O will optimize away!
int prime(int min, int max) {
  int num_primes = 0;
  
  // check for min > max
  if (min > max) {
    fprintf(stderr, "ERROR: min %d must be <= max %d\n", min, max);
    return -1;
  }

  // if all negative numbers, nothing to do
  if (max < 2) {
    return num_primes;
  }

  // special case < 3: 2 is prime
  if (min < 3) {
    OUTPUT("2\n");
    num_primes++;
  }

  for (int i = 3; i <= max; i++) {
    DEBUG("CHECKING %d\n", i);

    // special case: even number
    if (i % 2 == 0) {
      DEBUG("  %d: EVEN NOT PRIME\n", i);
      continue;
    } 

    int is_prime = true;

    // try to divide (odd) number by all lower odd numbers, count up
    // instead of down as we are more likely to be able to divide by
    // lower (odd) numbers, this is more readable too!


    // Newer ChatGPT code Aug 2025 vs Jan 2024 has an interesting improvment
    // involving square root.

    // You use the square root when checking for prime numbers because
    // if a number, n, is composite (not prime), it can be factored
    // into two numbers, a and b, such that n = a x b. If you find a
    // factor a greater than the square root of n, there must be a
    // corresponding factor b that is less than the square root of
    // n. Therefore, you only need to check for factors up to the
    // square root of n to determine if n has any factors other than 1
    // and itself.  HUGE SPEEDUP!

    for (int up = 3; up * up <= i; up += 2) {
      DEBUG("i %d up %d\n", i, up);
      if (i % up == 0) {
	DEBUG("i %d mod up %d is not prime\n", i, up);
	is_prime = false;
	break;
      }
    }
    
    if (is_prime) {
      OUTPUT("%d\n", i);
      num_primes++;
    } else {
      DEBUG("  %d: NOT PRIME\n", i);
    }	    
  }

  return num_primes;
}

int main(int argc, char **argv) {
  int num_primes = -1;
  
  // TODO: option to skip output, just time output?  I kinda lkke
  // compile time option instead.  Can use multiple makefile targets
  // too.
  
  if (argc == 3) {
    num_primes = prime(atoi(argv[1]), atoi(argv[2]));
  } else if (argc == 2) {
    num_primes = prime(1, atoi(argv[1]));
  } else {

    // pick a reasonable set
    
    // TODO: just print usage message?

    num_primes = prime(-2, 1000000);
  }

  printf("num_primes = %d\n", num_primes);
  return 0;
}

