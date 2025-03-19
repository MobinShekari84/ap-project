#include <bits/stdc++.h>
#include "client.h"

using namespace std;

int SignUpFunc(client *head) {
    // =========== variable 
    int inp;
    string userName;
    string userId;
    string userPass;
    // ==================== 
    printSeparator(printConst);
    cout << "   Signup page";
    cout << endl;
    cout << endl;
    cout << "1. Create new account";
    cout << endl;
    cout << "2. Return to main menu";
    cout << endl;
    cout << "3. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(lowPrintConst);
    inp = getChoises(3);
    if (inp == 1) {
        do {
            cout << endl;
            cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
            cout << endl;
            cout << "Enter your desired username (no spaces or \\ allowed): ";
            getline(cin, userName);
            if (userName == "\\MENU\\") {
                return 1;
            }
            if (containSpaceSlash(userName)) {
                cout << "Error: Username cannot contain spaces or \\. Please try again.";
                cout << endl;
                cout << endl;
            }
        } while (containSpaceSlash(userName));
        do {
            cout << endl;
            cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
            cout << endl;
            cout << "Enter your desired user ID (numbers only): ";
            getline(cin, userId);
            if (userId == "\\MENU\\") {
                return 1;
            }
            if (containNumber(userId) == 1 || head->checkUserId(userId) == 0) {
                if (head->checkUserId(userId) == 0) {
                    cout << "Error: ID has been taken. Please try again.";
                    cout << endl;
                    cout << endl;
                }
                else {
                    cout << "Error: User ID must be a number. Please try again.";
                    cout << endl;
                    cout << endl;
                }
            }
        } while (containNumber(userId) == 1 || head->checkUserId(userId) == 0);
        do {
            cout << endl;
            cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
            cout << endl;
            cout << "Enter your desired password (no spaces or \\ allowed): ";
            getline(cin, userPass);
            if (userPass == "\\MENU\\") {
                return 1;
            }
            if (containSpaceSlash(userPass)) {
                cout << "Error: Password cannot contain spaces or \\. Please try again.";
                cout << endl;
                cout << endl;
            }
        } while (containSpaceSlash(userPass));
        client *newUser = new client(head, userName, userId, userPass);
        cout << "Thank you for signing up! You can now login with your credentials.";
        cout << endl;
        printSeparator(printConst);
        cout << endl;
        return 1;
    }
    else if (inp == 2) {
        return 1;
    }
    else {
        return 0;
    }
}

int loginFunc(client *head) {
    // =========== variable 
    int inp;
    string userName;
    string userPass;
    client *user;
    // ==================== 
    printSeparator(printConst);
    cout << "   Login Page";
    cout << endl;
    cout << endl;
    cout << "1. Login to you account";
    cout << endl;
    cout << "2. Return to main menu";
    cout << endl;
    cout << "3. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(lowPrintConst);
    inp = getChoises(3);
    if (inp == 1) {
        do {
            cout << endl;
            cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
            cout << endl;
            cout << "Enter your username: ";
            getline(cin, userName);
            if (userName == "\\MENU\\") {
                return 1;
            }
            cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
            cout << endl;
            cout << "Enter your password: ";
            getline(cin, userPass);
            if (userName == "\\MENU\\") {
                return 1;
            }
            user = head->getClinet(userName, userPass);
            if (user != NULL) {
                break;
            }
            cout << endl;
            cout << "Error: Invalid username or password. Please try again.";
            cout << endl;
        } while (user == NULL);
        cout << endl;
        printSeparator(printConst);
        cout << "   Login Successful!";
        cout << endl;
        cout << endl;
        printSeparator(printConst);
        cout << "Welcome back, " << user->getName() << '!' << endl;
        printSeparator(printConst);
        cout << endl;
        return 1;
    }
    else if (inp == 2) {
        return 1;
    }
    else {
        return 0;
    }
}


int welcomeFunc(client *head) {
    // =========== variable 
    int inp;
    // ==================== 
    printSeparator(printConst);
    cout << endl;
    cout << "Please choose an option.";
    cout << endl;
    cout << endl;
    cout << "1 - Create New Account (Signup)";
    cout << endl;
    cout << "   Select this if you're new here";
    cout << endl;
    cout << endl;
    cout << "2 - Login to Existing Account";
    cout << endl;
    cout << "   Choose this if you already have an account";
    cout << endl;
    cout << endl;
    cout << "3 - Exit ";
    cout << endl;
    cout << "    Choose this to exit the program";
    cout << endl;
    cout << endl;
    printSeparator(lowPrintConst);
    inp = getChoises(3);
    if (inp == 1) {
        return SignUpFunc(head);
    }
    else if (inp == 2) {
        return loginFunc(head);
    }
    else {
        return 0;
    }
}

int main() {
    client *head = new client;
    while (welcomeFunc(head)) {
        continue;
    }
    delete head;
}
