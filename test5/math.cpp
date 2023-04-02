#include "math.h"
#include "log.h"
#include <random>

//public
void math::DisplayScore(Log& log)
{
	log.LogToConsole("Your score: ", log.LOGMESSAGE, false);
	if (score < 0) score = 0;
	std::cout << score << std::endl;
}

void math::GetDifficulty(int range, Log& log)
{
	std::string string = "Enter difficulty (1~";
	string += char_numbers[range];
	string += "): ";
	const char* c = string.c_str();
	log.LogToConsole(c, log.LOGMESSAGE, false);
	int& option = difficulty;
	while (log.GetValue(option) > range-1)
	{
		log.LogToConsole("Invalid difficulty!", log.LOGERROR, true);
		log.LogToConsole(c, log.LOGMESSAGE, false);
	}
}

void math::InitVars()
{
	lives = 3;
	score = 0;
	difficulty = 0;
}

//GM1
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

bool math::GetAnswerGM1(Log& log, int* numbers, int* signs, int size)
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

//GM2
void math::GetPythagorean()
{
	//change rand() here for difficulty setting
	py_id = rand() % (4 * difficulty);
	sides[0] = pya[py_id];
	sides[1] = pyb[py_id];
	sides[2] = pyc[py_id];
}

void math::OutputPythagorean(Log& log)
{
	//get a random missing_side var
	//make sides[2] the missing side
	if (sqrt(pow(sides[0], 2) + pow(sides[1], 2)) != sides[2]) log.LogToConsole("The solution for this doesn't match with the expected value. Please report this!", log.LOGERROR, true);
	int missing_side = rand() % 3;
	if (missing_side != 2)
	{
		int solution = sides[missing_side];
		sides[missing_side] = sides[2];
		sides[2] = solution;
	}
	//make string
	std::string string = "";
	int i = rand();
	string += log.toString(sides[i%2]);
	string += ' ';
	string += log.toString(sides[(i+1)%2]);
	string += ' ';
	const char* c = string.c_str();
	log.LogToConsole(c, log.LOGMESSAGE, false);
}

bool math::GetAnswerGM2(Log& log)
{
	if (GetInput() == sides[2])
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

//private
int math::GetInput()
{
	int x; std::cin >> x;
	return x;
}