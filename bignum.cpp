#include <iostream>
#include <string>
using namespace std;

// Node structure for a linked list
struct Node {
    int digit;
    Node* next;
};

// Function to insert a digit into the linked list
void insertDigit(Node*& head, int digit) {
    Node* newNode = new Node;
    newNode->digit = digit;
    newNode->next = nullptr;

    if (head == nullptr) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next != nullptr) {
            current = current->next;
        }
        current->next = newNode;
    }
}

// Function to display the linked list
void displayLinkedList(Node* head) {
    if (head == nullptr) {
        cout << "The linked list is empty." << endl;
        return;
    }

    Node* current = head;
    while (current != nullptr) {
        cout << current->digit;
        current = current->next;
    }
    cout << endl;
}

int main() {
    string bigNumber;
    cout << "Enter a large integer number: ";
    cin >> bigNumber;

    Node* linkedList = nullptr;

    // Iterate through the string and insert each digit into the linked list
    for (char digitChar : bigNumber) {
        int digit = digitChar - '0'; // Convert character to integer
        insertDigit(linkedList, digit);
    }

    cout << "Linked List Representation of the Number: ";
    displayLinkedList(linkedList);

    // Clean up the linked list
    Node* current = linkedList;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }

    return 0;
}
