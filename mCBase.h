#pragma once

class mCBase
{
public:
	mCBase();
	~mCBase();
};

#define utoa(u) (LPCSTR)CW2A(u)
#define utou8(u) (LPCSTR)CW2A(u, CP_UTF8)

#define atou(a) (CStringW)CA2W(a)
#define atou8(a) (LPCSTR)CW2A(CA2W(a), CP_UTF8)

#define stou8(s) (LPCSTR)CW2A(CA2W( s.c_str() ), CP_UTF8)

#define u8tou(u8) (CStringW)CA2W(u8, CP_UTF8)

CStringW GetCurrentPath(CStringW &sPath);
CStringW ToAbsolutePath(CStringW &sPath);

bool IsValidPath(CStringW sPath);
void NewPath(CStringW sPath);

__int64 GetTime();
CStringW GetDateTimeU(bool bIncludingMS = true);
string GetDateTime(bool bIncludingMS = true);
CStringW GetDateU();
string GetDate();
void GetDateTime(CStringW &sDateTime, bool bIncludingMS = true);
void GetDateTime(string &sDateTime, bool bIncludingMS = true);
void GetDate(CStringW &sDate);
void GetDate(string &sDate);

int GetProcessorNumber();
CRect GetDesktopCRect(bool bIncludeTaskbar = false);

void filetostr(CStringW file, CStringW &str);
void filetostr(CStringW file, string &str);
CStringW filetostrU(CStringW file);
string filetostr(CStringW file);

void strtofile(CStringW str, CStringW file);
void strtofile(string str, CStringW file);

bool WaitForObjects(HANDLE *pHandles);

void GenerateGuid(string &sGuid);
string GenerateGuid();

void Log(CStringW sPrefix, const CStringW sFormat, ...);

