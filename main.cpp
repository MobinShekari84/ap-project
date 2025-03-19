#include <bits/stdc++.h>
using namespace std;

class client {
    private:
        string userName;
        string userId;
        string userPass;
        client *userNext;
    public:
        client();
        client(client*);
        client* getLast();
        int changeUserNext(client*);
        int checkUserId(string);
        void print();
};

client::client() {
    userName = "HEAD";
    userPass = "HEAD";
    userId = "HEAD";
    userNext = NULL;
}

client::client(client *head) {
    cout << "Username: " << endl;
    cin >> userName;
    cout << "User ID: " << endl;
    cin >> userId;
    while(head->checkUserId(userId) == 0) {
        cout << "ID has been taken, try again! " << endl << "User ID: " << endl;
        cin >> userId;
    }
    cout << "User Password" << endl;
    cin >> userPass;
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

int client::checkUserId(string id) {
    if (this->userId == id) {
        return 0;
    }
    if (this->userNext != NULL) {
        return this->userNext->checkUserId(id);
    }
    return 1;
}

void client::print() {
    cout << userName << ' ' << userId << ' ' << userPass << endl;
}

int main() {
    client *head = new client;
    do {
        cout << "signUp: " << endl;
        int x;
        cin >> x;
        if (x == -1) {
            break;
        }
        client *newUser = new client(head);
        head->getLast()->changeUserNext(newUser);
    } while (true);
}
