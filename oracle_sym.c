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

#include <assert.h>
#include "oracle_sym.h"

int get_symbols_from_ORACLE_SYM (const char *fname, address PE_img_base, SIZE_T PE_size, DWORD PE_timestamp, 
        bool check_PE_timestamp,
        callback_add_symbol add_symbol_fn, void *add_symbol_fn_params, int oracle_version)
{
    BOOL b;
    REG cnt;
    REG *d1, *d2;
    char* d3;
    int rt=ORACLE_SYM_IMPORTER_ERROR_SUCCESS;

    HANDLE f=CreateFile (fname, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, 
            FILE_ATTRIBUTE_NORMAL, NULL);

    if (f==NULL)
        return ORACLE_SYM_IMPORTER_ERROR_FILE_OPENING_ERROR;

    DWORD len=GetFileSize (f, NULL);
    assert (len!=INVALID_FILE_SIZE);

    HANDLE fm=CreateFileMapping (f, NULL, PAGE_READONLY, 0, 0, NULL);

    if (fm==NULL)
        return ORACLE_SYM_IMPORTER_ERROR_FILE_OPENING_ERROR;

    address adr=(REG)MapViewOfFile (fm, FILE_MAP_READ, 0, 0, 0);

    if (adr==0)
        return ORACLE_SYM_IMPORTER_ERROR_FILE_OPENING_ERROR;

#ifdef _WIN64
    char* sig="OSYMAM64";
    unsigned sig_len=8;
#else
    char* sig="OSYM";
    unsigned sig_len=4;
#endif

    if (memcmp ((void*)adr, sig, sig_len)!=0 || memcmp ((BYTE*)adr+len-sizeof(REG)*2, sig, sig_len)!=0)
    {
        rt=ORACLE_SYM_IMPORTER_ERROR_SIGNATURE_MISMATCH;
        goto unmap_close_exit;
    };

    // point after signature
    memcpy (&cnt, (BYTE*)adr+sizeof (REG), sizeof (REG));
    
    REG SYM_timedatestamp;

    if (oracle_version==11)
    {
        memcpy (&SYM_timedatestamp, (BYTE*)adr+sizeof (REG)*2, sizeof (REG));

        if (check_PE_timestamp)
            // this is how check is done in orageneric11.dll!_ssskgdsym_init_symtab
            if ((PE_timestamp-60 > (SYM_timedatestamp&0xffffffff)) || (PE_timestamp+60 < (SYM_timedatestamp&0xffffffff)))
            {
                rt=ORACLE_SYM_IMPORTER_ERROR_PE_FILE_MISMATCH;
                goto unmap_close_exit;
            };
        d1=(REG*)adr+3;
    }
    else
        d1=(REG*)adr+2;

    d2=d1+cnt;
    d3=(char*)(d2+cnt);

    for (REG i=0; i<cnt; i++)
    {
        char *name=d3+(*(d2+i));
        REG a=(REG)*(d1+i);

        // All oracle .SYM files for Oracle DLLs has addresses starting at 0x10000000
        // without any relation to DLL's image base
        if ((a&0xF0000000) == 0x10000000)
        {
            // dirty hack
            a=(a - 0x10000000) + (REG)PE_img_base;
        };

        if (a >= (REG)PE_img_base && a <= ((REG)PE_img_base + PE_size))
            add_symbol_fn(a, name, add_symbol_fn_params);
    };

unmap_close_exit:
    b=UnmapViewOfFile ((LPCVOID)adr);
    assert (b==TRUE);
    CloseHandle (f);
    return rt;
};
