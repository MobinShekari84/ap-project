#include <bits/stdc++.h>
#include "welcome.h"
#include "commonFunctions.h"
#include "signUp.h"
#include "logIn.h"
using namespace std;

signed main() {
    int exitProgram = 0;
    do {
        exitProgram = welcome();
        if (exitProgram == 1) {
            exitProgram = signUp();
        }
        if (exitProgram == 2) {
            exitProgram = logIn();
        }
    } while (exitProgram != 0);
    return 0;
}