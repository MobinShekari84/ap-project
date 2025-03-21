#include <bits/stdc++.h>
#include "input.h"

using namespace std;

int teacherFunc(client *user) {
    string examName;
    string question;
    string answer;
    int examCode;
    int inp;
    int questionNumber;
    int ind;
    cout << "   Teacher's Page";
    cout << endl;
    cout << endl;
    cout << "1. Create exam";
    cout << endl;
    cout << "2. View exams";
    cout << endl;
    cout << "3. Return to main menu";
    cout << endl;
    cout << "4. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(lowPrintConst);
    inp = getChoises(4);
    if (inp == 1) {
        printSeparator(printConst);
        cout << endl;
        cout << "   Create exam";
        cout << endl;
        cout << endl;
        cout << "Enter the exam name: ";
        getline(cin, examName);
        cout << endl;
        examCode = rand();
        cout << "Exam \\" << examName << "\\ created with code \\" << examCode << "\\ successfully.";
        cout << endl;
        printSeparator(printConst);
        questionNumber = 0;
        linkedListString *examQuestions = new linkedListString;
        linkedListString *examAnswers = new linkedListString;
        do {
            cout << endl;
            cout << "1. Add question";
            cout << endl;
            cout << "2. Remove question";
            cout << endl;
            cout << "3. Save and quit";
            cout << endl;
            cout << endl;
            inp = getChoises(3);
            if (inp == 1) {
                printSeparator(lowPrintConst);
                cout << "   Add question";
                cout << endl;
                cout << endl;
                cout << "Enter the question text: ";
                getline(cin, question);
                cout << endl;
                cout << "Enter the answer: ";
                getline(cin, answer);
                new linkedListString(examQuestions, question);
                new linkedListString(examAnswers, answer);
                cout << endl;
                cout << endl;
                printSeparator(lowPrintConst);
                questionNumber++;
            }
            else if (inp == 2) {
                printSeparator(lowPrintConst);
                cout << "   Remove question";
                cout << endl;
                cout << endl;
                cout << "Enter the index of question to remove: ";
                ind = getChoises(questionNumber);
                cout << endl;
                printSeparator(lowPrintConst);
            }
        } while (inp != 3);
        user->addExam(examName, examCode, examQuestions, examAnswers, questionNumber);
        return 2;
    }
    else if (inp == 2) {
        return 2;
    }
    else if (inp == 3) {
        return 1;
    }
    else {
        return 0;
    }
}

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
        if (user->isTeacher()) {
            do {
                inp = teacherFunc(user);
            } while (inp == 2);
        }
        return inp;
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
    srand(time(0));
    client *head = new client;
    while (welcomeFunc(head)) {
        continue;
    }
    delete head;
}
