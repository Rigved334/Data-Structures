#include <stdio.h>

int arr[32767];
int q = -1;

void enqueue(int value){
    arr[++q] = value;
}

void dequeue(){
    if(q == -1){
        printf("the queue is empty\n");
        return;
    }
    q--;
}

void printQ(){
    printf("Queue:\n");
    for(int i = 0; i <= q; i++){
        printf("%d ", arr[i]);
    }
}

int main(){

    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    dequeue();
    printQ();

    return 0;
}