#pragma once

#include <vector>
#include <string>
#include <time.h>


enum LogType
{
	MLOG_DEFAULT,
	MLOG_INFO,
	MLOG_WARNING,
	MLOG_ERROR
};

// struct
struct LogEntry
{
	LogType Type;
	std::string Message;
	time_t TimeStamp;
};


class Log
{
public:
	//static void Message(const std::string& message);
	//static void SpacedMessage(const std::string& message);

	static std::vector<LogEntry> LogEntries;

	static void LogMessage(LogType Type, const std::string& Message);
	static void Separator();
	static void PrintLog(LogEntry &Entry);
};