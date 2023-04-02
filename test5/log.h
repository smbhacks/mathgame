#pragma once
#include <iostream>
class Log
{
public:
	const unsigned int LOGINFO = 0;
	const unsigned int LOGWARNING = 1;
	const unsigned int LOGERROR = 2;
	const unsigned int LOGMESSAGE = 3;
private:
	int m_LogLevel = LOGINFO;
	std::string m_LogTitle;
public:
	void SetLogTitle(const char* string);
	bool SetLogLevel(unsigned int level);
	void LogToConsole(const char* message, int level, bool NewLine);
	void EndOfProgram();
	void NewLine();
private:
	wchar_t* convertCharArrayToLPCWSTR(const char* charArray);
};