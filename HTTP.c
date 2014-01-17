#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <winhttp.h>

char *HTTP_get_first_block_if_possible(wchar_t *host, wchar_t *path, wchar_t *agent_name)
{
	BOOL bResults;
	HINTERNET hSession = NULL, hConnect = NULL, hRequest = NULL; 
	char *rt;

	hSession = WinHttpOpen(agent_name, 
			WINHTTP_ACCESS_TYPE_DEFAULT_PROXY,
			WINHTTP_NO_PROXY_NAME, 
			WINHTTP_NO_PROXY_BYPASS, 0);

	if (hSession==NULL)
		return NULL;

	hConnect = WinHttpConnect( hSession, host,
			INTERNET_DEFAULT_HTTP_PORT, 0);

	if (hConnect==NULL)
		return NULL;

	hRequest = WinHttpOpenRequest( hConnect, NULL, 
			path, 
			NULL, WINHTTP_NO_REFERER, 
			WINHTTP_DEFAULT_ACCEPT_TYPES,
			0);

	if (hRequest==NULL) 
		return NULL;

	bResults = WinHttpSendRequest( hRequest, 
			WINHTTP_NO_ADDITIONAL_HEADERS,
			0, WINHTTP_NO_REQUEST_DATA, 0, 
			0, 0);

	// End the request.
	if(bResults==FALSE)
		return NULL;

	bResults = WinHttpReceiveResponse( hRequest, NULL );

	if(bResults==FALSE)
		return NULL;

	LPSTR pszOutBuffer;
	DWORD dwDownloaded = 0;
	DWORD dwSize = 0;

	// Check only for first portion!
	if( !WinHttpQueryDataAvailable( hRequest, &dwSize ) )
		return NULL;

	pszOutBuffer = malloc (dwSize+1);

	ZeroMemory(pszOutBuffer, dwSize+1);

	if(WinHttpReadData(hRequest, (LPVOID)pszOutBuffer, 
				dwSize, &dwDownloaded))
		rt=pszOutBuffer;
	else
	{
		free (pszOutBuffer);
		rt=NULL;
	};

	if (hRequest) WinHttpCloseHandle(hRequest);
	if (hConnect) WinHttpCloseHandle(hConnect);
	if (hSession) WinHttpCloseHandle(hSession);

	return rt;
};
