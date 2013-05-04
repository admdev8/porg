#pragma once

#include "strbuf.h"

#ifdef  __cplusplus
extern "C" {
#endif

void full_path_and_filename_to_path_only (strbuf *sb, const char* fullpath);
void full_path_and_filename_to_filename_only (strbuf *sb, const char* fullpath);
void die_GetLastError(const char *s);

// some stuff absent in MinGW

#ifndef ERROR_ELEVATION_REQUIRED
#define ERROR_ELEVATION_REQUIRED         740L
#endif

#ifdef  __cplusplus
}
#endif
