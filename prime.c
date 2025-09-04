// prime.c: calculate prime numbers

// $Id: prime.c,v 1.15 2025/09/04 03:11:32 scott Exp scott $

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// https://www.mathsisfun.com/prime_numbers.html
// TODO: write a program to compare my results with this site

// C is unique in that is has a preprocessor, which people like the X
// Window System group abused horribly in the 80's with their imake
// utility (using C macros to create Makefiles, clever but so fugly).
// I have to admit I used it to at my Talarian startup to generate
// platform-specific Makefiles.

#if 0
#define DEBUG(...) printf(__VA_ARGS__)
#define OUTPUT(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#define OUTPUT(...)
#endif

// wow, have to actually do  something, or -O will optimize away!
int prime(int min, int max) {
  int num_primes = 0;
  
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
    // and itself.  HUGE SPEEDUP!  This is O(sqrt), there are faster,
    // more complicated algorithms, but that's not what I'm going for
    // here.

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

  // defaults
  int min = -2;
  int max = 50000000;
  
  // TODO: option to skip output, just time output?  I kinda lkke
  // compile time option instead.  Can use multiple makefile targets
  // too.
  
  if (argc == 3) {
    min = atoi(argv[1]);
    max = atoi(argv[2]);
  } else if (argc == 2) {
    max = atoi(argv[1]);
  }

  // check for min > max
  if (min > max) {
    fprintf(stderr, "ERROR: min %d must be <= max %d\n", min, max);
    return 1;
  }

  num_primes = prime(min, max);

  printf("min = %d, max = %d, num_primes = %d\n", min, max, num_primes);
  return 0;
}
