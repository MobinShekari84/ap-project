#pragma once
#include <bits/stdc++.h>
#include "commonFunctions.h"
#include "class/courses.h"
#include "class/client.h"
#include "class/student.h"
#include "class/teacher.h"
#include "teachersHub.h"
#include "studentsHub.h"
using namespace std;

void logInPrint() {
    printSeparator(longPrintConst);
    cout << "   Login page";
    cout << endl;
    cout << endl;
    cout << "1. Login as a Student";
    cout << endl;
    cout << "2. Login as a Teacher";
    cout << endl;
    cout << "3. Return to main menu";
    cout << endl;
    cout << "4. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

Client *getStudent(string userName, string userPass, string userId) {
    ifstream studentFile("files/students/" + userId + ".txt");
    string line;
    getline(studentFile, line);
    getline(studentFile, line);
    getline(studentFile, line);
    getline(studentFile, line);
    string studyField = line;
    return new Student(userName, userPass, userId, studyField);
}

Client *getTeacher(string userName, string userPass, string userId) {
    ifstream teacherFile("files/teachers/" + userId + ".txt");
    string line;
    getline(teacherFile, line);
    getline(teacherFile, line);
    getline(teacherFile, line);
    getline(teacherFile, line);
    Courses *courses = new Courses();
    string course = "";
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            courses->addCourse(course);
            course = "";
        }
        else {
            course += line[i];
        }
    }
    return new Teacher(userName, userPass, userId, courses);
}

int doesUserExist(ifstream &logInFile, string userName, string userPass) {
    string line;
    getline(logInFile, line);
    if (line != userName) {
        return 0;
    }
    getline(logInFile, line);
    if (line != userPass) {
        return 0;
    }
    return 1;
}

Client* logInCheck(string filePath, int type) {
    printSeparator(longPrintConst);
    cout << "Enter your username: ";
    string userName;
    getline(cin, userName);
    cout << "Enter your password: ";
    string userPass;
    getline(cin, userPass);
    ifstream logInFile(filePath);
    string line;
    while (getline(logInFile, line)) {
        if (line == "*" && doesUserExist(logInFile, userName, userPass)) {
            getline(logInFile, line);
            string userId = line;
            Client* user;
            if (type == 0) {
                user = getStudent(userName, userPass, userId);
            }
            else {
                user = getTeacher(userName, userPass, userId);
            }
            logInFile.close();
            printSeparator(longPrintConst);
            cout << "Login successful!" << endl;
            return user;
        }
    }
    logInFile.close();
    printSeparator(shortPrintConst);
    cout << "No user found with this username and password";
    cout << endl;
    return NULL;
}

int logIn() {
    logInPrint();
    int option = getChoises(4);
    if (option == 1) {
        Client *user = logInCheck("files/students.txt", 0);
        if (user == NULL) {
            cout << "Login failed. Please try again.";
            cout << endl;
            return 1;
        }
        user->print();
        int returnValue;
        do {
            returnValue = studentsHub(user);
        } while (returnValue == 2);
        delete user;
        return returnValue;
    }
    if (option == 2) {
        Client *user = logInCheck("files/teachers.txt", 1);
        if (user == NULL) {
            cout << "Login failed. Please try again.";
            cout << endl;
            return 1;
        }
        user->print();
        int returnValue;
        do {
            returnValue = teachersHub(user);
        } while (returnValue == 2);
        delete user;
        return returnValue;
    }
    if (option == 3) {
        return 1;
    }
    return 0;
}