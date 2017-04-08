/*
**  MA203 - TP noté
**
**  AUTHOR: Guilherme KURIKE MATSUMOTO
*/

#include <Blum.h>

/*
This function is going to receive the output file name as the file_plain variable.
It will store the decrypted message in this file_plain file.
*/
void decrypt_BG(char *file_cipher, char *file_plain, mpz_t p, mpz_t q) {
    // A completer
    char* ciphertext;
    unsigned long size;
    mpz_t xt1, tplus, d1, d2, u, v, a, b, x, pminus, qminus, pplus, qplus, base1, base2, tlast, n;
    mpz_inits(xt1, tplus, d1, d2, u, v, a, b, x, pminus, qminus, pplus, qplus, base1, base2, tlast, n, NULL);

    //reading the cipher and getting size and t
	read_ciphertext(file_cipher, &ciphertext, &size, &xt1); 

	//initializing a lot of variables, gotta find a better way of doing it
	mpz_set_ui(tplus, size+1);
	mpz_add_ui(pplus, p, 1);
	mpz_add_ui(qplus, q, 1);
	mpz_sub_ui(pminus, p, 1);
	mpz_sub_ui(qminus, q, 1);
	mpz_cdiv_q_ui(base1, pplus, 4);
	mpz_cdiv_q_ui(base2, qplus, 4);

	//setting initial conditions
	mpz_powm(d1, base1, tplus, pminus); //d1
	mpz_powm(d2, base2, tplus, qminus); //d2
	//gmp_printf("size: %d\ntamanho efetivo: %Z\n", size, x); //it works until here
	mpz_powm(u, xt1, d1, p); //u
	mpz_powm(v, xt1, d2, q); //v
	mpz_invert(a, p, q);
	mpz_invert(b, q, p);

	//to calculate x0 a little bit of garbage
	mpz_t aux1, aux2;
	mpz_inits(aux1, aux2, NULL);
	mpz_mul(aux1, v, a);
	mpz_mul(aux1, aux1, p); //vap
	mpz_mul(aux2, u, b);
	mpz_mul(aux2, aux2, q); //ubq
	mpz_mul(n, p, q); //n
	mpz_add(aux1, aux1, aux2);
	mpz_mod(x, aux1, n); //x0
	mpz_clears(aux1, aux2, NULL); //clearing aux variables

	char *m = (char*)malloc(size); //allocating space for the decrypted message
	mpz_t z;
	mpz_init(z); //gonna hold temporary z
	unsigned int i = 0;
	for ( ; i < size; ++i){
		mpz_powm_ui(x, x, 2, n);
		mpz_mod_ui(z, x, 2);
		//I'm tired of handling all this mpz...
		if (ciphertext[i]+mpz_get_ui(z) == 1)
			m[i] = 1;
		else
			m[i] = 0;
	}
	write_plaintext(file_plain, m, size);
	mpz_clear(z);
	mpz_clears(xt1, tplus, d1, d2, u, v, a, b, x, pminus, qminus, pplus, qplus, base1, base2, tlast, n, NULL);
}

int main(int argc, char *argv[]){
  if (argc != 4) {
    fprintf(stderr, "Usage : %s <filename of the private key> <filename of the ciphertext> <filename of the plaintext>\n\n", argv[0]);
    exit(EXIT_FAILURE);
  }
  
  // A completer
  char* file_plain = argv[3];
  char* file_cipher = argv[2];
  char* file_privatekey = argv[1];
  mpz_t p, q;
  mpz_init(p);
  mpz_init(q);
  read_key(file_privatekey, &p, &q);
  //gmp_printf("%Zd e %Zd\n", p, q);
  decrypt_BG(file_cipher, file_plain, p, q);
  mpz_clears(p, q, NULL);
  exit(EXIT_SUCCESS);
}
