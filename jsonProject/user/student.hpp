#ifndef STUDENT_HPP
#define STUDENT_HPP

#include <bits/stdc++.h>
#include "user.hpp"
#include "../functions/stringFunctions.hpp"
#include "../json/json.hpp"

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

#endif