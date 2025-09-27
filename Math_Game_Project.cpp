#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

enum enQuestionsLevel { EasyLevel = 1, MidLevel = 2, HardLevel = 3, MixLevel = 4 };
enum enOperationType { Add = 1, Sub = 2, Mult = 3, Div = 4, MixOp = 5 };

struct stQuestion
{
    enQuestionsLevel Level;
    enOperationType OperationType;
    short RandomNumber1 = 0;
    short RandomNumber2 = 0;
    int CorrectAnswer = 0;
    int PlayerAnswer = 0;
    bool AnswerResult;
};

struct stQuiz
{
    stQuestion QuestionsList[100]; // each index has data of each exam's questions.
    short NumberOfQuestions = 0;
    enQuestionsLevel QuestionsLevel;
    enOperationType OperationType;
    short NumberOfRightAnswers = 0;
    short NumberOfWrongAnswers = 0;
    bool isPass;
};

short ReadHowManyQuestions()
{
    short NumberOfQuestions = 0;

    do
    {
        cout << "How many questions do you want to answer ? ";
        cin >> NumberOfQuestions;

    } while (NumberOfQuestions < 1 || NumberOfQuestions > 10);
    return NumberOfQuestions;
}

enQuestionsLevel ReadExamLevel()
{
    short ExamLevel = 0;

    do
    {
        cout << "\nSelect Level of Exam: |[1] Easy, [2] Mid, [3] Hard, [4] Mix| : ";
        cin >> ExamLevel;

    } while (ExamLevel < 1 || ExamLevel > 4);
    return (enQuestionsLevel)ExamLevel;
}

string GetExamLevelName(enQuestionsLevel Level)
{
    string arrLevels[4] = { "Easy" , "Mid" , "Hard" , "Mix" };
    return arrLevels[Level - 1];
}

enOperationType ReadExamOperationType()
{
    short ExamOperation = 0;

    do
    {
        cout << "\nSelect Operation of Exam: |[1] Add, [2] Sub, [3] Multiplication, [4] Division, [5] MixOperations| : ";
        cin >> ExamOperation;

    } while (ExamOperation < 1 || ExamOperation > 5);
    return (enOperationType)ExamOperation;
}

int RandomNumber(int From, int To)
{
    return rand() % (To - From + 1) + From;
}

/*
enQuestionsLevel GetRandomLevel()
{
    return (enQuestionsLevel)RandomNumber(1,3);
}
*/

enOperationType GetRandomOperationType()
{
    return (enOperationType)RandomNumber(1, 4);
}

string GetOperationTypeSymbol(enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return "+";

    case enOperationType::Sub:
        return "-";

    case enOperationType::Mult:
        return "*";

    case enOperationType::Div:
        return "/";

    default:
        return "Mix";
    }
}

int SimpleCalculater(short RandomNumber1, short RandomNumber2, enOperationType OpType)
{
    switch (OpType)
    {
    case enOperationType::Add:
        return RandomNumber1 + RandomNumber2;

    case enOperationType::Sub:
        return RandomNumber1 - RandomNumber2;

    case enOperationType::Mult:
        return RandomNumber1 * RandomNumber2;

    case enOperationType::Div:
        return (RandomNumber2 != 0) ? (RandomNumber1 / RandomNumber2) : 0;

    default:
        return RandomNumber1 + RandomNumber2;
    }
}

stQuestion GenerateQuestion(enQuestionsLevel QuestionLevel, enOperationType OpType)
{
    stQuestion Question;

    if (QuestionLevel == enQuestionsLevel::MixLevel)
        // QuestionLevel = GetRandomLevel();
        QuestionLevel = (enQuestionsLevel)RandomNumber(1, 3);

    if (OpType == enOperationType::MixOp)
        OpType = GetRandomOperationType();

    Question.OperationType = OpType;

    switch (QuestionLevel)
    {
    case enQuestionsLevel::EasyLevel:
        Question.RandomNumber1 = RandomNumber(1, 10);
        Question.RandomNumber2 = RandomNumber(1, 10);
        break;

    case enQuestionsLevel::MidLevel:
        Question.RandomNumber1 = RandomNumber(10, 50);
        Question.RandomNumber2 = RandomNumber(10, 50);
        break;

    case enQuestionsLevel::HardLevel:
        Question.RandomNumber1 = RandomNumber(50, 100);
        Question.RandomNumber2 = RandomNumber(50, 100);
        break;
    }

    Question.CorrectAnswer = SimpleCalculater(Question.RandomNumber1, Question.RandomNumber2, Question.OperationType);

    Question.Level = QuestionLevel;

    return Question;
}

void PrintTheQuestion(stQuiz& Quiz, short QuestionNumber)
{
    cout << "\n";
    cout << "Question [" << QuestionNumber + 1 << "/" << Quiz.NumberOfQuestions << "]\n\n";
    cout << Quiz.QuestionsList[QuestionNumber].RandomNumber1 << endl;
    cout << Quiz.QuestionsList[QuestionNumber].RandomNumber2 << " ";
    cout << GetOperationTypeSymbol(Quiz.QuestionsList[QuestionNumber].OperationType);
    cout << "\n__________" << endl;
}

int ReadQuestionAnswer()
{
    int PlayerAnswer = 0;
    cin >> PlayerAnswer;
    return PlayerAnswer;
}

void SetConsoleScreenColor(bool Right)
{
    if (Right)
        system("color 2F"); // Green for correct answers.
    else
    {
        system("color 4F"); // Red for incorrect answers.
        cout << "\a"; // Plays an alert sound.
    }
}

void CorrectTheQuestionAnswer(stQuiz& Quiz, short QuestionNumber)
{
    if (Quiz.QuestionsList[QuestionNumber].CorrectAnswer != Quiz.QuestionsList[QuestionNumber].PlayerAnswer)
    {
        Quiz.QuestionsList[QuestionNumber].AnswerResult = false;
        Quiz.NumberOfWrongAnswers++;
        cout << "Wrong Answer :( \n";
        cout << "The Right answer is: ";
        cout << Quiz.QuestionsList[QuestionNumber].CorrectAnswer; // from simple calculter
        cout << "\n";
    }
    else
    {
        Quiz.QuestionsList[QuestionNumber].AnswerResult = true;
        Quiz.NumberOfRightAnswers++;
        cout << "Right Answer (: \n";
    }

    cout << endl;
    SetConsoleScreenColor(Quiz.QuestionsList[QuestionNumber].AnswerResult);
}

void AskAndCorrectQuestionsListAnswers(stQuiz& Quiz)
{
    for (short QuestionNumber = 0; QuestionNumber < Quiz.NumberOfQuestions; QuestionNumber++)
    {
        PrintTheQuestion(Quiz, QuestionNumber);

        Quiz.QuestionsList[QuestionNumber].PlayerAnswer = ReadQuestionAnswer();

        CorrectTheQuestionAnswer(Quiz, QuestionNumber);
    }
    // until here the Exam is finish:
    Quiz.isPass = (Quiz.NumberOfRightAnswers >= Quiz.NumberOfWrongAnswers);
}

void GenerateQuizQuestions(stQuiz& Quiz)
{
    for (short QuestionNum = 0; QuestionNum < Quiz.NumberOfQuestions; QuestionNum++)
    {
        Quiz.QuestionsList[QuestionNum] = GenerateQuestion(Quiz.QuestionsLevel, Quiz.OperationType);
    }
}

string GetFinalQuizResultByText(bool Pass)
{
    if (Pass)
        return "Pass (: ";
    else
        return "Fail ): ";
}

void PrintQuizResults(stQuiz Quiz)
{
    cout << "\n";
    cout << "_______________________________\n\n";
    cout << "Final Result is " << GetFinalQuizResultByText(Quiz.isPass);
    cout << "\n_______________________________\n\n";
    cout << "Number Of Questions: " << Quiz.NumberOfQuestions << endl;
    cout << "Questions Level: " << GetExamLevelName(Quiz.QuestionsLevel) << endl;
    cout << "Questions Operation Type: " << GetOperationTypeSymbol(Quiz.OperationType) << endl;
    cout << "Number of Right Answers: " << Quiz.NumberOfRightAnswers << endl;
    cout << "Number of Wrong Answers: " << Quiz.NumberOfWrongAnswers << endl;
    cout << "_______________________________\n\n";
}

void PlayMathGame()
{
    stQuiz Quiz;

    Quiz.NumberOfQuestions = ReadHowManyQuestions();
    Quiz.QuestionsLevel = ReadExamLevel();
    Quiz.OperationType = ReadExamOperationType();

    GenerateQuizQuestions(Quiz);
    AskAndCorrectQuestionsListAnswers(Quiz);
    PrintQuizResults(Quiz);
}

void ResetScreen()
{
    system("cls"); // clear screen
    system("color 0F"); // back to black color of screen
}

void StartGame()
{
    char PlayAgain = ' ';
    do
    {
        ResetScreen();
        PlayMathGame();
        cout << "\nDo you want to play again? Y/N: ";
        cin >> PlayAgain;

    } while (PlayAgain == 'Y' || PlayAgain == 'y');
}

int main()
{
    srand((unsigned)time(NULL));

    StartGame();

    return 0;
}