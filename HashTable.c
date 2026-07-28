#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Node{
    char key[100];
    int value;
    struct Node* next;
};

struct HashMap{
    int capacity;
    struct Node **arr;
};

struct HashMap* createHashMap(int capacity){
    struct HashMap *map = malloc(sizeof(struct HashMap));
    if(map->capacity == 0){
        printf("could not allocate memory\n");
        return NULL;
    }

    map->arr = malloc(capacity * sizeof(struct Node*));
    if(map->arr == NULL){
        free(map);
        printf("could not allocate memory\n");
        return NULL;
    }

    map->capacity = capacity;
    for(int i = 0; i < capacity; i++){
        map->arr[i] = NULL;
    }

    return map;
}

struct Node* createNode(char key[], int value){
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode == NULL){
        printf("could not allocate memory\n");
        return NULL;
    }

    strcpy(newNode->key, key);
    newNode->value = value;
    newNode->next = NULL;

    return newNode;
}

int hash(char key[], int capacity){

    int sum = 0, index = 0;
    for(int i = 0; key[i] != '\0'; i++){
        sum += key[i];
    }

    index = sum % capacity;

    return index;
}

void insert(struct HashMap *map, char key[], int value){
    int index = hash(key, map->capacity);
    struct Node *temp = map->arr[index];
    while(temp != NULL){
        if(strcmp(temp->key, key) == 0){
            temp->value = value;
            return;
        }
        temp = temp->next;
    }
    struct Node *newNode = createNode(key, value);

    newNode->next = map->arr[index];
    map->arr[index] = newNode;
}

int search(struct HashMap *map, char key[]){
    int index = hash(key, map->capacity);
    struct Node *temp = map->arr[index];
    if(temp == NULL){
        printf("HashMap is empty\n");
        return -1;
    }

    while(temp != NULL){
        if(strcmp(temp->key, key) == 0){
            return temp->value;
        }
        temp = temp->next;
    }
   
    printf("Key not found\n");
    return -1;
}

void delete(struct HashMap *map, char key[]){
    int index = hash(key, map->capacity);
    struct Node *temp = map->arr[index];
    if(temp == NULL){
        printf("HashMap is empty\n");
        return;
    }

    struct Node *prev = NULL;

    while((temp != NULL) && (strcmp(temp->key, key) != 0)){
        prev = temp;
        temp = temp->next;
    }  

    if(temp == NULL){
        printf("key not found\n");
        return;
    }
    
    if(prev == NULL){
        map->arr[index] = temp->next;
        free(temp);
        return;
    }
    else{
        prev->next = temp->next;
        free(temp);
        temp = NULL;
        return;
    }
}

void printHashMap(struct HashMap *map);
void freeHashMap(struct HashMap *map);

int main(){

    struct HashMap *map = createHashMap(5);
    if(map == NULL){
        return 1;
    }

    insert(map, "rigved", 100);
    insert(map, "praveen", 50);
    insert(map, "kiran", 25);

    printf("Key: %d\n", (search(map, "rigved")));
    printf("Key: %d\n", (search(map, "praveen")));
    printf("Key: %d\n", (search(map, "kiran")));
    delete(map, "praveen");
    printf("Key: %d\n", (search(map, "praveen")));

    return 0;
}