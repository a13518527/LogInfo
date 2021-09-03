#include "stdafx.h"
#include "LogInfo.h"
#include <fstream>
#include <Windows.h>

NS_LOGINFO_BEGIN

const unsigned BUFFSIZE       = 8192U;      // 8KB
const unsigned DEFLOGFILESIZE = 0x200000;   // 2M

#define MAKETEXTA(logType, fmtStr) \
    string text; \
    text.append(GetDateTimeA()); \
    text.append("    "); \
    text.append(LogTypeToStringA(logType)); \
    text.append("\t"); \
    char szBuffer[BUFFSIZE]{0}; \
    va_list vl; \
    va_start(vl, fmtStr);\
    vsnprintf_s(szBuffer, BUFFSIZE, BUFFSIZE, fmtStr.c_str(), vl);\
    va_end(vl);\
    text.append(szBuffer); \
    text.append("\n")

#define MAKETEXTW(logType, fmtStr) \
    wstring text; \
    text.append(GetDateTimeW()); \
    text.append(L"    "); \
    text.append(LogTypeToStringW(logType)); \
    text.append(L"\t"); \
    wchar_t szBuffer[BUFFSIZE]{0}; \
    va_list vl; \
    va_start(vl, fmtStr);\
    _vsnwprintf_s(szBuffer, BUFFSIZE, BUFFSIZE, fmtStr.c_str(), vl);\
    va_end(vl);\
    text.append(szBuffer); \
    text.append(L"\n")

//
// class CLogInfo
//

CLogInfo::CLogInfo()
    : m_limitSize(DEFLOGFILESIZE)
{
}


CLogInfo::CLogInfo(string filePath)
    : m_limitSize(DEFLOGFILESIZE)
{
    SetFilePath(filePath);
}


CLogInfo::CLogInfo(wstring filePath)
    : m_limitSize(DEFLOGFILESIZE)
{
    SetFilePath(filePath);
}


void CLogInfo::Print(LogType logType, string fmtStr, ...)
{
    MAKETEXTA(logType, fmtStr);
    OutputDebugStringA(text.c_str());
}


void CLogInfo::Print(LogType logType, wstring fmtStr, ...)
{
    MAKETEXTW(logType, fmtStr);
    OutputDebugStringW(text.c_str());
}


void CLogInfo::Write(LogType logType, string fmtStr, ...)
{
    Backup();
    ofstream ofs(m_filePath, ios::app | ios::out);
    if (ofs.bad()) return;
    ofs.imbue(locale(locale(), "", LC_CTYPE));
    MAKETEXTA(logType, fmtStr);
    ofs.write(text.c_str(), text.length());
    ofs.close();
}


void CLogInfo::Write(LogType logType, wstring fmtStr, ...)
{
    Backup();
    wofstream ofs(m_filePath, ios::app|ios::out);
    if (ofs.bad()) return;
    ofs.imbue(locale(locale(), "", LC_CTYPE));
    MAKETEXTW(logType, fmtStr);
    ofs.write(text.c_str(), text.length());
    ofs.close();
}


string CLogInfo::LogTypeToStringA(LogType logType)
{
    switch (logType)
    {
    default:
    case Info:
        return "INFO";
    case Debug:
        return "DEBUG";
    case Warning:
        return "WARNING";
    case Error:
        return "ERROR";
    case Fatal:
        return "FATAL";
    }
}


wstring CLogInfo::LogTypeToStringW(LogType logType)
{
    switch (logType)
    {
    default:
    case Info:
        return L"INFO";
    case Debug:
        return L"DEBUG";
    case Warning:
        return L"WARNING";
    case Error:
        return L"ERROR";
    case Fatal:
        return L"FATAL";
    }
}


string CLogInfo::GetDateTimeA()
{
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    char szTime[64] = { 0 };
    sprintf_s(szTime, _countof(szTime), "%04d-%02d-%02d %02d:%02d:%02d",
        tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
    return szTime;
}


wstring CLogInfo::GetDateTimeW()
{
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    wchar_t szTime[64] = { 0 };
    swprintf_s(szTime, _countof(szTime), L"%04d-%02d-%02d %02d:%02d:%02d",
        tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond);
    return szTime;
}


string CLogInfo::GetDateTimeNumberA()
{
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    char szTime[64] = { 0 };
    sprintf_s(szTime, _countof(szTime), "%04d%02d%02d%02d%02d%02d%04d",
        tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
    return szTime;
}


wstring CLogInfo::GetDateTimeNumberW()
{
    SYSTEMTIME tm;
    GetLocalTime(&tm);
    wchar_t szTime[64] = { 0 };
    swprintf_s(szTime, _countof(szTime), L"%04d%02d%02d%02d%02d%02d%04d",
        tm.wYear, tm.wMonth, tm.wDay, tm.wHour, tm.wMinute, tm.wSecond, tm.wMilliseconds);
    return szTime;
}


bool CLogInfo::Backup()
{
    if (m_filePath.empty()) return false;

    ifstream ifs(m_filePath);
    if (ifs.bad()) return false;
    
    ifs.seekg(0, ios::end);
    ios::pos_type fsize = ifs.tellg();
    ifs.seekg(0, ios::beg);
    ifs.close();
    
    if (fsize > m_limitSize)
    {
        wstring newPath = m_filePath;
        newPath.append(L".");
        newPath.append(GetDateTimeNumberW());
        newPath.append(L".log");
        if (MoveFileW(m_filePath.c_str(), newPath.c_str()))
            return true;
        else
            return false;
    }
    else return false;
}


void CLogInfo::SetLimitSize(ios::pos_type fileSize)
{
    m_limitSize = fileSize;
}


void CLogInfo::SetFilePath(string filePath)
{
    _wsetlocale(LC_ALL, L"");

    size_t sizeInWords = filePath.length() + 1;
    wchar_t *pDstBuf = new wchar_t[sizeInWords] { 0 };
    mbstowcs_s(NULL, pDstBuf, sizeInWords, filePath.c_str(), _TRUNCATE);
    wstring wstr = pDstBuf;
    delete[]pDstBuf;

    SetFilePath(wstr);
}


void CLogInfo::SetFilePath(wstring filePath)
{
    m_filePath = filePath;
}


//
// class CLogInfoInstance
//

CLogInfo *CLogInfoInstance::GetInstance()
{
    static CLogInfo logInfo;
    return &logInfo;
}


NS_LOGINFO_END

