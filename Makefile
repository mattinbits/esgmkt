# I am a comment, and I want to say that the variable CC will be
# the compiler to use.
CC=gcc
# Hey!, I am comment number 2. I want to say that CFLAGS will be the
# options I'll pass to the compiler.
CFLAGS= -std=c99 -Wall

all: esgmkt

esgmkt: bin/vec_mat.o

bin/vec_mat.o : src/math/vec_mat.c
	$(CC) $(CFLAGS) -c src/math/vec_mat.c -o bin/vec_mat.o

clean:
	rm -f *.o bin/*.o

bin/test_vec_mat.o: test/math/test_vec_mat.c
	$(CC) $(CFLAGS) -c test/math/test_vec_mat.c -o bin/test_vec_mat.o 

test: bin/test_vec_mat.o bin/vec_mat.o
	$(CC)  bin/test_vec_mat.o bin/vec_mat.o -o test_pack -lm -lcheck


