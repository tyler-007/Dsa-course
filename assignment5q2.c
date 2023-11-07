#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100

typedef struct MinMaxHeap {
    int arr[MAX_SIZE];
    int size;
} MinMaxHeap;


void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

int findMaxChildIndex(MinMaxHeap* heap, int i) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    int maxChildIndex = i;
    if (leftChild < heap->size && heap->arr[leftChild] > heap->arr[maxChildIndex]) {
        maxChildIndex = leftChild;
    }
    if (rightChild < heap->size && heap->arr[rightChild] > heap->arr[maxChildIndex]) {
        maxChildIndex = rightChild;
    }

    return maxChildIndex;
}

int findMinChildIndex(MinMaxHeap* heap, int i) {
    int leftChild = 2 * i + 1;
    int rightChild = 2 * i + 2;

    int minChildIndex = i;
    if (leftChild < heap->size && heap->arr[leftChild] < heap->arr[minChildIndex]) {
        minChildIndex = leftChild;
    }
    if (rightChild < heap->size && heap->arr[rightChild] < heap->arr[minChildIndex]) {
        minChildIndex = rightChild;
    }

    return minChildIndex;
}

void deleteMax(MinMaxHeap* heap) {
    if (heap->size == 0) {
        printf("Heap is empty. Cannot delete.\n");
        return;
    }

    int maxElementIndex = 0;
    int lastElementIndex = heap->size - 1;
    swap(&heap->arr[maxElementIndex], &heap->arr[lastElementIndex]);

    heap->size--;

    int i = maxElementIndex;
    int maxChildIndex = findMaxChildIndex(heap, i);
    int minChildIndex = findMinChildIndex(heap, i);

    if (heap->arr[maxChildIndex] > heap->arr[i]) {
        swap(&heap->arr[maxChildIndex], &heap->arr[i]);
        deleteMax(heap); 
    }

    if (heap->arr[minChildIndex] < heap->arr[i]) {
        swap(&heap->arr[minChildIndex], &heap->arr[i]);
        deleteMax(heap); 
    }
}

void printMinMaxHeap(MinMaxHeap* heap) {
    printf("Min-Max Heap: ");
    for (int i = 0; i < heap->size; i++) {
        printf("%d ", heap->arr[i]);
    }
    printf("\n");
}

int main() {
    MinMaxHeap heap;
    heap.size = 0;

    int elements[] = {3, 1, 6, 5, 9, 8, 7, 4, 2};
    int numElements = sizeof(elements) / sizeof(elements[0]);
    for (int i = 0; i < numElements; i++) {
        heap.arr[heap.size] = elements[i];
        heap.size++;
    }

    printf("Original ");
    
    deleteMax(&heap);
    printf("After deleting the maximum element: ");
    printMinMaxHeap(&heap);

    return 0;
}
