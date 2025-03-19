#include <bits/stdc++.h>
#include "class.h"
using namespace std;

string getUserName() {
    string userName;
    do {
        cout << endl;
        cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
        cout << endl;
        cout << "Enter your desired username (no spaces or \\ allowed): ";
        getline(cin, userName);
        if (userName == "\\MENU\\") {
            return userName;
        }
        if (containSpaceSlash(userName)) {
            cout << "Error: Username cannot contain spaces or \\. Please try again.";
            cout << endl;
            cout << endl;
        }
    } while (containSpaceSlash(userName));
    return userName;
}

string getUserId(client *head) {
    string userId;
    do {
        cout << endl;
        cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
        cout << endl;
        cout << "Enter your desired user ID (numbers only): ";
        getline(cin, userId);
        if (userId == "\\MENU\\") {
            return userId;
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
    return userId;
}

string getUserPass() {
    string userPass;
    do {
        cout << endl;
        cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
        cout << endl;
        cout << "Enter your desired password (no spaces or \\ allowed): ";
        getline(cin, userPass);
        if (userPass == "\\MENU\\") {
            return userPass;
        }
        if (containSpaceSlash(userPass)) {
            cout << "Error: Password cannot contain spaces or \\. Please try again.";
            cout << endl;
            cout << endl;
        }
    } while (containSpaceSlash(userPass));
    return userPass;
}

string getUserStudyField() {
    string userStudyField;
    do {
        cout << endl;
        cout << "**for return to main menu, type in \\MENU\\ with \\ included**";
        cout << endl;
        cout << "Enter your field of study (no spaces or \\ allowed):  ";
        getline(cin, userStudyField);
        if (userStudyField == "\\MENU\\") {
            return userStudyField;
        }
        if (containSpaceSlash(userStudyField)) {
            cout << "Error: Field of study cannot contain spaces or \\. Please try again.";
            cout << endl;
            cout << endl;
        }
    } while (containSpaceSlash(userStudyField));
    return userStudyField;
}