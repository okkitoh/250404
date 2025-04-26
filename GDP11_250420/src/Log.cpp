
#include "Log.h"
#include <iostream>



std::vector<LogEntry> Log::LogEntries;
//void Log::Message(const std::string& message)
//{
//	std::cout << message << std::endl;
//}
//void Log::SpacedMessage(const std::string& message)
//{
//	std::cout << std::endl << message << std::endl;
//}

void Log::LogMessage(LogType Type, const std::string& Message)
{
	LogEntry Entry;
	Entry.Type = Type;
	Entry.Message = Message;
	//Entry.TimeStamp = time();
	LogEntries.push_back(Entry);
	PrintLog(Entry);
	
}
void Log::Separator()
{
	std::cout << "----------------------------------------------------------" << std::endl;
}
void Log::PrintLog(LogEntry& Entry)
{
	std::string color;
	switch (Entry.Type)
	{
	case MLOG_INFO:
		color = "\x1B[32m"; // Green
		break;
	case MLOG_WARNING:
		color = "\x1B[33m"; // Yellow
		break;
	case MLOG_ERROR:
		color = "\x1B[91m"; // Red
		break;
	case MLOG_DEFAULT:
		color = "\x1B[0m"; // White
		break;
	}
	std::cout << color << Entry.Message << "\x1B[0m" << std::endl;
}
