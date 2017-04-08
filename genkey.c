/*
**  MA203 - TP noté
**
**  AUTHOR: Guilherme KURIKE MATSUMOTO
*/

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <Blum.h>

int main(int argc, char *argv[]){
  if (argc != 4) {
    fprintf(stderr, "Usage : %s <filename of the public key> <filename of the private key> <size of the key>\n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // A completer

  mpz_t p, q, n;
  mpz_inits(p, q, n, NULL);
  gmp_randstate_t state;
  gmp_randinit_default (state);
  unsigned int k = 10000;	//I guess it's ok, should assure an actual prime number

  //retrieving argv parameters just in case we change them when we shouldn't
  mp_bitcnt_t size = 0;
  sscanf(argv[3], "%lu", &size);
  printf("%lu\n", size);
  char *file_pubkey = argv[1];
  char *file_key = argv[2];

  //generating both p and q, primes of size that was passed by argv
  Genpremier(k, size, state, &p);
  Genpremier(k, size, state, &q);

  mpz_mul(n, p, q);

  //saving keys
  write_pub_key(file_pubkey, n);
  write_key(file_key, p, q);

  mpz_clears(p, q, n, NULL);
  exit(EXIT_SUCCESS);
}
