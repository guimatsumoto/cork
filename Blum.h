/*
**  MA203 - TP noté
**
**  AUTHOR: Guilherme KURIKE MATSUMOTO
*/

#ifndef BLUM_H
#define BLUM_H

#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <string.h>
#include <limits.h>


// test de primalité fondé sur le théorème de Fermat
// retourne un entier non nul si n est premier (pseudo premier) et 0 sinon
int Fermat(const mpz_t n, unsigned int k, gmp_randstate_t state);

// retourne un entier premier qui congru à 3 modulo 4
void Genpremier(unsigned int k, mp_bitcnt_t size, gmp_randstate_t state, mpz_t *n);

// lire une clé publique
void read_pub_key(char *file, mpz_t *n);

// écrire une clé publique
void write_pub_key(char *file, mpz_t n);

// lire une clé privée
void read_key(char *file, mpz_t *p, mpz_t *q);

// écrire une clé privée
void write_key(char *file, mpz_t p, mpz_t q);

// lire un texte clair
void read_plaintext(char *file, char **plaintext, unsigned long *size);

// écrire un texte clair
void write_plaintext(char *file, char *plaintext, unsigned long size);

// lire un texte chiffré
void read_ciphertext(char *file, char **ciphertext, unsigned long *size, mpz_t *x);

// écrire un texte chiffré
void write_ciphertext(char *file, char *ciphertext, unsigned long size, mpz_t x);

// une étape de Blum Blum Shub
char BBS_step(mpz_t *x, mpz_t n);

#endif /* BLUM_H */
