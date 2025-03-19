#include <bits/stdc++.h>
using namespace std;

const int printConst = 40;

class client {
    private:
        string userName;
        string userId;
        string userPass;
        client *userNext;
    public:
        client();
        client(client*);
        ~client();
        client* getLast();
        int changeUserNext(client*);
        int checkUserId(string);
        void print();
};

int containSpace(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
            return 1;
        }
    }
    return 0;
}

int containNumber(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] > '9' || s[i] < '0') {
            return 1;
        }
    }
    return 0;
}

client::client() {
    userName = "HEAD";
    userPass = "HEAD";
    userId = "HEAD";
    userNext = NULL;
}

client::client(client *head) {
    cout << endl;
    for (int i = 0; i < printConst; i++) {
        cout << "*";
    }
    cout << endl;
    cout << "   Signup progress;" << endl << endl;
    cout << "Enter your desired username (no spaces allowed):";
    getline(cin, userName);
    while (containSpace(userName)) {
        cout << "   Username cannot contain spaces. Please try again." << endl << endl;
        cout << "Enter your desired username (no spaces allowed):";
        getline(cin, userName);
    }
    cout << endl;
    cout << "Enter your desired user ID (numbers only): ";
    getline(cin, userId);
    while (containNumber(userId) == 1 || head->checkUserId(userId) == 0) {
        if (head->checkUserId(userId) == 0) {
            cout << "Error: ID has been taken, try again! " << endl << endl;
        }
        else {
            cout << "Error: User ID must be a number. Please try again." << endl << endl;
        }
        cout << "Enter your desired user ID (numbers only): ";
        getline(cin, userId);
    }
    cout << endl;
    cout << "Enter your desired password (no spaces allowed): ";
    getline(cin, userPass);
    while (containSpace(userPass)) {
        cout << "Error: Password cannot contain spaces. Please try again." << endl << endl;
        cout << "Enter your desired password (no spaces allowed): ";
        getline(cin, userPass);
    }
    cout << endl;
    userNext = NULL;
    head->changeUserNext(this);
    cout << "   Signup Successful!" << endl;
    this->print();
    cout << "Thank you for signing up! You can now login with your credentials." << endl;
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
    for (int i = 0; i < printConst; i++) {
        cout << "*";
    }
    cout << endl << endl;
    cout << "Usename: " << userName << endl;
    cout << "User ID: " << userId << endl;
    cout << "Password: " << userPass << endl;
    cout << endl;
    for (int i = 0; i < printConst; i++) {
        cout << "*";
    }
    cout << endl << endl;
}

void loginFunc(client *head) {
    return;
}

void SignUpFunc(client *head) {
    client *newUser = new client(head);
}

int welcomeFunc(client *head) {
    for (int i = 0; i < printConst; i++) {
        cout << '=';
    }
    cout << endl << endl;
    cout << "Please choose an option." << endl << endl;
    cout << "1 - Create New Account (Signup)" << endl << "    Select this if you're new here" << endl << endl;
    cout << "2 - Login to Existing Account" << endl << "    Choose this if you already have an account" << endl << endl;
    cout << "3 - Exit " << endl << "    Choose this to exit the program" << endl << endl;
    for (int i = 0; i < printConst; i++) {
        cout << '=';
    }
    cout << endl << endl;
    cout << "Enter your choice (1/2/3): ";
    string inp;
    getline(cin, inp);
    while (inp != "1" && inp != "2" && inp != "3") {
        cout << "Error: Invalid choice! Please enter 1 or 2 or 3 only." << endl;
        getline(cin, inp);
    }
    if (inp == "1") {
        SignUpFunc(head);
    }
    else if (inp == "2") {
        loginFunc(head);
    }
    else {
        cout << "   Thank you for using our system. Goodbye! " << endl;
        return 0;
    }
    return 1;
}

int main() {
    client *head = new client;
    while (welcomeFunc(head)) {
        continue;
    }
    delete head;
}
