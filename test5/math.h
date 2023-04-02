#pragma once
#include "log.h"

class math
{
public:
	int lives = 3;
	int score = 0;
private:
	int numbers[3];
	int signs[3]; // only use 2
	#define ADDITION_SIGN 0
	#define SUBSTRACTION_SIGN 1
	#define MULTIPLICATION_SIGN 2
	const char* char_signs = "+-*";
	const char* char_numbers = "0123456789";
public:
	void GetRandomNumbers();
	void OutputQuestion(Log& log);
	bool GetAnswer(Log& log);
	void CheckIfCorrect();
private:
	int CalculateAnswer();
	int GetInput();
};