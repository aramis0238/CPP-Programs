/*
    Aramis M. Figueroa

    paintEstimator.cpp

    Based on the price of the paint per gallon, number of rooms to be painted, and square feet of wall speace in each room 
    this will be a program to create a report showing: The number of gallons of paint required, cost of the paint,
    hours of labor required, labor charges and the total cost of the paint job. 

    Input:  Price per gallon of paint - pricePaint, 
            number of rooms to be painted - rooms, 
            square feet of wall space in each room - wallSpace.

    Process:    Prompt user for the following:

                    1. The price of gallon of paint using getPricePerGallon();
                        - Prompt user for price of gallons, stored as double pricePaint;
                            - if user enters 0 or less, re-prompt for correct input
                            - if input is correct (>=0), then continue to next prompt

                    2. Number of rooms to be painted using getRooms();
                        - Prompt user for number of rooms, stored as int rooms;
                            - If rooms < 1 then loop until 1 or greater amount of rooms is entered
                            - If rooms >= 1, continue to next prompt

                    3. Square feet of wall space using calcWallSpace();
                        - Prompt user for square feet of wall space for as many rooms as entered, stored as wallSpace;
                            - If wallSpace < 25, re-prompt for correct input (>=25)
                            - If wallSpace >= 25, prompt for next room in range of rooms.
                        - Add wallSpace to squareFeet - squareFeet += wallSpace;

                Calculate company's charges of paint (per 115 sqft, one gal of paint) and labor ($25 per hour, 8 hours per gal of paint) using the following:
                    - calcPaint(); 
                        gallons = squareFeet / squareFootPerGallon + 1;
                        cost = gallons * pricePaint;
                    - calcLabor(); 
                        hours = squareFeet * hoursPerSquareFeet;
                        cost = hours * 25.00;
                    - Add paint cost and labor cost for total
                        totalCost = paintCost + laborCost;

                Display Paint Job estimate showing
                    Gallons of paint - gallons
                    Cost of paint - paintCost
                    Hours of labor - laborHours
                    Cost of labor - laborCost
                    Total cost - totalCost

    Output: The number of gallons of paint required
            The cost of the paint
            The hours of labor required
            The labor charges
            The total cost of the paint job

*/

// Header files
#include<iostream>
#include<iomanip>
using namespace std;

// Function Prototypes
double getPricePerGallon();
int getRooms();
int calcWallSpace(int rooms);
void calcPaint(int squareFeet, double pricePaint, int& gallons, double& cost);
void calcLabor(int squareFeet, double& hours, double& cost);


// Prompt user for price of gallons
double getPricePerGallon(){

    double pricePaint;
    
    cout << "Price per gallon of paint: $";
    cin >> pricePaint;
    
    while (pricePaint < 0){

        cout << "Error ... Price per gallon must be greater than 0! Try again." << endl;

        cout << "Price per gallon of paint: $";
        cin >> pricePaint;
    }
    return pricePaint;

}

// Prompt user for number of rooms to be painted
int getRooms(){

    int rooms;

    cout << "\nNumber of rooms to be painted: ";
    cin >> rooms;

    while (rooms < 1){
        
        cout << "Error ... Number of rooms must be 1 or higher! Try again." << endl;

        cout << "Number of rooms to be painted: ";
        cin >> rooms;
    }
    return rooms;

}

// Prompt user for square feet of wall space
int calcWallSpace(int rooms){
    
    double squareFeet = 0, wallSpace;

    cout << "\nEnter square feet of wall space:" << endl;

    for(int x = 1; x <= rooms; x++){
        
        cout << "Room number " << x << ": ";
        cin >> wallSpace;

        while (wallSpace < 25){

            cout << "Error ... Square feet of wall space must be at least 25 sqrft! Try again." << endl;

            cout << "Room " << x << ": ";
            cin >> wallSpace;
        }
        squareFeet += wallSpace;
    }
    return squareFeet;
}

// Calculate company's charges of paint (per 115 sqft, one gal of paint)
void calcPaint(int squareFeet, double pricePaint, int& gallons, double& cost){
    const double squareFootPerGallon = 115.0;
    gallons = squareFeet / squareFootPerGallon + 1;
    cost = gallons * pricePaint;
}

// Calculate company's charges of labor ($25 per hour, 8 hours per gal of paint)
void calcLabor(double squareFeet, double& hours, double& cost){
    const double hoursPerSquareFeet = 8.0 / 115.0;
    hours = squareFeet * hoursPerSquareFeet;
    cost = hours * 25.00;
}

// Display Paint Job estimate 
int main(){

    

    // Intro
    cout << "Paint Job Estimator ... " << "\n\n";
    
    // Variables and function calls
    double price = getPricePerGallon();
    int rooms = getRooms();
    double sqrFeet = calcWallSpace(rooms);
    int gallons;
    double paintCost, laborHours, laborCost, totalCost;
    calcPaint(sqrFeet, price, gallons, paintCost);
    calcLabor(sqrFeet, laborHours, laborCost);
    totalCost = paintCost + laborCost;

    // Output
    cout << "\n-------PAINT JOB ESTIMATE-------\n\n";
    cout << "-------PAINT COSTS--------------\n\n";
    cout << "Gallons of Paint:\t" << gallons << " gal(s)" << endl;
    cout << "Total Cost of Paint:\t$ " << fixed << setprecision(2) << showpoint << paintCost << endl << endl;
    cout << "-------LABOR COSTS---------------\n\n";
    cout << "Hours of Labor:\t\t" << fixed << setprecision(2) << showpoint << laborHours << " hrs" << endl;
    cout << "Cost of Labor:\t\t$ " << fixed << setprecision(2) << showpoint << laborCost << endl;
    cout << "---------------------------------\n";
    cout << "Total Cost:\t\t$ " << fixed << setprecision(2) << showpoint << totalCost << endl;

    return 0;
}