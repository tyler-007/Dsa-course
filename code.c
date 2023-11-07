#include <stdio.h>
#include <stdlib.h>

// Define a structure to represent an element in the sorted lists
struct Element {
    int value;
    int listIndex;
    int elementIndex;
};

// Function to swap two elements
void swap(struct Element* a, struct Element* b) {
    struct Element temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify an array
void minHeapify(struct Element arr[], int n, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left].value < arr[smallest].value)
        smallest = left;

    if (right < n && arr[right].value < arr[smallest].value)
        smallest = right;

    if (smallest != i) {
        swap(&arr[i], &arr[smallest]);
        minHeapify(arr, n, smallest);
    }
}

// Function to build a min-heap
void buildMinHeap(struct Element arr[], int n) {
    int i;
    for (i = (n / 2) - 1; i >= 0; i--)
        minHeapify(arr, n, i);
}

// Function to merge m sorted lists
void mergeSortedLists(int* lists[], int m, int n) {
    struct Element* heap = (struct Element*)malloc(m * sizeof(struct Element));
    int result[n];

    // Initialize the heap with the first element from each list
    for (int i = 0; i < m; i++) {
        heap[i].value = lists[i][0];
        heap[i].listIndex = i;
        heap[i].elementIndex = 0;
    }

    // Build a min-heap
    buildMinHeap(heap, m);

    // Merge the sorted lists
    for (int i = 0; i < n; i++) {
        struct Element min = heap[0];
        result[i] = min.value;

        // Replace the extracted element with the next element from the same list
        if (min.elementIndex < n - 1) {
            min.elementIndex++;
            min.value = lists[min.listIndex][min.elementIndex];
        }
        else {
            min.value = INT_MAX;  // Mark this list as finished
        }

        // Update the root of the heap and maintain the heap property
        heap[0] = min;
        minHeapify(heap, m, 0);
    }

    // Print the merged sorted list
    printf("Merged sorted list: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", result[i]);
    }

    free(heap);
}

int main() {
    int* lists[] = {
        (int[]){1, 4, 7},
        (int[]){2, 5, 8},
        (int[]){3, 6, 9}
    };

    int m = 3; // Number of sorted lists
    int n = 9; // Total number of elements in all lists

    mergeSortedLists(lists, m, n);

    return 0;
}
