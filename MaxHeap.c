#include <stdio.h>
#include <stdlib.h>

struct Heap{
    int size;
    struct Heap *arr;
};

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void heapifyUp(struct Heap *heap, int idx){
    int parent_idx = (idx - 1) / 2;
    
    while(idx > 0){
        if(heap->arr[parent_idx] < heap->arr[idx]){
            swap(&heap->arr[parent_idx], &heap->arr[idx]);
            idx = parent_idx;
        }
        else{
            break;
        }
    }
}

int main(){



    return 0;
}