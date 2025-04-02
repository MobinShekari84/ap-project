#include <bits/stdc++.h>
#include "input.h"

using namespace std;

int teacherFunc(client *head, client *user) {
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
            cout << "3. View exam";
            cout << endl;
            cout << "4. Save and quit";
            cout << endl;
            cout << endl;
            inp = getChoises(4);
            if (inp == 1) {
                printSeparator(lowPrintConst);
                cout << "   Add question";
                cout << endl;
                cout << endl;
                cout << "Enter the question text: ";
                getline(cin, question);
                do {
                    cout << endl;
                    cout << "Enter the answer (should be a number): ";
                    getline(cin, answer);
                    if (containNumber(answer) == 1) {
                        cout << "Error: Answer is not a number. Please try again.";
                        cout << endl;
                    }
                } while(containNumber(answer) == 1);
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
                delete (examQuestions->deleteInd(ind));
                delete (examAnswers->deleteInd(ind));
                questionNumber--;
                printSeparator(lowPrintConst);
            }
            else if (inp == 3) {
                cout << endl;
                cout << "Exam name: " << examName << " - Exam code: " << examCode << " - Number of questions: " << questionNumber;
                cout << endl;
                cout << endl;
                printSeparator(lowPrintConst);
                for (int i = 1; i <= questionNumber; i++) {
                    cout << "Question number " << i << ": ";
                    examQuestions->print(i);
                    cout << endl;
                    cout << "Answer: ";
                    examAnswers->print(i);
                    cout << endl;
                    cout << endl;
                    printSeparator(lowPrintConst);
                }
                cout << endl;
            }
        } while (inp != 4);
        user->addExam(examName, examCode, examQuestions, examAnswers, questionNumber);
        return 2;
    }
    else if (inp == 2) {
        string inpCode;
        examList *exam;
        do {
            user->showExams();
            do {
                cout << "To return back, type \\MENU\\ with \\ included.";
                cout << endl;
                cout << "Enter exam code (should only contain number): ";
                getline(cin, inpCode);
                if (containNumber(inpCode) && inpCode != "\\MENU\\") {
                    cout << "Error: exam code contains only numbers. Please try again.";
                    cout << endl;
                    cout << endl;
                }
            } while (containNumber(inpCode) && inpCode != "\\MENU\\");
            if (inpCode != "\\MENU\\") {
                exam = user->searchExamCode(inpCode);
                if (exam != NULL) {
                    exam->print(1);
                    printSeparator(printConst);
                }
                else {
                    cout << "Error: there is no exam with this code. Please try again.";
                    cout << endl;
                }
            }
        } while (inpCode != "\\MENU\\" && exam == NULL);
        return 2;
    }
    else if (inp == 3) {
        return 1;
    }
    else {
        return 0;
    }
}

int studentFunc(client *head, client *user) {
    int inp;
    string inpCode;
    cout << "   Student's Page";
    cout << endl;
    cout << endl;
    cout << "1. Add an exam";
    cout << endl;
    cout << "2. View exams";
    cout << endl;
    cout << "3. Participate in an exam";
    cout << endl;
    cout << "4. Return to main menu";
    cout << endl;
    cout << "5. Exit Programm";
    cout << endl;
    cout << endl;
    printSeparator(lowPrintConst);
    inp = getChoises(5);
    if (inp == 1) {
        printSeparator(printConst);
        cout << endl;
        cout << "   Add an exam";
        cout << endl;
        cout << endl;
        examList *exam;
        do {
            do {
                cout << "To return back, type \\MENU\\ with \\ included.";
                cout << endl;
                cout << "Enter the exam code (should only contain numbers): ";
                getline(cin, inpCode);
                cout << endl;
                if (containNumber(inpCode) && inpCode != "\\MENU\\") {
                    cout << "Error: exam code contains only numbers. Please try again.";
                    cout << endl;
                    cout << endl;
                }
            } while (containNumber(inpCode) && inpCode != "\\MENU\\");
            if (inpCode != "\\MENU\\") {
                exam = head->searchExamCode(inpCode);
                if (exam != NULL) {
                    exam->print(2);
                    user->addExamCode(inpCode);
                    printSeparator(printConst);
                }
                else {
                    cout << "Error: there is no exam with this code. Please try again.";
                    cout << endl;
                }
            }
        } while (inpCode != "\\MENU\\" && exam == NULL);
        return 2;
    }
    else if (inp == 2) {
        user->showExams(head);
        return 2;
    }
    else if (inp == 3) {
        printSeparator(printConst);
        cout << endl;
        cout << "   Participate in an exam";
        cout << endl;
        cout << endl;
        examList *exam;
        do {
            do {
                cout << "To return back, type \\MENU\\ with \\ included.";
                cout << endl;
                cout << "Enter the exam code you've registered (should only contain numbers): ";
                getline(cin, inpCode);
                cout << endl;
                if (containNumber(inpCode) && inpCode != "\\MENU\\") {
                    cout << "Error: exam code contains only numbers. Please try again.";
                    cout << endl;
                    cout << endl;
                }
            } while (containNumber(inpCode) && inpCode != "\\MENU\\");
            if (inpCode != "\\MENU\\") {
                exam = user->getExam(inpCode, head);
                if (exam != NULL && exam->getQuestionNumber() > 0) {
                    int correctAnswers = exam->participateExam();
                    printSeparator(printConst);
                    printSeparator(printConst);
                    cout << endl;
                    cout << "Your score is " << (1.0 * correctAnswers) / (1.0 * exam->getQuestionNumber());
                    cout << endl;
                    cout << endl;
                    printSeparator(printConst);
                    printSeparator(printConst);
                }
                else if (exam->getQuestionNumber() <= 0) {
                    printSeparator(printConst);
                    printSeparator(printConst);
                    cout << endl;
                    cout << "Exam has no questions!";
                    cout << endl;
                    cout << endl;
                    printSeparator(printConst);
                    printSeparator(printConst);
                }
                else {
                    cout << "Error: there is no exam with this code. Please try again.";
                    cout << endl;
                }
            }
        } while (inpCode != "\\MENU\\" && exam == NULL);
        return 2;
    }
    else if (inp == 4) {
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
        printSeparator(printConst);
        cout << endl;
        cout << "   Signup Successful!";
        cout << endl;
        cout << endl;
        cout << "Thank you for signing up! You can now login with your credentials.";
        cout << endl;
        cout << endl;
        newUser->print();
        cout << endl;
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
                inp = teacherFunc(head, user);
            } while (inp == 2);
        }
        else {
            do {
                inp = studentFunc(head, user);
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
