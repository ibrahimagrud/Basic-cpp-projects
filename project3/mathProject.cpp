#include<iostream>
#include<cstdlib>
#include<string>
#include<time.h>
using namespace std;

enum QuestionLevels { easy = 1, medium = 2, hard = 3, mixedLevel = 4 };
enum OperationTypes { addition = 1, subtraction = 2, multiplication = 3, division = 4, mixedOperation = 5 };

string displayOperationSymbol(OperationTypes selectedOperation) {
    switch (selectedOperation) {
        case addition: return "+"; break;
        case subtraction: return "-"; break;
        case multiplication: return "x"; break;
        case division: return "/"; break;
        default: return "\nError in displayOperationSymbol\n"; break;
    }
}

OperationTypes selectOperationType() {
    short choice;
    do {
        cout << "Choose operation type: addition[1], subtraction[2], multiplication[3], division[4], mix[5]\n";
        cin >> choice;
    } while (choice < 1 || choice > 5);
    return (OperationTypes)choice;
}

QuestionLevels selectQuestionLevel() {
    short choice;
    do {
        cout << "Choose question level: easy[1], medium[2], hard[3], mix[4]\n";
        cin >> choice;
    } while (choice < 1 || choice > 4);
    return (QuestionLevels)choice;
}

int getRandomNumber(int lowerLimit, int upperLimit) {
    return rand() % ((upperLimit - lowerLimit) + 1) + lowerLimit;
}

void setTerminalColor(bool correct) {
    if (correct) {
        system("color 2F");
    } else {
        system("color 4F");
        cout << "\a";
    }
}

int getNumberOfQuestions() {
    int numberOfQuestions = 0;
    cout << "How many questions for the test?\n";
    cin >> numberOfQuestions;
    return numberOfQuestions;
}

string getOperationName(OperationTypes operationType) {
    string operationNames[5] = { "addition", "subtraction", "multiplication", "division", "mixed" };
    return operationNames[operationType - 1];
}

string getQuestionLevelName(QuestionLevels questionLevel) {
    string levelNames[4] = { "easy", "medium", "hard", "mixed" };
    return levelNames[questionLevel - 1];
}

struct Question {
    int num1;
    int num2;
    QuestionLevels level;
    OperationTypes operationType;
    int correctAnswer;
    int userAnswer;
    bool isCorrect = false;
};

struct Exam {
    Question questions[100];
    short numberOfQuestions;
    int correctAnswerCount = 0;
    int incorrectAnswerCount = 0;
    QuestionLevels questionLevel;
    OperationTypes operationType;
    bool passed = false;
};

int calculate(int num1, int num2, OperationTypes operation) {
    switch (operation) {
        case addition: return (num1 + num2);
        case subtraction: return (num1 - num2);
        case division: return (num1 / num2);
        case multiplication: return (num1 * num2);
        default: return 999;
    }
}

QuestionLevels getRandomQuestionLevel() {
    return (QuestionLevels)getRandomNumber(1, 3);
}

Question createQuestion(QuestionLevels level, OperationTypes operationType) {
    Question newQuestion;
    if (level == mixedLevel) {
        level = (QuestionLevels)getRandomNumber(1, 3);
    }
    if (operationType == mixedOperation) {
        operationType = (OperationTypes)getRandomNumber(1, 4);
    }
    newQuestion.operationType = operationType;

    switch (level) {
        case easy:
            newQuestion.num1 = getRandomNumber(1, 10);
            newQuestion.num2 = getRandomNumber(1, 10);
            newQuestion.level = level;
            newQuestion.correctAnswer = calculate(newQuestion.num1, newQuestion.num2, newQuestion.operationType);
            return newQuestion;

        case medium:
            newQuestion.num1 = getRandomNumber(11, 50);
            newQuestion.num2 = getRandomNumber(11, 50);
            newQuestion.level = level;
            newQuestion.correctAnswer = calculate(newQuestion.num1, newQuestion.num2, newQuestion.operationType);
            return newQuestion;

        case hard:
            newQuestion.num1 = getRandomNumber(51, 99);
            newQuestion.num2 = getRandomNumber(51, 99);
            newQuestion.level = level;
            newQuestion.correctAnswer = calculate(newQuestion.num1, newQuestion.num2, newQuestion.operationType);
            return newQuestion;
    }
}

void createExam(Exam& exam) {
    for (int i = 0; i < exam.numberOfQuestions; i++) {
        exam.questions[i] = createQuestion(exam.questionLevel, exam.operationType);
    }
}

int getAnswerFromUser() {
    int answer = 0;
    cin >> answer;
    return answer;
}

void displayQuestion(Exam& exam, short questionIndex) {
    cout << "\nQuestion [" << questionIndex + 1 << "/" << exam.numberOfQuestions << "]\n\n";
    cout << exam.questions[questionIndex].num1 << endl;
    cout << exam.questions[questionIndex].num2 << " ";
    cout << displayOperationSymbol(exam.questions[questionIndex].operationType);
    cout << "\n______________" << endl;
}

void compareAnswer(Exam& exam, short questionIndex) {
    if (exam.questions[questionIndex].userAnswer != exam.questions[questionIndex].correctAnswer) {
        exam.questions[questionIndex].isCorrect = false;
        exam.incorrectAnswerCount++;
        cout << "Incorrect answer\n";
        cout << "Correct answer: " << exam.questions[questionIndex].correctAnswer << "\n";
    } else {
        exam.questions[questionIndex].isCorrect = true;
        exam.correctAnswerCount++;
        cout << "Correct answer :-)\n";
    }
    cout << endl;
    setTerminalColor(exam.questions[questionIndex].isCorrect);
}

void askAndListQuestions(Exam& exam) {
    for (short i = 0; i < exam.numberOfQuestions; i++) {
        displayQuestion(exam, i);
        exam.questions[i].userAnswer = getAnswerFromUser();
        compareAnswer(exam, i);
    }
    exam.passed = (exam.correctAnswerCount >= exam.incorrectAnswerCount);
}

string getPassStatus(bool passed) {
    return passed ? "Passed :-)" : "Failed :-(";
}

void displayResults(Exam exam) {
    cout << "\n__________________________\n\n";
    cout << getPassStatus(exam.passed) << endl;
    cout << "Summary:\n";
    cout << "Number of questions: " << exam.numberOfQuestions << endl;
    cout << "Question level: " << getQuestionLevelName(exam.questionLevel) << endl;
    cout << "Operation type: " << getOperationName(exam.operationType) << endl;
    cout << "Correct answers: " << exam.correctAnswerCount << endl;
    cout << "Incorrect answers: " << exam.incorrectAnswerCount << endl;
    cout << "___________________________\n\n";
}

void gameLoop() {
    Exam exam;
    exam.numberOfQuestions = getNumberOfQuestions();
    exam.questionLevel = selectQuestionLevel();
    exam.operationType = selectOperationType();
    createExam(exam);
    askAndListQuestions(exam);
    displayResults(exam);
}

void resetTerminal() {
    system("cls");
    system("color 0F");
}

void start() {
    char playAgain = 'y';
    do {
        resetTerminal();
        gameLoop();
        cout << "Play again? Y/N\n";
        cin >> playAgain;
    } while (playAgain == 'y' || playAgain == 'Y');
}

int main() {
    srand((unsigned)time(NULL));
    start();
    return 0;
}
