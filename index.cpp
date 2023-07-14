#include<iostream>
#include<cstdlib>
using namespace std;
enum enQuestionsLevel { EasyLevel = 1, MedLevel = 2, HardLevel = 3, Mix = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };
short ReadHowManyQuestions()
{
	short NumberOfQuestions = 1;
	do
	{
		cout << "How Many Questions do you want to answer ? \n";
		cin >> NumberOfQuestions;
	} while (NumberOfQuestions < 1 || NumberOfQuestions >10);
	return NumberOfQuestions;
}
void RsetScreen()
{
	system("cls"); // clear screen
	system("color 0F"); // color Black
}
int RandomNumber(int From, int To)
{
	int RandomNumber = rand() % (To - From + 1) + From;
	return  RandomNumber;
}
int SimpleCalculator(int Number1, int Number2, enOperationType  OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return Number1 + Number2;
	case enOperationType::Sub:
		return Number1 - Number2;
	case enOperationType::Mult:
		return Number1 * Number2;
	case enOperationType::Div:
		return Number1 / Number2;
	default:
		return Number1 + Number2;
	}
}
//an enum (short for "enumeration") is a user-defined data type that allows you to define
//a set of named integer constants.

// declare enum data type  
enQuestionsLevel GetQuestionsLevel()
{
	short QuestionLevel = 0;
	do
	{
		cout << "Enter Questions Level [1] Easy, [2] Med, [3]Hard, [4] Mix ? ";
		cin >> QuestionLevel;
	} while (QuestionLevel < 1 || QuestionLevel >4);

	return  (enQuestionsLevel)QuestionLevel;
}
enOperationType ReadOpType()
{
	short OpType;
	do
	{
		cout << "Enter Operation Type [1] Add, [2] Sub, [3] Mul,[4] Div, [5] Mix ? ";
		cin >> OpType;
	} while (OpType < 1 || OpType >5);
	return (enOperationType)OpType;
}
//a struct is a user-defined data type that groups together related data under a single name.
//An array of struct is simply an array where each element is a struct.
//To define an array of struct, you first need to define the struct itself, and then you can declare an array of that struct type.
//we define a struct called "stQuestion" with "7" members
//We then declare an array of "stQuestion" structs with "100" elements,
struct stQuestion
{
	int Number1 = 0;
	int Number2 = 0;
	enOperationType OperationType; //same as => int x;
	enQuestionsLevel QuestionLevel;//same as => int y;
	int CorrectAnswer = 0;
	int PlayerAnswer = 0;
	bool AnswerResult = false;
};

struct stQuizz
{
	stQuestion QuestionList[100]; //An array of struct
	short NumberOfQuestions;
	enQuestionsLevel QuestionsLevel;
	enOperationType OpType;
	short NumberOfWrongAnswers = 0;
	short NumberOfRightAnswers = 0;
	bool isPass = false;
};

stQuestion GenerateQuestion(enQuestionsLevel QuestionsLevel, enOperationType OperationType)
{
	stQuestion Question;
	if (QuestionsLevel == enQuestionsLevel::Mix)
	{
		QuestionsLevel = (enQuestionsLevel)RandomNumber(1, 3);
	}
	if (OperationType == enOperationType::MixOp)
	{
		OperationType = (enOperationType)RandomNumber(1, 4);
	}
	Question.OperationType = OperationType;

	switch (QuestionsLevel)
	{
	case EasyLevel:
		Question.Number1 = RandomNumber(1, 10);
		Question.Number2 = RandomNumber(1, 10);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	case MedLevel:
		Question.Number1 = RandomNumber(10, 100);
		Question.Number2 = RandomNumber(10, 100);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	case HardLevel:
		Question.Number1 = RandomNumber(100, 1000);
		Question.Number2 = RandomNumber(100, 1000);
		Question.CorrectAnswer = SimpleCalculator(Question.Number1, Question.Number2, Question.OperationType);
		Question.QuestionLevel = QuestionsLevel;
		return Question;
	}
	return Question;

}
string GetOpTypeSymbol(enOperationType OpType)
{
	switch (OpType)
	{
	case enOperationType::Add:
		return "+";
	case enOperationType::Sub:
		return "-";
	case enOperationType::Mult:
		return "x";
	case enOperationType::Div:
		return "/";
	default:
		return "Mix";
	}
}
void PrintTheQuestion(stQuizz& Quizz, short QuestionNumber)
{
	cout << "\n";
	cout << "Question [" << QuestionNumber + 1 << "/" << Quizz.NumberOfQuestions << "] \n\n";
	cout << Quizz.QuestionList[QuestionNumber].Number1 << endl;
	cout << Quizz.QuestionList[QuestionNumber].Number2 << " ";
	cout << GetOpTypeSymbol(Quizz.QuestionList[QuestionNumber].OperationType);
	cout << "\n_________" << endl;
}
int ReadQuestionAnswer()
{
	int answer;
	cin >> answer;
	return answer;
}
void SetScreenColor(bool Right)
{
	if (Right)
		system("color 2F"); //turn screen to Green
	else
	{
		system("color 4F"); //turn screen to Red
		cout << "\a";
	}
}
void CorrectTheQuestionAnswer(stQuizz& Quizz, short QuestionNumber)
{
	if (Quizz.QuestionList[QuestionNumber].PlayerAnswer !=
		Quizz.QuestionList[QuestionNumber].CorrectAnswer)
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = false;
		Quizz.NumberOfWrongAnswers++;
		cout << "Worng Answer :-( \n";
		cout << "The right answer is: ";
		cout << Quizz.QuestionList[QuestionNumber].CorrectAnswer;
		cout << "\n";
	}
	else
	{
		Quizz.QuestionList[QuestionNumber].AnswerResult = true;
		Quizz.NumberOfRightAnswers++;
		cout << "Right Answer :-) \n";
	}
	cout << endl;
	SetScreenColor(Quizz.QuestionList[QuestionNumber].AnswerResult);
}
void AskAndCorrectQuestionListAnswers(stQuizz& Quizz)
{
	for (short QuestionNumber = 0; QuestionNumber < Quizz.NumberOfQuestions; QuestionNumber++)
	{
		PrintTheQuestion(Quizz, QuestionNumber);
		Quizz.QuestionList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();
		CorrectTheQuestionAnswer(Quizz, QuestionNumber);
	}
	Quizz.isPass = (Quizz.NumberOfRightAnswers >= Quizz.NumberOfWrongAnswers);
}
void GenerateQuizzQuestions(stQuizz& Quizz)
{
	for (short Question = 0; Question < Quizz.NumberOfQuestions; Question++)
	{
		Quizz.QuestionList[Question] = GenerateQuestion(Quizz.QuestionsLevel, Quizz.OpType);
	}
}
string GetFinalResultsText(bool Pass)
{
	if (Pass)
		return "PASS :-)";
	else
		return "Fail :-(";
}
string GetQuestionLevelText(enQuestionsLevel QuestionLevel)
{
	string arrQuestionLevelText[4] = { "Easy","Med","Hard","Mix"
	};
	return arrQuestionLevelText[QuestionLevel - 1];
}
void PrintQuizzResults(stQuizz Quizz)
{
	cout << "\n";
	cout << "______________________________\n\n";
	cout << " Final Resutls is " << GetFinalResultsText(Quizz.isPass);
	cout << "\n______________________________\n\n";
	cout << "Number of Questions: " << Quizz.NumberOfQuestions << endl;
	cout << "Questions Level : " << GetQuestionLevelText(Quizz.QuestionsLevel) << endl;
	cout << "OpType : " << GetOpTypeSymbol(Quizz.OpType) << endl;
	cout << "Number of Right Answers: " << Quizz.NumberOfRightAnswers << endl;
	cout << "Number of Wrong Answers: " << Quizz.NumberOfWrongAnswers << endl;
	cout << "______________________________\n";
}

void PlayMathGame()
{
	stQuizz Quizz;
	Quizz.NumberOfQuestions = ReadHowManyQuestions();
	Quizz.QuestionsLevel = GetQuestionsLevel();
	Quizz.OpType = ReadOpType();

	GenerateQuizzQuestions(Quizz);

	AskAndCorrectQuestionListAnswers(Quizz);

	PrintQuizzResults(Quizz);
}

void StartGame()
{
	char PlayAgain = 'Y';
	do
	{
		RsetScreen();

		PlayMathGame();

		cout << "Do You want to play again? Y/N ?";
		cin >> PlayAgain;

	} while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
	//Seeds the random number generator in C++, called only once
	srand((unsigned)time(NULL));


	cout << "Welcome to my small project \n";
	cout << "This project done by the help of Mohamed Abo-Hadhod";

	StartGame();
	int a = 0;

	return 0;
}