#ifndef USER_HPP
#define USER_HPP

#include <bits/stdc++.h>
#include "../functions/stringFunctions.hpp"
#include "../json/json.hpp"

using namespace std;
using json = nlohmann::json;
class User {
    protected:
        string userName;
        string userId;
        string userPass;
    public:
        User();
        User(bool);
        ~User();
        void isUserNameValid(string userName);
        void isUserIdValid(string userId);
        void isUserPassValid(string userPass);
        void isCourseValid(string course);
        string getUserId();
        virtual void addExam(int examCode);
};

User::User() {
    cout << "Enter the user's name: ";
    getline(cin, userName);
    isUserNameValid(userName);
    cout << "Enter the user's id: ";
    getline(cin, userId);
    isUserIdValid(userId);
    cout << "Enter the user's password: ";
    getline(cin, userPass);
    isUserPassValid(userPass);
}

User::~User() {

}

User::User(bool) {

}

void User::isUserNameValid(string userName) {
    if (checkString(userName, containLetter, containSpace) == false) {
        throw invalid_argument("Invalid user name. User name must contain only letters and spaces.");
    }
}

void User::isUserIdValid(string userId) {
    if (checkString(userId, containNumber) == false || userId.length() != 10) {
        throw invalid_argument("Invalid user id. User id must contain only numbers and be 10 characters long.");
    }
    ifstream file("users/userIds.json");
    json userIds;
    file >> userIds;
    if (find(userIds["ids"].begin(), userIds["ids"].end(), userId) != userIds["ids"].end()) {
        throw invalid_argument("User id already exists.");
    }
    file.close();
}

void User::isUserPassValid(string userPass) {
    if (checkString(userPass, containLetter, containNumber, containSpecialChar) == false) {
        throw invalid_argument("Invalid user password. User password must contain only letters, numbers and special characters.");
    }
}

void User::isCourseValid(string course) {
    if (checkString(course, containLetter, containSpace, containNumber) == false) {
        throw invalid_argument("Invalid course. Course must contain only letters and spaces and numbers.");
    }
}

string User::getUserId() {
    return userId;
}

void User::addExam(int examCode) {
}

#endif