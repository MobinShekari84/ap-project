#include <bits/stdc++.h>
#include "function.h"
using namespace std;

// ==================================================================
// ==================================================================
// ==================================================================

class linkedListString {
    protected:
        string str;
        int ind;
        linkedListString *nextString;
    public:
        linkedListString();
        linkedListString(linkedListString *, string);
        void changeNextString(linkedListString *);
        ~linkedListString();
        void print();
        void print(int);
        linkedListString* deleteInd(int);
        void addToInd(int);
};

linkedListString::linkedListString() {
    this->str = "\\HEAD\\";
    this->ind = 0;
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
        nextString->ind = this->ind + 1;
    }
}

void linkedListString::print() {
    if (this->str != "\\HEAD\\") {
        cout << this->str;
        cout << " ";
    }
    if (this->nextString != NULL) {
        this->nextString->print();
    }
}

void linkedListString::print(int ind) {
    if (this->ind == ind) {
        cout << this->str;
        cout << endl;
    }
    else if (this->ind < ind) {
        this->nextString->print(ind);
    }
    else {
        cout << "Error: there is no " << ind << " string.";
        cout << endl;
    }
}

linkedListString* linkedListString::deleteInd(int ind) {
    linkedListString *question;
    if (this->ind == ind) {
        if (this->nextString != NULL) {
            this->nextString->addToInd(-1);
        }
        return this;
    }
    else if ((this->ind + 1) == ind) {
        question = this->nextString->deleteInd(ind);
        this->nextString = this->nextString->nextString;
        question->nextString = NULL;
    }
    else {
        question = this->nextString->deleteInd(ind);
    }
    return question;
}

void linkedListString::addToInd(int k) {
    this->ind += k;
    if (this->nextString != NULL) {
        this->nextString->addToInd(k);
    }
}

// ==================================================================
// ==================================================================
// ==================================================================

class examList {
    private:
        string examName;
        int examCode;
        int examQuestionNumber;
        linkedListString *examQuestion;
        linkedListString *examAnswer;
        examList *nextExam;
    public:
        examList();
        examList(examList *, string, int, linkedListString *, linkedListString *, int);
        ~examList();
        void print();
        void changeNextExam(examList *);
        void showExams();
};

examList::examList() {
    examName = "\\HEAD\\";
    examCode = -1;
    examQuestionNumber = 0;
    nextExam = NULL;
}

examList::examList(examList *head, string examName, int examCode, linkedListString *examQuestion, linkedListString *examAnswer, int examQuestionNumber) {
    this->examName = examName;
    this->examCode = examCode;
    this->examQuestion = examQuestion;
    this->examAnswer = examAnswer;
    this->examQuestionNumber = examQuestionNumber;
    nextExam = NULL;
    head->changeNextExam(this);
}

examList::~examList() {
    if (this->nextExam != NULL) {
        delete this->nextExam;
    }
    delete this->examQuestion;
    delete this->examAnswer;
}

void examList::print() {
    if (examName == "\\HEAD\\") {
        printSeparator(lowPrintConst);
        cout << "Exam list: ";
        cout << endl;
        cout << endl;
    }
    if (examName != "\\HEAD\\") {
        cout << endl;
        cout << "Exam name: " << examName << " - Exam code: " << examCode << " - Number of questions: " << examQuestionNumber;
        cout << endl;
        cout << endl;
        printSeparator(lowPrintConst);
        for (int i = 1; i <= examQuestionNumber; i++) {
            cout << "Question number " << i << ": ";
            examQuestion->print(i);
            cout << endl;
            cout << "Answer: ";
            examAnswer->print(i);
            cout << endl;
            cout << endl;
            printSeparator(lowPrintConst);
        }
        cout << endl;
        printSeparator(printConst);
    }
    if (this->nextExam != NULL) {
        this->nextExam->print();
    }
    if (examName == "\\HEAD\\") {
        cout << endl;
        cout << "End of list.";
        cout << endl;
        printSeparator(lowPrintConst);
    }
}

void examList::changeNextExam(examList *nextExam) {
    if (this->nextExam != NULL) {
        this->nextExam->changeNextExam(nextExam);
    }
    else {
        this->nextExam = nextExam;
    }
}

void examList::showExams() {
    if (examName == "\\HEAD\\") {
        cout << "Exam codes: ";
    }
    else {
        cout << examCode << " - ";
    }
    if (this->nextExam != NULL) {
        this->nextExam->showExams();
    }
    if (examName == "\\HEAD\\") {
        cout << endl;
        printSeparator(lowPrintConst);
    }
}

// ==================================================================
// ==================================================================
// ==================================================================

class client {
    protected:
        string userName;
        string userId;
        string userPass;
        client *userNext;
        int userTeacher;
    public:
        client();
        client(client*, string, string, string);
        virtual ~client();
        void changeUserNext(client*);
        int checkUserId(string);
        string getName();
        int isNameTaken(string);
        virtual void print();
        client *getClinet(string, string);
        int isTeacher();
        virtual void addExam(string, int, linkedListString *, linkedListString *, int);
        virtual void showExams();
};

client::client() {
    userName = "\\HEAD\\";
    userPass = "\\HEAD\\";
    userId = "\\HEAD\\";
    userNext = NULL;
    userTeacher = -1;
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

int client::isNameTaken(string userName) {
    if (this->userName == userName) {
        return 1;
    }
    if (this->userNext != NULL) {
        return this->userNext->isNameTaken(userName);
    }
    return 0;
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

int client::isTeacher() {
    return userTeacher;
}

void client::addExam(string examName, int examCode, linkedListString *examQuestion, linkedListString *examAnswer, int questionNumber) {
    cout << "Error: user is not teacher.";
    cout << endl;
}

void client::showExams() {
    cout << "Error: user is not teacher.";
    cout << endl;
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
    userTeacher = 0;
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


class teacher : public client {
    private:
        linkedListString *userCourse;
        examList *userExam;
    public:
        teacher(client*, string, string, string, linkedListString*);
        virtual ~teacher();
        virtual void print();
        virtual void addExam(string, int, linkedListString *, linkedListString *, int);
        virtual void showExams();
};

teacher::teacher(client *head, string userName, string userId, string userPass, linkedListString *userCourse) : client(head, userName, userId, userPass) {
    this->userCourse = userCourse;
    this->userExam = new examList;
    userTeacher = 1;
}

teacher::~teacher() {
    if (this->userCourse != NULL) {
        delete this->userCourse;
        delete userExam;
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
    this->userExam->print();
    cout << endl;
}

void teacher::addExam(string examName, int examCode, linkedListString *examQuestion, linkedListString *examAnswer, int questionNumber) {
    examList *newExam = new examList(this->userExam, examName, examCode, examQuestion, examAnswer, questionNumber);
    newExam->print();
}

void teacher::showExams() {
    userExam->showExams();
}