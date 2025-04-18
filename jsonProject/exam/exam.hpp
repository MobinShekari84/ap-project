#ifndef EXAM_HPP
#define EXAM_HPP

#include <bits/stdc++.h>
#include "../functions/printFunctions.hpp"
#include "../functions/stringFunctions.hpp"
#include "../json/json.hpp"

using namespace std;
using json = nlohmann::json;

class Exam {
    private:
        string examName;
        int examCode;
        vector <string> questions;
        vector <json> answers;
        vector <json> results;
    public:
        Exam(string examName, int examCode);
        Exam(string examName, int examCode, vector <string> questions, vector <json> answers);
        Exam(json examJson);
        Exam(int examCode);
        ~Exam();
        void addQuestion();
        void removeQuestion();
        friend ostream& operator<<(ostream& os, Exam& exam);
        json getExamJson();
        void hideInformations();
        int getExamCode();
        void participate(User *user);
        void addMultipleChoiceQuestion(string question);
        void addShortAnswerQuestion(string question);
        void addLongAnswerQuestion(string question);
        void addResult(int examCode, string userId, int totalPoints, int correctPoints, int negativePoints, vector <string> userLongAnswers, vector <pair <int, bool>> usersAnswers);
        string getAnswer(int questionNumber);
        int findRank(int score);
        double findAverage();
        int findHighest();
        void showResults(ostream& os);
};

Exam::Exam(string examName, int examCode) : examName(examName), examCode(examCode) {
}

Exam::Exam(string examName, int examCode, vector <string> questions, vector <json> answers) : examName(examName), examCode(examCode), questions(questions), answers(answers) {
    results.resize(0);
}

Exam::Exam(json examJson) {
    examName = examJson["examName"].get<string>();
    examCode = examJson["examCode"].get<int>();
    questions.resize(examJson["questions"].size());
    answers.resize(examJson["answers"].size());
    results.resize(examJson["results"].size());
    copy(examJson["questions"].begin(), examJson["questions"].end(), questions.begin());
    copy(examJson["answers"].begin(), examJson["answers"].end(), answers.begin());
    copy(examJson["results"].begin(), examJson["results"].end(), results.begin());
}   

Exam::~Exam() {
}

Exam::Exam(int examCode) {
    fstream file("exam/" + to_string(examCode) + ".json");
    json examJson;
    file >> examJson;
    examName = examJson["examName"].get<string>();
    this->examCode = examJson["examCode"].get<int>();
    questions.resize(examJson["questions"].size());
    answers.resize(examJson["answers"].size());
    results.resize(examJson["results"].size());
    copy(examJson["questions"].begin(), examJson["questions"].end(), questions.begin());
    copy(examJson["answers"].begin(), examJson["answers"].end(), answers.begin());
    copy(examJson["results"].begin(), examJson["results"].end(), results.begin());
    file.close();
}

Exam* getExam(string examCode) {
    ifstream file("exam/" + examCode + ".json");
    if (!file.is_open()) {
        throw invalid_argument("Exam not found.");
    }
    json examJson;
    file >> examJson;
    file.close();
    return new Exam(examJson);
}

void Exam::addMultipleChoiceQuestion(string question) {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Enter the number of options (between 2 and 5): ";
    string numberOfOptions;
    getline(cin, numberOfOptions);
    if (checkString(numberOfOptions, containNumber) == false) {
        throw invalid_argument("Invalid number of options. Number of options must be a number.");
    }
    int numberOfOptionsInt = stoi(numberOfOptions);
    if (numberOfOptionsInt < 2 || numberOfOptionsInt > 5) {
        throw invalid_argument("Invalid number of options. Number of options must be between 2 and 5.");
    }
    json optionJson;
    optionJson["type"] = "multipleChoice";
    for (int i = 0; i < numberOfOptionsInt; i++) {
        cout << "Enter the option " << i + 1 << ": ";
        string option;
        getline(cin, option);
        optionJson["options"].push_back(option);
    }
    cout << "Enter the correct option: ";
    string correctOption;
    getline(cin, correctOption);
    if (checkString(correctOption, containNumber) == false) {
        throw invalid_argument("Invalid correct option. Correct option must be a number.");
    }
    int correctOptionInt = stoi(correctOption);
    if (correctOptionInt < 1 || correctOptionInt > numberOfOptionsInt) {
        throw invalid_argument("Invalid correct option. Correct option must be between 1 and " + to_string(numberOfOptionsInt) + ".");
    }
    cout << "Enter the points for this question: ";
    string points;
    getline(cin, points);
    if (checkString(points, containNumber) == false) {
        throw invalid_argument("Invalid points. Points must be a number.");
    }
    int pointsInt = stoi(points);
    if (pointsInt < 0) {
        throw invalid_argument("Invalid points. Points must be a positive number.");
    }
    cout << "Enter the negative points for this question: ";
    string negativePoints;
    getline(cin, negativePoints);
    if (checkString(negativePoints, containNumber) == false) {
        throw invalid_argument("Invalid penalty. Penalty must be a number.");
    }
    int negativePointsInt = stoi(negativePoints) * -1;
    if (negativePointsInt > 0) {
        throw invalid_argument("Invalid penalty. Penalty mustn't be positive.");
    }
    optionJson["answer"] = correctOptionInt;
    optionJson["points"] = pointsInt;
    optionJson["negativePoints"] = negativePointsInt;
    answers.push_back(optionJson);
    questions.push_back(question);
}

void Exam::addShortAnswerQuestion(string question) {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Enter the short answer (answer only contain numbers): ";
    string answer;
    getline(cin, answer);
    if (checkString(answer, containNumber) == false) {
        throw invalid_argument("Invalid answer. Answer must contain only numbers.");
    }
    cout << "Enter the points for this question: "; 
    string points;
    getline(cin, points);
    if (checkString(points, containNumber) == false) {
        throw invalid_argument("Invalid points. Points must be a number.");
    }
    int pointsInt = stoi(points);
    if (pointsInt < 0) {
        throw invalid_argument("Invalid points. Points must be a positive number.");
    }
    cout << "Enter the negative points for this question: ";
    string negativePoints;
    getline(cin, negativePoints);
    if (checkString(negativePoints, containNumber) == false) {
        throw invalid_argument("Invalid penalty. Penalty must be a number.");
    }
    int negativePointsInt = stoi(negativePoints) * -1;
    if (negativePointsInt > 0) {
        throw invalid_argument("Invalid penalty. Penalty mustn't be positive.");
    }
    questions.push_back(question);
    json answerJson;
    answerJson["type"] = "shortAnswer";
    answerJson["answer"] = answer;
    answerJson["points"] = pointsInt;
    answerJson["negativePoints"] = negativePointsInt;
    answers.push_back(answerJson);
}

void Exam::addLongAnswerQuestion(string question) {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Enter the long answer: ";
    string answer;
    getline(cin, answer);
    questions.push_back(question);
    cout << "Enter the points for this question: ";
    string points;
    getline(cin, points);
    if (checkString(points, containNumber) == false) {
        throw invalid_argument("Invalid points. Points must be a number.");
    }
    int pointsInt = stoi(points);
    if (pointsInt < 0) {
        throw invalid_argument("Invalid points. Points must be a positive number.");
    }
    json answerJson;
    answerJson["type"] = "longAnswer";
    answerJson["answer"] = answer;
    answerJson["points"] = pointsInt;
    answers.push_back(answerJson);
}

void Exam::addQuestion() {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Enter the question: ";
    string question;
    getline(cin, question);
    printSeparator(shortPrintConst);
    cout << endl;
    cout << endl;
    cout << "1. multiple choice";
    cout << endl;
    cout << "2. short answer";
    cout << endl;
    cout << "3. long answer";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
    cout << endl;
    int input = getChoises(3);
    if (input == 1) {
        addMultipleChoiceQuestion(question);
    }
    if (input == 2) {
        addShortAnswerQuestion(question);
    }
    if (input == 3) {
        addLongAnswerQuestion(question);
    }
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Question added successfully.";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
}

void Exam::removeQuestion() {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Enter the question number to remove.";
    cout << endl;
    cout << endl;
    int questionNumber = getChoises(questions.size());
    questions.erase(questions.begin() + questionNumber - 1);
    answers.erase(answers.begin() + questionNumber - 1);
    cout << endl;
    cout << "Question removed successfully.";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
}   

ostream& operator<<(ostream& os, Exam& exam) {
    printSeparator(shortPrintConst);
    cout << endl;
    cout << "Exam: " << exam.examName;
    cout << endl;
    cout << endl;
    for (int i = 0; i < exam.questions.size(); i++) {
        cout << "Question " << i + 1 << ": " << exam.questions[i];
        cout << endl;
        cout << "Type: " << exam.answers[i]["type"].get<string>();
        cout << endl;
        if (exam.answers[i]["type"].get<string>() == "multipleChoice") {
            cout << "Options: ";
            for (int j = 0; j < exam.answers[i]["options"].size(); j++) {
                cout << j + 1 << ". " << exam.answers[i]["options"][j].get<string>();
                cout << "\t";
            }
            cout << endl;
            cout << "Answer: " << exam.answers[i]["answer"].get<int>();
            cout << endl;
        }
        if (exam.answers[i]["type"] == "shortAnswer") {
            cout << "Answer: " << exam.answers[i]["answer"].get<string>();
            cout << endl;
        }
        if (exam.answers[i]["type"] == "longAnswer") {
            cout << "Answer: " << exam.answers[i]["answer"].get<string>();
            cout << endl;
        }
        cout << "Points: " << exam.answers[i]["points"].get<int>();
        cout << endl;
        if (exam.answers[i]["type"].get<string>() != "longAnswer") {
            cout << "Negative Points: " << exam.answers[i]["negativePoints"].get<int>();
            cout << endl;
        }
        cout << endl;
        cout << endl;
    }
    printSeparator(shortPrintConst);
    return os;
}

string Exam::getAnswer(int questionNumber) {
    if (questionNumber < 1 || questionNumber > questions.size()) {
        throw invalid_argument("Invalid question number. Question number must be between 1 and " + to_string(questions.size()) + ".");
    }
    if (answers[questionNumber - 1]["type"].get<string>() == "multipleChoice") {
        return answers[questionNumber - 1]["options"][answers[questionNumber - 1]["answer"].get<int>() - 1].get<string>();
    }
    return answers[questionNumber - 1]["answer"].get<string>();
}

void Exam::hideInformations() {
    for (int i = 0; i < questions.size(); i++) {
        questions[i] = "**********";
    }
    for (int i = 0; i < answers.size(); i++) {
        if (answers[i]["type"].get<string>() == "multipleChoice") {
            answers[i]["answer"] = 0;
            for (int j = 0; j < answers[i]["options"].size(); j++) {
                answers[i]["options"][j] = "**********";
            }
        }
        else {
            answers[i]["answer"] = "**********";
        }
    }
}

json Exam::getExamJson() {
    json exam;
    exam["examName"] = examName;
    exam["examCode"] = examCode;
    exam["questions"] = questions;
    exam["answers"] = answers;
    return exam;
}

int Exam::getExamCode() {
    return examCode;
}

void Exam::addResult(int examCode, string userId, int totalPoints, int correctPoints, int negativePoints, vector <string> userLongAnswers, vector <pair <int, bool>> usersAnswers) {
    json result;
    result["userId"] = userId;
    result["totalPoints"] = totalPoints;
    result["correctPoints"] = correctPoints;
    result["negativePoints"] = negativePoints;
    result["userLongAnswers"] = userLongAnswers;
    result["usersAnswers"] = usersAnswers;
    results.push_back(result);
    fstream file("exam/" + to_string(examCode) + ".json");
    json examJson;
    file >> examJson;
    examJson["results"].push_back(result);
    file.seekp(0);
    file << examJson.dump(4);
    file.close();
}

void Exam::participate(User *user) {
    cout << "Participating in exam " << examName << " with code " << examCode << ".";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
    vector <string> userLongAnswers;
    vector <pair <int, bool>> usersAnswers;
    cout << endl;
    int correctPoints = 0;
    int negativePoints = 0;
    int totalPoints = 0;
    for (int i = 0; i < questions.size(); i++) {
        cout << "Question " << i + 1 << ": " << questions[i];
        cout << endl;
        cout << "Type: " << answers[i]["type"].get<string>();
        cout << endl;
        if (answers[i]["type"].get<string>() == "multipleChoice") {
            cout << "Options: ";
            string correctAnswer = answers[i]["options"][answers[i]["answer"].get<int>() - 1];
            static std::random_device rd;
            static std::mt19937 g(rd());
            shuffle(answers[i]["options"].begin(), answers[i]["options"].end(), g);
            for (int j = 0; j < answers[i]["options"].size(); j++) {
                cout << j + 1 << ". " << answers[i]["options"][j].get<string>();
                cout << "\t";
                if (answers[i]["options"][j].get<string>() == correctAnswer) {
                    answers[i]["answer"] = j + 1;
                }
            }
            cout << endl;
            cout << "Enter the answer (number): ";
            string answer;
            getline(cin, answer);
            if (answer == to_string(answers[i]["answer"])) {
                correctPoints += answers[i]["points"].get<int>();
                usersAnswers.push_back(make_pair(i + 1, true));
            }
            else {
                negativePoints += answers[i]["negativePoints"].get<int>();
                usersAnswers.push_back(make_pair(i + 1, false));
            }
            totalPoints += answers[i]["points"].get<int>();
        }
        if (answers[i]["type"].get<string>() == "shortAnswer") {
            cout << "Enter the answer (answer only contain numbers): ";
            string answer;
            getline(cin, answer);
            if (answer == answers[i]["answer"].get<string>()) {
                correctPoints += answers[i]["points"].get<int>();
                usersAnswers.push_back(make_pair(i + 1, true));
            }
            else {
                negativePoints += answers[i]["negativePoints"].get<int>();
                usersAnswers.push_back(make_pair(i + 1, false));
            }
            totalPoints += answers[i]["points"].get<int>();
        }
        if (answers[i]["type"].get<string>() == "longAnswer") {
            cout << "Enter the answer: ";
            string answer;
            getline(cin, answer);
            userLongAnswers.push_back(answer);
        }
        cout << endl;
        cout << endl;
    }
    cout << "You got score " << correctPoints + negativePoints << " out of " << totalPoints << " for short answer and multiple choice questions.";
    user->addResult(examCode, totalPoints, correctPoints, negativePoints, questions.size(), userLongAnswers, usersAnswers);
    addResult(examCode, user->getUserId(), totalPoints, correctPoints, negativePoints, userLongAnswers, usersAnswers);
    cout << endl;
    cout << endl;
    cout << "Result added successfully.";
    cout << endl;
    cout << endl;
    printSeparator(shortPrintConst);
}

int Exam::findRank(int score) {
    sort(results.begin(), results.end(), [](json a, json b) {
        return a["correctPoints"].get<int>() + a["negativePoints"].get<int>() > b["correctPoints"].get<int>() + b["negativePoints"].get<int>();
    });
    for (int i = 0; i < results.size(); i++) {
        if (results[i]["correctPoints"].get<int>() + results[i]["negativePoints"].get<int>() == score) {
            return i + 1;
        }
    }
    return 0;
}

double Exam::findAverage() {
    int totalPoints = 0;
    for (int i = 0; i < results.size(); i++) {
        totalPoints += results[i]["correctPoints"].get<int>() + results[i]["negativePoints"].get<int>();
    }
    return 1.0 * totalPoints / results.size();
}

int Exam::findHighest() {
    sort(results.begin(), results.end(), [](json a, json b) {
        return a["correctPoints"].get<int>() + a["negativePoints"].get<int>() > b["correctPoints"].get<int>() + b["negativePoints"].get<int>();
    });
    return results[0]["correctPoints"].get<int>() + results[0]["negativePoints"].get<int>();
}

void Exam::showResults(ostream& os) {
    if (results.size() == 0) {
        throw invalid_argument("No results found.");
    }
    os << endl;
    os << "Exam code, " << examCode << endl;
    os << "Exam name, " << examName << endl;
    os << endl;
    os << results.size() << " results found." << endl;
    sort(results.begin(), results.end(), [](json a, json b) {
        return a["correctPoints"].get<int>() + a["negativePoints"].get<int>() > b["correctPoints"].get<int>() + b["negativePoints"].get<int>();
    });
    for (int i = 0; i < results.size(); i++) {
        os << "Result number " << i + 1 << "," << endl;
        os << ",User id, " << results[i]["userId"].get<string>() << endl;
        os << ",Exam result, ";
        os << "User got " << results[i]["correctPoints"].get<int>() + results[i]["negativePoints"].get<int>() << " out of " << results[i]["totalPoints"].get<int>() << endl;
        os << endl;
        os << endl;
    }
    os << endl;
    os << "Average score, " << findAverage() << endl;
    os << "Highest score, " << findHighest() << endl;
    os << endl;
}

#endif