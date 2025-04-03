#pragma once
#include <bits/stdc++.h>
#include "class/client.h"
#include "class/courses.h"
#include "class/teacher.h"
#include "commonFunctions.h"
#include "class/exam.h"
using namespace std;

void teachersHubPrint() {
    printSeparator(longPrintConst);
    cout << "   Teacher's Page";
    cout << endl;
    cout << endl;
    cout << "1. Create exam";
    cout << endl;
    cout << "2. View exams";
    cout << endl;
    cout << "3. Return to main menu";
    cout << endl;
    cout << "4. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
}

void createExam(Client *user) {
    printSeparator(mediumPrintConst);
    cout << "Create exam";
    cout << endl;
    cout << endl;
    cout << "Enter the exam name: ";
    string examName;
    getline(cin, examName);
    cout << endl;
    int examCode = rand();
    cout << "Exam '" << examName << "' created with code '" << examCode << "' successfully.";
    cout << endl;
    string question;
    string answer;
    Exam *exam = new Exam(examName, examCode);
    do {
        printSeparator(shortPrintConst);
        cout << "Enter the question (type 'done' to finish): ";
        getline(cin, question);
        if (question == "done") {
            cout << "Exam created successfully.";
            cout << endl;
            exam->print();
            printSeparator(shortPrintConst);
        }
        else {
            cout << "Enter the answer: ";
            getline(cin, answer);
            exam->addQuestion(question, answer);
        }
    } while (question != "done");
    exam->save(user->getUserId());
    delete exam;
}

int teachersHub(Client *user) {
    srand(time(0));
    teachersHubPrint();
    int option = getChoises(4);
    if (option == 1) {
        createExam(user);
        return 2;
    }
    if (option == 2) {
        return 2;
    }
    if (option == 3) {
        return 1;
    }
    return 0;
}