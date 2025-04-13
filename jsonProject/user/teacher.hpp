#ifndef TEACHER_HPP
#define TEACHER_HPP

#include "user.hpp"

class Teacher : public User {
    private:
        vector <string> courses;
        vector <int> exams;
    public:
        Teacher();
        Teacher(string id);
        ~Teacher();
        void addExam(int examCode);
        void findExam(string examCode);
        void showResultsInfo();
        void showResult(string examCode);
        void findResult(string examCode);
};

Teacher::Teacher() {
    string course;
    do {
        cout << "Enter the teacher's course (or type exit to finish): ";
        getline(cin, course);
        if (course != "exit") {
            isCourseValid(course);
            courses.push_back(course);
        }
    } while (course != "exit");
    json teacherJson;
    teacherJson["name"] = userName;
    teacherJson["id"] = userId;
    teacherJson["password"] = userPass;
    teacherJson["courses"] = courses;
    ofstream file("users/" + userId + ".json");
    file << teacherJson.dump(4);
    file.close();
    fstream usersFile("users/userIds.json", ios::in | ios::out);
    json userIds;
    usersFile >> userIds;
    usersFile.seekp(0);
    userIds["ids"].push_back(userId);
    usersFile << userIds.dump(4);
    usersFile.close();
    fstream teachersFile("users/teachers.json");
    json teachers;
    teachersFile >> teachers;
    teachers["teachers"].push_back(teacherJson);
    teachersFile.seekp(0);
    teachersFile << teachers.dump(4);
    teachersFile.close();
}

Teacher::Teacher(string id) : User(false) {
    ifstream file("users/" + id + ".json");
    json teacherJson;
    file >> teacherJson;
    file.close();
    userName = teacherJson["name"];
    userId = id;
    userPass = teacherJson["password"];
    for (auto course: teacherJson["courses"]) {
        courses.push_back((string) (course));
    }
    for (auto exam: teacherJson["exams"]) {
        exams.push_back((int) (exam));
    }
    file.close();
}

Teacher::~Teacher() {

}

void Teacher::addExam(int examCode) {
    exams.push_back(examCode);
    fstream file("users/" + userId + ".json");
    json teacherJson;
    file >> teacherJson;
    teacherJson["exams"].push_back(examCode);
    file.seekp(0);
    file << teacherJson.dump(4);
    file.close();
}

void Teacher::findExam(string examCode) {
    if (checkString(examCode, containNumber) == false) {
        throw invalid_argument("Exam code must be a number.");
    }
    if (find(exams.begin(), exams.end(), stoi(examCode)) == exams.end()) {
        throw invalid_argument("Exam not found.");
    }
}

void Teacher::showResultsInfo() {
    for (int i = 0; i < exams.size(); i++) {
        cout << "Exam code: " << exams[i] << endl;
    }
    printSeparator(shortPrintConst);
}

void Teacher::showResult(string examCode) {
    Exam *exam = new Exam(stoi(examCode));
    ofstream file;
    file.open("Exam Results-" + examCode + ".csv");
    try {
        exam->showResults(file);
        cout << "Exam results have been saved to Exam Results-" << examCode << ".csv" << endl;
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
    }
    file.close();
    delete exam;
}

void Teacher::findResult(string examCode) {
    if (checkString(examCode, containNumber) == false) {
        throw invalid_argument("Exam code must be a number.");
    }
    if (find(exams.begin(), exams.end(), stoi(examCode)) == exams.end()) {
        throw invalid_argument("Exam not found.");
    }
}

#endif