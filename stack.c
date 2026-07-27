#include <stdio.h>

int arr[32767];
int top = -1;

void push(int value){
    arr[++top] = value;
}

void pop(){
    top--;
}

void peek(){
    printf("%d\n", arr[top]);
}

void printStack(){
    printf("Stack:\n");
    for(int i = 0; i <= top; i++){
        printf("%d\n", arr[i]);
    }
}

int main(){

    push(1);
    push(2);
    push(3);
    push(4);
    pop();
    printStack();

    return 0;
}