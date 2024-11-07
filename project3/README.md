# Math Quiz Game

This is a console-based math quiz game where players can choose the number of questions, difficulty level, and type of mathematical operations. The game generates random math problems based on the selected settings, evaluates the answers, and displays the final results.

## Features

- Select the **number of questions** for each quiz.
- Choose a **difficulty level**: 
  - Easy
  - Medium
  - Hard
  - Mixed (randomly chooses a difficulty for each question)
- Choose an **operation type**:
  - Addition
  - Subtraction
  - Multiplication
  - Division
  - Mixed (randomly chooses an operation for each question)
- **Automatic scoring** for correct and incorrect answers.
- **Pass/fail results** based on the number of correct answers.
- Option to **play again** after completing a quiz.

## How to Play

1. Run the program.
2. Enter the number of questions you want to answer.
3. Select the difficulty level.
4. Select the type of operation.
5. Answer the generated math questions.
6. View the results at the end of the game.

## Program Structure

The program contains the following key structures and functions:

### Enums

- `QuestionLevels`: Defines difficulty levels (`easy`, `medium`, `hard`, `mixedLevel`).
- `OperationTypes`: Defines the type of operation (`addition`, `subtraction`, `multiplication`, `division`, `mixedOperation`).

### Structs

- `Question`: Represents a single math question with fields for numbers, level, operation type, correct answer, and user answer.
- `Exam`: Represents an entire quiz session, including a list of questions, number of correct/incorrect answers, and pass status.

### Functions


-
-  `displayOperationSymbol()`: Returns the symbol for the selected operation.
- `selectOperationType()`: Prompts the user to select the operation type.
- `selectQuestionLevel()`: Prompts the user to select the difficulty level.
- `getRandomNumber()`: Generates a random number within specified limits.
- `setTerminalColor()`: Sets terminal color based on the correctness of the answer.
- `createQuestion()`: Creates a math question based on selected difficulty and operation.
- `createExam()`: Initializes an exam with a series of questions.
- `askAndListQuestions()`: Displays questions, takes answers, and evaluates them.
- `displayResults()`: Shows a summary of the quiz results.

## Example Code Snippet

Here's a quick example of how the questions are created and answered:

```cpp
Exam exam;
exam.numberOfQuestions = getNumberOfQuestions();
exam.questionLevel = selectQuestionLevel();
exam.operationType = selectOperationType();
createExam(exam);
askAndListQuestions(exam);
displayResults(exam);
