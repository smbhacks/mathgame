#include <iostream>
#include <windows.h>
#include "log.h"

wchar_t* Log::convertCharArrayToLPCWSTR(const char* charArray)
{
	wchar_t* wString = new wchar_t[4096];
	MultiByteToWideChar(CP_ACP, 0, charArray, -1, wString, 4096);
	return wString;
}

void Log::SetLogTitle(const char* string)
{
	m_LogTitle = string;
	SetConsoleTitle(convertCharArrayToLPCWSTR(string));
}

bool Log::SetLogLevel(unsigned int level)
{
	if (level > 2) return false;
	m_LogLevel = level;
	std::string updated_title = m_LogTitle;
	updated_title += " with log level: ";
	switch (level)
	{
	case 0:
		updated_title += "all";
		break;
	case 1:
		updated_title += "warnings and errors only";
		break;
	case 2:
		updated_title += "errors only";
		break;
	default:
		updated_title += "disabled";
		break;
	}
	const char* update_title_const_char = updated_title.c_str();
	SetLogTitle(update_title_const_char);
	return true;
}

void Log::NewLine()
{
	std::cout << std::endl;
}

void Log::LogToConsole(const char* message, int level, bool NewLine)
{
	if (m_LogLevel <= level)
	{
		switch (level)
		{
		case 0:
			std::cout << "\x1B[36m[INFO] ";
			break;
		case 1:
			std::cout << "\x1B[33m[WARN] ";
			break;
		case 2:
			std::cout << "\x1B[31m[ERROR] ";
			break;
		case 3:
			std::cout << "\x1B[37m";
			break;
		}
		std::cout << message;
		if (NewLine == true) std::cout << std::endl;
	}
}

void Log::EndOfProgram()
{
	LogToConsole("", LOGMESSAGE, true);
	LogToConsole("You can now exit the program...", LOGMESSAGE, false);
	std::cin >> m_LogLevel;
}

Log::Log(unsigned int level)
{
	//Set init log level
	SetLogLevel(level);
}