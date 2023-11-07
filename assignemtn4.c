#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

typedef struct Node Node;

Node* createNode(int data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    if (newNode) {
        newNode->data = data;
        newNode->prev = NULL;
        newNode->next = NULL;
    }
    return newNode;
}

Node* createLinkedListFromNumber(int number) {
    char numberStr[20]; 
    sprintf(numberStr, "%d", number);

    int length = strlen(numberStr);
    Node* head = NULL;
    Node* tail = NULL;

    for (int i = length - 1; i >= 0; i -= 4) {
        int segment = 0;
        int j;
        for (j = i; j >= 0 && j > i - 4; j--) {
            segment = segment * 10 + (numberStr[j] - '0');
        }
        Node* newNode = createNode(segment);

        if (!newNode) {
            
            return NULL;
        }

        if (!tail) {
            head = newNode;
            tail = newNode;
        } else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }
    return head;
}

Node* addLinkedLists(Node* list1, Node* list2) {
    Node* resultHead = NULL;
    Node* resultTail = NULL;
    int carry = 0;

    while (list1 || list2 || carry) {
        int val1 = (list1) ? list1->data : 0;
        int val2 = (list2) ? list2->data : 0;
        int total = val1 + val2 + carry;
        carry = total / 10000;
        total %= 10000;
        Node* newNode = createNode(total);

        if (!newNode) {
    
            return NULL;
        }

        if (!resultTail) {
            resultHead = newNode;
            resultTail = newNode;
        } else {
            resultTail->next = newNode;
            newNode->prev = resultTail;
            resultTail = newNode;
        }

        if (list1) list1 = list1->next;
        if (list2) list2 = list2->next;
    }
    return resultHead;
}

void printLinkedList(Node* head) {
    Node* current = head;
    while (current) {
        printf("%04d -> ", current->data);
        current = current->next;
    }
    printf("None\n");
}

int main() {

    int number1;
    int number2 ;
    printf("Enter the first number \n");
    scanf("%d",&number1);
    printf("Enter the second number \n");
    scanf("%d",&number2);
    Node* list1 = createLinkedListFromNumber(number1);
    Node* list2 = createLinkedListFromNumber(number2);

    if (!list1 || !list2) {
        printf("Memory allocation error.\n");
        return 1;
    }

    Node* result = addLinkedLists(list1, list2);
    if (!result) {
        printf("Memory allocation error.\n");
        return 1;
    }

    printf("Result:\n");
    printLinkedList(result);

    while (list1) {
        Node* temp = list1;
        list1 = list1->next;
        free(temp);
    }
    while (list2) {
        Node* temp = list2;
        list2 = list2->next;
        free(temp);
    }
    while (result) {
        Node* temp = result;
        result = result->next;
        free(temp);
    }

    return 0;
}