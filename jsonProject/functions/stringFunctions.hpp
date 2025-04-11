#ifndef STRINGFUNCTIONS_HPP
#define STRINGFUNCTIONS_HPP

#include <bits/stdc++.h>
using namespace std;

bool checkString(string input, bool (*f1)(char), bool (*f2)(char) = NULL, bool (*f3)(char) = NULL) {
    for (char charachter: input) {
        if (f1(charachter) == true) {
            continue;
        }
        if (f2 != NULL && f2(charachter) == 1) {
            continue;
        }
        if (f3 != NULL && f3(charachter) == 1) {
            continue;
        }
        return false;
    }
    return true;
}

bool containSpace(char charachter) {
    if (charachter == ' ') {
        return true;
    }
    return false;
}

bool containLetter(char charachter) {
    if (charachter >= 'a' && charachter <= 'z') {
        return true;
    }
    if (charachter >= 'A' && charachter <= 'Z') {   
        return true;
    }
    return false;
}

bool containNumber(char charachter) {
    if (charachter >= '0' && charachter <= '9') {
        return true;
    }
    return false;
}

bool containSpecialChar(char charachter) {
    if (charachter == '!' || charachter == '@' || charachter == '#' || charachter == '$' || charachter == '%' || charachter == '^' || charachter == '&' || charachter == '*' || charachter == '(' || charachter == ')' || charachter == '-' || charachter == '_' || charachter == '+' || charachter == '=' || charachter == '[' || charachter == ']' || charachter == '{' || charachter == '}' || charachter == '|' || charachter == '\\' || charachter == ':' || charachter == ';' || charachter == '"' || charachter == '<' || charachter == '>' || charachter == '.' || charachter == '?' || charachter == '/') {
        return true;
    }
    return false;
}

#endif