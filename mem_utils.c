#include <windows.h>
#include <stdio.h>
#include "bitfields.h"

void dump_MEMORY_BASIC_INFORMATION (MEMORY_BASIC_INFORMATION *m)
{
	printf ("BaseAddress=0x%p\n", m->BaseAddress);
	printf ("AllocationBase=0x%p\n", m->AllocationBase);
	printf ("AllocationProtect=0x%x\n", m->AllocationProtect);
	printf ("RegionSize=0x%x\n", m->RegionSize);
	printf ("State=%s%s%s(0x%x)\n", 
		IS_SET (m->Protect, MEM_COMMIT) ? "MEM_COMMIT " : "",
		IS_SET (m->Protect, MEM_FREE) ? "MEM_FREE " : "",
		IS_SET (m->Protect, MEM_RESERVE) ? "MEM_RESERVE " : "",
		m->State);

	printf ("Protect=%s%s%s%s%s%s%s%s%s%s%s(0x%x)\n",
		IS_SET (m->Protect, PAGE_EXECUTE) ? "PAGE_EXECUTE " : "",
		IS_SET (m->Protect, PAGE_EXECUTE_READ) ? "PAGE_EXECUTE_READ " : "",
		IS_SET (m->Protect, PAGE_EXECUTE_READWRITE) ? "PAGE_EXECUTE_READWRITE " : "",
		IS_SET (m->Protect, PAGE_EXECUTE_WRITECOPY) ? "PAGE_EXECUTE_WRITECOPY " : "",
		IS_SET (m->Protect, PAGE_NOACCESS) ? "PAGE_NOACCESS " : "",
		IS_SET (m->Protect, PAGE_READONLY) ? "PAGE_READONLY " : "",
		IS_SET (m->Protect, PAGE_READWRITE) ? "PAGE_READWRITE " : "",
		IS_SET (m->Protect, PAGE_WRITECOPY) ? "PAGE_WRITECOPY " : "",
		IS_SET (m->Protect, PAGE_GUARD) ? "PAGE_GUARD " : "",
		IS_SET (m->Protect, PAGE_NOCACHE) ? "PAGE_NOCACHE " : "",
		IS_SET (m->Protect, PAGE_WRITECOMBINE) ? "PAGE_WRITECOMBINE " : "",
		m->Protect);

	printf ("Type=%s%s%s(0x%x)\n", 
		IS_SET (m->Type, MEM_IMAGE) ? "MEM_IMAGE " : "",
		IS_SET (m->Type, MEM_MAPPED) ? "MEM_MAPPED " : "",
		IS_SET (m->Type, MEM_PRIVATE) ? "MEM_PRIVATE " : "",
		m->Type);
};

