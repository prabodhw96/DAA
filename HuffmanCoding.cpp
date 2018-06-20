#include <iostream>
#include <cstdlib>
using namespace std;
#define MAX_TREE_HT 100
class node {
    public:
        char data;
        unsigned freq;
        node *left, *right;
};
class MinHeap {
    public:
        unsigned size;
        unsigned capacity;
        node** arr;
};
node* newNode(char data, unsigned freq)
{
    node *temp;
    temp = new node;
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}
MinHeap *createMinHeap(unsigned capacity)
{
    MinHeap *minHeap = new MinHeap;
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->arr = new node*[minHeap->capacity];
    return minHeap;
}
void swapNode(node** a, node** b)
{
    node *t = *a;
    *a = *b;
    *b = t;
}
void minHeapify(struct MinHeap* minHeap, int idx)
{
    int smallest = idx;
    int left = 2*idx+1;
    int right = 2*idx+2;
    if(left<minHeap->size && minHeap->arr[left]->freq<minHeap->arr[smallest]->freq)
        smallest = left;
    if (right<minHeap->size && minHeap->arr[right]->freq<minHeap->arr[smallest]->freq)
        smallest = right;
    if (smallest != idx) {
        swapNode(&minHeap->arr[smallest], &minHeap->arr[idx]);
        minHeapify(minHeap, smallest);
    }
}
int isSizeOne(MinHeap* minHeap)
{
    return (minHeap->size == 1);
}
node* extractMin(MinHeap* minHeap)
{
    node* temp = minHeap->arr[0];
    minHeap->arr[0] = minHeap->arr[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}
void insertMinHeap(MinHeap* minHeap, node* Node)

{

    ++minHeap->size;
    int i = minHeap->size - 1;
    while(i && Node->freq<minHeap->arr[(i-1)/2]->freq){
        minHeap->arr[i] = minHeap->arr[(i-1)/2];
        i = (i-1)/2;
    }
    minHeap->arr[i] = Node;
}
void buildMinHeap(MinHeap* minHeap)
{
    int n = minHeap->size - 1;
    int i;
    for (i=(n-1)/2; i>=0; --i)
        minHeapify(minHeap, i);
}
void printArr(int arr[], int n)
{
    for(int i=0; i<n; i++)
        cout<<arr[i];
    cout<<endl;
}
int isLeaf(node *root)
{
    return !(root->left) && !(root->right);
}
MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)
{

    MinHeap* minHeap = createMinHeap(size);
    for(int i=0; i<size; i++)
        minHeap->arr[i] = newNode(data[i], freq[i]);
    minHeap->size = size;
    buildMinHeap(minHeap);
    return minHeap;
}
node* buildHuffmanTree(char data[], int freq[], int size)
{
    node *left, *right, *top;
    MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);
    while(!isSizeOne(minHeap))
    {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;
        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
void printCodes(node *root, int arr[], int top)
{
    if(root->left)
    {
        arr[top] = 0;
        printCodes(root->left, arr, top+1);
    }
    if(root->right)
    {
        arr[top] = 1;
        printCodes(root->right, arr, top+1);
    }
    if(isLeaf(root))
    {
        cout<<root->data<<": ";
        printArr(arr, top);
    }
}
void HuffmanCodes(char data[], int freq[], int size)
{
    node *root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top=0;
    printCodes(root, arr, top);
}
int main()
{
    char arr[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(arr) / sizeof(arr[0]);
    HuffmanCodes(arr, freq, size);
    return 0;
}
