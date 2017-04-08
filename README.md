/*
**  MA203 - TP noté
**
**  AUTHOR: Guilherme KURIKE MATSUMOTO
*/

To make it easier, the file names follow a pattern:

	1) The initial messages are always saved in files named message<i>.txt, where i is the number of the test. This is true for all tests, except the first one (the one that was provided), because it didn't have an initial version.

	2) The encrypted messages are saved in files named chiffre<i>.txt, where again i stands for the number of the test.

	3) The final decrypted message is saved in a file named result<i>.txt, i meaning the number of the test.

	4) Private keys are to be stored in files named key<i>, where i is the number of the key. 

	5) Public keys are to be stored in files named key.pub<i>, where i is the number of the key.

	6) The only public/private key pair that doesn't follow this rule is the provided pair, which doesn't have an index <i> in the name.


A few important points:
	
	1) The encrypt_BG() and decrypt_BG() functions do not return the encrypted/decrypted message through the pointer passed as parameter. Instead they save the message in the respective file passed by parameter.

	2) The main functions from both encrypt.c and decrypt.c are minimalists, they contain only the essential to run de algorithms. No messages are exhibited to the user after a successful encryption/decryption.

	3) Keys are stored in individual files (naturally, each public key pair shares the same file).

	4) A size of 1024 bits (size parameter in the genkey app, relative to the maximum bit size of the random number generated) is reasonable and its processor time is ok, for bigger sizes it takes a long time to compute.


Tests:
	
	A test configuration is: 
		-> (public key file, private key file) 
		-> (initial message file, encrypted message file, decrypted message file)

	1) First test was just the decryption of the provided encrypted message.
		cfg:
			-> (key, key.pub)
			-> (wasn't provided, chiffre.txt, result1.txt)

	2) Second test was made using a max prime number size of 1024 bits.
		cfg:
			-> (key2, key.pub2)
			-> (message2.txt, chiffre2.txt, result2.txt)

	3) Third test was made using a max prime number size of 1536 bits.
		cfg:
			-> (key3, key.pub3)
			-> (message3.txt, chiffre3.txt, result3.txt)

	4) Fourth test was made using a max prime number size of 2048 bits.
		cfg:
			-> (key4, key.pub4)
			-> (message4.txt, chiffre4.txt, result4.txt)

	All four tests worked and the most demanding task was the prime number generation.