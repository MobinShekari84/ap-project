#ifndef EXAM_HPP
#define EXAM_HPP

#include <bits/stdc++.h>
#include "../functions/printFunctions.hpp"
#include "../functions/stringFunctions.hpp"
#include "../json/json.hpp"

using namespace std;
using json = nlohmann::json;

class Exam {
    private:
        string examName;
        int examCode;
        vector <string> questions;
        vector <string> answers;
    public:
        Exam(string examName, int examCode);
        Exam(string examName, int examCode, vector <string> questions, vector <string> answers);
        Exam(json examJson);
        ~Exam();
        void addQuestion();
        void removeQuestion();
        friend ostream& operator<<(ostream& os, Exam& exam);
        json getExamJson();
        void hideInformations();
        int getExamCode();
        void participate(User *user);
};

Exam::Exam(string examName, int examCode) : examName(examName), examCode(examCode) {
}

Exam::Exam(string examName, int examCode, vector <string> questions, vector <string> answers) : examName(examName), examCode(examCode), questions(questions), answers(answers) {
}

Exam::Exam(json examJson) {
    examName = examJson["examName"];
    examCode = examJson["examCode"];
    questions.resize(examJson["questions"].size());
    answers.resize(examJson["answers"].size());
    copy(examJson["questions"].begin(), examJson["questions"].end(), questions.begin());
    copy(examJson["answers"].begin(), examJson["answers"].end(), answers.begin());
}

Exam::~Exam() {
}

Exam* findExam(string examCode) {
    ifstream file("exam/" + examCode + ".json");
    if (!file.is_open()) {
        throw invalid_argument("Exam not found.");
    }
    json examJson;
    file >> examJson;
    file.close();
    return new Exam(examJson);
}

void Exam::addQuestion() {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Enter the question: ";
    string question;
    getline(cin, question);
    cout << "Enter the answer (answer only contain numbers): ";
    string answer;
    getline(cin, answer);
    if (checkString(answer, containNumber) == false) {
        throw invalid_argument("Invalid answer. Answer must contain only numbers.");
    }
    questions.push_back(question);
    answers.push_back(answer);
    cout << endl;
    cout << "Question added successfully.";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
}

void Exam::removeQuestion() {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Enter the question number to remove.";
    cout << endl;
    cout << endl;
    int questionNumber = getChoises(questions.size());
    questions.erase(questions.begin() + questionNumber - 1);
    answers.erase(answers.begin() + questionNumber - 1);
    cout << endl;
    cout << "Question removed successfully.";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
}   

ostream& operator<<(ostream& os, Exam& exam) {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Exam: " << exam.examName;
    cout << endl;
    cout << endl;
    for (int i = 0; i < exam.questions.size(); i++) {
        cout << "Question " << i + 1 << ": " << exam.questions[i];
        cout << endl;
        cout << "Answer: " << exam.answers[i];
        cout << endl;
        cout << endl;
    }
    printSeparator(shortPrintConst);
    return os;
}

void Exam::hideInformations() {
    for (int i = 0; i < questions.size(); i++) {
        questions[i] = "**********";
    }
    for (int i = 0; i < answers.size(); i++) {
        answers[i] = "**********";
    }
}

json Exam::getExamJson() {
    json exam;
    exam["examName"] = examName;
    exam["examCode"] = examCode;
    exam["questions"] = questions;
    exam["answers"] = answers;
    return exam;
}

int Exam::getExamCode() {
    return examCode;
}


void Exam::participate(User *user) {
    cout << "Participating in exam " << examName << " with code " << examCode << ".";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
    cout << endl;
    int correctAnswers = 0;
    for (int i = 0; i < questions.size(); i++) {
        cout << "Question " << i + 1 << ": " << questions[i];
        cout << endl;
        cout << "Enter the answer: ";
        string answer;
        getline(cin, answer);
        if (answer == answers[i]) {
            correctAnswers++;
        }
        cout << endl;
        cout << endl;
    }
    cout << "You got " << correctAnswers << " out of " << questions.size() << " correct.";
    user->addResult(examCode, correctAnswers);
    cout << endl;
    cout << endl;
    cout << "Result added successfully.";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
}

#endif