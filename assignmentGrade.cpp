/*
    Aramis M. Figueroa

    assignmentGrade.cpp

    Menu-driven interface program that allows the user to:
        1. Calculate assignment grade for a student.
        2. Display assignment grades.
        3. Quit
    
    Input:  User's choice
            Student name, assignment grade, assignment max points


    Process:    1. Display menu & prompt user for choice
                2. Drive menu options
                        Case 1 - Calculate grade
                            Prompt user for student name, points
                            received (0-100) and maximum points (0-100)
                            Calculate assignment grade as a percentage
                                assignmentPercent = ceil(pointsReceived / maxPoints * 100);
                            Determine student standing 
                            (excellent / well done / good / need improvement / fail)
                            Display result
                            Write student record to "assignment.txt"
                                open file in appending mode (ios::app)
                                write record to file
                                close file
                        Case 2 - Display file
                            Open file for input
                            While there are records
                                read student records
                                Display the record
                            Close file
                        Case 3 - Quit

    Output: File containing the assignment grades of a series of students

*/

// Header Files
#include<iostream>
#include<string>
#include<iomanip>
#include<cmath>
#include<fstream>
using namespace std;

int main(){

    // Constants & Variables
    const int CALCULATE = 1, DISPLAY = 2, QUIT = 3;
    int choice, pointsReceived, maxPoints;
    string studentName, studentStanding;
    double assignmentPercent, total;
    fstream myFile;

    // Intro
    cout << "\nAssignment Grade Calculator ...";

    // Menu
    do{
        // Display menu & Prompt user for choice
        cout << "\nChoose one of the following options" << endl
            << "\t1. Calculate assignment grade for a student." << endl
            << "\t2. Display assignment grades." << endl
            << "\t3. Quit" << endl
            << "Option: ";
        cin >> choice;


        // Drive menu options
        switch(choice){

            case CALCULATE:
               
                // Prompt user for student name
                cin.ignore();
                cout << "Enter student name: ";
                getline(cin, studentName);
             
                // Prompt user for points received (0-100)
                cout << "\t\nPoints received: ";
                cin >> pointsReceived;
            

                // Prompt user for maximum points (0-100)
                cout << "\t\nMaximum points: ";
                cin >> maxPoints;
                
                
                // Calculate assignment grade as a percentage
                assignmentPercent = static_cast<double>(pointsReceived) / static_cast<double>(maxPoints);
                total = static_cast<int>(ceil(assignmentPercent * 100.0));
                
                // Determine student standing 
                if (total >= 90)
                    studentStanding = "Excellent";
                else if (total < 90 && total >= 80)
                    studentStanding = "Well Done";
                else if (total < 80 && total >= 70)
                    studentStanding = "Good";
                else if (total < 70 && total >= 60)
                    studentStanding = "Need Improvement";
                else 
                    studentStanding = "Fail";

                // Display result
                cout << "\nAssignment Calculator" << "\n\n"
                    << "----------------------------------------------" << "\n\n"
                    << left << setw(15) << studentName << right << setw(10) << total << "%" << right << setw(20) << studentStanding << endl; 
                
                // open file in appending mode (ios::app)
                myFile.open("assignment.txt", ios::app);

                if (myFile){
                    
                    // write record to file
                    myFile << left << setw(15) << studentName << right << setw(10) << total << "%" << right << setw(20) << studentStanding << endl;

                }

                // close file
                myFile.close();
                cout << "\nStudent info successfully added to assignment.txt!" << endl;
            break;

            case DISPLAY:
                // Open file for input
                myFile.open("assignment.txt", ios::in);
                if (myFile){
              

                    // while there are records
                    // read student record
                    // display record
                    cout << "\nList of student assignment grades..." << endl;
                    string studentRecord;
                    while(getline(myFile, studentRecord)){
                        cout << studentRecord << endl;

                    }
                    // close file
                    myFile.close();

                }
                else{
                    cout << "\nFatal error...Could not open assignment.txt." << endl;
                }
                break;

            case QUIT:
                cout << "\nGood bye ..." << endl;
                break;
            default:
                cout << "\nError...Invalid option. Try again." << endl;
        }
    }while (choice != QUIT);

    return 0;
}