CC = gcc
CFLAGS = --std=c11 -Wall -Wextra -Werror -pedantic
COVFLAGS = -fprofile-arcs -ftest-coverage

all: encode

encode: encode.c
	$(CC) $(CFLAGS) -o encode encode.c

test: encode tests.c
	$(CC) $(CFLAGS) -o tests tests.c
	./tests

coverage: clean
	$(CC) $(CFLAGS) $(COVFLAGS) -o encode encode.c
	$(CC) $(CFLAGS) -o tests tests.c
	./tests
	gcov encode.c

clean:
	rm -f encode tests *.gcda *.gcno *.gcov test_out*.bmp out.bmp
