#include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int value;
    struct node *left;
    struct node *right;
}tree;

tree* createNode(int key){
    tree* newNode = (tree*) malloc(sizeof(tree));
    newNode->value = key;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

tree* insertNode(int key, tree* t){
    if(t == NULL){
        t = createNode(key);
        return t;
    }
    
    if(key < t->value){
        t->left = insertNode(key, t->left);
    }
    else if(key > t->value){
        t->right = insertNode(key, t->right);
    }

    return t;
}

void displayInorder(tree* t){
    if(t == NULL){
        return;
    }

    displayInorder(t->left);
    printf("%d, ", t->value);
    displayInorder(t->right);
}

void displayPreorder(tree* t){
    if(t == NULL){
        return;
    }

    printf("%d, ", t->value);
    displayPreorder(t->left);
    displayPreorder(t->right);
}

void displayPostorder(tree* t){
    if(t == NULL){
        return;
    }
    
    displayPostorder(t->left);
    displayPostorder(t->right);
    printf("%d, ", t->value);
}

tree* recursiveFind(int key, tree* t){
    if(t == NULL){
        return t;
    }
    else if(key < t->value){
        return recursiveFind(key, t->left);
    }
    else if(key > t->value){
        return recursiveFind(key, t->right);
    }
    else{
        return t;
    }
}

void iterativeFind(int key, tree* t){
    tree* temp = t;

    while(temp != NULL && temp->value != key){
        if(key < temp->value){
            temp = temp->left;
        }
        else{
            temp = temp->right;
        }
    }

    if(temp == NULL){
        printf("%d was not found in the tree.\n", key);
    }
    else{
        printf("%d exists in the tree.\n", key);
    }
}

int isBinarySearchTree(tree* t){
    if(t == NULL || (t->left==NULL && t->right==NULL)){
        return 1;
    }
    else if((t->left!=NULL && t->value < t->left->value) || (t->right!=NULL && t->value > t->right->value)){
        return 0;
    }
    
    return (isBinarySearchTree(t->left) && isBinarySearchTree(t->right));
}

int findMax(tree* t){
    tree* temp = t;
    
    if(temp == NULL){
        return -1;
    }

    while(temp->right != NULL){
        temp = temp->right;
    }

    return temp->value;
}

int findMin(tree* t){
    tree* temp = t;
    
    if(temp == NULL){
        return -1;
    }

    while(temp->left != NULL){
        temp = temp->left;
    }

    return temp->value;
}

void findPredecessor(tree* t, int key){
    if(t == NULL){
        printf("Tree is empty\n");
        return;
    }

    tree* temp = recursiveFind(key, t);
    if(temp->left != NULL){
        temp = temp->left;

        while(temp->right != NULL){
            temp = temp->right;
        }
    }

    if(temp->value != key){
        printf("Predecessor of %d is %d\n", key, temp->value);
    }
    else{
        printf("%d has no predecessor\n", key);
    }
}

tree* findSuccessor(tree* t, int key){
    if(t == NULL){
        return t;
    }

    tree* temp = recursiveFind(key, t);
    if(temp->right != NULL){
        temp = temp->right;

        while(temp->left != NULL){
            temp = temp->left;
        }
    }

    if(temp->value != key){
        return temp;
    }
    else{
        return NULL;
    }
}

tree* deleteNode(tree* t, int key){
    if(t == NULL){
        return t;
    }
    else if(key < t->value){
        t->left = deleteNode(t->left, key);
    }
    else if(key > t->value){
        t->right = deleteNode(t->right, key);
    }
    else{
        if(t->left == NULL){
            tree* temp = t->right;
            free(t);
            return temp;
        }
        else if(t->right == NULL){
            tree* temp = t->left;
            free(t);
            return temp;
        }

        tree* temp = findSuccessor(t, t->value);

        t->value = temp->value;

        t->right = deleteNode(t->right, temp->value);
    }
    return t;
}

int main(){
    tree* bst = NULL;

    bst = insertNode(8, bst);
    bst = insertNode(5, bst);
    bst = insertNode(11, bst);
    bst = insertNode(15, bst);
    bst = insertNode(13, bst);
    bst = insertNode(12, bst);
    bst = insertNode(6, bst);
    bst = insertNode(1, bst);
    bst = insertNode(9, bst);

    if(isBinarySearchTree(bst)==1){
        printf("Given tree is a binary search tree.\n");
    }
    else{
        printf("Given tree is not a binary search tree.\n");
    }

    printf("Inorder of tree: {");
    displayInorder(bst);
    printf("\b\b}\n");

    printf("Preorder of tree: {");
    displayPreorder(bst);
    printf("\b\b}\n");

    printf("Postorder of tree: {");
    displayPostorder(bst);
    printf("\b\b}\n");

    tree* found = recursiveFind(13, bst);
    if(found != NULL){
        printf("%d exists in the tree.\n", 13);
    }
    else{
        printf("%d was not found in the tree.\n", 13);
    }

    iterativeFind(1, bst);

    int max = findMax(bst);
    if(max!=-1){
        printf("Maximum value in tree: %d\n", max);
    }
    else{
        printf("Tree is empty\n");
    }

    int min = findMin(bst);
    if(min!=-1){
        printf("Minimum value in tree: %d\n", min);
    }
    else{
        printf("Tree is empty\n");
    }

    findPredecessor(bst, 5);

    tree* Suc = findSuccessor(bst, 8);
    if(Suc){
        printf("Successor of %d is %d\n", 8, Suc->value);
    }
    else{
        printf("%d has no successor\n", 8);
    }

    printf("Deleteing root of tree....\n");
    bst = deleteNode(bst, 8);

    printf("Inorder of tree: {");
    displayInorder(bst);
    printf("\b\b}\n");

    printf("Preorder of tree: {");
    displayPreorder(bst);
    printf("\b\b}\n");

    return 0;
}