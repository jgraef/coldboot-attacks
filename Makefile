.PHONY: all clean

all: fill_mem find_key find_string

clean:
	rm -f fill_mem find_key find_string

fill_mem: fill_mem.c
	$(CC) -o $@ $^

find_key: find_key.c
	$(CC) -o $@ $^

find_string: find_string.c
	$(CC) -o $@ $^

