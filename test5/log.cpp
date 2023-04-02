#include <iostream>
#include <windows.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include "log.h"

//Taken from https://stackoverflow.com/questions/32140018/why-is-this-program-giving-an-error-to-string-is-not-a-member-of-std-why
//for some reason to_string() doesn't work for me
std::string Log::toString(int value) {
	std::ostringstream os;
	os << value;
	return os.str();
}

unsigned int Log::GetValue(int& x)
{
	std::cin >> x;
	return x - 1;
}

void Log::LogClear()
{
	system("CLS");
}

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

void Log::LogCharacter(char character, int size, unsigned int level, bool newline)
{
	if (m_LogLevel <= level)
	{
		//set color
		switch (level)
		{
		case 0:
			std::cout << "\x1B[36m";
			break;
		case 1:
			std::cout << "\x1B[33m";
			break;
		case 2:
			std::cout << "\x1B[31m";
			break;
		case 3:
			std::cout << "\x1B[37m";
			break;
		}
		for (int i = size; i > 0; i--)
		{
			std::cout << character;
		}
		if (newline == true) std::cout << std::endl;
	}
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