#include <bits/stdc++.h>
using namespace std;

class client {
    private:
        string userName;
        string userId;
        string userPassword;
        client *userNext;
    public:
        client(int);
        client();
        client* getLast();
        int changeUserNext(client*);
};

client::client(int code) {
    userName = "HEAD";
    userNext = NULL;
}

client::client() {
    cout << "Username: " << endl;
    cin >> userName;
    cout << endl << "User ID: " << endl;
    cin >> userId;
    cout << endl << "User Password" << endl;
    cin >> userPassword;
    cout << endl;
    userNext = NULL;
}

client* client::getLast() {
    if (this->userNext != NULL) {
        return (*this).userNext->getLast();
    }
    return this;
}

int client::changeUserNext(client *userNext) {
    if (this->userNext != NULL) {
        return -1;
    }
    this->userNext = userNext;
    return 1;
}

int main() {
    client *head = new client(0);
    do {
        cout << "signUp: " << endl;
        int x;
        cin >> x;
        if (x == -1) {
            break;
        }
        client *newUser = new client;
        head->getLast()->changeUserNext(newUser);
    } while (true);
}