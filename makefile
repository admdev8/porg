OCTOTHORPE=C:\Users\Administrator\Projects\octothorpe
OCTOTHORPE_LIB=$(OCTOTHORPE)\octothorped.lib

CL_OPTIONS=/c /D_DEBUG /Zi /I$(OCTOTHORPE)

porg_utils.obj: porg_utils.c porg_utils.h
	cl.exe porg_utils.c $(CL_OPTIONS)

porgd.lib: porg_utils.obj
	lib.exe porg_utils.obj /OUT:porgd.lib

all: porgd.lib

clean:
	del *.lib *.exe *.obj *.asm
