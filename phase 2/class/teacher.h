#pragma once
#include <bits/stdc++.h>
#include "client.h"
#include "courses.h"
using namespace std;

class Teacher : public Client {
    private:
        Courses *courses;
    public:
        Teacher(string, string, string, Courses*);
        ~Teacher();
        void print();
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