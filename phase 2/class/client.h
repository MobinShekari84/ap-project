#pragma once
#include <bits/stdc++.h>
using namespace std;

class Client {
    protected:
        string userName;
        string userPass;
        string userId;
    public:
        Client(string, string, string);
        ~Client();
        virtual void print();
        string getUserId();
        virtual void addExam(int);
        virtual void showExams();
        virtual void viewExam(string);
};

Client::Client(string userName, string userPass, string userId) : userName(userName), userPass(userPass), userId(userId) {

}

Client::~Client() {

}

void Client::print() {
    cout << "User name: " << userName << endl;
    cout << "User id: " << userId << endl;
}

string Client::getUserId() {
    return userId;
}

void Client::addExam(int examCode) {

}

void Client::showExams() {

}

void Client::viewExam(string examCode) {

}