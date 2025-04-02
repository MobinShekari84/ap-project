#pragma once
#include <bits/stdc++.h>
#include "commonFunctions.h"
#include "class/courses.h"
#include "class/client.h"
#include "class/student.h"
#include "class/teacher.h"
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

int findUserName(string line, string userName) {
    string userNameInFile;
    for (int i = 0, space = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            space++;
        }
        else if (space == 0) {
            userNameInFile = userNameInFile + line[i];
        }
    }
    if (userNameInFile == userName) {
        return 1;
    }
    return 0;
}

int findUserPass(string line, string userPass) {
    string userPassInFile;
    for (int i = 0, space = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            space++;
        }
        else if (space == 2) {
            userPassInFile = userPassInFile + line[i];
        }
    }
    if (userPassInFile == userPass) {
        return 1;
    }
    return 0;
}

string getUserId(string line) {
    string userId = "";
    for (int i = 0, space = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            space++;
        }
        else if (space == 1) {
            userId = userId + line[i];
        }
    }
    return userId;
}

string getUserStudyField(string line) {
    string userStudyField = "";
    for (int i = 0, space = 0; i < line.size(); i++) {
        if (line[i] == ' ') {
            space++;
        }
        else if (space == 3) {
            userStudyField = userStudyField + line[i];
        }
    }
    return userStudyField;
}

Courses* getUserCourses(string line) {
    Courses *courses = new Courses();
    string course = "";
    for (int i = 0, space = 0; i < line.size(); i++) {
        if (line[i] == ' ' && space < 3) {
            space++;
        }
        else if (line[i] == ' ' && space == 3) {
            courses->addCourse(course);
            course = "";
        }
        else if (space == 3) {
            course = course + line[i];
        }
    }
    return courses;
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
        if (findUserName(line, userName) && findUserPass(line, userPass)) {
            string userId = getUserId(line);
            Client* user;
            if (type == 0) {
                string studyField = getUserStudyField(line);
                user = new Student(userName, userPass, userId, studyField);
            }
            else {
                Courses *courses = getUserCourses(line);
                user = new Teacher(userName, userPass, userId, courses);
            }
            cout << "Login successful!" << endl;
            return user;
        }
    }
    logInFile.close();
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
            return 1;
        }
        user->print();
        delete user;
        return 1;
    }
    if (option == 2) {
        Client *user = logInCheck("files/teachers.txt", 1);
        if (user == NULL) {
            return 1;
        }
        user->print();
        delete user;
        return 1;
    }
    if (option == 3) {
        return 1;
    }
    return 0;
}