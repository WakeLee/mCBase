#include "stdafx.h"
#include "mCBase.h"

mCBase::mCBase(void)
{
}
mCBase::~mCBase(void)
{
}

CStringW GetCurrentPath(CStringW &sPath)
{
	WCHAR szPath[MAX_PATH] = {0}; 
	::GetModuleFileName(NULL, szPath, MAX_PATH);

	CStringW sTemp(szPath);
	sPath = sTemp.Left( sTemp.ReverseFind('\\') );

	return sPath;
}
CStringW ToAbsolutePath(CStringW &sPath)
{
	CStringW sTemp = sPath;
	if( ::PathIsRelative( sTemp.TrimLeft('\\') ) )
	{
		::GetCurrentPath(sPath);
		sPath += L"\\" + sTemp;
	}

	return sPath;
}

bool IsValidPath(CStringW sPath)
{
	return ::PathFileExists(sPath) ? true : false;
}
void NewPath(CStringW sPath)
{
	::ToAbsolutePath(sPath);

	sPath += L"\\";

	vector<CStringW> vPath;
	int iFirst = 0;
	int iCount = 0;
	for(int i = 0; i < sPath.GetLength(); i++)
	{
		if(sPath[i] == '\\')
		{
			iCount = i - iFirst;
			vPath.push_back( sPath.Mid(iFirst, iCount) );
			iFirst = i + 1;
		}
	}

	CStringW sPathT = vPath[0];
	for(unsigned int i = 1; i < vPath.size(); i++)
	{
		sPathT += L"\\" + vPath[i];
		if( !::PathFileExists(sPathT) )
		{
			::CreateDirectory(sPathT, NULL);
		}
	}
}

__int64 GetTime()
{
	SYSTEMTIME systime; ::GetLocalTime(&systime);
	CTime tm(systime);

	return tm.GetTime() * 1000i64 + systime.wMilliseconds;
}
CStringW GetDateTimeU(bool bIncludingMS)
{
	CStringW sDateTime;

	SYSTEMTIME systime; ::GetLocalTime(&systime);

	if (bIncludingMS)
	{
		sDateTime.Format(L"%d-%02d-%02d %02d:%02d:%02d.%03d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond,
			systime.wMilliseconds
		);
	}
	else
	{
		sDateTime.Format(L"%d-%02d-%02d %02d:%02d:%02d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond
		);
	}

	return sDateTime;
}
string GetDateTime(bool bIncludingMS)
{
	string sDateTime;

	SYSTEMTIME systime; ::GetLocalTime(&systime);

	CStringA csa;
	if (bIncludingMS)
	{
		csa.Format("%d-%02d-%02d %02d:%02d:%02d.%03d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond,
			systime.wMilliseconds
		);
	}
	else
	{
		csa.Format("%d-%02d-%02d %02d:%02d:%02d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond
		);
	}
	sDateTime = csa;

	return sDateTime;
}
CStringW GetDateU()
{
	CStringW sDate;
	SYSTEMTIME systime; ::GetLocalTime(&systime);
	sDate.Format(L"%d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
	return sDate;
}
string GetDate()
{
	string sDate;

	SYSTEMTIME systime; ::GetLocalTime(&systime);

	CStringA csa;
	csa.Format("%d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
	sDate = csa;

	return sDate;
}
void GetDateTime(CStringW &sDateTime, bool bIncludingMS)
{
	SYSTEMTIME systime; ::GetLocalTime(&systime);

	if(bIncludingMS)
	{
		sDateTime.Format(L"%d-%02d-%02d %02d:%02d:%02d.%03d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond,
			systime.wMilliseconds
			);
	}
	else
	{
		sDateTime.Format(L"%d-%02d-%02d %02d:%02d:%02d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond
			);
	}
}
void GetDateTime(string &sDateTime, bool bIncludingMS)
{
	SYSTEMTIME systime; ::GetLocalTime(&systime);

	CStringA csa;
	if(bIncludingMS)
	{
		csa.Format("%d-%02d-%02d %02d:%02d:%02d.%03d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond,
			systime.wMilliseconds
		);
	}
	else
	{
		csa.Format("%d-%02d-%02d %02d:%02d:%02d",
			systime.wYear, systime.wMonth, systime.wDay,
			systime.wHour, systime.wMinute, systime.wSecond
			);
	}
	sDateTime = csa;
}
void GetDate(CStringW &sDate)
{
	SYSTEMTIME systime; ::GetLocalTime(&systime);
	sDate.Format(L"%d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
}
void GetDate(string &sDate)
{
	SYSTEMTIME systime; ::GetLocalTime(&systime);

	CStringA csa;
	csa.Format("%d-%02d-%02d", systime.wYear, systime.wMonth, systime.wDay);
	sDate = csa;
}

int GetProcessorNumber()
{
	SYSTEM_INFO si; ::GetSystemInfo(&si);
	return si.dwNumberOfProcessors;
}
CRect GetDesktopCRect(bool bIncludeTaskbar)
{
	CRect crect;

	if(bIncludeTaskbar)
	{
		crect.left = 0;
		crect.top = 0;
		crect.right = ::GetSystemMetrics(SM_CXSCREEN); 
		crect.bottom = ::GetSystemMetrics(SM_CYSCREEN); 
	}
	else
	{
		::SystemParametersInfo(SPI_GETWORKAREA, 0, (PVOID)&crect, 0);
	}

	return crect;
}

void filetostr(CStringW file, CStringW &str)
{
	string strT; ::filetostr(file, strT);

	int size = ::MultiByteToWideChar(CP_UTF8, 0, strT.c_str(), -1, NULL, 0);
	str.GetBuffer(size);
	::MultiByteToWideChar(CP_UTF8, 0, strT.c_str(), -1, (LPWSTR)(LPCTSTR)str, size);
	str.ReleaseBuffer();
}
void filetostr(CStringW file, string &str)
{
	::ToAbsolutePath(file);

	CFile f;
	f.Open(file, CFile::modeRead | CFile::shareDenyNone);
	unsigned int size = (unsigned int)f.GetLength();
	str.resize(size);
	f.Read(&str[0], size);
	f.Close();
}
CStringW filetostrU(CStringW file)
{
	CStringW str;

	string strT; ::filetostr(file, strT);

	int size = ::MultiByteToWideChar(CP_UTF8, 0, strT.c_str(), -1, NULL, 0);
	str.GetBuffer(size);
	::MultiByteToWideChar(CP_UTF8, 0, strT.c_str(), -1, (LPWSTR)(LPCTSTR)str, size);
	str.ReleaseBuffer();

	return str;
}
string filetostr(CStringW file)
{
	string str;

	::ToAbsolutePath(file);

	CFile f;
	f.Open(file, CFile::modeRead | CFile::shareDenyNone);
	unsigned int size = (unsigned int)f.GetLength();
	str.resize(size);
	f.Read(&str[0], size);
	f.Close();

	return str;
}

void strtofile(CStringW str, CStringW file)
{
	::strtofile(utou8(str), file);
}
void strtofile(string str, CStringW file)
{
	::ToAbsolutePath(file);

	CFile f;
	f.Open(file, CFile::modeCreate | CFile::modeWrite | CFile::shareDenyWrite);
	f.Write( str.c_str(), (unsigned int)str.size() );
	f.Close();
}

bool WaitForObjects(HANDLE *pHandles)
{
	int iHandlesCount = sizeof(pHandles) / sizeof( pHandles[0] );

	int iCount = 0;
	while(true)
	{
		DWORD dwReturnurn = ::MsgWaitForMultipleObjects(iHandlesCount, pHandles, FALSE, INFINITE, QS_ALLINPUT);
		if( dwReturnurn >= WAIT_OBJECT_0 && dwReturnurn <= WAIT_OBJECT_0 + iHandlesCount - 1)
		{
			iCount++;
		}
		else
		{
			MSG msg;
			::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE);
			::TranslateMessage(&msg);
			::DispatchMessage(&msg);
		}

		if(iCount >= iHandlesCount)
		{
			break;
		} 
	}
	return false;
}

void GenerateGuid(string &sGuid)
{
	::CoInitialize(NULL);

	GUID guid;
	if(::CoCreateGuid(&guid) == S_OK)
	{
		SYSTEMTIME systime; ::GetLocalTime(&systime);
		CTime tm(systime);
		__int64 iTime = tm.GetTime() * 1000i64 + systime.wMilliseconds;

		CStringA csa;
		csa.Format("%I64d%08X%04X%04x%02X%02X%02X%02X%02X%02X%02X%02X",
			iTime,
			guid.Data1, guid.Data2, guid.Data3, 
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3], 
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
		);

		sGuid = csa;
	}

	::CoUninitialize();
}
string GenerateGuid()
{
	string sGuid;

	::CoInitialize(NULL);

	GUID guid;
	if (::CoCreateGuid(&guid) == S_OK)
	{
		SYSTEMTIME systime; ::GetLocalTime(&systime);
		CTime tm(systime);
		__int64 iTime = tm.GetTime() * 1000i64 + systime.wMilliseconds;

		CStringA csa;
		csa.Format("%I64d%08X%04X%04x%02X%02X%02X%02X%02X%02X%02X%02X",
			iTime,
			guid.Data1, guid.Data2, guid.Data3,
			guid.Data4[0], guid.Data4[1], guid.Data4[2], guid.Data4[3],
			guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]
		);

		sGuid = csa;
	}

	::CoUninitialize();

	return sGuid;
}

void Log(CStringW sPrefix, const CStringW sFormat, ...)
{
	CStringW sLog;
	va_list vlist;
	va_start(vlist, sFormat);
	sLog.FormatV(sFormat, vlist);
	va_end(vlist);

	CStringW sPath = L"\\Log";
	NewPath(sPath);
	CStringW sFile;
	sFile.Format(L"\\%s-%010x.log", sPrefix, GetCurrentThreadId());
	sFile = sPath + sFile;
	ToAbsolutePath(sFile);

	CFile file;
	file.Open(sFile, CFile::modeCreate | CFile::modeWrite | CFile::modeNoTruncate);  
	file.SeekToEnd();
	string u8 = utou8(sLog);
	file.Write( u8.c_str(), (unsigned int)u8.size() );
	file.Write("\r\n", 2);
	file.Close();
}