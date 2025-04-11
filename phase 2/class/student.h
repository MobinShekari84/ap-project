#pragma once
#include <bits/stdc++.h>
#include "client.h"
#include "exam.h"
using namespace std;

class Student : public Client {
    private:
        string studyField;
    public:
        Student(string, string, string, string);
        ~Student();
        virtual void print();
        void addExam(string examIdCode);
        void showExams();
        int checkIfUserHasExam(string examIdCode);
        void viewExam(string examIdCode);
};

Student::Student(string userName, string userPass, string userId, string studyField) : Client(userName, userPass, userId) , studyField(studyField) {

}

Student::~Student() {

}

void Student::print() {
    Client::print();
    cout << "User study field: " << studyField << endl;
}

void Student::addExam(string examIdCode) {
    ofstream examsFile("files/students/" + userId + ".txt", ios::app);
    examsFile << examIdCode;
    examsFile << endl;
    examsFile.close();
}

void Student::showExams() {
    ifstream examsFile("files/students/" + userId + ".txt");
    string line;
    while (getline(examsFile, line) && line != "Exams:") {
        continue;
    }
    cout << "Exams: " << endl;
    int ind = 1;
    while (getline(examsFile, line)) {
        cout << ind++ << ". " << line << endl;
    }
}

int Student::checkIfUserHasExam(string examIdCode) {
    ifstream examsFile("files/students/" + userId + ".txt");
    string line;
    while (getline(examsFile, line) && line != "Exams:") {
        continue;
    }
    while (getline(examsFile, line)) {
        if (line == examIdCode) {
            return 1;
        }
    }
    return 0;
}

void Student::viewExam(string examIdCode) {
    ifstream examFile("files/exams.txt");
    string line;
    int score = 0;
    while (getline(examFile, line)) {
        if (line != "*") {
            continue;
        }
        getline(examFile, line);
        if (line != examIdCode) {
            continue;
        }
        getline(examFile, line);
        string examName = line;
        cout << "Exam name: " << examName;
        cout << endl;
        getline(examFile, line);
        int questionNumber = stoi(line);
        cout << "Question number: " << questionNumber;
        cout << endl;
        for (int i = 0; i < questionNumber; i++) {
            getline(examFile, line);
            cout << "Question " << i + 1 << ": " << line;
            cout << endl;
            getline(examFile, line);
            string answer;
            do {
                cout << "Enter your answer (answer should be a number): ";
                getline(cin, answer);
                if (answer == line) {
                    score++;
                } 
                if (checkString(answer, containNumber) == 0) {
                    cout << "Error: Answer should be a number.";
                    cout << endl;
                }
            } while (checkString(answer, containNumber) == 0);
            printSeparator(shortPrintConst);
        }
        cout << "Your score: " << score << "/" << questionNumber;
        cout << endl;
    }
    addUserScore(userId, examIdCode, score);
    examFile.close();
}