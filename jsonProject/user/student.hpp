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
    public:
        Student();
        Student(string id);
        ~Student();
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
    file.close();
}

Student::~Student() {

}


#endif