#include "porg_utils.h"

int main()
{
	obj *o=FindProcessByName ("smss.exe");

	//obj_dump(o);

	if (o)
		return 0; // test passed
	else
	{
		printf ("%s(): test failed\n", __FILE__);
		return 1; // test failed
	};
};
