#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// A Huffman tree node 
struct MinHeapNode{ 
    // One of the input characters 
	char data; 

	// Frequency of the character 
	unsigned freq; 

	// Left and right child of this node 
	struct MinHeapNode *left, *right; 
}; 

// A Min Heap: Collection of 
// min-heap (or Huffman tree) nodes 
struct MinHeap{ 
    // Current size of min heap 
	unsigned size; 

	// capacity of min heap 
	unsigned capacity; 

	// Array of minheap node pointers 
	struct MinHeapNode** array; 
}; 

// A utility function allocate a new 
// min heap node with given character 
// and frequency of the character 
struct MinHeapNode* newNode(char data, unsigned freq) 
{ 
	struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode)); 
    temp->left = temp->right = NULL; 
	temp->data = data; 
	temp->freq = freq; 

	return temp; 
} 

// A utility function to create 
// a min heap of given capacity 
struct MinHeap* createMinHeap(unsigned capacity){ 
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap)); 

	// current size is 0 
	minHeap->size = 0; 

	minHeap->capacity = capacity; 

	minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*)); 
	return minHeap; 
} 

// A utility function to 
// swap two min heap nodes 
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b){ 
    struct MinHeapNode* t = *a; 
	*a = *b; 
	*b = t; 
} 

// The standard minHeapify function. 
void minHeapify(struct MinHeap* minHeap, int idx){ 
    int smallest = idx; 
	int left = 2 * idx + 1; 
	int right = 2 * idx + 2; 

	if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) 
		smallest = left; 

	if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) 
		smallest = right; 

	if (smallest != idx) { 
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]); 
		minHeapify(minHeap, smallest); 
	} 
} 

// A utility function to check 
// if size of heap is 1 or not 
int isSizeOne(struct MinHeap* minHeap){ 
    return (minHeap->size == 1); 
} 

// A standard function to extract 
// minimum value node from heap 
struct MinHeapNode* extractMin(struct MinHeap* minHeap){ 
    struct MinHeapNode* temp = minHeap->array[0]; 
	minHeap->array[0] = minHeap->array[minHeap->size - 1]; 

	--minHeap->size; 
	minHeapify(minHeap, 0); 

	return temp; 
} 

// A utility function to insert 
// a new node to Min Heap 
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode){ 
    ++minHeap->size; 
	int i = minHeap->size - 1; 

	while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) { 
        minHeap->array[i] = minHeap->array[(i - 1) / 2]; 
		i = (i - 1) / 2; 
	} 

	minHeap->array[i] = minHeapNode; 
} 

// A standard function to build min heap 
void buildMinHeap(struct MinHeap* minHeap){ 
    int n = minHeap->size - 1;

	for (int i=(n-1)/2; i>=0; --i){
		minHeapify(minHeap, i);
    }
} 

// A utility function to print an array of size n 
void printArr(int arr[], int n){
	for (int i = 0; i < n; ++i){
		printf("%d", arr[i]); 
    }
	printf("\n"); 
} 

// Utility function to check if this node is leaf 
int isLeaf(struct MinHeapNode* root){ 
    return !(root->left) && !(root->right); 
} 

void countFreq(const char *sentence, char *arr, int *freq, int *uniqueCount){
    int size = strlen(sentence);

    for(int i=0; i<size; i++){
        arr[(int)sentence[i]] = sentence[i];
        freq[(int)sentence[i]] += 1;
    }

    *uniqueCount = 0;
    for(int i=0; i<256; i++){
        if(freq[i] > 0){
            *uniqueCount += 1;
        }
    }
}

struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int uniqueCount){
    struct MinHeap* minHeap = createMinHeap(uniqueCount);

    for(int i=0; i<256; i++){
        if(freq[i] > 0){
            minHeap->array[minHeap->size] = newNode(data[i], freq[i]);
            minHeap->size++;
        }
    }
    buildMinHeap(minHeap);

    while(!isSizeOne(minHeap)){
        struct MinHeapNode* left = extractMin(minHeap);
        struct MinHeapNode* right = extractMin(minHeap);

        struct MinHeapNode* mid = newNode('\0', left->freq + right->freq);
        mid->left = left;
        mid->right = right;

        insertMinHeap(minHeap, mid);
    }

    return extractMin(minHeap);
}

void printCodes(struct MinHeapNode* root, int arr[], int top){
    if(root == NULL){
        return;
    }

    if(isLeaf(root)){
        if(root->data == ' '){
            printf("(space) : ");
        }
        else{
            printf("%c : ", root->data);
        }
        printArr(arr, top);
    }

    arr[top] = 0;
    printCodes(root->left, arr, top + 1);

    arr[top] = 1;
    printCodes(root->right, arr, top + 1);
}

void HuffmanCodes(char data[], int freq[], int uniqueCount){
    struct MinHeapNode* root = buildHuffmanTree(data, freq, uniqueCount);
    
    int arr[256];
    printCodes(root, arr, 0);
    printf("\n");

    printf("No. of unique characters = %d\n", uniqueCount);
}

int main(){
    char sentence[] = "iit patna is situated in bihta";
    char arr[256]; // Assuming max 256 unique characters
    int freq[256];
    int uniqueCount;

    for(int i=0; i<256; i++){
        freq[i] = 0;
    }

    countFreq(sentence, arr, freq, &uniqueCount);
    HuffmanCodes(arr, freq, uniqueCount);
    
    return 0;
}