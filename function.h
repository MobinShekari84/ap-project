#include <bits/stdc++.h>
using namespace std;

int containSpace(string s) {
    for (int i = 0; i < s.size(); i++) {
        if (s[i] == ' ') {
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