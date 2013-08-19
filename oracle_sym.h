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
#include <stdbool.h>
#include "datatypes.h"

typedef void (*callback_add_symbol)(address a, char *name, void* param);

#define ORACLE_SYM_IMPORTER_ERROR_SUCCESS 0
#define ORACLE_SYM_IMPORTER_ERROR_FILE_OPENING_ERROR 1
#define ORACLE_SYM_IMPORTER_ERROR_SIGNATURE_MISMATCH 2
#define ORACLE_SYM_IMPORTER_ERROR_PE_FILE_MISMATCH 3

int get_symbols_from_ORACLE_SYM (const char *fname, address PE_img_base, SIZE_T PE_size, DWORD PE_timestamp, 
        bool check_PE_timestamp,
        callback_add_symbol add_symbol_fn, void *add_symbol_fn_params, int oracle_version);

/* vim: set expandtab ts=4 sw=4 : */
