#include <iostream>
using namespace std;

// Node structure for a (row, column, data) element
struct Node {
    int row, col, data;
    Node* next;
};

// Function to insert a new (row, column, data) element into the linked list
void insertElement(Node*& head, int row, int col, int data) {
    Node* newNode = new Node;
    newNode->row = row;
    newNode->col = col;
    newNode->data = data;
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

// Function to add two sparse matrices represented as linked lists
Node* addSparseMatrices(Node* mat1, Node* mat2) {
    Node* result = nullptr;

    while (mat1 != nullptr && mat2 != nullptr) {
        if (mat1->row == mat2->row && mat1->col == mat2->col) {
            // Elements in both matrices have the same (row, column)
            int sum = mat1->data + mat2->data;
            insertElement(result, mat1->row, mat1->col, sum);
            mat1 = mat1->next;
            mat2 = mat2->next;
        } else if (mat1->row < mat2->row || (mat1->row == mat2->row && mat1->col < mat2->col)) {
            // Element from mat1 is smaller (lexicographically)
            insertElement(result, mat1->row, mat1->col, mat1->data);
            mat1 = mat1->next;
        } else {
            // Element from mat2 is smaller (lexicographically)
            insertElement(result, mat2->row, mat2->col, mat2->data);
            mat2 = mat2->next;
        }
    }

    // Append any remaining elements from mat1 and mat2
    while (mat1 != nullptr) {
        insertElement(result, mat1->row, mat1->col, mat1->data);
        mat1 = mat1->next;
    }

    while (mat2 != nullptr) {
        insertElement(result, mat2->row, mat2->col, mat2->data);
        mat2 = mat2->next;
    }

    return result;
}

// Function to display the entire matrix, including zeros
void displayEntireMatrix(Node* head, int numRows, int numCols) {
    Node* current = head;
    int currentRow = 0;
    int currentCol = 0;

    while (currentRow < numRows && currentCol < numCols) {
        if (current != nullptr && current->row == currentRow && current->col == currentCol) {
            // Element exists at this position
            cout << current->data << " ";
            current = current->next;
        } else {
            // Element is zero
            cout << "0 ";
        }

        currentCol++;
        if (currentCol == numCols) {
            currentCol = 0;
            currentRow++;
            cout << endl;
        }
    }
}

int main() {
    // Create linked lists to represent two sparse matrices
    Node* matrix1 = nullptr;
    Node* matrix2 = nullptr;

    // Insert elements into matrix1 and matrix2
    insertElement(matrix1, 0, 0, 1);
    insertElement(matrix1, 1, 1, 2);
    insertElement(matrix1, 2, 2, 3);

    insertElement(matrix2, 0, 0, 4);
    insertElement(matrix2, 1, 1, 5);
    insertElement(matrix2, 2, 2, 6);

    // Define the number of rows and columns in the matrices
    int numRows = 9;
    int numCols = 5;

    cout << "Sparse Matrix 1:" << endl;
    displayEntireMatrix(matrix1, numRows, numCols);

    cout << "Sparse Matrix 2:" << endl;
    displayEntireMatrix(matrix2, numRows, numCols);

    Node* resultMatrix = addSparseMatrices(matrix1, matrix2);

    cout << "Resultant Sparse Matrix:" << endl;
    displayEntireMatrix(resultMatrix, numRows, numCols);

    // Clean up memory
    while (matrix1 != nullptr) {
        Node* temp = matrix1;
        matrix1 = matrix1->next;
        delete temp;
    }

    while (matrix2 != nullptr) {
        Node* temp = matrix2;
        matrix2 = matrix2->next;
        delete temp;
    }

    while (resultMatrix != nullptr) {
        Node* temp = resultMatrix;
        resultMatrix = resultMatrix->next;
        delete temp;
    }

    return 0;
}
