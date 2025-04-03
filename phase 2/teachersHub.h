#pragma once
#include <bits/stdc++.h>
#include "class/client.h"
#include "class/courses.h"
#include "class/teacher.h"
#include "commonFunctions.h"
#include "stringFunctions.h"
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

string getExamName() {
    cout << "Enter the exam name: ";
    string examName;
    getline(cin, examName);
    cout << endl;
    return examName;
}

string getExamQuestion() {
    cout << "Enter the question: ";
    string question;
    getline(cin, question);
    return question;
}

string getExamAnswer() {
    string answer;
    do {
        cout << "Enter the answer (answer should only contain numbers): ";
        getline(cin, answer);
        if (checkString(answer, containNumber) == 0) {
            cout << "Error: Answer should only contain numbers. Try again.";
            cout << endl;
        }
    } while (checkString(answer, containNumber) == 0);
    return answer;
}

void removeExamQuestion(Exam *exam) {
    printSeparator(shortPrintConst);
    exam->print();
    printSeparator(shortPrintConst);
    cout << "Enter the question number to remove: ";
    int questionNumber = getChoises(exam->getQuestionNumber());
    exam->removeQuestion(questionNumber);
}

void createExam(Client *user) {
    printSeparator(mediumPrintConst);
    cout << "Create exam";
    cout << endl;
    cout << endl;
    string examName = getExamName();
    int examCode = rand();
    cout << "Exam '" << examName << "' created with code '" << examCode << "' successfully.";
    cout << endl;
    string question;
    string answer;
    Exam *exam = new Exam(examName, examCode);
    cout << "Exam created successfully.";
    cout << endl;
    int option;
    do {
        createExamPrint();
        option = getChoises(4);
        if (option == 1) {
            question = getExamQuestion();
            answer = getExamAnswer();
            exam->addQuestion(question, answer);
        }
        if (option == 2) {
            removeExamQuestion(exam);
        }
        if (option == 3) {
            printSeparator(shortPrintConst);
            exam->print();
            printSeparator(shortPrintConst);
        }
    } while (option != 4);
    cout << "Exam created successfully.";
    cout << endl;
    exam->save(user->getUserId());
    delete exam;
}

void viewExams(Client *user) {
    printSeparator(mediumPrintConst);
    cout << "View exams";
    cout << endl;
    cout << endl;
    user->showExams();
    string examCode;
    cout << endl;
    cout << "Enter the exam code to view (type MENU to return back): ";
    getline(cin, examCode);
    if (examCode == "MENU") {
        return;
    }
    user->viewExam(examCode);
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
        viewExams(user);
        return 2;
    }
    if (option == 3) {
        return 1;
    }
    return 0;
}