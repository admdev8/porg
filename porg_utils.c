#include "porg_utils.h"
#include <stdlib.h>
#include <assert.h>

void full_path_and_filename_to_path_only (strbuf *sb, const char* fullpath)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    errno_t e;

    e=_splitpath_s (fullpath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
    assert (e==0);
    strbuf_addstr (sb, drive);
    strbuf_addstr (sb, dir);
    //L(__FUNCTION__"() fullpath=%s\n", fullpath);
    //L(__FUNCTION__"() out=%s\n", sb->buf);
};

void full_path_and_filename_to_filename_only (strbuf *sb, const char* fullpath)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
    errno_t e;

    e=_splitpath_s (fullpath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
    assert (e==0);
    strbuf_addstr (sb, fname);
    strbuf_addc (sb, '.');
    strbuf_addstr (sb, ext);
    L(__FUNCTION__"() fullpath=%s\n", fullpath);
    L(__FUNCTION__"() out=%s\n", sb->buf);
};
