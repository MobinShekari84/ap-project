#pragma once
#include <bits/stdc++.h>
using namespace std;

int checkString(string input, int (*f1)(char), int (*f2)(char) = NULL, int (*f3)(char) = NULL) {
    for (char charachter: input) {
        if (f1(charachter) == 1) {
            continue;
        }
        if (f2 != NULL && f2(charachter) == 1) {
            continue;
        }
        if (f3 != NULL && f3(charachter) == 1) {
            continue;
        }
        return 0;
    }
    return 1;
}

int containSpace(char charachter) {
    if (charachter == ' ') {
        return 0;
    }
    return 1;
}

int containLetter(char charachter) {
    if (charachter >= 'a' && charachter <= 'z') {
        return 1;
    }
    if (charachter >= 'A' && charachter <= 'Z') {   
        return 1;
    }
    return 0;
}

int containNumber(char charachter) {
    if (charachter >= '0' && charachter <= '9') {
        return 1;
    }
    return 0;
}

int containSpecialChar(char charachter) {
    if (charachter == '!' || charachter == '@' || charachter == '_') {
        return 1;
    }
    return 0;
}