/*
    Aramis M. Figueroa

    personality.cpp

    This is a program to perform a personality quiz that asks a user
    10 questions to find out their animal based personality.

    Input:  Number corresponding to answer for given question in quiz.
            Y || y or N || n to restart quiz or not

    Process:    1. User will be prompted to answer 10 questions that are read from "quizQuestions.txt"
                2. After each question is displayed, 4 answers will be displayed below it, corresponding to answers
                    in "quizAnswers.txt" that are stored in a 2D array.
                    - Each answer will add to an animal accumulator for final result.
                3. Highest scored animal personality type will be displayed to user along with its description.
                4. Prompt user if he or she would like to take the quiz again or not.

    Output: User's personality type and its description, based on their selected answers
*/

// Header Files
#include <iostream>
#include <fstream>
#include <string>
#include <windows.h>
using namespace std;

// Constants
const int NUM_QUESTIONS = 10;
const int NUM_ANSWERS = 4;

// Function prototypes
void loadAnswers(char answers[][NUM_ANSWERS]);
void printQuestion(int questionNum, char answers[][NUM_ANSWERS]);
int getResponse();
void updateAccumulator(int response, int questionNum, char answers[][NUM_ANSWERS], int& lionCount, int& otterCount, int& beaverCount, int& retrieverCount);
char getPersonality(int lionCount, int otterCount, int beaverCount, int retrieverCount);
void printResult(char personality);

// wstring CurrentWorkingDirectory() {
//     wchar_t buffer[MAX_PATH];
    
//     if (_wgetcwd(buffer, sizeof(buffer)) == NULL) {
//         return L"Error retrieving current working directory";
//     }

//     return wstring(buffer);
// }
int main() {
    // Declare and initialize variables
    char answers[NUM_QUESTIONS][NUM_ANSWERS];
    char response;
    int lionCount, otterCount, beaverCount, retrieverCount;
    char personality;
    int questionNum;

    // wcout << L"My current working directory is: " << CurrentWorkingDirectory() << endl;
    // Load answers from file
    loadAnswers(answers);

    // print out answers 2d array for testing
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        for (int j = 0; j < NUM_ANSWERS; j++) {
            cout << answers[i][j] << " ";
        }
        cout << endl;
    }


    // Start quiz loop
    do {
        // Initialize accumulators
        lionCount = 0;
        otterCount = 0;
        beaverCount = 0;
        retrieverCount = 0;

        // Print welcome message
        cout << "Let's Find the Animal in You ..." << "\n\n"
            << "Please answer the following questions: " << "\n\n";

        // Loop through questions and update accumulators
        for (questionNum = 1; questionNum <= NUM_QUESTIONS; questionNum++) {
            // Print question and answers
            printQuestion(questionNum, answers);

            // Get response from user and update accumulators
            response = getResponse();
            updateAccumulator(response, questionNum, answers, lionCount, otterCount, beaverCount, retrieverCount);

            cout << endl;
        }

        // Determine personality based on accumulator values
        personality = getPersonality(lionCount, otterCount, beaverCount, retrieverCount);

        // Print quiz result
        printResult(personality);

        // Ask user if they want to take the quiz again
        cout << "Would you like to take the quiz again (y/n)?  ";
        cin >> response;

        // Clear cin buffer
        cin.ignore();

        cout << endl;

    } while (response == 'y' || response == 'Y');

    cout << "Thank you for taking the Personality Quiz!" << endl;

    return 0;
}

// Function to load answers into 2D array for user to select
void loadAnswers(char answers[][NUM_ANSWERS]) {

    ifstream inputFile;
    string filename = "quizAnswers.txt";

    inputFile.open(filename);

    // Check if file opened successfully
    if (!inputFile) {
        cout << "Error opening " << filename << " file." << endl;
        exit(1);
    }

    // Read answers from file into 2D array
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        for (int j = 0; j < NUM_ANSWERS; j++) {
            inputFile >> answers[i][j];
        }
    }

    // Close file
    inputFile.close();
}

void printQuestion(int questionNum, char answers[][NUM_ANSWERS]) {

    ifstream inputFile;
    string filename = "quizQuestions.txt";
    string question;
    int answerNum = 1;

    inputFile.open(filename);

    // Check if file opened successfully
    if (!inputFile) {
        cout << "Error opening " << filename << " file." << endl;
        exit(1);
    }

    // Find question and answers in file
    for (int i = 1; i <= questionNum; i++) {
        getline(inputFile, question);
        if (i == questionNum) {

            // Print question
            cout << i << ". " << question << endl << endl;
            
            // Print answer choices
            for (int j = 0; j < NUM_ANSWERS; j++) {
                getline(inputFile, question);
                cout << answerNum << ") " << question << endl;
                //answers[i-1][j] = question[0];
                answerNum++;
            }
        }
        else {
            // skip over the four possible answers for this question
            for (int j = 0; j < NUM_ANSWERS; j++) {
                getline(inputFile, question);
            }
            // skip the question itself
            getline(inputFile, question);
        }
    }

    // Close file
    inputFile.close();
}


// Function to get response of user for answer selection
int getResponse(){

    int response;
    
    cout << "Answer: ";
    cin >> response;

// Validate response
    while (response < 1 || response > 4) {
        cout << "Invalid response. Please enter numbers 1-4 ";
        cin >> response;
    }

    return response;
}

// Function to add to the count of animal personality type
void updateAccumulator(int response, int questionNum, char answers[][NUM_ANSWERS], int& lionCount, int& otterCount, int& beaverCount, int& retrieverCount) {
    
   
    // // print out answers 2d array for testing
    for (int i = 0; i < NUM_QUESTIONS; i++) {
        for (int j = 0; j < NUM_ANSWERS; j++) {
            cout << answers[i][j] << " ";
        }
        cout << endl;
    }
    cout << "This is response - " << response << endl;
    cout << "This is questionNum - " << questionNum << endl;
    cout << "This is answers[questionNum-1][response] during updateAccumulator - " << answers[questionNum-1][response -1] << endl;
    if (answers[questionNum-1][response-1] == 'L' ) {
                lionCount++;
    }
    else if (answers[questionNum-1][response-1] == 'O' ) {
                otterCount++;
    }
    else if (answers[questionNum-1][response-1] == 'B' ) {
                beaverCount++;
    }
    else if (answers[questionNum-1][response-1] == 'G' ) {
                retrieverCount++;
    }
 
                                      
}

// Function to display personality type based on which animal
// had the most value
char getPersonality(int lionCount, int otterCount, int beaverCount, int retrieverCount) {

    char personality;

    // Determine personality based on accumulator values
    if (lionCount > otterCount && lionCount > beaverCount && lionCount > retrieverCount) {

        personality = 'L';
    }
    else if (otterCount > lionCount && otterCount > beaverCount && otterCount > retrieverCount) {

        personality = 'O';
    }
    else if (beaverCount > lionCount && beaverCount > otterCount && beaverCount > retrieverCount) {

        personality = 'B';
    }
    else if (beaverCount == otterCount){

        personality = 'B';
    }
    else {
        personality = 'R';
    }

    return personality;
}

// Function to print the result of personality description based on user choices
void printResult(char personality) {
    switch (personality) {
            
            case 'L':

                cout << "Your are a Lion!" << endl 
                    << " Lions love to lead!\nIf you are a lion personality you like to stick up for yourself and your ideas, and often people want to follow you."
                    << endl; 

                break;

            case 'O':

                cout << "You are an Otter!" << endl
                    << "Otters love to have fun!\n They bring joy and often mischief into the lives of the people around them."
                    << endl;

                break;

            case 'B':

                cout << "You are a Beaver!" << endl
                    << "Beavers get things done!\n Beavers work hard at everything they do and persist until they achieve their goals."
                    << endl;

                break;

            case 'R':

                cout << "You are a Golden Retriever!" << endl
                    << "Golden Retrievers love people!\n They are the peacemakers who just want people to get on with each other."
                    << endl;

                break;

            default:
                break;
    }
}