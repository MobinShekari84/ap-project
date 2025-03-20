#include <bits/stdc++.h>
#include "function.h"
using namespace std;

// ==================================================================
// ==================================================================
// ==================================================================

class client {
    protected:
        string userName;
        string userId;
        string userPass;
        client *userNext;
    public:
        client();
        client(client*, string, string, string);
        virtual ~client();
        void changeUserNext(client*);
        int checkUserId(string);
        string getName();
        virtual void print();
        client *getClinet(string, string);
};

client::client() {
    userName = "HEAD !";
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
}

client::~client() {
    if (this->userNext != NULL) {
        delete this->userNext;
    }
    this->print();
    cout << endl;
    cout << "deleted!";
    cout << endl;
}

void client::changeUserNext(client *userNext) {
    if (this->userNext != NULL) {
        this->userNext->changeUserNext(userNext);
    }
    else {
        this->userNext = userNext;
    }
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
    cout << "Password: ";
    for (int i = 0; i < userPass.size(); i++) {
        cout << "*";
    }
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

// ==================================================================
// ==================================================================
// ==================================================================

class student : public client {
    private: 
        string userStudyField;
    public:
        student(client*, string, string, string, string);
        virtual ~student();
        virtual void print();
};

student::student(client *head, string userName, string userId, string userPass, string userStudyField) : client(head, userName, userId, userPass){
    this->userStudyField = userStudyField;
}

student::~student() {
}

void student::print() {
    cout << "Usename: " << this->userName;
    cout << endl;
    cout << "Field of study: " << this->userStudyField;
    cout << endl;
    cout << "User ID: " << this->userId;
    cout << endl;
    cout << "Password: ";
    for (int i = 0; i < userPass.size(); i++) {
        cout << "*";
    }
    cout << endl;
}

// ==================================================================
// ==================================================================
// ==================================================================

class linkedListString {
    private:
        string str;
        linkedListString *nextString;
    public:
        linkedListString();
        linkedListString(linkedListString *, string);
        void changeNextString(linkedListString *);
        ~linkedListString();
        void print();
};

linkedListString::linkedListString() {
    this->str = "HEAD !";
    this->nextString = NULL;
}

linkedListString::linkedListString(linkedListString *head, string str) {
    this->str = str;
    head->changeNextString(this);
}

linkedListString::~linkedListString() {
    if (this->nextString != NULL) {
        delete this->nextString;
    }
}

void linkedListString::changeNextString(linkedListString *nextString) {
    if (this->nextString != NULL) {
        this->nextString->changeNextString(nextString);
    }
    else {
        this->nextString = nextString;
    }
}

void linkedListString::print() {
    if (this->str == "HEAD !") {
        cout << "Courses: ";
    }
    else {
        cout << this->str;
        cout << " ";
    }
    if (this->nextString != NULL) {
        this->nextString->print();
    }
}

// ==================================================================
// ==================================================================
// ==================================================================

class teacher : public client {
    private:
        linkedListString *userCourse;
    public:
        teacher(client*, string, string, string, linkedListString*);
        virtual ~teacher();
        virtual void print();
};

teacher::teacher(client *head, string userName, string userId, string userPass, linkedListString *userCourse) : client(head, userName, userId, userPass) {
    this->userCourse = userCourse;
}

teacher::~teacher() {
    if (this->userCourse != NULL) {
        delete this->userCourse;
    }
}

void teacher::print() {
    cout << "Usename: " << this->userName;
    cout << endl;
    userCourse->print();
    cout << endl;
    cout << "User ID: " << this->userId;
    cout << endl;
    cout << "Password: ";
    for (int i = 0; i < userPass.size(); i++) {
        cout << "*";
    }
    cout << endl;
}