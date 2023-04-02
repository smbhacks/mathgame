#include "math.h"
#include "log.h"
#include <random>

//public
void math::GetRandomNumbers()
{
	for (int i = 2; i > -1; i--)
	{
		numbers[i] = rand() % 9 + 1;
		signs[i] = rand() % 3;
	}
}

void math::OutputQuestion(Log& log)
{
	std::string question = "a x b y c = ";
	question[question.find('x')] = char_signs[signs[0]];
	question[question.find('y')] = char_signs[signs[1]];
	question[question.find('a')] = char_numbers[numbers[0]];
	question[question.find('b')] = char_numbers[numbers[1]];
	question[question.find('c')] = char_numbers[numbers[2]];
	const char* c = question.c_str();
	log.LogToConsole(c, log.LOGMESSAGE, false);
}

bool math::GetAnswer(Log& log)
{
	if (GetInput()==CalculateAnswer())
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

int math::CalculateAnswer()
{
	if (signs[1] >= MULTIPLICATION_SIGN)
	{
		numbers[1] *= numbers[2];
		numbers[2] = 1;
	}
	for (int i = 0; i < 2; i++)
		switch (signs[i])
		{
		case ADDITION_SIGN:
			numbers[i + 1] += numbers[i];
			break;
		case SUBSTRACTION_SIGN:
			numbers[i + 1] = numbers[i] - numbers[i + 1];
			break;
		case MULTIPLICATION_SIGN:
			numbers[i + 1] *= numbers[i];
			break;
		}
	return numbers[2];
}