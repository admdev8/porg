#pragma once

#include <windows.h>
#include "strbuf.h"
#include "mingw_addons.h"

#ifdef  __cplusplus
extern "C" {
#endif

void full_path_and_filename_to_path_only (strbuf *sb, const char* fullpath);
void full_path_and_filename_to_filename_only (strbuf *sb, const char* fullpath);

// $s$ shouldn't be newline-terminated
void die_GetLastError(const char *s);
bool GetFileNameFromHandle(HANDLE hFile, strbuf *filename_out);

#ifdef  __cplusplus
}
#endif
