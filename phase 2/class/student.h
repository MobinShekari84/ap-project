#pragma once
#include <bits/stdc++.h>
#include "client.h"
using namespace std;

class Student : public Client {
    private:
        string studyField;
    public:
        Student(string, string, string, string);
        ~Student();
        virtual void print();
};

Student::Student(string userName, string userPass, string userId, string studyField) : Client(userName, userPass, userId) , studyField(studyField) {

}

Student::~Student() {

}

void Student::print() {
    Client::print();
    cout << "User study field: " << studyField << endl;
}