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