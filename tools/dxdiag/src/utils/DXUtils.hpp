#pragma once
#include <windows.h>

namespace DXUtils {
	char* getDirectXVersion() {
		/**
		 * XP implementation (from leaks)
		 */
		// Get DirectX Version using dsetup.dll
		/*TCHAR szSetupPath[MAX_PATH];
		HINSTANCE hInstDSetup;
		LPDXSETUPGETVERSION pDXSGetVersion;
		BOOL bFound = FALSE;
		LoadString(NULL, IDS_NOTFOUND, pSysInfo->m_szDirectXVersionLong, 100);

		if (!BIsPlatformNT() && GetDxSetupFolder(szSetupPath))
		{
			lstrcat(szSetupPath, TEXT("\\dsetup.dll"));
			hInstDSetup = LoadLibrary(szSetupPath);
			if (hInstDSetup != NULL)
			{
				pDXSGetVersion = (LPDXSETUPGETVERSION)GetProcAddress(hInstDSetup,
					"DirectXSetupGetVersion");
				if (pDXSGetVersion != NULL)
				{
					DWORD dwVersion = 0;
					DWORD dwRevision = 0;
					if (pDXSGetVersion(&dwVersion, &dwRevision) != 0)
					{
						wsprintf(pSysInfo->m_szDirectXVersion, TEXT("%d.%02d.%02d.%04d"),
							HIWORD(dwVersion), LOWORD(dwVersion),
							HIWORD(dwRevision), LOWORD(dwRevision));
						bFound = TRUE;
					}
				}
				FreeLibrary(hInstDSetup);
			}
		}
		if (!bFound)
		{
			// Look in registry for DX version instead
			HKEY hkey;

			if (ERROR_SUCCESS == RegOpenKeyEx(HKEY_LOCAL_MACHINE, TEXT("Software\\Microsoft\\DirectX"),
				0, KEY_READ, &hkey))
			{
				cbData = 100;
				RegQueryValueEx(hkey, TEXT("Version"), 0, &ulType, (LPBYTE)pSysInfo->m_szDirectXVersion, &cbData);
				RegCloseKey(hkey);
				if (lstrlen(pSysInfo->m_szDirectXVersion) > 6 &&
					lstrlen(pSysInfo->m_szDirectXVersion) < 20)
				{
					bFound = TRUE;
				}
			}
		}
		if (!bFound && !BIsPlatformNT())
		{
			// Report ddraw.dll version instead
			// (except on Win2000, where ddraw.dll version is way different from DX version)
			TCHAR szDDrawPath[MAX_PATH];
			GetSystemDirectory(szDDrawPath, MAX_PATH);
			lstrcat(szDDrawPath, TEXT("\\ddraw.dll"));
			GetFileVersion(szDDrawPath, pSysInfo->m_szDirectXVersion, NULL, NULL, NULL);
		}
		if (lstrlen(pSysInfo->m_szDirectXVersion) > 0)
		{
			// Bug 18501: Add "friendly" version of version name
			DWORD dwMajor;
			DWORD dwMinor;
			DWORD dwRevision;
			DWORD dwBuild;
			TCHAR szFriendly[100];
			lstrcpy(szFriendly, TEXT(""));
			if( _stscanf(pSysInfo->m_szDirectXVersion, TEXT("%d.%d.%d.%d"), &dwMajor, &dwMinor, &dwRevision, &dwBuild) != 4 )
			{
				dwMajor = 0;
				dwMinor = 0;
				dwRevision = 0;
				dwBuild = 0;
			}
			wsprintf(pSysInfo->m_szDirectXVersion, TEXT("%d.%02d.%02d.%04d"), dwMajor, dwMinor, dwRevision, dwBuild);
			// According to http://xevious/directx/versions.htm:
			// 4.02.xx.xxxx is DX1
			// 4.03.xx.xxxx is DX2
			// 4.04.xx.xxxx is DX3
			// 4.05.xx.xxxx is DX5
			// 4.06.00.xxxx is DX6
			// 4.06.02.xxxx is DX6.1
			// 4.06.03.xxxx is DX6.1A
			// 4.07.00.xxxx is DX7.0
			// 4.07.01.xxxx is DX7.1
			// Beyond that, who knows...
			pSysInfo->m_dwDirectXVersionMajor = 0;
			pSysInfo->m_dwDirectXVersionMinor = 0;
			pSysInfo->m_cDirectXVersionLetter = TEXT(' ');
			if (dwMajor == 4 && dwMinor == 2)
			{
				lstrcpy(szFriendly, TEXT("DirectX 1"));
				pSysInfo->m_dwDirectXVersionMajor = 1;
			}
			if (dwMajor == 4 && dwMinor == 3)
			{
				lstrcpy(szFriendly, TEXT("DirectX 2"));
				pSysInfo->m_dwDirectXVersionMajor = 2;
			}
			if (dwMajor == 4 && dwMinor == 4)
			{
				lstrcpy(szFriendly, TEXT("DirectX 3"));
				pSysInfo->m_dwDirectXVersionMajor = 3;
			}
			if (dwMajor == 4 && dwMinor == 5)
			{
				lstrcpy(szFriendly, TEXT("DirectX 5"));
				pSysInfo->m_dwDirectXVersionMajor = 5;
			}
			else if (dwMajor == 4 && dwMinor == 6 && dwRevision == 0)
			{
				lstrcpy(szFriendly, TEXT("DirectX 6"));
				pSysInfo->m_dwDirectXVersionMajor = 6;
			}
			else if (dwMajor == 4 && dwMinor == 6 && dwRevision == 2)
			{
				lstrcpy(szFriendly, TEXT("DirectX 6.1"));
				pSysInfo->m_dwDirectXVersionMajor = 6;
				pSysInfo->m_dwDirectXVersionMinor = 1;
			}
			else if (dwMajor == 4 && dwMinor == 6 && dwRevision == 3)
			{
				lstrcpy(szFriendly, TEXT("DirectX 6.1a"));
				pSysInfo->m_dwDirectXVersionMajor = 6;
				pSysInfo->m_dwDirectXVersionMinor = 1;
				pSysInfo->m_cDirectXVersionLetter = TEXT('a');
			}
			else if (dwMajor == 4 && dwMinor == 7 && dwRevision == 0 && dwBuild == 716)
			{
				lstrcpy(szFriendly, TEXT("DirectX 7.0a"));
				pSysInfo->m_dwDirectXVersionMajor = 7;
				pSysInfo->m_cDirectXVersionLetter = TEXT('a');
			}
			else if (dwMajor == 4 && dwMinor == 7 && dwRevision == 0)
			{
				lstrcpy(szFriendly, TEXT("DirectX 7.0"));
				pSysInfo->m_dwDirectXVersionMajor = 7;
			}
			else if (dwMajor == 4 && dwMinor == 7 && dwRevision == 1)
			{
				lstrcpy(szFriendly, TEXT("DirectX 7.1"));
				pSysInfo->m_dwDirectXVersionMajor = 7;
				pSysInfo->m_dwDirectXVersionMinor = 1;
			}
			else if (dwMajor == 4 && dwMinor == 8 && dwRevision == 0 )
			{
				lstrcpy(szFriendly, TEXT("DirectX 8.0"));
				pSysInfo->m_dwDirectXVersionMajor = 8;
			}
			else if (dwMajor == 4 && dwMinor == 8 && dwRevision == 1 )
			{
				lstrcpy(szFriendly, TEXT("DirectX 8.1"));
				pSysInfo->m_dwDirectXVersionMajor = 8;
				pSysInfo->m_dwDirectXVersionMinor = 1;
			}
			else if (dwMajor == 4 && dwMinor == 9 )
			{
				lstrcpy(szFriendly, TEXT("DirectX 9.0"));
				pSysInfo->m_dwDirectXVersionMajor = 9;
				pSysInfo->m_dwDirectXVersionMinor = 0;
			}
			else
			{
				pSysInfo->m_dwDirectXVersionMajor = dwMinor;
				pSysInfo->m_dwDirectXVersionMinor = dwRevision;
			}

			if (lstrlen(szFriendly) > 0)
				wsprintf(pSysInfo->m_szDirectXVersionLong, TEXT("%s (%s)"), szFriendly, pSysInfo->m_szDirectXVersion);
			else
				lstrcpy(pSysInfo->m_szDirectXVersionLong, pSysInfo->m_szDirectXVersion);
		}*/

	}
}
