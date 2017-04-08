/*
**  MA203 - TP noté
**
**  AUTHOR: Guilherme KURIKE MATSUMOTO
*/

#include <Blum.h>

int Fermat(const mpz_t n, unsigned int k, gmp_randstate_t state) {
  // n est-il pair?
  if(mpz_divisible_2exp_p(n, 1)) return 0;

  int res = 1;
  mpz_t a, bound, e, tmp;
  mpz_init(a);
  mpz_init(tmp);
  mpz_init_set(bound, n);
  mpz_sub_ui(bound, bound, 3);
  mpz_init_set(e, n);
  mpz_sub_ui(e, e, 1);

  for( ; k > 0 ; k--){
    mpz_add_ui(a, a, 2); // 1 < a < n-1

    mpz_gcd(tmp, a, n);
    if(mpz_cmp_ui(tmp, 1)) {
      res = 0;
      break;
    }

    mpz_powm(tmp, a, e, n);
    if(mpz_cmp_ui(tmp, 1)) {
      res = 0;
      break;
    }
  }
  mpz_clear(a);
  mpz_clear(bound);
  mpz_clear(e);
  mpz_clear(tmp);
  return res;
}

void Genpremier(unsigned int k, mp_bitcnt_t size, gmp_randstate_t state, mpz_t *n){
  mpz_t r;
  mpz_init(r);
  while(1){
    mpz_urandomb (*n, state, size);
    if (Fermat(*n,k,state)) {
      mpz_mod_ui(r,*n,4);
      if (!mpz_cmp_ui(r,3)) {
        mpz_clear(r);
        return;
      }
    }
  }
}


void read_pub_key(char *file, mpz_t *n) {
  FILE *fd = fopen(file, "r");
  if (fd == NULL) {
    fprintf(stderr, "%s does not exist !\n", file);
    exit(EXIT_FAILURE);
  }
  fseek(fd, 0, SEEK_END);
  unsigned long size=ftell(fd);
  rewind(fd);
  char line[size+1];
  fgets(line, size+1, fd);
  mpz_set_str(*n, line, 10);
  fclose(fd);
}

void write_pub_key(char *file, mpz_t n) {
  FILE *fd = fopen(file, "w");
  mpz_out_str(fd, 10, n);
  fclose(fd);
}

void read_key(char *file, mpz_t *p, mpz_t *q) {
  FILE *fd = fopen(file, "r");
  if (fd == NULL) {
    fprintf(stderr, "%s does not exist !\n", file);
    exit(EXIT_FAILURE);
  }
  fseek(fd, 0, SEEK_END);
  unsigned long size=ftell(fd);
  rewind(fd);
  char line[size];
  fgets(line, size, fd);

  char *val = strtok(line, "(;)");
  mpz_set_str(*p, val, 10);
  val = strtok(NULL, "(;)");
  mpz_set_str(*q, val, 10);

  fclose(fd);
}


void write_key(char *file, mpz_t p, mpz_t q) {
  FILE *fd = fopen(file, "w");
  gmp_fprintf(fd, "(%Zd;%Zd)", p,q);
  fclose(fd);
}

void read_plaintext(char *file, char **plaintext, unsigned long *size) {
  char c;
  int i;
  unsigned long j = 0;
  FILE *fd = fopen(file, "r");
  fseek(fd, 0, SEEK_END);
  *size = ftell(fd);
  (*size) *= 8;
  rewind(fd);
  *plaintext = (char *)malloc((*size));
  while ((c = fgetc(fd)) != EOF) {
    // read bits from byte
    for(i = 0 ; i < 8 ; ++i) {
      (*plaintext)[j] = (c & 128 ? 1 : 0);
      c <<= 1;
      ++j;
    }
  }
  fclose(fd);
}

void write_plaintext(char *file, char *plaintext, unsigned long size) {
  char c = 0;
  int i;
  unsigned long j = 0;
  FILE *fd = fopen(file, "w");
  while( j < size ) {
    // make byte
    for(i = 0 ; i < 8 ; ++i) {
      c <<= 1;
      c ^= (plaintext[j] ? 1 : 0);
      ++j;
    }
    fprintf(fd, "%c", c);
    c = 0;
  }
  fclose(fd);
}

//return as taille the number of bits
void read_ciphertext(char *file, char **ciphertext, unsigned long *size, mpz_t *x) {
  mpz_init(*x);
  char c;
  unsigned long i = 0, size_tot;
  FILE *fd = fopen(file, "r");
  if (fd == NULL) {
    fprintf(stderr, "%s does not exist !\n", file);
    exit(EXIT_FAILURE);
  }
  fseek(fd, 0, SEEK_END);
  size_tot = ftell(fd);
  rewind(fd);
  *ciphertext = (char *)malloc(size_tot);
  while ((c = fgetc(fd)) != ';') {
    (*ciphertext)[i] = ((c - '0') ? 1 : 0);
    ++i;
  }

  *size = i;
  char x_str[size_tot - i];
  fgets(x_str, size_tot - i, fd);
  if (!mpz_set_str(*x, x_str, 10))
    printf("x_str not valid in base 10\n");
  fclose(fd);
}

void write_ciphertext(char *file, char *ciphertext, unsigned long size, mpz_t x) {
  unsigned long i = 0;
  FILE *fd = fopen(file, "w");
  while( i < size ) {
    fprintf(fd, "%d", ciphertext[i]);
    ++i;
  }
  gmp_fprintf(fd, ";%Zu", x);
  fclose(fd);
}

char BBS_step(mpz_t *x, mpz_t n) {
    // A completer
    //x[i] = x^2[i-1] mod n
    //z[i] = x[i] mod n

	mpz_t r, deux;
	mpz_init(r);
	mpz_init(deux);
	mpz_set_ui(deux, 2);
	char *ret = 0;
	mpz_mul(*x, *x, *x);
	mpz_mod(*x, *x, n);
	mpz_mod(r, *x, deux);
	ret = mpz_get_str(ret, 10, r);

	mpz_clear(r);
	mpz_clear(deux);
	return *ret;
}
