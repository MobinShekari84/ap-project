#pragma once
#include <bits/stdc++.h>
#include "class/client.h"
#include "class/courses.h"
#include "class/teacher.h"
#include "commonFunctions.h"
#include "stringFunctions.h"
#include "class/exam.h"
using namespace std;

void studentsHubPrint() {
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
    cout << "4. Return to main menu";
    cout << endl;
    cout << "5. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

void addExamStudent(Client *user) {
    cout << "Add an exam";
    cout << endl;
    cout << endl;
    string examIdCode;
    do {
        cout << "Enter the exam id code (type MENU to return back): ";
        getline(cin, examIdCode);
        if (examIdCode == "MENU") {
            return;
        }
        if (user->checkIfUserHasExam(examIdCode) == 1) {
            cout << "Error: You already have this exam.";
            cout << endl;
        }
        if (checkIfExamExists(examIdCode) == 0) {
            cout << "Error: Exam not found. Please try again.";
            cout << endl;
        }
    } while (checkIfExamExists(examIdCode) == 0 || user->checkIfUserHasExam(examIdCode) == 1);
    user->addExam(examIdCode);
    cout << "Exam with id code " << examIdCode << " added successfully.";
    cout << endl;
    printSeparator(shortPrintConst);
}

void viewExamsStudent(Client *user) {
    cout << "View exams";
    cout << endl;
    cout << endl;
    user->showExams();
    printSeparator(shortPrintConst);
}

void participateInExamStudent(Client *user) {
    cout << "Participate in an exam";
    cout << endl;
    cout << endl;
    user->showExams();
    printSeparator(shortPrintConst);
    string examIdCode;
    do {
        cout << "Enter the exam id code (type MENU to return back): ";
        getline(cin, examIdCode);
        if (examIdCode == "MENU") {
            return;
        }
        if (user->checkIfUserHasExam(examIdCode) == 0) {
            cout << "Error: You don't have this exam.";
            cout << endl;
        }
    } while (user->checkIfUserHasExam(examIdCode) == 0);
    user->viewExam(examIdCode);
    printSeparator(shortPrintConst);
}

int studentsHub(Client *user) {
    studentsHubPrint();
    int option = getChoises(5);
    if (option == 1) {
        addExamStudent(user);
        return 2;
    }
    if (option == 2) {
        viewExamsStudent(user);
        return 2;
    }
    if (option == 3) {
        participateInExamStudent(user);
        return 2;
    }
    if (option == 4) {
        return 1;
    }
    return 0;
}