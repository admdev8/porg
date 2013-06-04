CC=gcc
OCTOTHORPE=../octothorpe
OCTOTHORPE_LIBRARY=$(OCTOTHORPE)/$(MSYSTEM)_debug/octothorped.a
CPPFLAGS=-D_DEBUG -I$(OCTOTHORPE)
CFLAGS=-c -Wall -g -std=gnu99
SOURCES=porg_utils.c oracle_sym.c
DEPFILES=$(SOURCES:.c=.d)
OUTDIR=$(MSYSTEM)_debug
OBJECTS=$(addprefix $(OUTDIR)/,$(SOURCES:.c=.o))
LIBRARY=$(OUTDIR)/porgd.a
TEST_SOURCES=test1.c
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
