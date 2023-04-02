#include "math.h"
#include "log.h"
#include <random>

//public
int math::GetDifficulty()
{
	int x; std::cin >> x;
	switch (x)
	{
	case 1:
		difficulty = 2;
		break;
	case 2:
		difficulty = 3;
		break;
	case 3:
		difficulty = 6;
	default:
		break;
	}
	return difficulty;
}

void math::GetRandomNumbers(int* numbers, int* signs, int random_size)
{
	for (int i = 0; i < random_size; i++)
	{
		numbers[i] = rand() % 9 + 1;
		//signs[0] is not going to be read!
		signs[i] = rand() % 3;
	}
}

void math::OutputQuestion(Log& log, int* numbers, int* signs, int size)
{;
	std::string question;
	question += char_numbers[numbers[0]];
	for (int i = 1; i < size; i++)
	{
		question += ' ';
		question += char_signs[signs[i]];
		question += ' ';
		question += char_numbers[numbers[i]];
	}
	question += " = ";
	const char* c = question.c_str();
	log.LogToConsole(c, log.LOGMESSAGE, false);
}

bool math::GetAnswer(Log& log, int* numbers, int* signs, int size)
{
	if (GetInput()==CalculateAnswer(numbers, signs, size))
	{
		log.LogToConsole("Correct Answer!", log.LOGINFO, true);
		return true;
	}
	else
	{
		log.LogToConsole("Incorrect Answer!", log.LOGERROR, true);
		lives--;
		return false;
	}
}

int math::CalculateAnswer(int* numbers, int* signs, int size)
{
	//Check multiplications first
	for (int i = size-1; i > 0; i--)
	{
		if (signs[i] == MULTIPLICATION_SIGN)
		{
			numbers[i-1] *= numbers[i];
			numbers[i] = 1;
		}
	}
	//Handle new equation from left to right
	for (int i = 1; i < size; i++)
	{
		switch (signs[i])
		{
		case ADDITION_SIGN:
			numbers[i] += numbers[i - 1];
			break;
		case SUBSTRACTION_SIGN:
			numbers[i] = numbers[i-1] - numbers[i];
			break;
		case MULTIPLICATION_SIGN:
			numbers[i] *= numbers[i - 1];
			break;
		}
	}
	return numbers[size-1];
}

//private
int math::GetInput()
{
	int x; std::cin >> x;
	return x;
}