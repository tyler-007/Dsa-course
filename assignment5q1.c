#include <stdio.h>
#include <limits.h>
#include <stdlib.h>

typedef struct MinHeap {
    int* arr;
    int maxSize;
    int heapSize;
} MinHeap;

MinHeap* createMinHeap(int maxSize) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->maxSize = maxSize;
    minHeap->heapSize = 0;
    minHeap->arr = (int*)malloc(maxSize * sizeof(int));
    return minHeap;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}


void minHeapify(MinHeap* minHeap, int i) {
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

// Function to insert a key into the Min Heap.
void insertKey(MinHeap* minHeap, int key) {
    if (minHeap->heapSize == minHeap->maxSize) {
        printf("\nOverflow: Could not insert key\n");
        return;
    }

    minHeap->heapSize++;
    int i = minHeap->heapSize - 1;
    minHeap->arr[i] = key;

    while (i != 0 && minHeap->arr[(i - 1) / 2] > minHeap->arr[i]) {
        swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void decreaseKey(MinHeap* minHeap, int i, int newVal) {
    minHeap->arr[i] = newVal;
    while (i != 0 && minHeap->arr[(i - 1) / 2] > minHeap->arr[i]) {
        swap(&minHeap->arr[i], &minHeap->arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}


int removeMin(MinHeap* minHeap) {
    if (minHeap->heapSize <= 0)
        return INT_MAX;

    if (minHeap->heapSize == 1) {
        minHeap->heapSize--;
        return minHeap->arr[0];
    }

    int root = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[minHeap->heapSize - 1];
    minHeap->heapSize--;
    minHeapify(minHeap, 0);

    return root;
}

void deleteKey(MinHeap* minHeap, int i) {
    decreaseKey(minHeap, i, INT_MIN);
    removeMin(minHeap);
}

int getMin(MinHeap* minHeap) {
    return minHeap->arr[0];
}

int curSize(MinHeap* minHeap) {
    return minHeap->heapSize;
}

int main() {
    MinHeap* h = createMinHeap(15);

    printf("Entered 6 keys: 1, 5, 6, 9, 7, 3\n");
    insertKey(h, 1);
    insertKey(h, 5);
    insertKey(h, 6);
    insertKey(h, 9);
    insertKey(h, 7);
    insertKey(h, 3);

    printf("The current size of the heap is %d\n", curSize(h));
    printf("The current minimum element is %d\n", getMin(h));

    return 0;
}


