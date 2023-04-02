#include <iostream>
#include "log.h"
#include "math.h"
#include "resource1.h"
#include <time.h>
#include <windows.h>
#include <chrono>
#pragma comment(lib, "Winmm.lib")

static int GetInput()
{
	int x; std::cin >> x;
	return x;
}

int main()
{
	//Make ANSI codes work
	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD dwMode = 0;
	GetConsoleMode(hOut, &dwMode);
	dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
	SetConsoleMode(hOut, dwMode);

	//Init log settings
	Log log;
	log.SetLogTitle("Math game!!!!!");
	log.LogToConsole("Enter log level (0~2): [ENTER 0]", log.LOGMESSAGE, false);
	while (log.SetLogLevel(GetInput()) == false)
	{
		log.LogToConsole("Incorrect level value!", log.LOGERROR, true);
		log.LogToConsole("Enter log level (0~2): ", log.LOGMESSAGE, false);
	}

	//Play Music
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	//Random Math Game
	srand(std::time(nullptr));
	math game;
	while (game.lives > 0)
	{
		game.GetRandomNumbers();
		game.OutputQuestion(log);
		time_t start, end;
		time(&start);
		if (game.GetAnswer(log) == true)
		{
			time(&end);
			int change_score = -difftime(end, start) + 5;
			if (change_score < -8) change_score = -8;
			game.score += change_score;
		}
	}
	log.LogToConsole("Your score: ", log.LOGMESSAGE, false);
	if (game.score < 0) game.score = 0;
	std::cout << game.score;

	//End of program
	log.EndOfProgram();
}
