.PHONY: all, clean
SRCMPICC=$(sort $(wildcard *p.c))
SRCGCC=$(sort $(wildcard *s.c))
OUTMPICC=$(patsubst %.c,%,$(SRCMPICC))
OUTGCC=$(patsubst %.c,%,$(SRCGCC))

CFLAGS=-pedantic -Wall
CLIBS=-lm

all: $(OUTGCC) $(OUTMPICC)

$(OUTGCC): $(SRCGCC)
	gcc $(CFLAGS) $(CLIBS) $(patsubst %,%.c,$@) -o $@

$(OUTMPICC): $(SRCMPICC)
	mpicc $(CFLAGS) $(CLIBS) $(patsubst %,%.c,$@) -o $@

clean:
	rm $(OUTGCC) $(OUTMPICC)
