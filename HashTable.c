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

void printHashMap(struct HashMap *map){
    for(int i = 0; i < map->capacity; i++){
        struct Node *temp = map->arr[i];
        
        if(temp == NULL){
            printf("Bucket %d -> Map does not exist\n", i + 1);
            continue;
        }

        printf("Bucket %d -> ", i + 1);
        while(temp != NULL){
            printf("%s: %d -> ",temp->key, temp->value);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freeHashMap(struct HashMap *map){
    for(int i = 0; i < map->capacity; i++){
        struct Node *temp = map->arr[i];
        while(temp != NULL){
            struct Node *new = temp->next;
            free(temp);
            temp = new;
        }
    }
    free(map->arr);
    free(map);
    printf("Successfully Freed HashMap\n");
}

int main(){

    struct HashMap *map = createHashMap(5);
    if(map == NULL){
        return 1;
    }

    insert(map, "Rigved", 100);
    insert(map, "Praveen", 50);
    insert(map, "Kiran", 40);
    insert(map, "Srajan", 80);

    printHashMap(map);
    printf("\n");
    int key = search(map, "Rigved");
    char *searching = (key != -1) ? "Found" : "Not Found";
    printf("%s -> ", searching);
    printf("Rigved: %d\n", key);
    printf("\n");
    freeHashMap(map);

    return 0;
}