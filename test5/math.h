#pragma once
#include "log.h"

class math
{
public:
	int lives = 3;
	int score = 0;
	int difficulty = 0;
	int gamemode = 0;
private:
	#define ADDITION_SIGN 0
	#define SUBSTRACTION_SIGN 1
	#define MULTIPLICATION_SIGN 2
	const char* char_signs = "+-*";
	const char* char_numbers = "0123456789";
	int sides[3];
	int py_id;
	const int pya[16] = { 3, 5,  8,  7,  20, 12, 9,  28, 11, 16, 33, 48, 13, 36, 39, 65 };
	const int pyb[16] = { 4, 12, 15, 24, 21, 35, 40, 45, 60, 63, 56, 55, 84, 77, 80, 72 };
	const int pyc[16] = { 5, 13, 17, 25, 29, 37, 41, 53, 61, 65, 65, 73, 85, 85, 89, 97 };
public:
	void GetDifficulty(int range, Log& log);
	void InitVars();
	void DisplayScore(Log& log);
	//gm1
	void GetRandomNumbers(int* numbers, int* signs, int random_size);
	void OutputQuestion(Log& log, int* numbers, int* signs, int size);
	bool GetAnswerGM1(Log & log, int* numbers, int* signs, int size);
	int CalculateAnswer(int* numbers, int* signs, int size);
	//gm2
	void GetPythagorean();
	void OutputPythagorean(Log& log);
	bool GetAnswerGM2(Log& log);
private:
	int GetInput();
};