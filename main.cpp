#include <bits/stdc++.h>
#include "input.h"

using namespace std;

int SignUpFunc(client *head) {
    // =========== variable 
    int inp;
    client *newUser;
    linkedListString *userCourse;
    string userName;
    string userId;
    string userPass;
    string userStudyField;
    // ==================== 
    printSeparator(printConst);
    cout << "   Signup page";
    cout << endl;
    cout << endl;
    cout << "1. Sign up as a Student";
    cout << endl;
    cout << "2. Sign up as a Teacher";
    cout << endl;
    cout << "3. Return to main menu";
    cout << endl;
    cout << "4. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(lowPrintConst);
    inp = getChoises(4);
    if (inp == 1) {
        userName = getUserName(head);
        if (userName == "\\MENU\\") {
            return 1;
        }
        userStudyField = getUserStudyField();
        if (userStudyField == "\\MENU\\") {
            return 1;
        }
        userId = getUserId(head);
        if (userId == "\\MENU\\") {
            return 1;
        }
        userPass = getUserPass();
        if (userPass == "\\MENU\\") {
            return 1;
        }
        newUser = new student(head, userName, userId, userPass, userStudyField); 
    }
    if (inp == 2) {
        userName = getUserName(head);
        if (userName == "\\MENU\\") {
            return 1;
        }
        userCourse = getUserCourse();
        if (userCourse == NULL) {
            return 1;
        }
        userId = getUserId(head);
        if (userId == "\\MENU\\") {
            return 1;
        }
        userPass = getUserPass();
        if (userPass == "\\MENU\\") {
            return 1;
        }
        newUser = new teacher(head, userName, userId, userPass, userCourse);
    }
    if (inp == 1 || inp == 2) {
        cout << "Thank you for signing up! You can now login with your credentials.";
        cout << endl;
        printSeparator(printConst);
        cout << endl;
        printSeparator(printConst);
        cout << "   Signup Successful!" << endl;
        printSeparator(printConst);
        cout << endl;
        newUser->print();
        return 1;
    }
    else if (inp == 3) {
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
            if (user == NULL) {
                cout << endl;
                cout << "Error: Invalid username or password. Please try again.";
                cout << endl;
            }
        } while (user == NULL);
        cout << endl;
        printSeparator(printConst);
        cout << "   Login Successful!";
        cout << endl;
        cout << endl;
        printSeparator(printConst);
        cout << "Welcome back, " << user->getName() << '!' << endl;
        user->print();
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
