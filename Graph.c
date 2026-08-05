#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *next;
};

struct Graph{
    int V;
    struct Node **arr; 
};

struct Stack{
    int size;
    int top;
    int *arr;
};

struct Queue{
    int size;
    int *arr;
    int front;
    int rear;
};

struct Graph *createGraph(int vertices){
    struct Graph *graph = malloc(sizeof(*graph));
    if(graph == NULL){
        return NULL;
    }

    graph->V = vertices;
    graph->arr = calloc(vertices, sizeof(*graph->arr));
    if(graph->arr == NULL){
        free(graph);
        return NULL;
    }

    return graph;
}

void addEdge(struct Graph *graph, int src, int dest){
    if(src < 0 || src >= graph->V || dest < 0 || dest >= graph->V){
        return;
    }

    struct Node *newNode = malloc(sizeof(*newNode));
    if(newNode == NULL){
        return;
    }

    newNode->data = dest;
    newNode->next = graph->arr[src];
    graph->arr[src] = newNode;

    newNode = malloc(sizeof(*newNode));
    if(newNode == NULL){
        return;
    }

    newNode->data = src;
    newNode->next = graph->arr[dest];
    graph->arr[dest] = newNode;
}

struct Queue *createQueue(int size){
    struct Queue *queue = malloc(sizeof(*queue));

    if(queue == NULL){
        return NULL;
    }

    queue->size = size;
    queue->arr = malloc(size * sizeof(int));
    queue->front = -1;
    queue->rear = -1;

    if(queue->arr == NULL){
        free(queue);
        return NULL;
    }

    return queue;
}

bool isEmptyQ(struct Queue *queue){
    return queue->front == -1;
}

void enqueue(struct Queue *queue, int data){
    if(queue->rear == queue->size - 1){
        printf("Queue Overflow\n");
        return;
    }

    if(queue->front == -1){
        queue->front = 0;
    }

    queue->arr[++queue->rear] = data;
}

int dequeue(struct Queue *queue){
    if(isEmptyQ(queue)){
        printf("Queue Underflow\n");
        return -1;
    }

    int value = queue->arr[queue->front++];

    if(queue->front > queue->rear){
        queue->front = -1;
        queue->rear = -1;
    }

    return value;
}

struct Stack *createStack(int size){    
    struct Stack *stack = malloc(sizeof(*stack));

    if(stack == NULL){
        return NULL;
    }
    
    stack->size = size;
    stack->top = -1;
    stack->arr = malloc(size * sizeof(int));

    if(stack->arr == NULL){
        free(stack);
        return NULL;
    }

    return stack;
}

void push(struct Stack *stack, int data){
    if(stack->top == stack->size - 1){
        printf("Stack Overflow\n");
        return;
    }
    stack->arr[++(stack->top)] = data;
}

int pop(struct Stack *stack){
    if(stack->top == - 1){
        printf("Stack Underflow\n");
        return -1;
    }
    return stack->arr[(stack->top)--];
}

bool isEmptyS(struct Stack *stack){
    return stack->top == -1;
}

bool visitedS[32767];
void DFS_R(struct Graph *graph, int source){
    if(source < 0 || source >= graph->V){
        return;
    }

    visitedS[source] = 1;
    printf("%d ", source);

    struct Node *temp = graph->arr[source];
    while(temp != NULL){
        if(!visitedS[temp->data]){
            DFS_R(graph, temp->data);
        }
        temp = temp->next;
    }
}

void DFS_I(struct Graph *graph, struct Stack *stack, int source){
    if(source < 0 || source >= graph->V){
        return;
    }

    push(stack, source);
    visitedS[source] = 1;

    while(!isEmptyS(stack)){
        int current = pop(stack);
        printf("%d ", current);

        struct Node *temp = graph->arr[current];

        while(temp != NULL){
            if(!visitedS[temp->data]){
                push(stack, temp->data);
                visitedS[temp->data] = 1;
            }

            temp = temp->next;
        }
    }
}

bool visitedQ[32767];
void BFS(struct Graph *graph, struct Queue *queue, int source){
    if(source < 0 || source >= graph->V){
        return;
    }

    enqueue(queue, source);
    visitedQ[source] = 1;

    while(!isEmptyQ(queue)){
        int current = dequeue(queue);
        printf("%d ", current);

        struct Node *temp = graph->arr[current];

        while(temp != NULL){
            if(!visitedQ[temp->data]){
                enqueue(queue, temp->data);
                visitedQ[temp->data] = 1;
            }

            temp = temp->next;
        }
    }
}

void printGraph(struct Graph *graph){
    for(int i = 0; i < graph->V; i++){
        struct Node *temp = graph->arr[i];

        if(temp == NULL){
            printf("%d -> NULL\n", i);
            continue;
        }

        printf("%d -> ", i);
        while(temp != NULL){
            printf("%d -> ", temp->data);
            temp = temp->next;
        }
        printf("NULL\n");
    }
}

void freeGraph(struct Graph *graph){
    if(graph == NULL){
        return;
    }

    for(int i = 0; i < graph->V; i++){
        struct Node *temp = graph->arr[i];
        while(temp != NULL){
            struct Node *nextNode = temp->next;
            free(temp);
            temp = nextNode;
        }
    }
    free(graph->arr);
    free(graph);
}

void freeStack(struct Stack *stack){
    if(stack == NULL){
        return;
    }

    free(stack->arr);
    free(stack);
}

void freeQueue(struct Queue *queue){
    if(queue == NULL){
        return;
    }

    free(queue->arr);
    free(queue);
}

int main(){

    struct Graph *graph = createGraph(7);
    struct Stack *stack = createStack(graph->V);
    struct Queue *queue = createQueue(graph->V);

    addEdge(graph, 1, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 2, 4);
    addEdge(graph, 3, 4);
    addEdge(graph, 3, 5);
    addEdge(graph, 4, 6);
    addEdge(graph, 5, 6);
    printf("\n");
    printGraph(graph);
    printf("\n");

    for(int i = 0; i < graph->V; i++){
        visitedS[i] = 0;
    } 
    printf("Depth First Search (recursive):\n");
    DFS_R(graph, 1);
    printf("\n");

    for(int i = 0; i < graph->V; i++){
        visitedS[i] = 0;
    }
    printf("Depth First Search (iterative):\n");
    DFS_I(graph, stack, 1);
    printf("\n");

    for(int i = 0; i < graph->V; i++){
        visitedQ[i] = 0;
    }
    printf("Breadth First Search:\n");
    BFS(graph, queue, 1);
    printf("\n");

    freeStack(stack);
    freeQueue(queue);
    freeGraph(graph);

    return 0;
}