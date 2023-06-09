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
	Log(unsigned int level);
	void SetLogTitle(const char* string);
	bool SetLogLevel(unsigned int level);
	void LogToConsole(const char* message, int level, bool NewLine);
	void EndOfProgram();
	void NewLine();
	void LogCharacter(char character, int size, unsigned int level, bool newline);
	void LogClear();
	unsigned int GetValue(int&);
	std::string toString(int value);
private:
	wchar_t* convertCharArrayToLPCWSTR(const char* charArray);
};