/*
**  MA203 - TP noté
**
**  AUTHOR: Guilherme KURIKE MATSUMOTO
*/

#include <Blum.h>
/*
This function receives a plaintext file, reads it, encrypt it and saves it to file_cipher.
*/
void encrypt_BG(char *file_plain, char *file_cipher, mpz_t n) {
  // A completer
  //all mpz variables
  gmp_randstate_t state;
  mpz_t s, x;
  mpz_inits(s, x, NULL);
  gmp_randinit_default (state);
  mpz_urandomm(s, state, n); //generating s
  mpz_powm_ui(x, s, 2, n); //initializing x0

  char *plaintext;
  unsigned long size;
  //reading text, extracting text to encrypt and its size
  read_plaintext(file_plain, &plaintext, &size);
  char *c = (char*)malloc(size); //the encrypted message (those are the c[i]'s)
  unsigned int i = 0;
  //still aux variables...
  mpz_t aux;
  mpz_init(aux);
  for ( ; i < size; ++i){
    mpz_powm_ui(x, x, 2, n);
    mpz_mod_ui(aux, x, 2);
    if (plaintext[i]+mpz_get_ui(aux) == 1)
      c[i] = 1;
    else
      c[i] = 0;
  }
  mpz_powm_ui(x, x, 2, n);
  write_ciphertext(file_cipher, c, size, x);
  mpz_clears(s, x, aux, NULL);

}

int main(int argc, char *argv[]){
  if (argc != 4) {
    fprintf(stderr, "Usage : %s <filename of the public key> <filename of the plaintext> <filename of the ciphertext>\n\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // A completer
  char* file_publickey = argv[1];
  char* file_plain = argv[2];
  char* file_cipher = argv[3];
  mpz_t n;
  mpz_init(n);
  read_pub_key(file_publickey, &n);
  encrypt_BG(file_plain, file_cipher, n);
  mpz_clear(n);

  exit(EXIT_SUCCESS);
}
