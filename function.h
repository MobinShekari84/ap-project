#include <bits/stdc++.h>
using namespace std;

const int printConst = 40;
const int lowPrintConst = 20;

void printSeparator(int var) {
    for (int i = 0; i < var; i++) {
        cout << '=';
    }
    cout << endl;
}

int getChoises(int k) {
    // =========== variable 
    string inp;
    int flag = 0;
    // ====================
    do {
        cout << "Enter your choice (";
        for (int i = 1; i <= k; i++) {
            cout << i;
            if (i != k) {
                cout << "/";
            }
        }
        cout << "): ";
        getline(cin, inp);
        for (int i = 1; i <= k; i++) {
            if (inp.size() == 1 && (inp[0] - '0') == i) {
                flag = 1;
            }
        }
        if (flag == 0) {
            cout << "Error: Invalid choice! Please enter 1 or 2 or 3 only.";
            cout << endl;
        }
    } while (!flag);
    return (inp[0] - '0');
}

int containSpaceSlash(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ' || s[i] == '\\') {
            return 1;
        }
    }
    return 0;
}

int containNumber(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] > '9' || s[i] < '0') {
            return 1;
        }
    }
    return 0;
}