#include <stdio.h>
#include <stdlib.h>

struct Heap{
    int data;
    struct Heap *heap;
};

void swap(int *a, int *b){
    int *temp = *a;
    *a = *b;
    *b = *temp;
}

int main(){



    return 0;
}