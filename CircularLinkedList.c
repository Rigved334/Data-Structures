#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

struct LinkedList{
    struct Node *head;
    struct Node *tail;
};

struct LinkedList* createList(){
    struct LinkedList *list = malloc(sizeof(struct LinkedList));
    if(list == NULL){
        printf("List does not exist\n");
        return NULL;
    }

    list->head = NULL;
    list->tail = NULL;
    return list;
}

struct Node* createNode(int data){
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode == NULL){
        printf("Node does not exist\n");
        return NULL;
    }

    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void insertFront(struct LinkedList *list, int data){
    if(list == NULL){
        return;
    }

    struct Node *newNode = createNode(data);
    if(newNode == NULL){
        printf("Node does not exist\n");
        return;
    }

    if(list->head == NULL){
        list->head = newNode;
        list->tail = newNode;
        newNode->next = newNode;
    }
    else{
        newNode->next = list->head;   
        list->head = newNode;         
        list->tail->next = list->head;
    }
}

void insertEnd(struct LinkedList *list, int data){
    if(list == NULL){
        return;
    }

    struct Node *newNode = createNode(data);
    if(newNode == NULL){
        printf("Node does not exist\n");
        return;
    }

    if(list->head == NULL){
        insertFront(list, data);
    }
    else{
        list->tail->next = newNode;
        list->tail = newNode;
        newNode->next = list->head;
    }
}

void deleteFront(struct LinkedList *list){
    if(list == NULL || list->head == NULL){
        return;
    }

    if(list->head->next == list->head){
        struct Node *temp = list->head;   
        list->head = NULL;   
        list->tail = NULL;   
        free(temp);          
    }
    else{
        struct Node *temp1 = list->head;
        struct Node *temp2 = list->head;
        temp1 = temp1->next;
        list->head = temp1;
        free(temp2);
        temp2 = NULL;
        list->tail->next = list->head;
    }
}

void deleteEnd(struct LinkedList *list){
    if(list == NULL || list->head == NULL){
        return;
    }

    if(list->head->next == list->head){
        deleteFront(list);
        return;
    }
    struct Node *temp = list->head;
    while(temp->next != list->tail){
        temp = temp->next;
    }

    struct Node *nodeToDelete = list->tail;
    list->tail = temp;
    list->tail->next = list->head;
    free(nodeToDelete);
}

void search(struct LinkedList *list, int data){
    if(list == NULL || list->head == NULL){
        return;
    }

    struct Node *temp = list->head;

    do{
        if(temp->data == data){
            printf("Found\n");
            return;
        }
        else{
            temp = temp->next;
        }
    }while(temp != list->head);
}

void displayList(struct LinkedList *list){
    if(list == NULL || list->head == NULL){
        printf("The list is empty\n");
        return;
    }

    struct Node *temp = list->head;

    printf("Circular Linked List:\n");

    do{
        printf("%d -> ", temp->data);
        temp = temp->next;
    }while(temp != list->head);

    printf("(back to head)\n");
}

int main(){

    struct LinkedList *list = createList();
    if(list == NULL){
        return 1;
    }

    insertFront(list, 3);
    insertFront(list, 2);
    insertFront(list, 1);
    insertEnd(list, 4);
    insertFront(list, 5);
    displayList(list);
    deleteFront(list);
    displayList(list);
    insertEnd(list, 6);
    displayList(list);
    deleteEnd(list);
    displayList(list);

    return 0;
}