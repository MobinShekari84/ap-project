#pragma once
#include <bits/stdc++.h>
#include "commonFunctions.h"
#include "class/courses.h"
using namespace std;

void signUpPrint() {
    printSeparator(longPrintConst);
    cout << "   Signup page";
    cout << endl;
    cout << endl;
    cout << "1. Sign up as a Student";
    cout << endl;
    cout << "2. Sign up as a Teacher";
    cout << endl;
    cout << "3. Return to main menu";
    cout << endl;
    cout << "4. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

string getUserName() {
    string userName;
    do {
        printSeparator(mediumPrintConst);
        cout << "Type in 'MENU' to return to main menu!";
        cout << endl;
        cout << endl;
        cout << "Enter your name: ";
        getline(cin, userName);
        if (userName == "MENU") {
            printSeparator(mediumPrintConst);
            return userName;
        }
    } while (isUserNameValid(userName) == 0);
    return userName;
}

string getUserId() {
    string userId;
    do {
        printSeparator(mediumPrintConst);
        cout << "Type in 'MENU' to return to main menu!";
        cout << endl;
        cout << endl;
        cout << "Enter your ID: ";
        getline(cin, userId);
        if (userId == "MENU") {
            printSeparator(mediumPrintConst);
            return userId;
        }
    } while (isUserIdValid(userId) == 0 || isUserIdTaken(userId) == 1);
    return userId;
}

string getUserPass() {
    string userPass;
    do {
        printSeparator(mediumPrintConst);
        cout << "Type in 'MENU' to return to main menu!";
        cout << endl;
        cout << endl;
        cout << "Enter your password: ";
        getline(cin, userPass);
        if (userPass == "MENU") {
            printSeparator(mediumPrintConst);
            return userPass;
        }
    } while (isUserPassValid(userPass) == 0);
    return userPass;
}

string getUserStudyField() {
    string userStudyField;
    do {
        printSeparator(mediumPrintConst);
        cout << "Type in 'MENU' to return to main menu!";
        cout << endl;
        cout << endl;
        cout << "Enter your study field: ";
        getline(cin, userStudyField);
        if (userStudyField == "MENU") {
            printSeparator(mediumPrintConst);
            return userStudyField;
        }
    } while (isUserStudyFieldValid(userStudyField) == 0);
    return userStudyField;
}

void signUpStudent() {
    string userName = getUserName();
    if (userName == "MENU") {
        return;
    }
    string userId = getUserId();
    if (userId == "MENU") {
        return;
    }
    ofstream usersIdFile("files/usersId.txt", ios::app);
    usersIdFile << userId << endl;
    usersIdFile.close();
    string userPass = getUserPass();
    if (userPass == "MENU") {
        return;
    }
    string userStudyField = getUserStudyField();
    if (userStudyField == "MENU") {
        return;
    }
    printSeparator(longPrintConst);
    cout << "User " << userName << " with ID " << userId << " and study field " << userStudyField << " has been created successfully!";
    cout << endl;
    ofstream studentsFile("files/students.txt", ios::app);
    // structure (for students.txt):
    // *
    // userName
    // userPass
    // userId
    // *
    // nextStudent...
    studentsFile << "*";
    studentsFile << endl;
    studentsFile << userName;
    studentsFile << endl;
    studentsFile << userPass;
    studentsFile << endl;
    studentsFile << userId;
    studentsFile << endl;
    studentsFile.close();
    ofstream studentsIdFile("files/students/" + userId + ".txt", ios::app);
    // structure (for students/userId.txt):
    // userName
    // userPass
    // userId
    // studyField
    studentsIdFile << userName;
    studentsIdFile << endl;
    studentsIdFile << userPass;
    studentsIdFile << endl;
    studentsIdFile << userId;
    studentsIdFile << endl;
    studentsIdFile << userStudyField;
    studentsIdFile << endl;
    studentsIdFile.close();
}

void signUpTeacher() {
    string userName = getUserName();
    if (userName == "MENU") {
        return;
    }
    Courses *userCourses = getUserCourses();
    if (userCourses == NULL) {
        return;
    }
    string userId = getUserId();
    if (userId == "MENU") {
        return;
    }
    ofstream usersIdFile("files/usersId.txt", ios::app);
    usersIdFile << userId << endl;
    usersIdFile.close();
    string userPass = getUserPass();
    if (userPass == "MENU") {
        return;
    }
    cout << "User " << userName << " with ID " << userId << " and courses ";
    userCourses->print();
    cout << "has been created successfully!";
    cout << endl;
    ofstream teachersFile("files/teachers.txt", ios::app);
    // structure (for teachers.txt):
    // *
    // userName
    // userPass
    // userId
    // *
    // nextTeacher...
    teachersFile << "*";
    teachersFile << endl;
    teachersFile << userName;
    teachersFile << endl;
    teachersFile << userPass;
    teachersFile << endl;
    teachersFile << userId;
    teachersFile << endl;
    teachersFile.close();
    ofstream teachersIdFile("files/teachers/" + userId + ".txt", ios::app);
    // structure (for teachers/userId.txt):
    // userName
    // userPass
    // userId
    // courses
    // Exams:
    // exam1
    // exam2
    // ...
    teachersIdFile << userName;
    teachersIdFile << endl;
    teachersIdFile << userPass;
    teachersIdFile << endl;
    teachersIdFile << userId;
    teachersIdFile << endl;
    vector <string> courses = userCourses->getCourses();
    for (string course : courses) {
        teachersIdFile << course << " ";
    }
    teachersIdFile << endl;
    teachersIdFile << "Exams:";
    teachersIdFile << endl;
    teachersIdFile.close();
    delete userCourses;
}

int signUp() {
    signUpPrint();
    int option = getChoises(4);
    if (option == 1) {
        signUpStudent();
        return 1;
    }
    if (option == 2) {
        signUpTeacher();
        return 1;
    }
    if (option == 3) {
        return 1;
    }
    return 0;
}