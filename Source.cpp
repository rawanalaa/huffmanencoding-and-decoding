#include <iostream>
#include <fstream>
#include<vector> 
#include<algorithm>
#include <sstream>
#include<map>
#define MAX_TREE_HT 256
using namespace std;
void BinaryToDecimal (int n);
struct MinNode { 
    char data;
    unsigned frequency; 
    struct MinNode* left, * right;
};
struct Heap {
    unsigned size;
    unsigned capacity;
    struct MinNode** arr;
};
struct MinNode* newNode(char data, unsigned f)
{
    struct MinNode* temp
        = (struct MinNode*)malloc
        (sizeof(struct MinNode));

    temp->left = temp->right = NULL;
    temp->data = data;
    temp->frequency = f;
    return temp;
}
struct Heap* createMinHeap(unsigned capacity)

{
      struct Heap* minHeap = (struct Heap*)malloc(sizeof(struct Heap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->arr = (struct MinNode**)malloc(minHeap-> capacity * sizeof(struct MinNode*));
    return minHeap;
}
void swapMinHeapNode(struct MinNode** a, struct MinNode** b)
{

    struct MinNode* t = *a;
    *a = *b;
    *b = t;
}
void Heapify(struct Heap* minHeap, int idx)

{

    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->arr[left]->
        frequency < minHeap->arr[smallest]->frequency)
        smallest = left;

    if (right < minHeap->size && minHeap->arr[right]->
        frequency < minHeap->arr[smallest]->frequency)
        smallest = right;

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->arr[smallest],
            &minHeap->arr[idx]);
        Heapify(minHeap, smallest);
    }
}
int isSizeOne(struct Heap* minHeap)
{

    return (minHeap->size == 1);
}
struct MinNode* extractMin(struct Heap* minHeap)
{

    struct MinNode* temp = minHeap->arr[0];
    minHeap->arr[0]
        = minHeap->arr[minHeap->size - 1];
        --minHeap->size;
     Heapify(minHeap, 0);
     return temp;
}
void insertHeap(struct Heap* minHeap, struct MinNode* minHeapNode)

{
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->frequency < minHeap->arr[(i - 1) / 2]->frequency) {

        minHeap->arr[i] = minHeap->arr[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->arr[i] = minHeapNode;
}
void buildMinHeap(struct Heap* minHeap)

{

    int n = minHeap->size - 1;
    int i;

    for (i = (n - 1) / 2; i >= 0; --i)
        Heapify(minHeap, i);
}
void print(int arr[], int n)
{
    for (int i = 0; i < n; ++i)
        cout << arr[i];

    cout << "\n";
}
int isLeaf(struct MinNode* root)
{

    return !(root->left) && !(root->right);
}
struct Heap* BuildHeap(vector<char> l, vector<int> freq)

{

    struct Heap* minHeap = createMinHeap(l.size());

    for (int i = 0; i < l.size(); ++i)
        minHeap->arr[i] = newNode(l[i], freq[i]);
    minHeap->size = l.size();
    buildMinHeap(minHeap);
    return minHeap;
}
struct MinNode* buildHuffmanTree(vector<char> l, vector<int> freq)

{
    struct MinNode* left, * right, * top; 
    struct Heap* minHeap = BuildHeap(l, freq);
    while (!isSizeOne(minHeap)) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);
        top = newNode('$', left->frequency + right->frequency);
        top->left = left;
        top->right = right;
        insertHeap(minHeap, top);
    }
    return extractMin(minHeap);
}
void printCodes(struct MinNode* root, int arr[], int top)
{ 
    if (root->left) {

        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }
    if (root->right) {

        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }
    if (isLeaf(root)) {

        cout << root->data << ": ";
        print(arr, top);
    }
}
void HuffmanCodes(vector<char> l, vector<int> freq)
{
    struct MinNode* root = buildHuffmanTree(l, freq);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}
int main()
{
    vector<char> l, R;
    vector<int> freq;
    int count=1;
    ifstream f("file.txt", ios::binary | ios::in);
    char c;
    vector<int> ascii;
    while (f.get(c))
        l.push_back(c);
    sort(l.begin(), l.end());
    for (int i = 0; i < l.size()-1; i++)
    {
        if (l[i] == l[i+1])
            count++;
        else 
        {
            R.push_back(l[i]);
            freq.push_back(count);
            ascii.push_back(int(l[i]));
            if (l[i + 1] == l[l.size() - 1])
            {
                ascii.push_back(int(l[i + 1]));
                R.push_back(l[i + 1]);
                freq.push_back(count);
            }
            count = 1;
        }
    }
    int size = sizeof(R) / sizeof(R[0]);
    HuffmanCodes(R, freq);
}
int binaryToDecimal(int n)
{
    int num = n;
    int dec_value = 0;
    int base = 1;
    int temp = num;
    while (temp) {
        int last_digit = temp % 10;
        temp = temp / 10;
 
        dec_value += last_digit * base;
 
        base = base * 2;
    }
    return dec_value;
}