#pragma once

#include <string>

// 日志类型：INFO、DEBUG、WARNING、ERROR、FATAL
// 输出举例：2021-07-30 15:38:18	 DEBUG  hello deubg info.

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

    // 向调试窗口输出日志
    void Print(LogType logType, string fmtStr, ...);
    void Print(LogType logType, wstring fmtStr, ...);
    
    // 向文件输出日志
    void Write(LogType logType, string fmtStr, ...);
    void Write(LogType logType, wstring fmtStr, ...);

    static string   LogTypeToStringA(LogType logType);
    static wstring  LogTypeToStringW(LogType logType);    
    static string   GetDateTimeA();
    static wstring  GetDateTimeW();    
    static string   GetDateTimeNumberA();
    static wstring  GetDateTimeNumberW();
    
    // 如果文件可用，则根据设置的文件大小备份文件，成功备份返回true，否则返回false
    bool Backup();

    // 设置文件大于该大小时备份文件，字节为单位
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
// 全局函数
//

#ifndef LOGINFODISABLE

#define PrintInfo(fmtStr, ...)    LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Info, fmtStr, __VA_ARGS__)
#define PrintDebug(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Debug, fmtStr, __VA_ARGS__)
#define PrintWarning(fmtStr, ...) LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Warning, fmtStr, __VA_ARGS__)
#define PrintError(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Error, fmtStr, __VA_ARGS__)
#define PrintFatal(fmtStr, ...)   LogInfo::CLogInfoInstance::GetInstance()->Print(LogInfo::Fatal, fmtStr, __VA_ARGS__)

// 设置单个日志文件的最大大小，fileSize字节为单位
#define SetLogFileSize(fileSize)  LogInfo::CLogInfoInstance::GetInstance()->SetLimitSize(fileSize)

// 设置日志文件存放路径
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

// 设置单个日志文件的最大大小，fileSize字节为单位
#define SetLogFileSize(fileSize)  LogInfo::CLogInfoInstance::GetInstance()->SetLimitSize(fileSize)

// 设置日志文件存放路径
#define SetLogFilePath(filePath)  LogInfo::CLogInfoInstance::GetInstance()->SetFilePath(filePath)

#define WriteInfo(fmtStr, ...)
#define WriteDebug(fmtStr, ...)
#define WriteWarning(fmtStr, ...)
#define WriteError(fmtStr, ...)
#define WriteFatal(fmtStr, ...)

#endif
