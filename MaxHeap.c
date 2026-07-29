#include <stdio.h>
#include <stdlib.h>

struct Heap{
    int size;
    int arr[32767];
};

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct Heap *heap, int idx){
    while(idx > 0){
        int parent_idx = (idx - 1) / 2;

        if(heap->arr[parent_idx] < heap->arr[idx]){
            swap(&heap->arr[parent_idx], &heap->arr[idx]);
            idx = parent_idx;
        }
        else{
            break;
        }
    }
}

void heapifyDown(struct Heap *heap, int idx){
    while(1){
        int temp = idx;
        int left_child = 2 * idx + 1;
        int right_child = 2 * idx + 2;

        if(left_child < heap->size && heap->arr[left_child] > heap->arr[temp]){
            temp = left_child;
        }
        if(right_child < heap->size && heap->arr[right_child] > heap->arr[temp]){
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

void insert(struct Heap *heap, int data){
    if(heap->size > 32767){
        printf("Not enough space\n");
        return;
    }

    heap->arr[heap->size] = data;
    heapifyUp(heap, heap->size);
    heap->size++;
}

void delete(struct Heap *heap){
    if(heap == 0){
        printf("No elements in Heap\n");
        return;
    }

    heap->arr[0] = heap->arr[heap->size - 1];
    heap->size--;
    heapifyDown(heap, 0);
}

int peek(struct Heap *heap){
    if(heap == 0){
        printf("No elements in Heap\n");
        return -1;
    }

    return heap->arr[0];
}

void printHeap(struct Heap *heap){
    if(heap == 0){
        printf("No elements in Heap\n");
        return;
    }

    printf("Heap:\n");
    for(int i = 0; i < heap->size; i++){
        printf("%d ", heap->arr[i]);
    }
}

int main(){

    struct Heap heap;
    heap.size = 0;

    insert(&heap, 1);
    insert(&heap, 2);
    insert(&heap, 3);
    insert(&heap, 4);
    insert(&heap, 5);
    insert(&heap, 6);

    delete(&heap);

    peek(&heap);

    printHeap(&heap);

    return 0;
}