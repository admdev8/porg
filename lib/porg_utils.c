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

#include <stdlib.h>
#include <assert.h>
#include <errno.h>
#include <windows.h>

#include <stdio.h>
#include <tchar.h>
#include <string.h>
#include <psapi.h>
#include <tlhelp32.h>

#include "porg_utils.h"

// from octothorpe library:
#include "stuff.h"
#include "oassert.h"

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
};

void full_path_and_filename_to_filename_only (strbuf *sb_filename, strbuf *sb_filename_without_ext, const char* fullpath)
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
	strbuf_addstr (sb_filename, fname);
	strbuf_addstr (sb_filename, ext);

	strbuf_addstr (sb_filename_without_ext, fname);
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
	exit(0);
};

// http://msdn.microsoft.com/en-us/library/windows/desktop/aa366789(v=vs.85).aspx
#define BUFSIZE 512
bool GetFileNameFromHandle(HANDLE hFile, strbuf *filename_out)
{
	bool bSuccess = false;
	char pszFilename[MAX_PATH+1];
	HANDLE hFileMap;

	// Get the file size.
	DWORD dwFileSizeHi = 0;
	DWORD dwFileSizeLo = GetFileSize(hFile, &dwFileSizeHi); 

	if( dwFileSizeLo == 0 && dwFileSizeHi == 0 )
	{
		printf ("%s() Cannot map a file with a length of zero.\n", __func__); // but why?
		return false;
	}

	// Create a file mapping object.
	hFileMap = CreateFileMapping(hFile, NULL, PAGE_READONLY, 0, 1, NULL);

	if (hFileMap==NULL)
		die_GetLastError ("GetFileNameFromHandle(): CreateFileMapping()");

	// Create a file mapping to get the file name.
	void* pMem = MapViewOfFile(hFileMap, FILE_MAP_READ, 0, 0, 1);
	if (pMem==NULL)
		die_GetLastError ("GetFileNameFromHandle(): MapViewOfFile()");

// FIXME: may fail with:
// "The volume for a file has been externally altered so that the opened file is no longer valid."
	if (GetMappedFileName (GetCurrentProcess(), pMem, pszFilename, MAX_PATH)==0)
		die_GetLastError ("GetFileNameFromHandle(): GetMappedFileName()");

	// Translate path with device name to drive letters.
	char szTemp[BUFSIZE];
	szTemp[0] = '\0';

	if (GetLogicalDriveStrings(BUFSIZE-1, szTemp)==0)
		die_GetLastError ("GetFileNameFromHandle(): GetLogicalDriveStrings()");

	char szName[MAX_PATH];
	char szDrive[3] = TEXT(" :");
	BOOL bFound = FALSE;
	char* p = szTemp;

	do 
	{
		// Copy the drive letter to the template string
		*szDrive = *p;

		// Look up each device name
		if (QueryDosDevice(szDrive, szName, MAX_PATH)==0)
			die_GetLastError ("GetFileNameFromHandle(): QueryDosDevice()");

		size_t uNameLen = _tcslen(szName);

		oassert (uNameLen < MAX_PATH);

		bFound = _tcsnicmp(pszFilename, szName, uNameLen) == 0
			&& *(pszFilename + uNameLen) == _T('\\');

		//printf ("%s() _tcsnicmp(%s,%s)\n", __func__, pszFilename, szName);

		if (bFound)
		{
			// Reconstruct pszFilename using szTempFile
			// Replace device path with DOS path
			char szTempFile[MAX_PATH];
			snprintf(szTempFile,
				 MAX_PATH,
				 "%s%s",
				 szDrive,
				 pszFilename+uNameLen);
			strncpy(pszFilename, szTempFile, MAX_PATH+1);
		}

		// Go to the next NULL character.
		while (*p++);
	} while (!bFound && *p); // end of string

	bSuccess = true;
	UnmapViewOfFile(pMem);

	CloseHandle(hFileMap);

	strbuf_addstr (filename_out, pszFilename);
	//_tprintf(TEXT("File name is %s\n"), pszFilename);
	return bSuccess;
}

// find all processes PIDs by name

obj* FindProcessByName (const char* name)
{
	PROCESSENTRY32 proc;
	proc.dwSize = sizeof(proc);
	obj* rt=NULL;

	HANDLE hSysSnapshot = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );

	if ( hSysSnapshot == INVALID_HANDLE_VALUE )
		die ("CreateToolhelp32Snapshot() failed\n");

	if ( Process32First ( hSysSnapshot, &proc ) )
	{
		proc.dwSize = sizeof(proc);
		do
			if (_stricmp (name, proc.szExeFile)==0)
				rt=cons (obj_tetrabyte(proc.th32ProcessID), rt);
		while ( Process32Next ( hSysSnapshot, &proc ) );
	}
	CloseHandle ( hSysSnapshot );
	return rt;
};

BOOL EnableDebugPrivilege(BOOL Enable) 
{
	HANDLE hToken = NULL;
	BOOL b;

	b=OpenProcessToken( GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES, &hToken);
	if (b==FALSE)
		die_GetLastError ("OpenProcessToken");

	TOKEN_PRIVILEGES tp; 

	tp.PrivilegeCount = 1;

	b=LookupPrivilegeValue( NULL, SE_DEBUG_NAME, &tp.Privileges[0].Luid);
	if (b==FALSE)
		die_GetLastError ("LookupPrivilegeValue");

	tp.Privileges[0].Attributes = Enable ? SE_PRIVILEGE_ENABLED : 0;

	b=AdjustTokenPrivileges( hToken, FALSE, &tp, sizeof(tp), NULL, NULL);
	if (b==FALSE)
		die_GetLastError ("AdjustTokenPrivileges");

	if( hToken != NULL ) 
	{
		b=CloseHandle( hToken );
		assert (b);
	};

	return TRUE;
}

DWORD get_file_size (const char* fname)
{
	DWORD fsize;

	HANDLE h=CreateFile (fname, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, 0, NULL);

	if (h==INVALID_HANDLE_VALUE)
		die("%s() Cannot open file %s", __func__, fname);

	fsize=GetFileSize (h, NULL);

	CloseHandle (h);

	return fsize;
};

void write_to_the_end_of_file_or_die (char* fname, BYTE* buf, SIZE_T sz)
{
	HANDLE h=CreateFile (fname, GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (h==INVALID_HANDLE_VALUE)
		die_GetLastError ("CreateFile");
	DWORD tmp=SetFilePointer (h, 0, 0, FILE_END);
	if (tmp==INVALID_SET_FILE_POINTER)
		die_GetLastError("SetFilePointer");
	BOOL b=WriteFile (h, buf, sz, &tmp, NULL);
	if (b==FALSE)
		die_GetLastError("WriteFile");
	CloseHandle(h);
};

