.PHONY: all, clean
SRCMPICC=$(sort $(wildcard *p.c))
SRCGCC=$(sort $(wildcard *s.c))
OUTMPICC=$(patsubst %.c,%,$(SRCMPICC))
OUTGCC=$(patsubst %.c,%,$(SRCGCC))

CFLAGS=-pedantic -Wall
CLIBS=-lm

all: $(OUTGCC) $(OUTMPICC)

$(OUTGCC): $(SRCGCC)
	gcc $(CFLAGS) $(patsubst %,%.c,$@) -o $@ $(CLIBS) 

$(OUTMPICC): $(SRCMPICC)
	mpicc $(CFLAGS) $(patsubst %,%.c,$@) -o $@ $(CLIBS) 

clean:
	rm $(OUTGCC) $(OUTMPICC)
