CC=gcc
CFLAGS=-I/usr/local/include -L/usr/local/lib -lcriterion
TESTS=./tests/test_hello

all: $(TESTS)

$(TESTS): $(TESTS).c
	$(CC) $(CFLAGS) -o $@ $<

run: $(TESTS)
	./$(TESTS)

clean:
	rm -f $(TESTS)