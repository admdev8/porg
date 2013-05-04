#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <windows.h>

#include "porg_utils.h"

void full_path_and_filename_to_path_only (strbuf *sb, const char* fullpath)
{
    char drive[_MAX_DRIVE];
    char dir[_MAX_DIR];
    char fname[_MAX_FNAME];
    char ext[_MAX_EXT];
#ifdef _MSC_VER
    errno_t e;
#endif

#ifdef _MSC_VER
    e=_splitpath_s (fullpath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
    assert (e==0);
#else
    _splitpath (fullpath, drive, dir, fname, ext);
#endif
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
#ifdef _MSC_VER
    errno_t e;
#endif

#ifdef _MSC_VER
    e=_splitpath_s (fullpath, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);
    assert (e==0);
#else
    _splitpath (fullpath, drive, dir, fname, ext);
#endif
    strbuf_addstr (sb, fname);
    strbuf_addc (sb, '.');
    strbuf_addstr (sb, ext);
    //L(__FUNCTION__"() fullpath=%s\n", fullpath);
    //L(__FUNCTION__"() out=%s\n", sb->buf);
};

void die_GetLastError(const char *s) 
{
    DWORD dw=GetLastError();
    LPVOID lpMsgBuf;

    FormatMessage(
            FORMAT_MESSAGE_ALLOCATE_BUFFER | 
            FORMAT_MESSAGE_FROM_SYSTEM |
            FORMAT_MESSAGE_IGNORE_INSERTS,
            NULL,
            dw,
            MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
            (LPTSTR) &lpMsgBuf,
            0, NULL );

    printf ("%s\n%s", s, (char*)lpMsgBuf);
    LocalFree(lpMsgBuf);
};
