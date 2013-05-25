#include <stdio.h>

#include "strbuf.h"
#include "porg_utils.h"

int main()
{
    strbuf sb1=STRBUF_INIT, sb2_fname=STRBUF_INIT, sb2_fname_without_ext=STRBUF_INIT;
    char *fullpath="C:\\Users\\Administrator\\Projects\\tracer-0.7\\opts_test.exe";

    full_path_and_filename_to_path_only (&sb1, fullpath);
    full_path_and_filename_to_filename_only (&sb2_fname, &sb2_fname_without_ext, fullpath);

    printf ("path: [%s]\n", sb1.buf);
    printf ("filename: [%s]\n", sb2_fname.buf);
    printf ("filename_without_ext: [%s]\n", sb2_fname_without_ext.buf);
    
    return 0;
};
