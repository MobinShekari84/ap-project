#pragma once
#include <bits/stdc++.h>
#include "commonFunctions.h"
using namespace std;

void welcomePrint() {
    printSeparator(longPrintConst);
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
    printSeparator(longPrintConst);
}

int welcome() {
    welcomePrint();
    int option = getChoises(3);
    if (option == 1) {
        return 1;
    }
    if (option == 2) {
        return 2;
    }
    return 0;
}