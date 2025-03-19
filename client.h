#include <bits/stdc++.h>
#include "function.h"
using namespace std;

class client {
    private:
        string userName;
        string userId;
        string userPass;
        client *userNext;
    public:
        client();
        client(client*, string, string, string);
        ~client();
        client* getLast();
        int changeUserNext(client*);
        int checkUserId(string);
        string getName();
        void print();
        client *getClinet(string, string);
};

client::client() {
    userName = "HEAD";
    userPass = "HEAD";
    userId = "HEAD";
    userNext = NULL;
}

client::client(client *head, string userName, string userId, string userPass) {
    this->userName = userName;
    this->userId = userId;
    this->userPass = userPass;
    this->userNext = NULL;
    head->changeUserNext(this);
    printSeparator(printConst);
    cout << "   Signup Successful!" << endl;
    printSeparator(printConst);
    cout << endl;
    this->print();
}

client::~client() {
    if (this->userNext != NULL) {
        delete this->userNext;
    }
    this->print();
    cout << "deleted!" << endl;
}

client* client::getLast() {
    if (this->userNext != NULL) {
        return (*this).userNext->getLast();
    }
    return this;
}

int client::changeUserNext(client *userNext) {
    if (this->userNext != NULL) {
        return -1;
    }
    this->userNext = userNext;
    return 1;
}

int client::checkUserId(string id) {
    if (this->userId == id) {
        return 0;
    }
    if (this->userNext != NULL) {
        return this->userNext->checkUserId(id);
    }
    return 1;
}

void client::print() {
    cout << "Usename: " << userName;
    cout << endl;
    cout << "User ID: " << userId;
    cout << endl;
    cout << "Password: " << userPass;
    cout << endl;
    cout << endl;
}

client* client::getClinet(string name, string pass) {
    if (name == this->userName && pass == this->userPass) {
        return this;
    }
    if (this->userNext == NULL) {
        return NULL;
    }
    return this->userNext->getClinet(name, pass);
}

string client::getName() {
    return this->userName;
}