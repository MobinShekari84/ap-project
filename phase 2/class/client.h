#pragma once
#include <bits/stdc++.h>
using namespace std;

class Client {
    private:
        string userName;
        string userPass;
        string userId;
    public:
        Client(string, string, string);
        ~Client();
        virtual void print();
};

Client::Client(string userName, string userPass, string userId) : userName(userName), userPass(userPass), userId(userId) {

}

Client::~Client() {

}

void Client::print() {
    cout << "User name: " << userName << endl;
    cout << "User id: " << userId << endl;
}