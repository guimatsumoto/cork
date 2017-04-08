CC=gcc
AR=ar
ARFLAGS=-cvq
CFLAGS=-Wall -O3 -I.
LDFLAGS=-L. -lgmp -lBlum
EXEC=genkey encrypt decrypt

.PHONY:clean mrproper

all:$(EXEC) clean

genkey:genkey.o libBlum.a
	$(CC) $(CFLAGS) -o $@ $<  $(LDFLAGS)

genkey.o:genkey.c
	$(CC) $(CFLAGS) -c $< -o $@

encrypt:encrypt.o libBlum.a
	$(CC) $(CFLAGS) -o $@ $<  $(LDFLAGS)

encrypt.o:encrypt.c
	$(CC) $(CFLAGS) -c $< -o $@

decrypt:decrypt.o libBlum.a
	$(CC) $(CFLAGS) -o $@ $<  $(LDFLAGS)

decrypt.o:decrypt.c
	$(CC) $(CFLAGS) -c $< -o $@

libBlum.a:Blum.o
	$(AR) $(ARFLAGS) $@ $<

Blum.o:Blum.c Blum.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -name '*.o' -exec rm -f {} ';'
	find . -name '*~' -exec rm -f {} ';'
	find . -name '#*#' -exec rm -f {} ';'
	find . -name '.#*' -exec rm -f {} ';'
	find . -name 'core' -exec rm -f {} ';'
	find . -name '*.core' -exec rm -f {} ';'

mrproper:clean
	rm -rf $(EXEC)
	rm -rf *.a
	rm -rf *.so

pkg:mrproper
	tar -cvf ../archive.tgz .
