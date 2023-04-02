#include <iostream>
#include <time.h>
#include <windows.h>
#include <chrono>
#include "log.h"
#include "math.h"
#include "resource1.h"
#include "gm1.h"
#include "gm2.h"
#pragma comment(lib, "Winmm.lib")

static int GetInput()
{
	int x; std::cin >> x;
	return x;
}

static void GetGamemode(Log& log, math& game)
{
	log.LogToConsole("Choose a gamemode: ", log.LOGMESSAGE, false);
	int& x = game.gamemode;
	while (log.GetValue(x) > 1)
	{
		log.LogToConsole("Invalid gamemode!", log.LOGERROR, true);
		log.LogToConsole("Choose a gamemode: ", log.LOGMESSAGE, false);
	}
}

static int GetOption(Log& log)
{
	log.LogToConsole("Choose option: ", log.LOGMESSAGE, false);
	int option;
	int& x = option;
	while (log.GetValue(x) > 2)
	{
		log.LogToConsole("Invalid option!", log.LOGERROR, true);
		log.LogToConsole("Choose option: ", log.LOGMESSAGE, false);
	}
	return option;
}

int main()
{
	//Make ANSI codes work
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	//Init classes
	Log log(0);
	log.SetLogTitle("Math game!!!!!");
	math game;
	int option = 2;
	while (option == 2)
	{
		//Choose gamemode
		log.LogClear();
		std::cout << R"(
  
                                                                                                            
                                    I8    ,dPYb,                                                            
                                    I8    IP'`Yb                                                            
                                 88888888 I8  8I                                                            
                                    I8    I8  8'                                                            
    ,ggg,,ggg,,ggg,     ,gggg,gg    I8    I8 dPgg,         ,gggg,gg    ,gggg,gg   ,ggg,,ggg,,ggg,    ,ggg,  
   ,8" "8P" "8P" "8,   dP"  "Y8I    I8    I8dP" "8I       dP"  "Y8I   dP"  "Y8I  ,8" "8P" "8P" "8,  i8" "8i 
   I8   8I   8I   8I  i8'    ,8I   ,I8,   I8P    I8      i8'    ,8I  i8'    ,8I  I8   8I   8I   8I  I8, ,8I 
  ,dP   8I   8I   Yb,,d8,   ,d8b, ,d88b, ,d8     I8,    ,d8,   ,d8I ,d8,   ,d8b,,dP   8I   8I   Yb, `YbadP' 
  8P'   8I   8I   `Y8P"Y8888P"`Y888P""Y8888P     `Y8    P"Y8888P"888P"Y8888P"`Y88P'   8I   8I   `Y8888P"Y888
                                                               ,d8I'                                        
                                                             ,dP'8I                                         
                                                            ,8"  8I                                         
                                                            I8   8I                                         
                                                            `8, ,8I                                         
                                                             `Y8P"                                          
  by studs
)" << '\n';
		log.LogCharacter('=', 110, log.LOGMESSAGE, true);
		log.LogToConsole("[1] Addition, subtraction, multiplication", log.LOGMESSAGE, true);
		log.LogToConsole("[2] Pythagorean triangles", log.LOGMESSAGE, true);
		GetGamemode(log, game);

		do
		{
			//Run through game
			srand(std::time(nullptr));
			log.LogClear();
			game.InitVars();
			switch (game.gamemode)
			{
			case 1:
				//[1] Addition, subtraction, multiplication
				Gamemode1(log, game);
				break;
			case 2:
				//[2] Pythagorean triangles
				Gamemode2(log, game);
			default:
				break;
			}
			log.LogToConsole("[1] Replay game", log.LOGMESSAGE, true);
			log.LogToConsole("[2] Go back to the menu", log.LOGMESSAGE, true);
			log.LogToConsole("[3] Quit game", log.LOGMESSAGE, true);
			option = (GetOption(log));
		} while (option == 1);
	}
}
