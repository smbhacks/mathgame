#include <iostream>
#include "log.h"
#include "math.h"
#include "resource1.h"
#include <time.h>
#include <windows.h>
#include <chrono>
#pragma comment(lib, "Winmm.lib")

void Gamemode2(Log& log, math& game)
{
	//Get difficulty
	game.GetDifficulty(4, log);

	//Play Music
	PlaySound(MAKEINTRESOURCE(IDR_WAVE1), NULL, SND_RESOURCE | SND_LOOP | SND_ASYNC);

	//Pythagorean Game
	while (game.lives > 0)
	{
		//Get pyth. triangles and save them to class vars
		game.GetPythagorean();
		//Output questions
		game.OutputPythagorean(log);
		//Get answer
		time_t start, end;
		time(&start);
		if(game.GetAnswerGM2(log) == true)
		{
			time(&end);
			int change_score = -difftime(end, start) + game.difficulty * 3;
			if (change_score < 0) change_score = 0;
			game.score += change_score;
		}
	}
	game.DisplayScore(log);

	//Play Music
	PlaySound(MAKEINTRESOURCE(IDR_WAVE2), NULL, SND_RESOURCE | SND_ASYNC);
}