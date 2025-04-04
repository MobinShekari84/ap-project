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
        string getInd(int);
        int findString(string);
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

string linkedListString::getInd(int k) {
    if (ind == k) {
        return str;
    }
    else if (nextString == NULL) {
        return "NO IND FOUND";
    }
    return nextString->getInd(k);
}

int linkedListString::findString(string inpCode) {
    if (str == inpCode) {
        return ind;
    }
    else if (nextString == NULL) {
        return -1;
    }
    else {
        return nextString->findString(inpCode);
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
        void print(int onlyOne);
        void changeNextExam(examList *);
        void showExams();
        examList* searchExamCode(string);
        int participateExam();
        int getQuestionNumber();
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

void examList::print(int onlyOne = 0) {
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
        for (int i = 1; i <= examQuestionNumber && onlyOne != 2; i++) {
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
    if (this->nextExam != NULL && onlyOne == 0) {
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
        cout << endl;
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

examList* examList::searchExamCode(string inpCode) {
    string examCodeString = "";
    {
        int x = examCode;
        while (x > 0) {
            examCodeString = (char) (x % 10 + '0') + examCodeString;
            x /= 10;
        }
    }
    if (inpCode == examCodeString) {
        return this;
    }
    else if (nextExam != NULL) {
        return nextExam->searchExamCode(inpCode);
    }
    return NULL;
}

int examList::participateExam() {
    int *correctAnswers = new int[examQuestionNumber + 1];
    for (int i = 1; i <= examQuestionNumber; i++) {
        correctAnswers[i] = 0;
    }
    if (examName == "\\HEAD\\") {
        cout << "Error: exam is HEAD.";
        cout << endl;
    }
    else {
        cout << endl;
        cout << "Exam name: " << examName << " - Exam code: " << examCode << " - Number of questions: " << examQuestionNumber;
        cout << endl;
        cout << endl;
        printSeparator(lowPrintConst);
        for (int i = 1; i <= examQuestionNumber; i++) {
            cout << "Question number " << i << ": ";
            examQuestion->print(i);
            cout << endl;
            string ans;
            do {
                if (i > 1) {
                    cout << "Enter \\BACK\\ to return to previous question.";
                    cout << endl;
                }
                if (i < examQuestionNumber) {
                    cout << "Enter \\NEXT\\ to go to next question.";
                    cout << endl;
                }
                cout << "Enter your answer: ";
                getline(cin, ans);
                if (i > 1 && ans == "\\BACK\\") {
                    i -= 2;
                    break;
                }
                else if (i < examQuestionNumber && ans == "\\NEXT\\") {
                    break;
                }
                else if (containNumber(ans)) {
                    cout << "Error: answer contains only numbers. Please try again.";
                    cout << endl;
                    cout << endl;
                }
            } while (containNumber(ans));
            if (containNumber(ans) == 0 && examAnswer->getInd(i) == ans) {
                correctAnswers[i] = 1;
            }
            else if (containNumber(ans) == 0) {
                correctAnswers[i] = 0;
            }
            cout << endl;
            cout << endl;
            printSeparator(lowPrintConst);
        }
        cout << endl;
        printSeparator(printConst);
    }
    int numAnswer = 0;
    cout << endl;
    for (int i = 1; i <= examQuestionNumber; i++) {
        numAnswer += correctAnswers[i];
        cout << "question number " << i << " : " << (correctAnswers[i] ? "True" : "False") << endl;
    }
    return numAnswer;

}

int examList::getQuestionNumber() {
    return examQuestionNumber;
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
        virtual void showExams(client *);
        virtual examList* searchExamCode(string);
        virtual void addExamCode(string);
        virtual examList* getExam(string, client*);
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

void client::showExams(client *head) {
    cout << "Error: user is not student";
    cout << endl;
}

examList* client::searchExamCode(string inpCode) {
    if (this->userNext != NULL) {
        return this->userNext->searchExamCode(inpCode);
    }
    else {
        return NULL;
    }
}

void client::addExamCode(string examCode) {
    cout << "Error: user is not student.";
    cout << endl;
}

examList* client::getExam(string inpCode, client *head) {
    cout << "Error: user is not teacher";
    cout << endl;
    return NULL;
}


// ==================================================================
// ==================================================================
// ==================================================================

class student : public client {
    private: 
        string userStudyField;
        linkedListString *userExamCode;
        int numberOfExams;
    public:
        student(client*, string, string, string, string);
        virtual ~student();
        virtual void print();
        virtual void addExamCode(string);
        virtual void showExams(client *);
        examList* getExam(string, client*);
};

student::student(client *head, string userName, string userId, string userPass, string userStudyField) : client(head, userName, userId, userPass){
    this->userStudyField = userStudyField;
    userExamCode = new linkedListString;
    userTeacher = 0;
    numberOfExams = 0;
}

student::~student() {
    delete userExamCode;
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

void student::addExamCode(string examCode) {
    new linkedListString(userExamCode, examCode);
    numberOfExams++;
}

void student::showExams(client *head) {
    for (int i = numberOfExams; i > 0; i--) {
        examList *exam = head->searchExamCode(userExamCode->getInd(i));
        if (exam != NULL) {
            exam->print(2);
        }
    }
}

examList* student::getExam(string inpCode, client *head) {
    int ind = userExamCode->findString(inpCode);
    if (ind == -1) {
        return NULL;
    }
    else {
        return head->searchExamCode(userExamCode->getInd(ind));
    }
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
        virtual examList* searchExamCode(string);
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
    cout << "Courses: ";
    userCourse->print();
    cout << endl;
    cout << "User ID: " << this->userId;
    cout << endl;
    cout << "Password: ";
    for (int i = 0; i < userPass.size(); i++) {
        cout << "*";
    }
    //cout << endl;
    //this->userExam->print();
    cout << endl;
}

void teacher::addExam(string examName, int examCode, linkedListString *examQuestion, linkedListString *examAnswer, int questionNumber) {
    examList *newExam = new examList(this->userExam, examName, examCode, examQuestion, examAnswer, questionNumber);
    newExam->print();
}

void teacher::showExams() {
    userExam->showExams();
}

examList* teacher::searchExamCode(string inpCode) {
    examList *examOk = userExam->searchExamCode(inpCode);
    if (examOk == NULL) {
        if (userNext != NULL) {
            return userNext->searchExamCode(inpCode);
        }
        else {
            return NULL;
        }
    }
    else {
        return examOk;
    }
}