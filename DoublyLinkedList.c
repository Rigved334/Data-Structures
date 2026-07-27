#include <stdio.h>
#include <stdlib.h>

struct Node{
    int data;
    struct Node *next;
    struct Node *prev;
};

struct LinkedList{
    struct Node *head;
};

struct LinkedList* createList(){
    struct LinkedList *list = malloc(sizeof(*list));
    if(list == NULL){
        printf("list does not exist\n");
        return NULL;
    }

    list->head = NULL;
    return list;
}

struct Node* createNode(int value){
    struct Node* newNode = malloc(sizeof(*newNode));

    if(newNode == NULL){
        printf("could not allocate memory to node\n");
        return NULL;
    }

    newNode->data = value;
    newNode->next = NULL;
    newNode->prev = NULL;

    return newNode;
}

void insertFront(struct LinkedList* list, int value){
    if(list == NULL){
        return;
    }

    struct Node* newNode = createNode(value);

    if(newNode == NULL){
        return;
    }

    newNode->next = list->head;
    newNode->prev = NULL;
    if(list->head != NULL){
        list->head->prev = newNode;
    }
    list->head = newNode;
}

void insertEnd(struct LinkedList* list, int value){
    if(list == NULL){
        return;
    }

    struct Node* newNode = createNode(value);

    if(newNode == NULL){
        return;
    }

    if(list->head == NULL){
        list->head = newNode;
        return;
    }

    struct Node *temp = list->head;
    while(temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;
    newNode->prev = temp;
}

void deleteFront(struct LinkedList *list){
    if(list == NULL || list->head == NULL){
        return;
    }

    struct Node *temp = list->head;
    list->head = temp->next;
    if(list->head != NULL){
        list->head->prev = NULL;
    }
    temp->next = NULL;
    temp->prev = NULL;
    free(temp);
}

void deleteEnd(struct LinkedList *list){
    if(list->head == NULL){
        return;
    }

    struct Node *temp = list->head;
    struct Node *prev = NULL;

    if(temp->next == NULL){
        deleteFront(list);
        return;
    }

    while(temp->next != NULL){
        prev = temp;
        temp = temp->next;
    }

    prev->next = NULL;
    temp->prev = NULL;
    free(temp);
    temp = NULL;
}

void insertAfterIdx(struct LinkedList *list, int value, int idx){
    if(list == NULL || list->head == NULL){
        return;
    }

    if(idx < 0){
        return;
    }

    struct Node *newNode = createNode(value);
    if(newNode == NULL){
        return;
    }

    struct Node *temp = list->head;

    int i = 0;
    while(temp != NULL && i < idx){
        temp = temp->next;
        i++;
    }

    if(temp == NULL){
        free(newNode);
        return;
    }

    newNode->next = temp->next;
    if(temp->next != NULL){
        temp->next->prev = newNode;
    }
    temp->next = newNode;
    newNode->prev = temp;
}

void deleteByValue(struct LinkedList *list, int value){
    if(list == NULL || list->head == NULL){
        return;
    }

    struct Node *temp = list->head;
    if(temp->data == value){
        list->head = temp->next;
        if(list->head != NULL){
            list->head->prev = NULL;
        }
        temp->next = NULL;
        free(temp);
        return;
    }

    while(temp != NULL && temp->data != value){
        temp = temp->next;
    }

    if(temp == NULL){
        return;
    }

    if(temp->prev != NULL){
        temp->prev->next = temp->next;
    }
    if(temp->next != NULL){
        temp->next->prev = temp->prev;
    }
    temp->next = NULL;
    temp->prev = NULL;
    free(temp);
}

void displayList(struct LinkedList *list){
    if(list->head == NULL){
        printf("the list is empty\n");
        return;
    }
    struct Node *temp = list->head;

    printf("Linked List:\n");
    while(temp != NULL){
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

int main(){

    struct LinkedList *list = createList();

    if(list == NULL){
        return 1;
    }

    insertFront(list, 1);
    insertEnd(list, 2);
    insertEnd(list, 3);
    insertAfterIdx(list, 4, 1);
    deleteByValue(list, 4);
    displayList(list);
    insertEnd(list, 4);
    displayList(list);

    return 0;
}