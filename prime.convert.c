// prime.convert.c: stripped down code to feed to http://codeconvert.ai

// $Id: prime.convert.c,v 1.2 2026/01/04 05:24:54 scott Exp scott $

#include <stdio.h>
#include <stdbool.h>

int prime(int min, int max) {
  int num_primes = 0;
  
  if (max < 2) {
    return num_primes;
  }

  if (min < 3) {
    num_primes++;
  }

  for (int i = 3; i <= max; i++) {

    if (i % 2 == 0) {
      continue;
    } 

    int is_prime = true;

    for (int up = 3; up * up <= i; up += 2) {
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

  // defaults
  int min = 1;
  int max = 50000000;
  
  if (argc == 3) {
    min = atoi(argv[1]);
    max = atoi(argv[2]);
  } else if (argc == 2) {
    max = atoi(argv[1]);
  }

  if (min > max) {
    fprintf(stderr, "ERROR: min %d must be <= max %d\n", min, max);
    return 1;
  }

  num_primes = prime(min, max);

  printf("min = %d, max = %d, num_primes = %d\n", min, max, num_primes);
  return 0;
}
