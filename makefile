CC=gcc

ifeq ($(BUILD),debug)
bsuffix=debug
CPPFLAGS_ADD=-D_DEBUG
else
bsuffix=release
CPPFLAGS_ADD=-O3
endif

OCTOTHORPE=../octothorpe
OCTOTHORPE_LIBRARY=$(OCTOTHORPE)/$(MSYSTEM)_$(bsuffix)/octothorpe.a
CPPFLAGS=-I$(OCTOTHORPE) $(CPPFLAGS_ADD)
CFLAGS=-c -Wall -g -std=gnu99
SOURCES=porg_utils.c oracle_sym.c mem_utils.c
DEPFILES=$(SOURCES:.c=.d)
OUTDIR=$(MSYSTEM)_$(bsuffix)
OBJECTS=$(addprefix $(OUTDIR)/,$(SOURCES:.c=.o))
LIBRARY=$(OUTDIR)/porg.a
TEST_SOURCES=test1.c oracle_sym_test.c
TEST_EXECS=$(addprefix $(OUTDIR)/,$(TEST_SOURCES:.c=.exe))

all: $(OUTDIR) $(LIBRARY)($(OBJECTS)) $(TEST_EXECS)

$(OUTDIR):
	mkdir $(OUTDIR)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(DEPFILES)
	$(RM) $(LIBRARY)

-include $(OBJECTS:.o=.d)

$(OUTDIR)/%.o: %.c
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

%.d: %.c
	$(CC) -MM $(CFLAGS) $(CPPFLAGS) $< > $@

# for tests:

%.exe: %.o $(LIBRARY)
	$(CC) $< $(LIBRARY) $(OCTOTHORPE_LIBRARY) $(PORG_LIBRARY) -lpsapi -limagehlp -o $@
