#pragma once

#include <string>

// ��־���ͣ�INFO��DEBUG��WARNING��ERROR��FATAL
// ���������2021-07-30 15:38:18	 DEBUG  hello deubg info.

#define NS_LOGINFO_BEGIN namespace LogInfo {
#define NS_LOGINFO_END   }

NS_LOGINFO_BEGIN

using namespace std;

enum LogType
{
    Info,
    Debug,
    Warning,
    Error,
    Fatal
};

//
// class CLogInfo
//
class CLogInfo
{
public:
    CLogInfo();
    CLogInfo(string filePath);
    CLogInfo(wstring filePath);

    // ����Դ��������־
    void Print(LogType logType, string fmtStr, ...);
    void Print(LogType logType, wstring fmtStr, ...);
    
    // ���ļ������־
    void Write(LogType logType, string fmtStr, ...);
    void Write(LogType logType, wstring fmtStr, ...);

    static string   LogTypeToStringA(LogType logType);
    static wstring  LogTypeToStringW(LogType logType);    
    static string   GetDateTimeA();
    static wstring  GetDateTimeW();    
    static string   GetDateTimeNumberA();
    static wstring  GetDateTimeNumberW();
    
    // ����ļ����ã���������õ��ļ���С�����ļ����ɹ����ݷ���true�����򷵻�false
    bool Backup();

    // �����ļ����ڸô�Сʱ�����ļ����ֽ�Ϊ��λ
    void SetLimitSize(ios::pos_type fileSize);

    void SetFilePath(string filePath);
    void SetFilePath(wstring filePath);

private:
    ios::pos_type m_limitSize;
    wstring m_filePath;
};


//
// class CLogInfoInstance
//
class CLogInfoInstance
{
public:
    static CLogInfo *GetInstance();
};


NS_LOGINFO_END

//
// ȫ�ֺ���
//

#ifndef LOGINFODISABLE

#define PrintInfo(fmtStr, ...)    LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Info, fmtStr, __VA_ARGS__)
#define PrintDebug(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Debug, fmtStr, __VA_ARGS__)
#define PrintWarning(fmtStr, ...) LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Warning, fmtStr, __VA_ARGS__)
#define PrintError(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Error, fmtStr, __VA_ARGS__)
#define PrintFatal(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Fatal, fmtStr, __VA_ARGS__)

// ���õ�����־�ļ�������С��fileSize�ֽ�Ϊ��λ
#define SetLogFileSize(fileSize)  LogInfo::CLogInfoInstance::GetInstance()->SetLimitSize(fileSize)

// ������־�ļ����·��
#define SetLogFilePath(filePath)  LogInfo::CLogInfoInstance::GetInstance()->SetFilePath(filePath)

#define WriteInfo(fmtStr, ...)    LogInfo::CLogInfoInstance::GetInstance()->Write(LogInfo::Info, fmtStr, __VA_ARGS__)
#define WriteDebug(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Write(LogInfo::Debug, fmtStr, __VA_ARGS__)
#define WriteWarning(fmtStr, ...) LogInfo::CLogInfoInstance::GetInstance()->Write(LogInfo::Warning, fmtStr, __VA_ARGS__)
#define WriteError(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Write(LogInfo::Error, fmtStr, __VA_ARGS__)
#define WriteFatal(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Write(LogInfo::Fatal, fmtStr, __VA_ARGS__)

#else

#define PrintInfo(fmtStr, ...)
#define PrintDebug(fmtStr, ...)
#define PrintWarning(fmtStr, ...)
#define PrintError(fmtStr, ...)
#define PrintFatal(fmtStr, ...)

// ���õ�����־�ļ�������С��fileSize�ֽ�Ϊ��λ
#define SetLogFileSize(fileSize)  LogInfo::CLogInfoInstance::GetInstance()->SetLimitSize(fileSize)

// ������־�ļ����·��
#define SetLogFilePath(filePath)  LogInfo::CLogInfoInstance::GetInstance()->SetFilePath(filePath)

#define WriteInfo(fmtStr, ...)
#define WriteDebug(fmtStr, ...)
#define WriteWarning(fmtStr, ...)
#define WriteError(fmtStr, ...)
#define WriteFatal(fmtStr, ...)

#endif
