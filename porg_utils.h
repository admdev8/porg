#pragma once

#include "strbuf.h"

#ifdef  __cplusplus
extern "C" {
#endif

void full_path_and_filename_to_path_only (strbuf *sb, const char* fullpath);
void full_path_and_filename_to_filename_only (strbuf *sb, const char* fullpath);

#ifdef  __cplusplus
}
#endif
