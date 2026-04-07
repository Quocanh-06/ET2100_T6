#include <iostream>
#include <string>

using namespace std;

struct File {
    string name;
    long long size;
    int time;
};

struct Node {
    File data;
    Node* next;
};

void insertByTime(Node* &head, File f) {
    Node* newNode = new Node{f, nullptr};
    if (!head || head->data.time >= f.time) {
        newNode->next = head;
        head = newNode;
        return;
    }
    Node* curr = head;
    while (curr->next && curr->next->data.time < f.time) {
        curr = curr->next;
    }
    newNode->next = curr->next;
    curr->next = newNode;
}

int main() {
    Node* list = nullptr;
    cout << "Da khoi tao danh sach lien ket quan ly file." << endl;
    // Thêm các thao tác khác tại đây...
    return 0;
}
