#pragma once
#include "log.h"

class math
{
public:
	int lives = 3;
	int score = 0;
	int difficulty = 0;
private:
	#define ADDITION_SIGN 0
	#define SUBSTRACTION_SIGN 1
	#define MULTIPLICATION_SIGN 2
	const char* char_signs = "+-*";
	const char* char_numbers = "0123456789";
public:
	void GetRandomNumbers(int* numbers, int* signs, int random_size);
	void OutputQuestion(Log& log, int* numbers, int* signs, int size);
	bool GetAnswer(Log& log, int* numbers, int* signs, int size);
	int CalculateAnswer(int* numbers, int* signs, int size);
	int GetDifficulty();
private:
	int GetInput();
};