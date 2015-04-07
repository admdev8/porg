#include "porg_utils.h"

int main()
{
	obj *o=FindProcessByName ("smss.exe");

	obj_dump(o);

	if (o)
		return 0; // test passed
	else
		return 1; // test failed
};
