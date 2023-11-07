#include <iostream>
using namespace std;

// Node structure for the singly linked list
struct Node {
    int data;
    int priority;
    Node* next;
};

class PriorityQueue {
private:
    Node* head;

public:
    PriorityQueue() {
        head = nullptr;
    }

    // Function to push an element into the priority queue
    void push(int data, int priority) {
        Node* newNode = new Node;
        newNode->data = data;
        newNode->priority = priority;
        newNode->next = nullptr;

        if (head == nullptr || priority < head->priority) {
            newNode->next = head;
            head = newNode;
        } else {
            Node* current = head;
            while (current->next != nullptr && current->next->priority <= priority) {
                current = current->next;
            }
            newNode->next = current->next;
            current->next = newNode;
        }
    }

    // Function to pop the element with the highest priority
    int pop() {
        if (isEmpty()) {
            cout << "Priority queue is empty. Cannot pop." << endl;
            return -1; // Return a sentinel value to indicate an empty queue
        }

        Node* temp = head;
        int data = temp->data;
        head = head->next;
        delete temp;

        return data;
    }

    // Function to check if the priority queue is empty
    bool isEmpty() {
        return head == nullptr;
    }

    // Function to display the priority queue
    void display() {
        Node* current = head;
        while (current != nullptr) {
            cout << "Data: " << current->data << " Priority: " << current->priority << endl;
            current = current->next;
        }
    }
};

int main() {
    PriorityQueue pq;

    // Push elements with priorities
    pq.push(10, 2);
    pq.push(20, 1);
    pq.push(30, 3);
    pq.push(40, 2);

    cout << "Priority Queue Contents:" << endl;
    pq.display();

    // Pop elements
    cout << "Popping the highest priority element: " << pq.pop() << endl;
    cout << "Popping the highest priority element: " << pq.pop() << endl;

    cout << "Priority Queue Contents after popping:" << endl;
    pq.display();

    return 0;
}
