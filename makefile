CC := gcc
CFLAGS := -Wall -Wextra -pedantic -O3

.PHONY: demo benchmark clean help

demo: src/demo.c src/dyn_array/dyn_array.c src/dyn_array/dyn_array.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)
	./demo

benchmark: src/benchmark.c src/dyn_array/dyn_array.c src/dyn_array/dyn_array.h
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

clean:
	rm -f demo benchmark

help:
	@echo "make demo - build and run demo"
	@echo "make benchmark - build benchmark (./benchmark <count>)"
	@echo "make clean - remove all executables"
	@echo "make help - show this message"
