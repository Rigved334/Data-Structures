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
    heap->size++;
}

int main(){



    return 0;
}