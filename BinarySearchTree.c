#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    struct Node *right;
    struct Node *left;
};

struct BST{
    struct Node *root;
};

struct Node* createNode(int data){
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode == NULL){
        printf("Could not allocate memory\n");
        return NULL;
    }

    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;

    return newNode;
}

struct Node* insert(struct Node *newNode, int data){
    if(newNode == NULL){
        return createNode(data);
    }

    if(newNode->data == data){
        printf("Node already exists\n");
        return newNode;
    }

    if(newNode->data > data){
        newNode->left = insert(newNode->left, data);
    }
    else{
        newNode->right = insert(newNode->right, data);
    }

    return newNode;
}

bool search(struct Node *newNode, int data){
    if(newNode == NULL){
        return false;
    }

    if(newNode->data == data){
        return true;
    }

    if(newNode->data > data){
        return search(newNode->left, data);
    }
    else{
        return search(newNode->right, data);
    }
}

void inorderTraversal(struct Node *newNode){
    if(newNode == NULL){
        return;
    }

    inorderTraversal(newNode->left);
    printf("%d ", newNode->data);
    inorderTraversal(newNode->right);
}

void preorderTraversal(struct Node *newNode){
    if(newNode == NULL){
        return;
    }

    printf("%d ", newNode->data);
    preorderTraversal(newNode->left);
    preorderTraversal(newNode->right);
}

void postorderTraversal(struct Node *newNode){
    if(newNode == NULL){
        return;
    }

    postorderTraversal(newNode->left);
    postorderTraversal(newNode->right);
    printf("%d ", newNode->data);
}

struct Node *findMin(struct Node *newNode){
    if(newNode == NULL){
        return NULL;
    }

    if(newNode->left == NULL){
        return newNode;
    }

    return findMin(newNode->left);
}

struct Node *findMax(struct Node *newNode){
    if(newNode == NULL){
        return NULL;
    }

    if(newNode->right == NULL){
        return newNode;
    }

    return findMax(newNode->right);
}

struct Node *deleteNode(struct Node *newNode, int data){
    if(newNode == NULL){
        return NULL;
    }

    if(data < newNode->data){
        newNode->left = deleteNode(newNode->left, data);
    }
    else if(data > newNode->data){
        newNode->right = deleteNode(newNode->right, data);
    }
    else{
        if(newNode->left == NULL && newNode->right == NULL){
            free(newNode);
            return NULL;
        }

        if(newNode->left == NULL && newNode->right != NULL){
            struct Node *temp = newNode->right;
            free(newNode);
            return temp;
        }
        if(newNode->left != NULL && newNode->right == NULL){
            struct Node *temp = newNode->left;
            free(newNode);
            return temp;
        }
        
        struct Node *temp = findMin(newNode->right);
        newNode->data = temp->data;
        newNode->right = deleteNode(newNode->right, temp->data);
    }

    return newNode;
}

int main(){
    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 45);
    
    printf("\nIn Order Traversal:\n");
    inorderTraversal(root);
    printf("\nPre Order Traversal:\n");
    preorderTraversal(root);
    printf("\nPost Order Traversal:\n");
    postorderTraversal(root);
    printf("\n");
    printf("\nSearch 20: %s\n", search(root, 20) ? "Found" : "Not found");
    printf("Search 50: %s\n", search(root, 50) ? "Found" : "Not found");
    printf("\n");
    printf("Minimum:");
    struct Node *minNode = findMin(root);
    if (minNode != NULL){
        printf(" %d\n", minNode->data);
    }
    
    printf("Maximum:");
    struct Node *maxNode = findMax(root);
    if (maxNode != NULL){
        printf(" %d\n", maxNode->data);
    }
    printf("\n");
    root = deleteNode(root, 10);
    printf("Search 10: %s\n", search(root, 10) ? "Found" : "Not found");

    return 0;
}