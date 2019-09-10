.PHONY: all, clean
SRCMPICC=$(sort $(wildcard src/*.c))
OUTMPICC=$(patsubst src/%.c,bin/%,$(SRCMPICC))

CFLAGS=-pedantic -Wall
CLIBS=-lm

all: $(OUTGCC) $(OUTMPICC)

$(OUTMPICC): $(SRCMPICC)
	mpicc $(CFLAGS) $(CLIBS) $(patsubst bin/%,src/%.c,$@) -o $@

clean:
	rm $(OUTGCC) $(OUTMPICC)
