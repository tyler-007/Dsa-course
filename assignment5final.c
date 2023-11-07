#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

struct MinHeap {
    int* arr;
    int maxSize;
    int heapSize;
};

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void minHeapify(struct MinHeap* minHeap, int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < minHeap->heapSize && minHeap->arr[left] < minHeap->arr[smallest])
        smallest = left;

    if (right < minHeap->heapSize && minHeap->arr[right] < minHeap->arr[smallest])
        smallest = right;

    if (smallest != i) {
        swap(&minHeap->arr[i], &minHeap->arr[smallest]);
        minHeapify(minHeap, smallest);
    }
}

struct MinHeap* buildMinHeap(int arr[], int n) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->maxSize = n;
    minHeap->heapSize = n;
    minHeap->arr = (int*)malloc(n * sizeof(int));

    for (int i = 0; i < n; i++) {
        minHeap->arr[i] = arr[i];
    }

    for (int i = (n - 1) / 2; i >= 0; i--) {
        minHeapify(minHeap, i);
    }

    return minHeap;
}

int main() {
    int arr[] = {1, 5, 6, 8, 9, 7, 3};
    int n = sizeof(arr) / sizeof(arr[0]);

    struct MinHeap* h = buildMinHeap(arr, n);

    printf("The current size of the heap is %d\n", h->heapSize);
    printf("The current minimum element is %d\n", h->arr[0]);

    

    return 0;
}

#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

// Structure for the max heap
typedef struct MaxHeap {
    int* arr;
    int maxSize;
    int heapSize;
} MaxHeap;

// Function to swap two integers
void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify the max heap (sift down)
void maxHeapify(MaxHeap* maxHeap, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < maxHeap->heapSize && maxHeap->arr[left] > maxHeap->arr[largest])
        largest = left;

    if (right < maxHeap->heapSize && maxHeap->arr[right] > maxHeap->arr[largest])
        largest = right;

    if (largest != i) {
        swap(&maxHeap->arr[i], &maxHeap->arr[largest]);
        maxHeapify(maxHeap, largest);
    }
}

// Function to create a max heap
MaxHeap* createMaxHeap(int maxSize) {
    MaxHeap* maxHeap = (MaxHeap*)malloc(sizeof(MaxHeap));
    maxHeap->maxSize = maxSize;
    maxHeap->heapSize = 0;
    maxHeap->arr = (int*)malloc(maxSize * sizeof(int));
    return maxHeap;
}

// Function to insert a key into the max heap
void insertKey(MaxHeap* maxHeap, int key) {
    if (maxHeap->heapSize == maxHeap->maxSize) {
        printf("Overflow: Could not insert key\n");
        return;
    }

    maxHeap->heapSize++;
    int i = maxHeap->heapSize - 1;
    maxHeap->arr[i] = key;

    while (i != 0 && maxHeap->arr[(i - 1) / 2] < maxHeap->arr[i]) {
        swap(&maxHeap->arr[i], &maxHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to delete the maximum element from the max heap
int deleteMax(MaxHeap* maxHeap) {
    if (maxHeap->heapSize <= 0)
        return INT_MIN;

    if (maxHeap->heapSize == 1) {
        maxHeap->heapSize--;
        return maxHeap->arr[0];
    }

    int root = maxHeap->arr[0];
    maxHeap->arr[0] = maxHeap->arr[maxHeap->heapSize - 1];
    maxHeap->heapSize--;

    maxHeapify(maxHeap, 0);

    return root;
}

int main() {
    MaxHeap* maxHeap = createMaxHeap(10);

    insertKey(maxHeap, 4);
    insertKey(maxHeap, 10);
    insertKey(maxHeap, 7);
    insertKey(maxHeap, 1);
    insertKey(maxHeap, 5);

    printf("Max element: %d\n", deleteMax(maxHeap));
    printf("Max element: %d\n", deleteMax(maxHeap));

    free(maxHeap->arr);
    free(maxHeap);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void maxHeapify(int arr[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(&arr[i], &arr[largest]);
        maxHeapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
   
    for (int i = n / 2 - 1; i >= 0; i--) {
        maxHeapify(arr, n, i);
    }

    for (int i = n - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]); 
        maxHeapify(arr, i, 0); 
    }
}


void printArray(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {12, 11, 13, 5, 6, 7};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Original array: ");
    printArray(arr, n);

    heapSort(arr, n);

    printf("Sorted array: ");
    printArray(arr, n);

    return 0;
}
