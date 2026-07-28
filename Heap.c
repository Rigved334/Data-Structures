// Implementation of max heap

#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

struct Heap{
    int arr[MAX_SIZE];
    int size;
};

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

// for insertion - compare with parent and swap
void heapify_up(struct Heap *heap, int idx){
    while(idx > 0){
        int parent = (idx - 1) / 2;

        if(heap->arr[parent] < heap->arr[idx]){
            swap(&heap->arr[parent], &heap->arr[idx]);
            idx = parent;
        }
        else{
            break;
        }
    }
}

// for deletion - make the last element the root and compare
//                it with the children and swap
void heapify_down(struct Heap *heap, int idx){
    while(1){
        int temp = idx;
        int left_child = 2 * idx + 1;
        int right_child = 2 * idx + 2;

        if(left_child < heap->size && (heap->arr[left_child] > heap->arr[temp])){
            temp = left_child;
        }
        if(right_child < heap->size && (heap->arr[right_child] > heap->arr[temp])){
            temp = right_child;
        }
        if(temp != idx){
            swap(&heap->arr[idx], &heap->arr[temp]);
            idx = temp;
        }
        else{
            break;
        }
    }
}

void insert(struct Heap *heap, int value){
    if(heap->size == MAX_SIZE){
        printf("Heap Overflow\n");
        return;
    }

    heap->arr[heap->size] = value;
    heapify_up(heap, heap->size);
    heap->size++;
}

void delete(struct Heap *heap){
    if(heap->size == 0){
        printf("Heap Underflow\n");
        return;
    }

    int root = heap->arr[0];

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;

    heapify_down(heap, 0);
}

void peek(struct Heap *heap){
    if(heap->size == 0){
        printf("Heap is Empty\n");
        return;
    }

    printf("%d", heap->arr[0]);
}

void printHeap(struct Heap *heap){
    if(heap->size == 0){
        printf("Heap is Empty\n");
        return;
    }

    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->arr[i]);
    }

    printf("\n");
}

int main(){

    struct Heap heap;
    heap.size = 0;

    insert(&heap, 2);
    insert(&heap, 3);
    insert(&heap, 4);
    insert(&heap, 5);
    insert(&heap, 6);

    printf("Heap:-\n");
    printHeap(&heap);

    return 0;
}