#include <bits/stdc++.h>
#include "client.h"

using namespace std;

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
