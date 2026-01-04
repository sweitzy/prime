// prime.c: calculate prime numbers

// $Id: prime.c,v 1.18 2026/01/04 05:39:19 scott Exp scott $

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

// https://www.mathsisfun.com/prime_numbers.html
// I looked at the code for this site, and it has a list of
// primes < 100,000 hardcoded in images/prime-is-it.js.
// My list and this list check out.

// C is unique in that is has a preprocessor, which people like the X
// Window System group abused horribly in the 80's with their imake
// utility (using C macros to create Makefiles, clever but so fugly).
// I have to admit I used it to at my Talarian startup to generate
// platform-specific Makefiles.

// Enabling OUTPUT will print every prime number.
#if 0
#define OUTPUT(...) printf(__VA_ARGS__)
#else
#define OUTPUT(...)
#endif

// Enabling DEBUG will print debug info about each test.
#if 0
#define DEBUG(...) printf(__VA_ARGS__)
#else
#define DEBUG(...)
#endif

// wow, have to actually do  something, or -O will optimize away!
int prime(int min_val, int max_val) {
  int num_primes = 0;
  
  // if all negative numbers, nothing to do
  if (max_val < 2) {
    return num_primes;
  }

  // special case < 3: 2 is prime
  if (min_val < 3) {
    OUTPUT("2\n");
    num_primes++;
  }

  for (int i = 3; i <= max_val; i++) {
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

    // Python ChatGPT code uses range(), and makes one call to sqrt()
    // instead of checking up * up <= i, and this speeds up the Python
    // code quite a bit (342 sec down to 193 sec!).  The C speedup
    // is neglible, but Pythonic range() is important.
    int limit = (int)sqrt(i);

    for (int up = 3; up <= limit; up += 2) {
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
  int min_val = 1;
  int max_val = 50000000;
  
  // TODO: option to skip output, just time output?  I kinda lkke
  // compile time option instead.  Can use multiple makefile targets
  // too.
  
  if (argc == 3) {
    min_val = atoi(argv[1]);
    max_val = atoi(argv[2]);
  } else if (argc == 2) {
    max_val = atoi(argv[1]);
  }

  // check for min_val > max_val
  if (min_val > max_val) {
    fprintf(stderr, "ERROR: min %d must be <= max %d\n", min_val, max_val);
    return 1;
  }

  num_primes = prime(min_val, max_val);

  printf("min = %d, max = %d, num_primes = %d\n", min_val, max_val, num_primes);
  return 0;
}
