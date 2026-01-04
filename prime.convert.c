// prime.convert.c: stripped down code to feed to http://codeconvert.ai

// $Id: prime.convert.c,v 1.3 2026/01/04 05:41:51 scott Exp scott $

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int prime(int min_val, int max_val) {
  int num_primes = 0;
  
  if (max_val < 2) {
    return num_primes;
  }

  if (min_val < 3) {
    num_primes++;
  }

  for (int i = 3; i <= max_val; i++) {
    if (i % 2 == 0) {
      continue;
    } 

    int is_prime = true;

    int limit = (int)sqrt(i);

    for (int up = 3; up <= limit; up += 2) {
      if (i % up == 0) {
	is_prime = false;
	break;
      }
    }
    
    if (is_prime) {
      num_primes++;
    }
  }

  return num_primes;
}

int main(int argc, char **argv) {
  int num_primes = -1;

  int min_val = 1;
  int max_val = 50000000;
  
  if (argc == 3) {
    min_val = atoi(argv[1]);
    max_val = atoi(argv[2]);
  } else if (argc == 2) {
    max_val = atoi(argv[1]);
  }

  if (min_val > max_val) {
    fprintf(stderr, "ERROR: min %d must be <= max %d\n", min_val, max_val);
    return 1;
  }

  num_primes = prime(min_val, max_val);

  printf("min = %d, max = %d, num_primes = %d\n", min_val, max_val, num_primes);
  return 0;
}
