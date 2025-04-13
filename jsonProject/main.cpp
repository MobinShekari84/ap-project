#include <bits/stdc++.h>
#include "json/json.hpp"
#include "functions/printFunctions.hpp"
#include "user/user.hpp"
#include "user/student.hpp"
#include "user/teacher.hpp"
#include "exam/exam.hpp"

using namespace std;
using json = nlohmann::json;

User *loginStudent() {
    printSeparator(mediumPrintConst);
    cout << endl;
    cout << "Enter the student's name: ";
    string name;
    getline(cin, name);
    cout << "Enter the student's id: ";
    string id;
    getline(cin, id);
    cout << "Enter the student's password: ";
    string password;
    getline(cin, password);
    cout << endl;
    printSeparator(mediumPrintConst);
    ifstream file("users/students.json");
    json students;
    file >> students;
    file.close();
    for (auto &student : students["students"]) {
        if (student["name"] == name && student["id"] == id && student["password"] == password) {
            return new Student(id);
        }
    }
    return nullptr;
}

User *loginTeacher() {
    printSeparator(mediumPrintConst);
    cout << endl;
    cout << "Enter the teacher's name: ";
    string name;
    getline(cin, name);
    cout << "Enter the teacher's id: ";
    string id;
    getline(cin, id);
    cout << "Enter the teacher's password: ";
    string password;
    getline(cin, password);
    cout << endl;
    printSeparator(mediumPrintConst);
    ifstream file("users/teachers.json");
    json teachers;
    file >> teachers;
    file.close();
    for (auto &teacher : teachers["teachers"]) {
        if (teacher["name"] == name && teacher["id"] == id && teacher["password"] == password) {
            return new Teacher(id);
        }
    }
    return nullptr;
}

void createExam(User *user) {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "   Create exam";
    cout << endl;
    cout << endl;
    string examName;
    cout << "Enter the exam name: ";
    getline(cin, examName);
    int examCode;
    do {
        examCode = rand() % 1000000000;
        try {
            getExam(to_string(examCode));
        }
        catch (invalid_argument &e) {
            break;
        }
    } while (true);
    Exam exam(examName, examCode);
    cout << "Exam '" << examName << "' created with code '" << examCode << "' successfully.";
    cout << endl;
    cout << endl;
    int option;
    do {
        createExamPrint();
        option = getChoises(4);
        if (option == 1) {
            try {
                exam.addQuestion();
            }
            catch (invalid_argument &e) {
                cout << e.what() << endl;
            }
        }
        if (option == 2) {
            try {
                exam.removeQuestion();
            }
            catch (invalid_argument &e) {
                cout << e.what() << endl;
            }
        }
        if (option == 3) {
            cout << exam;
        }
    } while (option != 4);
    ofstream file("exam/" + to_string(examCode) + ".json");
    file << exam.getExamJson().dump(4);
    file.close();
    cout << "Exam created successfully." << endl;
    cout << endl;
    user->addExam(examCode);
    printSeparator(mediumPrintConst);
}

void viewExams(User *user, bool student) {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "   View exams";
    cout << endl;
    cout << endl;
    ifstream file("users/" + user->getUserId() + ".json");
    json userJson;
    file >> userJson;
    file.close();
    cout << "Exam codes: " << endl;
    for (auto &exam : userJson["exams"]) {
        cout << exam << endl;
    }
    cout << endl;
    cout << "Enter the exam code to view: ";
    string examCode;
    getline(cin, examCode);
    Exam *exam;
    try {
        user->findExam(examCode);
        exam = getExam(examCode);
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }
    if (student) {
        exam->hideInformations();
    }
    cout << *exam;
    delete exam;
    cout << endl;
    printSeparator(longPrintConst);
}

bool teacherMenu(User *user) {
    teacherMenuPrint();
    int option = getChoises(3);
    if (option == 1) {
        createExam(user);
        return true;
    }
    if (option == 2) {
        viewExams(user, false);
        return true;
    }
    return false;
}

void addExamStudent(User *user) {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "Add an exam";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
    cout << endl;
    cout << "Enter the exam code: ";
    string examCode;
    getline(cin, examCode);
    try {
        Exam *exam = getExam(examCode);
        user->addExam(exam->getExamCode());
        cout << "Exam added successfully." << endl;
        cout << endl;
        delete exam;
        printSeparator(mediumPrintConst);
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }
}

void participateInExam(User *user) {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "Participate in an exam";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
    cout << endl;
    cout << "Enter the exam code: ";
    string examCode;
    getline(cin, examCode);
    Exam *exam;
    try {
        user->findExam(examCode);
        exam = getExam(examCode);
        exam->participate(user);
        delete exam;
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }
    cout << endl;
    printSeparator(longPrintConst);
}

void viewResults(User *user) {
    printSeparator(longPrintConst);
    cout << endl;
    cout << "View results";
    cout << endl;
    cout << endl;
    printSeparator(longPrintConst);
    user->showResultsInfo();
    cout << endl;
    cout << "Enter the exam code to view: ";
    string examCode;
    getline(cin, examCode);
    try {
        user->findResult(examCode);
        user->showResult(examCode);
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return;
    }
}

bool studentMenu(User *user) {
    studentMenuPrint();
    int option = getChoises(5);
    if (option == 1) {
        addExamStudent(user);
        return true;
    }
    if (option == 2) {
        viewExams(user, true);
        return true;
    }
    if (option == 3) {
        participateInExam(user);
        return true;
    }
    if (option == 4) {
        viewResults(user);
        return true;
    }
    return false;
}

bool login() {
    loginPrint();
    int option = getChoises(3);
    if (option == 1) {
        User *user = loginStudent();
        if (user != nullptr) {
            printSeparator(mediumPrintConst);
            cout << endl;
            cout << "Login successful" << endl;
            cout << endl;
            printSeparator(mediumPrintConst);
            while (studentMenu(user) == true);
            delete user;
            return true;
        }
        else {
            printSeparator(mediumPrintConst);
            cout << endl;
            cout << "Login failed. Please try again." << endl;
            cout << endl;
            printSeparator(mediumPrintConst);
            return false;
        }
    }
    if (option == 2) {
        User *user = loginTeacher();
        if (user != nullptr) {
            printSeparator(mediumPrintConst);
            cout << endl;
            cout << "Login successful" << endl;
            cout << endl;
            printSeparator(mediumPrintConst);
            while (teacherMenu(user) == true);
            delete user;
            return true;
        }
        else {
            printSeparator(mediumPrintConst);
            cout << endl;
            cout << "Login failed. Please try again." << endl;
            cout << endl;
            printSeparator(mediumPrintConst);
            return false;
        }
    }
    return true;
}

bool createStudent() {
    printSeparator(longPrintConst);
    try {
        Student student;
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return false;
    }
    printSeparator(mediumPrintConst);
    cout << endl;
    cout << "User created successfully" << endl;
    cout << endl;
    printSeparator(mediumPrintConst);
    return true;
}

bool createTeacher() {
    printSeparator(longPrintConst);
    try {
        Teacher teacher;
    }
    catch (invalid_argument &e) {
        cout << e.what() << endl;
        return false;
    }
    printSeparator(mediumPrintConst);
    cout << endl;
    cout << "User created successfully" << endl;
    cout << endl;
    printSeparator(mediumPrintConst);
    return true;
}

bool signUp() {
    signUpPrint();
    int option = getChoises(3);
    if (option == 1) {
        return createStudent();
    }
    if (option == 2) {
        return createTeacher();
    }
    return true;
}


bool welcome() {
    welcomePrint();
    int option = getChoises(3);
    if (option == 1) {
        while (signUp() == false);
        return true;
    }
    if (option == 2) {
        while (login() == false);
        return true;
    }
    return false;
}

int main() {
    srand(time(NULL));
    while (welcome() == true) {
        continue;
    }
    return 0;
}