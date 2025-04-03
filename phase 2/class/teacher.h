#pragma once
#include <bits/stdc++.h>
#include "client.h"
#include "courses.h"
#include "../commonFunctions.h"
using namespace std;

class Teacher : public Client {
    private:
        Courses *courses;
    public:
        Teacher(string, string, string, Courses*);
        ~Teacher();
        void print();
        virtual void showExams();
        virtual void viewExam(string);
};

Teacher::Teacher(string userName, string userPass, string userId, Courses *courses) : Client(userName, userPass, userId), courses(courses) {

}

Teacher::~Teacher() {
    delete courses;
}

void Teacher::print() {
    Client::print();
    cout << "User courses: ";
    courses->print();
    cout << endl;
}

void Teacher::showExams() {
    ifstream examsFile("files/exams.txt");
    string line;
    while (getline(examsFile, line)) {
        if (line != "*") {
            continue;
        }
        getline(examsFile, line);
        string examCode = line;
        getline(examsFile, line);
        if (userId != line) {
            continue;
        }
        getline(examsFile, line);
        string examName = line;
        cout << "Exam name: " << examName;
        cout << endl;
        cout << "Exam code: " << examCode;
        cout << endl;
        getline(examsFile, line);
        int questionNumber = stoi(line); // string to int;
        cout << "Question number: " << questionNumber;
        cout << endl;
        printSeparator(shortPrintConst);
    }
    examsFile.close();
}

void Teacher::viewExam(string examCode) {
    ifstream examsFile("files/exams.txt");
    string line;
    while (getline(examsFile, line)) {
        if (line != "*") {
            continue;
        }
        getline(examsFile, line);
        if (line != examCode) {
            continue;
        }
        getline(examsFile, line);
        if (line != userId) {
            continue;
        }
        getline(examsFile, line);
        string examName = line;
        cout << "Exam name: " << examName;
        cout << endl;
        cout << "Exam code: " << examCode;
        cout << endl;
        getline(examsFile, line);
        int questionNumber = stoi(line);
        for (int i = 0; i < questionNumber; i++) {
            getline(examsFile, line);
            cout << "Question " << i + 1 << ": " << line;
            cout << endl;
            getline(examsFile, line);
            cout << "Answer " << i + 1 << ": " << line;
            cout << endl;
            printSeparator(shortPrintConst);
        }
    }
    examsFile.close();
}