/*
 *  _ __   ___  _ __ __ _ 
 * | '_ \ / _ \| '__/ _` |
 * | |_) | (_) | | | (_| |
 * | .__/ \___/|_|  \__, |
 * | |               __/ |
 * |_|              |___/
 *
 * Written by Dennis Yurichev <dennis(a)yurichev.com>, 2013
 *
 * This work is licensed under the Creative Commons Attribution-NonCommercial-NoDerivs 3.0 Unported License. 
 * To view a copy of this license, visit http://creativecommons.org/licenses/by-nc-nd/3.0/.
 *
 */

#pragma once

#include <windows.h>

#include "lisp.h"
#include "strbuf.h"
#include "mingw_addons.h"

#ifdef  __cplusplus
extern "C" {
#endif

	void full_path_and_filename_to_path_only (strbuf *sb, const char* fullpath);
	void full_path_and_filename_to_filename_only (strbuf *sb_filename, strbuf *sb_filename_without_ext, const char* fullpath);

	// $s$ shouldn't be newline-terminated
	void die_GetLastError(const char *s);
	bool GetFileNameFromHandle(HANDLE hFile, strbuf *filename_out);
	obj* FindProcessByName (const char* name);
	BOOL EnableDebugPrivilege(BOOL Enable);
	DWORD get_file_size (const char* fname);
	void write_to_the_end_of_file_or_die (char* fname, BYTE* buf, SIZE_T sz);

#ifdef  __cplusplus
}
#endif
