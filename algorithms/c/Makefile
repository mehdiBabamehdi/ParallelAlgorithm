SRCDIR = .

CC = gcc
MPICC = mpicc

# All relevant relative paths
SRCMPICC=$(sort $(wildcard $(SRCDIR)/*p.c))
SRCGCC=$(sort $(wildcard $(SRCDIR)/*s.c))
TESTMPICC = $(sort $(wildcard $(SRCDIR)/test_*p.c))
TESTGCC = $(sort $(wildcard $(SRCDIR)/test_*s.c))
#$(info $$SRCMPICC is [${SRCMPICC}])

# All sources
SMPICC = $(patsubst $(SRCDIR)/%.c, %.c, $(SRCMPICC))
SGCC = $(patsubst $(SRCDIR)/%.c, %.c, $(SRCGCC))

# Tests
TMPICC = $(patsubst $(SRCDIR)/%.c, %.c, $(TESTMPICC))
TGCC = $(patsubst $(SRCDIR)/%.c, %.c, $(TESTGCC))

# BARE- consist of all those codes, but tests
BAREMPICC = $(filter-out $(TMPICC), $(SMPICC))
BAREGCC = $(filter-out $(TGCC), $(SGCC))

# Object files for tests
OTMPICC = $(patsubst %.c, %.o, $(TMPICC))
OTGCC = $(patsubst %.c, %.o, $(TGCC))

# Object files for non-tests
OBAREMPICC = $(patsubst %.c, %.o, $(BAREMPICC))
OBAREGCC = $(patsubst %.c, %.o, $(BAREGCC))

# Outputs
TARGETMPICC = $(patsubst %.c, %, $(TMPICC))
TARGETGCC = $(patsubst %.c, %, $(TGCC))

CFLAGS=-pedantic -Wall
CLIBS=-lm
MPIFLAGS=
MPIFLAGS += CFLAGS
MPILIBS=
MPILIBS += CLIBS

.PHONY: all, clean

all: $(TARGETGCC) $(TARGETMPICC)

$(TARGETMPICC): $(OBAREMPICC) $(OTMPICC)
	$(CC) $(MPIFLAGS) $(MPILIBS) -o $@ $(OBAREMPICC) $(OTMPICC)

$(TARGETGCC): $(OBAREGCC) $(OTGCC)
	$(CC) $(CFLAGS) $(CLIBS) -o $@ $(OBAREGCC) $(OTGCC)

# Parallel tests
$(SRCDIR)/test_%p.o: $(SRCDIR)/test_%p.c
	$(MPICC) $(MPIFLAGS) $(MPILIBS) -c $< -o $@

# Seq tests
$(SRCDIR)/test_%s.o: $(SRCDIR)/test_%s.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $@

# Parallel implementations
$(SRCDIR)/impl_%p.o: $(SRCDIR)/impl_%p.c
	$(MPICC) $(MPIFLAGS) $(MPILIBS) -c $< -o $@

# Seq implementations
$(SRCDIR)/impl_%s.o: $(SRCDIR)/impl_%s.c
	$(CC) $(CFLAGS) $(CLIBS) -c $< -o $@

clean:
	$(RM) $(OBAREGCC) $(OTGCC) $(TARGETGCC) $(OBAREMPICC) $(OTMPICC) $(TARGETMPICC)
