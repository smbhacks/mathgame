#include <iostream>
#include "log.h"
#include "math.h"
#include "resource1.h"
#include <time.h>
#include <windows.h>
#include <chrono>
#pragma comment(lib, "Winmm.lib")

void Gamemode1(Log& log, math& game)
{
	//Get difficulty
	game.GetDifficulty(3, log);
	switch (game.difficulty)
	{
	case 1:
		game.difficulty = 2;
		break;
	case 2:
		game.difficulty = 3;
		break;
	case 3:
		game.difficulty = 6;
	default:
		break;
	}

	//Play Music
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	//Random Math Game
	while (game.lives > 0)
	{
		int random_number = rand() % game.difficulty + game.difficulty;
		int* numbers = new int[random_number];
		int* signs = new int[random_number];
		game.GetRandomNumbers(numbers, signs, random_number);
		game.OutputQuestion(log, numbers, signs, random_number);
		time_t start, end;
		time(&start);
		if (game.GetAnswerGM1(log, numbers, signs, random_number) == true)
		{
			time(&end);
			int change_score = -difftime(end, start) + random_number * 3;
			if (change_score < 0) change_score = 0;
			game.score += change_score;
		}
	}
	game.DisplayScore(log);

	//Play Music
	PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
}