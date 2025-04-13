#ifndef PRINTFUNCTIONS_HPP
#define PRINTFUNCTIONS_HPP

#include <bits/stdc++.h>
using namespace std;

const int longPrintConst = 60;
const int mediumPrintConst = 40;
const int shortPrintConst = 20;

void printSeparator(int length) {
    for (int i = 0; i < length; i++) {
        cout << "=";
    }
    cout << endl;
}

void welcomePrint() {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "Please choose an option.";
    cout << endl;
    cout << endl;
    cout << "1 - Create New Account (Signup)";
    cout << endl;
    cout << "   Select this if you're new here";
    cout << endl;
    cout << endl;
    cout << "2 - Login to Existing Account";
    cout << endl;
    cout << "   Choose this if you already have an account";
    cout << endl;
    cout << endl;
    cout << "3 - Exit ";
    cout << endl;
    cout << "    Choose this to exit the program";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

void signUpPrint() {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "   Signup page";
    cout << endl;
    cout << endl;
    cout << "1. Sign up as a Student";
    cout << endl;
    cout << "2. Sign up as a Teacher";
    cout << endl;
    cout << "3. Return to main menu";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

void loginPrint() {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "   Login page";
    cout << endl;
    cout << endl;
    cout << "1. Login as a Student";
    cout << endl;
    cout << "2. Login as a Teacher";
    cout << endl;
    cout << "3. Return to main menu";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

void teacherMenuPrint() {
    printSeparator(longPrintConst);
    cout << "   Teacher's Page";
    cout << endl;
    cout << endl;
    cout << "1. Create exam";
    cout << endl;
    cout << "2. View exams";
    cout << endl;
    cout << "3. View results";
    cout << endl;
    cout << "4. Return to main menu";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

void createExamPrint() {
    printSeparator(shortPrintConst);
    cout << "1. Add question";
    cout << endl;
    cout << "2. Remove question";
    cout << endl;
    cout << "3. Print exam";
    cout << endl;
    cout << "4. Finish exam";
    cout << endl;
    printSeparator(shortPrintConst);
}

void studentMenuPrint() {
    printSeparator(longPrintConst);
    cout << "Student's Page";
    cout << endl;
    cout << endl;
    cout << "1. Add an exam";
    cout << endl;
    cout << "2. View exams";
    cout << endl;
    cout << "3. Participate in an exam";
    cout << endl;
    cout << "4. View results";
    cout << endl;
    cout << "5. Return to main menu";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

int getChoises(int options) {
    int choice = 0;
    do {
        cout << "Enter your choice (";
        for (int i = 1; i <= options; i++) {
            cout << i;
            if (i != options) {
                cout << " or ";
            }
        }
        cout << "): ";
        string inputString;
        getline(cin, inputString);
        for (int i = 1; i <= options; i++) {
            if (inputString == to_string(i)) {
                choice = i;
            }
        }
        if (choice == 0) {
            cout << "Error: Invalid choice! Please try again.";
            cout << endl;
            printSeparator(mediumPrintConst);
        }
    } while (choice == 0);
    return choice;
}

#endif