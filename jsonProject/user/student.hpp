#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <bits/stdc++.h>
#include "user.hpp"
#include "../functions/stringFunctions.hpp"
#include "../json/json.hpp"
#include "../exam/exam.hpp"

using namespace std;
using json = nlohmann::json;

class Student : public User {
    private:
        string course;
        vector <int> exams;
        vector <json> results;
    public:
        Student();
        Student(string id);
        ~Student();
        void addExam(int examCode);
        void findExam(string examCode);
        void addResult(int examCode, int totalPoints, int correctPoints, int negativePoints, int questions, vector <string> userLongAnswers, vector <pair <int, bool>> usersAnswers);
        void showResultsInfo();
        void showResult(string examCode);
};

Student::Student() {
    cout << "Enter the student's course: ";
    getline(cin, course);
    isCourseValid(course);
    json studentJson;
    studentJson["name"] = userName;
    studentJson["id"] = userId;
    studentJson["password"] = userPass;
    studentJson["course"] = course;
    studentJson["exams"] = exams;
    studentJson["results"] = results;
    ofstream file("users/" + userId + ".json");
    file << studentJson.dump(4);
    file.close();
    fstream usersFile("users/userIds.json", ios::in | ios::out);
    json userIds;
    usersFile >> userIds;
    usersFile.seekp(0);
    userIds["ids"].push_back(userId);
    usersFile << userIds.dump(4);
    usersFile.close();
    fstream studentsFile("users/students.json");
    json students;
    studentsFile >> students;
    students["students"].push_back(studentJson);
    studentsFile.seekp(0);
    studentsFile << students.dump(4);
    studentsFile.close();
}

Student::Student(string id) : User(false) {
    ifstream file("users/" + id + ".json");
    json studentJson;
    file >> studentJson;
    file.close();
    userName = studentJson["name"];
    userId = id;
    userPass = studentJson["password"];
    course = studentJson["course"];
    exams.resize(studentJson["exams"].size());
    copy(studentJson["exams"].begin(), studentJson["exams"].end(), exams.begin());
    results.resize(studentJson["results"].size());
    copy(studentJson["results"].begin(), studentJson["results"].end(), results.begin());
    file.close();
}

Student::~Student() {

}

void Student::addExam(int examCode) {
    if (find(exams.begin(), exams.end(), examCode) != exams.end()) {
        throw invalid_argument("Exam already added.");
    }
    exams.push_back(examCode);
    fstream file("users/" + userId + ".json");
    json studentJson;
    file >> studentJson;
    studentJson["exams"].push_back(examCode);
    file.seekp(0);
    file << studentJson.dump(4);
    file.close();
}

void Student::findExam(string examCode) {
    if (checkString(examCode, containNumber) == false) {
        throw invalid_argument("Exam code must be a number.");
    }
    if (find(exams.begin(), exams.end(), stoi(examCode)) == exams.end()) {
        throw invalid_argument("Exam not found.");
    }
}

void Student::addResult(int examCode, int totalPoints, int correctPoints, int negativePoints, int questions, vector <string> userLongAnswers, vector <pair <int, bool>> usersAnswers) {
    json result;
    result["examCode"] = examCode;
    result["totalPoints"] = totalPoints;
    result["correctPoints"] = correctPoints;
    result["negativePoints"] = negativePoints;
    result["questions"] = questions;
    result["userLongAnswers"] = userLongAnswers;
    result["usersAnswers"] = usersAnswers;
    results.push_back(result);
    fstream file("users/" + userId + ".json");
    json studentJson;
    file >> studentJson;
    studentJson["results"].push_back(result);
    file.seekp(0);
    file << studentJson.dump(4);
    file.close();
}

void Student::showResultsInfo() {
    for (int i = 0; i < results.size(); i++) {
        printSeparator(shortPrintConst);
        cout << "Exam code: " << results[i]["examCode"] << endl;
        cout << "Total points: " << results[i]["totalPoints"] << endl;
        cout << "Correct points: " << results[i]["correctPoints"] << endl;
        cout << "Negative points: " << results[i]["negativePoints"] << endl;
        cout << endl;
    }
    printSeparator(shortPrintConst);
}

void Student::showResult(string examCode) {
    vector <int> ind; 
    for (int i = 0; i < results.size(); i++) {
        if (results[i]["examCode"].get<int>() == stoi(examCode)) {
            ind.push_back(i);
        }
    }
    if (ind.size() == 0) {
        throw invalid_argument("Exam not found.");
    }
    ofstream examResult(userId + "-" + examCode + ".txt");
    examResult << "User id: " << userId << endl;
    examResult << "Exam code: " << examCode << endl;
    examResult << "Exam result: " << endl;
    examResult << endl;
    Exam *exam = new Exam(stoi(examCode));
    for (int i = 0; i < ind.size(); i++) {
        examResult << "Result number " << i + 1 << ":" << endl;
        examResult << "Your total points achivied in multiple choice and short answer questions: " << results[ind[i]]["correctPoints"].get<int>() + results[ind[i]]["negativePoints"].get<int>() << " out of " << results[ind[i]]["totalPoints"].get<int>() << endl;
        examResult << "Your rank: " << exam->findRank(results[ind[i]]["correctPoints"].get<int>() + results[ind[i]]["negativePoints"].get<int>()) << endl;
        for (pair <int, bool> answer: results[ind[i]]["usersAnswers"]) {
            examResult << "Question number " << answer.first << ": " << endl;
            examResult << "Your answer was " << (answer.second ? "correct" : "incorrect") << endl;
            try {
                examResult << "Correct answer: " << exam->getAnswer(answer.first) << endl;
            }
            catch (invalid_argument &e) {
                examResult << e.what() << endl;
            }
            examResult << endl;
        }
        examResult << endl;
        examResult << endl;
    }
    examResult << "Average score: " << exam->findAverage() << endl;
    examResult << "Highest score: " << exam->findHighest() << endl;
    examResult.close();
}

#endif