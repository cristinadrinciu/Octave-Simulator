# compiler setup
CC=gcc
CFLAGS=-Wall -Wextra -std=c99

# define targets
TARGETS=my_octave

build: $(TARGETS)

octave: my_octave.c
	$(CC) $(CFLAGS) my_octave.c -lm -o my_octave



pack:
	zip -FSr My_Octave_Simulator.zip README.md Makefile *.c *.h

clean:
	rm -f $(TARGETS)

.PHONY: pack clean
