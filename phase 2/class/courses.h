#pragma once
#include <bits/stdc++.h>
using namespace std;

class Courses {
    private:
        vector <string> courses;
        int numberOfCourses;
    public:
        Courses();
        ~Courses();
        void addCourse(string course);
        void print();
        int removeCourse(string course);
        vector <string> getCourses();
};

Courses::Courses() {
    numberOfCourses = 0;
}

Courses::~Courses() {
    courses.clear();
}

void Courses::addCourse(string course) {
    courses.push_back(course);
    numberOfCourses++;
}

void Courses::print() {
    for (string course : courses) {
        cout << course << " ";
    }
}

int Courses::removeCourse(string course) {
    for (int i = 0; i < courses.size(); i++) {
        if (courses[i] == course) {
            swap(courses[i], courses[numberOfCourses - 1]);
            courses.pop_back();
            return 1;
        }
    }
    return 0;
}

vector <string> Courses::getCourses() {
    return courses;
}