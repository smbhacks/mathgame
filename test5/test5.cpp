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

	//Init classes
	Log log(0);
	log.SetLogTitle("Math game!!!!!");
	math game;
	/*
	log.LogToConsole("Enter log level (0~2): [ENTER 0]", log.LOGMESSAGE, false);
	while (log.SetLogLevel(GetInput()) == false)
	{
		log.LogToConsole("Incorrect level value!", log.LOGERROR, true);
		log.LogToConsole("Enter log level (0~2): ", log.LOGMESSAGE, false);
	}
	*/

	log.LogToConsole("Enter your difficulty (1:easy, 2:medium, 3:hard): ", log.LOGMESSAGE, false);
	while (game.GetDifficulty() == 0)
	{
		log.LogToConsole("Invalid difficulty type", log.LOGERROR, true);
		log.LogToConsole("Enter your difficulty (1:easy, 2:medium, 3:hard): ", log.LOGMESSAGE, false);
	}

	//Play Music
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	//Random Math Game
	srand(std::time(nullptr));
	while (game.lives > 0)
	{
		int random_number = rand() % game.difficulty + game.difficulty;
		int* numbers = new int[random_number];
		int* signs = new int[random_number];
		game.GetRandomNumbers(numbers, signs, random_number);
		game.OutputQuestion(log, numbers, signs, random_number);
		time_t start, end;
		time(&start);
		if (game.GetAnswer(log, numbers, signs, random_number) == true)
		{
			time(&end);
			int change_score = -difftime(end, start) + random_number*3;
			int score_limit = -14 + random_number;
			if (change_score < score_limit) change_score = score_limit;
			game.score += change_score;
		}
	}
	log.LogToConsole("Your score: ", log.LOGMESSAGE, false);
	if (game.score < 0) game.score = 0;
	std::cout << game.score;

	//Play Music
	PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);

	//End of program
	log.EndOfProgram();
}
