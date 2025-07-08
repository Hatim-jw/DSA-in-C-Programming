#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct node{
    char c;
    int freq;
    struct node *left, *right;
}tree;

typedef struct fifo{
    tree* t;
    struct fifo *next;
}queue;

tree* createNode(char c, int freq){
    tree* t = (tree*) malloc(sizeof(tree));
    t->c = c;
    t->freq = freq;
    t->left = t->right = NULL;
    return t;
}

queue* createQueueNode(tree *t){
    queue* q = (queue*) malloc(sizeof(queue));
    q->t = t;
    q->next = NULL;
    return q;
}

queue* enqueue(queue* head, tree* t){
    queue* newNode = createQueueNode(t);
    
    if(head == NULL){
        head = newNode;
        return head;
    }

    if (t->freq < head->t->freq){
        newNode->next = head;
        return newNode;
    }

    queue* temp = head;
    while(temp->next != NULL && temp->next->t->freq <= newNode->t->freq){
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;

    return head;
}

tree* dequeue(queue** head){
    if(*head == NULL){
        return NULL;
    }

    tree* t = (*head)->t;
    queue* q = *head;
    *head = (*head)->next;
    free(q);
    return t;
}

tree* HuffmanTree(char str[], int freq[]){
    queue* q = NULL;

    for(int i=0 ; i<strlen(str); i++){
        q = enqueue(q, createNode(str[i], freq[i]));
    }

    while(q->next != NULL){
        tree* l = dequeue(&q);
        tree* r = dequeue(&q);

        tree* mid = createNode('\0', l->freq + r->freq);
        mid->left = l;
        mid->right = r;

        q = enqueue(q, mid);
    }

    return dequeue(&q);
}

void generateCodes(tree* t, char codes[256][256], char tempCode[], int top){
    if(t == NULL){
        return;
    }

    if(t->left==NULL && t->right==NULL){
        tempCode[top] = '\0';
        strcpy(codes[(int)t->c], tempCode);
        return;
    }

    tempCode[top] = '0';
    generateCodes(t->left, codes, tempCode, top + 1);

    tempCode[top] = '1';
    generateCodes(t->right, codes, tempCode, top + 1);
}

int main(){
    char* str = (char*) malloc(50*sizeof(char));
    printf("Enter a sentence: ");
    fgets(str, 50, stdin);
    str[strcspn(str, "\n")] = '\0';

    char chars[50];
    int freq[50];
    int k = 0;

    for(int i=0; i<strlen(str); i++){
        char curr = str[i];
        int count = 0;
        
        if(curr!=1){
            for(int j=i+1; j<strlen(str); j++){
                if(str[j] == curr){
                    count++;
                    str[j] = 1;
                }
            }
            chars[k] = curr;
            freq[k++] = count + 1;

        }
    }
    
    chars[k] = '\0';

    tree* root = HuffmanTree(chars, freq);

    char codes[256][256], temp[256];
    generateCodes(root, codes, temp, 0);

    printf("\nCodes for the respective characters:\n");
    for(int i=0; i<k; i++){
        if(chars[i] == ' '){
            printf("(space) : %s\n", codes[' ']);
            continue;
        }
        printf("%c : %s\n", chars[i], codes[chars[i]]);
    }
    printf("\n");
    
    free(str);
    return 0;
}