#include <stdio.h>

#include "strbuf.h"
#include "porg_utils.h"

int main()
{
    strbuf sb1=STRBUF_INIT, sb2=STRBUF_INIT;
    char *fullpath="C:\\Users\\Administrator\\Projects\\tracer-0.7\\opts_test.exe";

    full_path_and_filename_to_path_only (&sb1, fullpath);
    full_path_and_filename_to_filename_only (&sb2, fullpath);

    printf ("path: [%s]\n", sb1.buf);
    printf ("filename: [%s]\n", sb2.buf);
    
    return 0;
};
