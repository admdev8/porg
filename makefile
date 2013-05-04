OCTOTHORPE=../octothorpe/
OCTOTHORPE_LIBRARY=$(OCTOTHORPE)octothorped.a
CPPFLAGS=-D_DEBUG -I$(OCTOTHORPE)
CFLAGS=-c -Wall -g
SOURCES=porg_utils.c
OBJECTS=$(SOURCES:.c=.o)
DEPFILES=$(SOURCES:.c=.d)
LIBRARY=porgd.a

all: $(LIBRARY)($(OBJECTS))

clean:
	$(RM) $(OBJECTS)
	$(RM) $(DEPFILES)
	$(RM) $(LIBRARY)

-include $(OBJECTS:.o=.d)

%.d: %.c
	$(CC) -MM $(CFLAGS) $(CPPFLAGS) $< > $@
