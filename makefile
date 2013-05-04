OCTOTHORPE=../octothorpe/
CC=gcc
CPPFLAGS=-D_DEBUG -I$(OCTOTHORPE)
#CPPFLAGS=
CFLAGS=-Wall -g $(CPPFLAGS)
COMPILE_ONLY_CFLAGS=-c $(CFLAGS)
SOURCES=porg_utils.c
#TEST_SOURCES=
OBJECTS=$(SOURCES:.c=.o)
#TEST_OBJECTS=$(TEST_SOURCES:.c=.o)
#TEST_EXECS=$(TEST_SOURCES:.c=.exe)
LIBRARY=porgd.a
OCTOTHORPE_LIBRARY=$(OCTOTHORPE)octothorped.a

all: $(LIBRARY)

clean:
	rm $(OBJECTS)
	#rm $(TEST_OBJECTS)
	rm $(LIBRARY)

$(LIBRARY): $(OBJECTS)
	ar -mc $(LIBRARY) $(OBJECTS)

-include $(OBJECTS:.o=.d)

%.o: %.c
	$(CC) $(COMPILE_ONLY_CFLAGS) $*.c -o $*.o
	$(CC) -MM $(COMPILE_ONLY_CFLAGS) $*.c > $*.d
