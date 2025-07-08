#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
    int key;
    struct Node* left;
    struct Node* right;
    int balanceFactor;
}tree;

int height(tree* root){
    if(root == NULL){
        return -1;
    }

    int l_height = height(root->left);
    int r_height = height(root->right);

    if(l_height >= r_height){
        return l_height + 1;
    }
    else{
        return r_height + 1;
    }
}

tree* createNode(int key) {
    tree* newNode = (tree*)malloc(sizeof(tree));
    newNode->key = key;
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->balanceFactor = 0;
    return newNode;
}

tree* leftRight(tree* x){
    tree* t1 = x->left;
    tree* t2 = t1->right;

    t1->right = t2->left;
    t2->left = t1;
    t1->balanceFactor = height(t1->left) - height(t1->right);

    x->left = t2->right;
    t2->right = x;
    x->balanceFactor = height(x->left) - height(x->right);

    t2->balanceFactor = height(t2->left) - height(t2->right);
    return t2;
}

tree* rightLeft(tree* x){
    tree* t1 = x->right;
    tree* t2 = t1->left;

    t1->left = t2->right;
    t2->right = t1;
    t1->balanceFactor = height(t1->left) - height(t1->right);

    x->right = t2->left;
    t2->left = x;
    x->balanceFactor = height(x->left) - height(x->right);
    
    t2->balanceFactor = height(t2->left) - height(t2->right);
    return t2;
}

tree* leftLeft(tree* x){
    tree* t1 = x->left;

    x->left = t1->right;
    t1->right = x;
    x->balanceFactor = height(x->left) - height(x->right);

    t1->balanceFactor = height(t1->left) - height(t1->right);
    return t1;
}

tree* rightRight(tree* x){
    tree* t1 = x->right;

    x->right = t1->left;
    t1->left = x;
    x->balanceFactor = height(x->left) - height(x->right);

    t1->balanceFactor = height(t1->left) - height(t1->right);
    return t1;
}

tree* insert(tree* node, int key){
    if(node == NULL){
        return createNode(key);
    }

    if(key < node->key){
        node->left = insert(node->left, key);
    }
    else if(key > node->key){
        node->right = insert(node->right, key);
    }
    else{
        return node;
    }

    node->balanceFactor = height(node->left) - height(node->right);

    // Left Left Case
    if(node->balanceFactor > 1 && key < node->left->key){
        return leftLeft(node);
    }

    // Right Right Case
    if (node->balanceFactor < -1 && key > node->right->key) {
        return rightRight(node);
    }

    // Left Right Case
    if (node->balanceFactor > 1 && key > node->left->key){
        return leftRight(node);
    }

    // Right Left Case
    if (node->balanceFactor < -1 && key < node->right->key) {
        return rightLeft(node);
    }

    // Return the unchanged node pointer
    return node;
}

void inorder(tree* root){
    if(root == NULL){
        return;
    }

    inorder(root->left);
    printf("%d ", root->key);
    inorder(root->right);
}

tree* Successor(tree* root){
    if(root == NULL){
        return root;
    }

    tree* temp = root;
    if(temp->right != NULL){
        temp = temp->right;
        
        while(temp->left != NULL){
            temp = temp->left;
        }
    }
    return temp;
}

int getBalance(tree* t){
    if(t == NULL){
        return 0;
    }

    return t->balanceFactor;
}

tree* delete(tree* t, int key){
    if(t == NULL){
        return t;
    }
    else if(key < t->key){
        t->left = delete(t->left, key);
    }
    else if(key > t->key){
        t->right = delete(t->right, key);
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

        tree* temp = Successor(t);
        t->key = temp->key;
        t->right = delete(t->right, temp->key);
    }

    if(t == NULL){
        return t;
    }

    t->balanceFactor = height(t->left) - height(t->right);

    // Left Left Case
    if (t->balanceFactor > 1 && getBalance(t->left) >= 0) {
        return leftLeft(t);
    }

    // Right Right Case
    if (t->balanceFactor < -1 && getBalance(t->right) <= 0) {
        return rightRight(t);
    }

    // Left Right Case
    if (t->balanceFactor > 1 && getBalance(t->left) < 0) {
        return leftRight(t);
    }

    // Right Left Case
    if (t->balanceFactor < -1 && getBalance(t->right) > 0) {
        return rightLeft(t);
    }

    return t;
}

int main() {
    tree* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 15);
    root = insert(root, 25);
    root = insert(root, 5);
    root = insert(root, 3);

    printf("Inorder traversal of the AVL tree is: ");
    inorder(root);
    printf("\n");

    root = delete(root, 25);

    printf("Inorder traversal of the AVL tree is: ");
    inorder(root);
    printf("\n");

    return 0;
}