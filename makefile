OCTOTHORPE=../octothorpe/
OCTOTHORPE_LIBRARY=$(OCTOTHORPE)octothorped.a
CPPFLAGS=-D_DEBUG -I$(OCTOTHORPE)
CFLAGS=-c -Wall -g
SOURCES=porg_utils.c
OBJECTS=$(SOURCES:.c=.o)
DEPFILES=$(SOURCES:.c=.d)
LIBRARY=porgd.a
TEST_SOURCES=test1.c
TEST_EXECS=$(TEST_SOURCES:.c=.exe)

all: $(LIBRARY)($(OBJECTS)) $(TEST_EXECS)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(DEPFILES)
	$(RM) $(LIBRARY)

-include $(OBJECTS:.o=.d)

%.d: %.c
	$(CC) -MM $(CFLAGS) $(CPPFLAGS) $< > $@

# for tests:

%.exe: %.o $(LIBRARY)
	$(CC) $< $(LIBRARY) $(OCTOTHORPE_LIBRARY) $(PORG_LIBRARY) -lpsapi -limagehlp -o $@
