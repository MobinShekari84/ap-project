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
        virtual void addExam(string);
        virtual void showExams();
        virtual void viewExam(string);
        virtual int checkIfUserHasExam(string);
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

void Teacher::addExam(string examCode) {
    ofstream examsFile("files/teachers/" + userId + ".txt", ios::app);
    examsFile << examCode;
    examsFile << endl;
    examsFile.close();
}

void Teacher::showExams() {
    ifstream examsFile("files/teachers/" + userId + ".txt");
    string line;
    while (getline(examsFile, line) && line != "Exams:") {
        continue;
    }
    while (getline(examsFile, line)) {
        cout << "Exam code: " << line;
        cout << endl;
    }
    examsFile.close();
}

int Teacher::checkIfUserHasExam(string examCode) {
    ifstream examsFile("files/teachers/" + userId + ".txt");
    string line;
    while (getline(examsFile, line) && line != "Exams:") {
        continue;
    }
    while (getline(examsFile, line)) {
        if (line == examCode) {
            return 1;
        }
    }
    return 0;
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