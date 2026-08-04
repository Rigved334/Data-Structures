#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node{
    int data;
    int height;
    struct Node *right;
    struct Node *left;
};

struct AVLT{
    struct Node *root;
};

int max(int a, int b){
    if(a > b){
        return a;
    }
    return b;
}

int height(struct Node *newNode){
    if(newNode == NULL){
        return 0;
    }

    return newNode->height;
}

int balanceFactor(struct Node *newNode){
    if(newNode == NULL){
        return 0;
    }

    return height(newNode->left) - height(newNode->right);
}

struct Node* createNode(int data){
    struct Node *newNode = malloc(sizeof(struct Node));
    if(newNode == NULL){
        printf("Could not allocate memory\n");
        return NULL;
    }

    newNode->data = data;
    newNode->right = NULL;
    newNode->left = NULL;
    newNode->height = 1;

    return newNode;
}

struct Node *Rrotation(struct Node *y){
    struct Node *x = y->left;
    struct Node *T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

struct Node *Lrotation(struct Node *x){
    struct Node *y = x->right;
    struct Node *T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

struct Node *rebalance(struct Node *newNode){
    if(newNode == NULL){
        return NULL;
    }

    int BF = balanceFactor(newNode);

    if(BF < -1){
        int BF_Rchild = balanceFactor(newNode->right);
        if(BF_Rchild > 0){
            newNode->right = Rrotation(newNode->right);
            return Lrotation(newNode);
        }
        else if(BF_Rchild <= 0){
            return Lrotation(newNode);
        }
    }

    else if(BF > 1){
        int BF_Lchild = balanceFactor(newNode->left);
        if(BF_Lchild >= 0){
            return Rrotation(newNode);
        }
        else if(BF_Lchild < 0){
            newNode->left = Lrotation(newNode->left);
            return Rrotation(newNode);
        }
    }

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

    newNode->height = max(height(newNode->left), height(newNode->right)) + 1;
    return rebalance(newNode);
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

    newNode->height = max(height(newNode->left), height(newNode->right)) + 1;
    return rebalance(newNode);
}

void printAVLInfo(struct Node *root){
    if(root == NULL){
        return;
    }

    printAVLInfo(root->left);

    printf("Value: %d, Height: %d, BF: %d\n",
           root->data,
           root->height,
           balanceFactor(root));

    printAVLInfo(root->right);
}

int main(){

    struct Node *root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 45);
    
    printf("In Order Traversal:\n");
    inorderTraversal(root);
    printf("\nPre Order Traversal:\n");
    preorderTraversal(root);
    printf("\nPost Order Traversal:\n");
    postorderTraversal(root);
    printf("\n");

    printf("\nInfo about Tree:\n");
    printAVLInfo(root);
    printf("\n");

    root = deleteNode(root, 10);
    printf("Search 10: %s\n", search(root, 10) ? "Found" : "Not found");

    return 0;
}