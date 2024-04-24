#include <iostream>
#include <vector>
#include <queue>
#include <ctime>

using namespace std;

// Binary Heap Implementation
class BinaryHeap {
private:
    vector<int> heap;

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)] > heap[index]) {
            swap(heap[index], heap[parent(index)]);
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int left = leftChild(index);
        int right = rightChild(index);
        int smallest = index;
        if (left < heap.size() && heap[left] < heap[index])
            smallest = left;
        if (right < heap.size() && heap[right] < heap[smallest])
            smallest = right;
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapifyDown(smallest);
        }
    }

public:
    BinaryHeap() {}

    int parent(int index) { return (index - 1) / 2; }
    int leftChild(int index) { return 2 * index + 1; }
    int rightChild(int index) { return 2 * index + 2; }

    void insert(int key) {
        heap.push_back(key);
        int index = heap.size() - 1;
        heapifyUp(index);
    }

    int findMin() {
        if (heap.empty()) return -1; // or throw exception
        return heap[0];
    }

    int extractMin() {
        if (heap.empty()) return -1; // or throw exception
        int min = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapifyDown(0);
        return min;
    }
};

// Fibonacci Heap Implementation
class FibonacciHeap {
private:
    // Node structure
    struct Node {
        int key;
        Node* parent;
        Node* child;
        Node* left;
        Node* right;
        int degree;
        bool marked;
    };

    Node* minNode;
    int numNodes;

public:
    FibonacciHeap() : minNode(nullptr), numNodes(0) {}

    void insert(int key) {
        Node* newNode = new Node();
        newNode->key = key;
        newNode->degree = 0;
        newNode->marked = false;
        newNode->parent = nullptr;
        newNode->child = nullptr;
        newNode->left = newNode;
        newNode->right = newNode;

        if (minNode == nullptr) {
            minNode = newNode;
        }
        else {
            newNode->left = minNode;
            newNode->right = minNode->right;
            minNode->right->left = newNode;
            minNode->right = newNode;
            if (key < minNode->key)
                minNode = newNode;
        }
        numNodes++;
    }

    int findMin() {
        if (minNode == nullptr) return -1; // or throw exception
        return minNode->key;
    }

    int extractMin() {
        if (minNode == nullptr) return -1; // or throw exception
        Node* min = minNode;
        if (min->child != nullptr) {
            Node* child = min->child;
            do {
                Node* next = child->right;
                child->left->right = child->right;
                child->right->left = child->left;
                child->left = minNode;
                child->right = minNode->right;
                minNode->right->left = child;
                minNode->right = child;
                child->parent = nullptr;
                child = next;
            } while (child != min->child);
        }

        min->left->right = min->right;
        min->right->left = min->left;

        if (min == min->right)
            minNode = nullptr;
        else {
            minNode = min->right;
            consolidate();
        }
        int minKey = min->key;
        delete min;
        numNodes--;
        return minKey;
    }

private:
    void consolidate() {
        vector<Node*> degreeRoots(numNodes, nullptr);
        queue<Node*> nodesQueue;
        nodesQueue.push(minNode);

        while (!nodesQueue.empty()) {
            Node* x = nodesQueue.front();
            nodesQueue.pop();
            int degree = x->degree;
            while (degreeRoots[degree] != nullptr) {
                Node* y = degreeRoots[degree];
                if (x->key > y->key) swap(x, y);
                link(y, x);
                degreeRoots[degree] = nullptr;
                degree++;
            }
            degreeRoots[degree] = x;
        }

        minNode = nullptr;
        for (Node* root : degreeRoots) {
            if (root != nullptr) {
                if (minNode == nullptr) {
                    minNode = root;
                }
                else {
                    root->left->right = root->right;
                    root->right->left = root->left;
                    root->left = minNode;
                    root->right = minNode->right;
                    minNode->right->left = root;
                    minNode->right = root;
                    if (root->key < minNode->key)
                        minNode = root;
                }
            }
        }
    }

    void link(Node* y, Node* x) {
        y->left->right = y->right;
        y->right->left = y->left;

        y->left = y;
        y->right = y;
        y->parent = x;

        if (x->child == nullptr) {
            x->child = y;
        }
        else {
            y->left = x->child;
            y->right = x->child->right;
            x->child->right->left = y;
            x->child->right = y;
        }
        x->degree++;
        y->marked = false;
    }
};

int main() {
    // Binary Heap
    BinaryHeap binaryHeap;
    clock_t start, end;
    double totalTime = 0.0, maxTime = 0.0;

    for (int i = 3; i <= 7; ++i) {
        int N = pow(10, i);
        cout << "Testing Binary Heap with N = " << N << endl;

        // Insert N elements
        start = clock();
        for (int j = 0; j < N; ++j)
            binaryHeap.insert(j);
        end = clock();
        double insertTime = double(end - start) / CLOCKS_PER_SEC;
        cout << "Insertion time for " << N << " elements: " << insertTime << " seconds" << endl;
        totalTime += insertTime;
        maxTime = max(maxTime, insertTime);

        // Testing findMin() and extractMin()
        start = clock();
        for (int j = 0; j < 1000; ++j) {
            binaryHeap.findMin();
            binaryHeap.extractMin();
        }
        end = clock();
        double findExtractTime = double(end - start) / CLOCKS_PER_SEC;
        cout << "Find and extract minimum 1000 times: " << findExtractTime << " seconds" << endl;
        totalTime += findExtractTime;
        maxTime = max(maxTime, findExtractTime);

        // Testing insert() 1000 times
        start = clock();
        for (int j = 0; j < 1000; ++j)
            binaryHeap.insert(j);
        end = clock();
        double insertAgainTime = double(end - start) / CLOCKS_PER_SEC;
        cout << "Inserting 1000 elements: " << insertAgainTime << " seconds" << endl;
        totalTime += insertAgainTime;
        maxTime = max(maxTime, insertAgainTime);

        cout << endl;
    }

    cout << "Total time for Binary Heap operations: " << totalTime << " seconds" << endl;
    cout << "Max time for a single operation: " << maxTime << " seconds" << endl << endl;

    // Fibonacci Heap
    FibonacciHeap fibHeap;
    totalTime = 0.0;
    maxTime = 0.0;

    for (int i = 3; i <= 7; ++i) {
        int N = pow(10, i);
        cout << "Testing Fibonacci Heap with N = " << N << endl;

        // Insert N elements
        start = clock();
        for (int j = 0; j < N; ++j)
            fibHeap.insert(j);
        end = clock();
        double insertTime = double(end - start) / CLOCKS_PER_SEC;
        cout << "Insertion time for " << N << " elements: " << insertTime << " seconds" << endl;
        totalTime += insertTime;
        maxTime = max(maxTime, insertTime);

        // Testing findMin() and extractMin()
        start = clock();
        for (int j = 0; j < 1000; ++j) {
            fibHeap.findMin();
            fibHeap.extractMin();
        }
        end = clock();
        double findExtractTime = double(end - start) / CLOCKS_PER_SEC;
        cout << "Find and extract minimum 1000 times: " << findExtractTime << " seconds" << endl;
        totalTime += findExtractTime;
        maxTime = max(maxTime, findExtractTime);

        // Testing insert() 1000 times
        start = clock();
        for (int j = 0; j < 1000; ++j)
            fibHeap.insert(j);
        end = clock();
        double insertAgainTime = double(end - start) / CLOCKS_PER_SEC;
        cout << "Inserting 1000 elements: " << insertAgainTime << " seconds" << endl;
        totalTime += insertAgainTime;
        maxTime = max(maxTime, insertAgainTime);

        cout << endl;
    }

    cout << "Total time for Fibonacci Heap operations: " << totalTime << " seconds" << endl;
    cout << "Max time for a single operation: " << maxTime << " seconds" << endl;

    return 0;
}