#pragma once
#include <bits/stdc++.h>
#include "stringFunctions.h"
#include "class/courses.h"
using namespace std;

const int longPrintConst = 60;
const int mediumPrintConst = 40;
const int shortPrintConst = 20;

void printSeparator(int printConst) {
    for (int i = 0; i < printConst; i++) {
        cout << "=";
    }
    cout << endl;
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

int isUserNameValid(string input) {
    if (checkString(input, containSpace) == 0) {
        cout << "Error: Username cannot contain spaces. Please try again.";
        cout << endl;
        return 0;
    }
    if (checkString(input, containLetter, containNumber) == 0) {
        cout << "Error: Username must contain letters and numbers. Please try again.";
        cout << endl;
        return 0;
    }
    if (input.length() < 3) {
        cout << "Error: Username must be at least 3 characters long. Please try again.";
        cout << endl;
        return 0;
    }
    if (input.length() > 15) {
        cout << "Error: Username must be at most 15 characters long. Please try again.";
        cout << endl;
        return 0;
    }
    return 1;
}

int isUserIdValid(string input) {
    if (checkString(input, containNumber) == 0) {
        cout << "Error: ID must contain numbers. Please try again.";
        cout << endl;
        return 0;
    }
    if (input.length() != 10) {
        cout << "Error: ID must be 10 characters long. Please try again.";
        cout << endl;
        return 0;
    }
    return 1;
}

int isUserIdTaken(string input) {
    ifstream file("files/usersId.txt");
    string line;
    while (getline(file, line)) {
        if (line == input) {
            cout << "Error: ID already taken. Please try again.";
            cout << endl;
            return 1;
        }
    }
    return 0;
}

int isUserPassValid(string input) {
    if (input.length() < 8) {
        cout << "Error: Password must be at least 8 characters long. Please try again.";
        cout << endl;
        return 0;
    }
    if (input.length() > 15) {
        cout << "Error: Password must be at most 15 characters long. Please try again.";
        cout << endl;
        return 0;
    }
    if (checkString(input, containLetter, containNumber, containSpecialChar) == 0) {
        cout << "Error: Password must contain letters, numbers, and special characters (! or @ or _). Please try again.";
        cout << endl;
        return 0;
    }
    return 1;
}

int isUserStudyFieldValid(string input) {
    if (checkString(input, containLetter) == 0) {
        cout << "Error: Study field must contain letters. Please try again.";
        cout << endl;
        return 0;
    }
    return 1;
}

int isUserCourseValid(string input) {
    if (checkString(input, containLetter, containNumber) == 0) {
        cout << "Error: Course must contain letters and numbers. Please try again.";
        cout << endl;
        return 0;
    }
    return 1;
}

Courses* getUserCourses() {
    Courses *userCourses = new Courses();
    string input;
    cout << "Type 'MENU' to return to main menu";
    cout << endl;
    cout << "Enter the courses you want to add (enter 'done' to finish): ";
    cout << endl;
    do {
        getline(cin, input);
        if (input == "MENU") {
            return NULL;
        }
        if (input == "done") {
            cout << "Courses: ";
            userCourses->print();
            cout << endl;
        }
        else if (isUserCourseValid(input) == 1) {
            userCourses->addCourse(input);
        }
    } while (input != "done");
    return userCourses;
}