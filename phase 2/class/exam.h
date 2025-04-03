#pragma once
#include <bits/stdc++.h>
using namespace std;

class Exam {
    private:
        string name;
        int code;
        int questionNumber;
        vector <string> questions;
        vector <string> answers;
    public:
        Exam(string, int);
        ~Exam();
        void addQuestion(string, string);
        void print();
        void save();
        int getQuestionNumber();
        void removeQuestion(int);
};

Exam::Exam(string name, int code) : name(name), code(code) {
    questionNumber = 0;
}

Exam::~Exam() {
    questions.clear();
    answers.clear();
}

void Exam::addQuestion(string question, string answer) {
    questions.push_back(question);
    answers.push_back(answer);
    questionNumber++;
}

void Exam::print() {
    cout << "Exam name: " << name;
    cout << endl;
    cout << "Exam code: " << code;
    cout << endl;
    cout << "Exam questions: ";
    cout << endl;
    for (int i = 0; i < questionNumber; i++) {
        cout << i + 1 << ". Question: " << questions[i] << " - Answer: " << answers[i] << endl;
    }
    cout << endl;
}

void Exam::save() {
    ofstream examFile("files/exams.txt", ios::app);
    // structure: 
    // *
    // examCode
    // examName
    // questionNumber
    // question1
    // answer1
    // question2
    // answer2
    // ...
    examFile << "*";
    examFile << endl;
    examFile << code;
    examFile << endl;
    examFile << name;
    examFile << endl;
    examFile << questionNumber;
    examFile << endl;
    for (int i = 0; i < questionNumber; i++) {
        examFile << questions[i];
        examFile << endl;
        examFile << answers[i];
        examFile << endl;
    }
    examFile.close();
}

int Exam::getQuestionNumber() {
    return questionNumber;
}

void Exam::removeQuestion(int ind) {
    swap(questions[ind - 1], questions[questionNumber - 1]);
    swap(answers[ind - 1], answers[questionNumber - 1]);
    questionNumber--;
    questions.pop_back();
    answers.pop_back();
}