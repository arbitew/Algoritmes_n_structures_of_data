#include <iostream>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <cmath>
#include <vector>

using namespace std;

// Класс для узла бинарного дерева поиска
class TreeNode {
public:
    int data;
    TreeNode* left;
    TreeNode* right;

    TreeNode(int value) : data(value), left(nullptr), right(nullptr) {}
};

// Класс для бинарного дерева поиска
class BST {
public:
    TreeNode* root;

    BST() : root(nullptr) {}

    // Метод для вставки значения в дерево
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Рекурсивный метод для вставки значения в дерево
    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }

        return node;
    }

    //deleting start
    TreeNode* delst(int key) {
        return this->deleteNode(this->root, key);
    }

    //exiting left node
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }

    //deleting node
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr) {
                TreeNode* temp = root->right;
                delete root;
                return temp;
            }
            else if (root->right == nullptr) {
                TreeNode* temp = root->left;
                delete root;
                return temp;
            }

            TreeNode* temp = minValueNode(root->right);

            root->data = temp->data;

            root->right = deleteNode(root->right, temp->data);
        }
        return root;
    }

    // Метод для поиска значения в дереве
    bool search(int value) {
        return searchRecursive(root, value);
    }

    // Рекурсивный метод для поиска значения в дереве
    bool searchRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (node->data == value) {
            return true;
        }
        else if (value < node->data) {
            return searchRecursive(node->left, value);
        }
        else {
            return searchRecursive(node->right, value);
        }
    }
};

// Класс для AVL-дерева
class AVLTree {
public:
    TreeNode* root;

    AVLTree() : root(nullptr) {}

    // Метод для вставки значения в AVL-дерево
    void insert(int value) {
        root = insertRecursive(root, value);
    }

    // Рекурсивный метод для вставки значения в AVL-дерево
    TreeNode* insertRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return new TreeNode(value);
        }

        if (value < node->data) {
            node->left = insertRecursive(node->left, value);
        }
        else if (value > node->data) {
            node->right = insertRecursive(node->right, value);
        }
        else {
            return node; // Дубликаты не допускаются
        }

        // Пересчитываем высоту узла
        int balance = getBalance(node);

        // Левое вращение
        if (balance > 1 && value < node->left->data) {
            return rightRotate(node);
        }

        // Правое вращение
        if (balance < -1 && value > node->right->data) {
            return leftRotate(node);
        }

        // Лево-правое вращение
        if (balance > 1 && value > node->left->data) {
            node->left = leftRotate(node->left);
            return rightRotate(node);
        }

        // Право-левое вращение
        if (balance < -1 && value < node->right->data) {
            node->right = rightRotate(node->right);
            return leftRotate(node);
        }

        return node;
    }
    //deleting start
    TreeNode* delst(int key) {
        return this->deleteNode(this->root, key);
    }
    //existing left node
    TreeNode* minValueNode(TreeNode* node) {
        TreeNode* current = node;
        while (current && current->left != nullptr)
            current = current->left;
        return current;
    }
    // deleting node
    TreeNode* deleteNode(TreeNode* root, int key) {
        if (root == nullptr) return root;

        if (key < root->data)
            root->left = deleteNode(root->left, key);
        else if (key > root->data)
            root->right = deleteNode(root->right, key);
        else {
            if (root->left == nullptr || root->right == nullptr) {
                TreeNode* temp = root->left ? root->left : root->right;
                if (temp == nullptr) {
                    temp = root;
                    root = nullptr;
                }
                else
                    *root = *temp;
                delete temp;
            }
            else {
                TreeNode* temp = minValueNode(root->right);
                root->data = temp->data;
                root->right = deleteNode(root->right, temp->data);
            }
        }

        if (root == nullptr)
            return root;

        //root->height = 1 + std::max(height(root->left), height(root->right));

        int balance = getBalance(root);

        if (balance > 1 && getBalance(root->left) >= 0)
            return rightRotate(root);

        if (balance > 1 && getBalance(root->left) < 0) {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }

        if (balance < -1 && getBalance(root->right) <= 0)
            return leftRotate(root);

        if (balance < -1 && getBalance(root->right) > 0) {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }

        return root;
    }

    // Метод для поиска значения в AVL-дереве
    bool search(int value) {
        return searchRecursive(root, value);
    }

    // Рекурсивный метод для поиска значения в AVL-дереве
    bool searchRecursive(TreeNode* node, int value) {
        if (node == nullptr) {
            return false;
        }

        if (node->data == value) {
            return true;
        }
        else if (value < node->data) {
            return searchRecursive(node->left, value);
        }
        else {
            return searchRecursive(node->right, value);
        }
    }

private:
    // Метод для получения высоты узла
    int height(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        return max(height(node->left), height(node->right)) + 1;
    }

    // Метод для получения баланса узла
    int getBalance(TreeNode* node) {
        if (node == nullptr) {
            return 0;
        }

        return height(node->left) - height(node->right);
    }

    // Метод для правого вращения поддерева с корнем node
    TreeNode* rightRotate(TreeNode* node) {
        TreeNode* leftChild = node->left;
        TreeNode* rightOfLeftChild = leftChild->right;

        leftChild->right = node;
        node->left = rightOfLeftChild;

        return leftChild;
    }

    // Метод для левого вращения поддерева с корнем node
    TreeNode* leftRotate(TreeNode* node) {
        TreeNode* rightChild = node->right;
        TreeNode* leftOfRightChild = rightChild->left;

        rightChild->left = node;
        node->right = leftOfRightChild;

        return rightChild;
    }
};

// Функция для генерации случайного числа в диапазоне [min, max]
int generateRandom(int min, int max) {
    return rand() % (max - min + 1) + min;
}

// Функция для заполнения массива случайными значениями
void fillRandomArray(vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr.push_back(generateRandom(1, size * 10)); // Для уникальности значений
    }
}

// Функция для заполнения массива значениями в порядке возрастания
void fillSortedArray(vector<int>& arr, int size) {
    for (int i = 1; i <= size; ++i) {
        arr.push_back(i);
    }
}

// Функция для замера времени вставки массива в деревья
void measureInsertionTime(BST& bst, AVLTree& avl, const vector<int>& arr) {
    auto start = chrono::steady_clock::now();

    // Вставка значений массива в BST
    for (int num : arr) {
        bst.insert(num);
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "BST insertion time: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;

    start = chrono::steady_clock::now();

    // Вставка значений массива в AVL
    for (int num : arr) {
        avl.insert(num);
    }

    end = chrono::steady_clock::now();
    diff = end - start;
    cout << "AVL insertion time: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
}

// Функция для замера времени поиска в деревьях
void measureSearchTime(BST& bst, AVLTree& avl, const vector<int>& searchValues) {
    auto start = chrono::steady_clock::now();

    // Поиск значений в BST
    for (int num : searchValues) {
        bst.search(num);
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "BST search time: " << chrono::duration <double, milli>(diff).count() << " ms for 1000 searches" << endl;

    start = chrono::steady_clock::now();

    // Поиск значений в AVL
    for (int num : searchValues) {
        avl.search(num);
    }

    end = chrono::steady_clock::now();
    diff = end - start;
    cout << "AVL search time: " << chrono::duration <double, milli>(diff).count() << " ms for 1000 searches" << endl;
}

// Функция для замера времени поиска в массиве
void measureArraySearchTime(const vector<int>& arr, const vector<int>& searchValues) {
    auto start = chrono::steady_clock::now();

    // Поиск значений в массиве
    for (int num : searchValues) {
        for (int value : arr) {
            if (value == num) {
                break;
            }
        }
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "Array search time: " << chrono::duration <double, milli>(diff).count() << " ms for 1000 searches" << endl;
}

// Функция для замера времени удаления значений из деревьев
void measureDeletionTime(BST& bst, AVLTree& avl, const vector<int>& searchValues) {
    auto start = chrono::steady_clock::now();

    // Удаление значений из BST
    for (int num : searchValues) {
        bst.delst(num);
    }

    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    cout << "BST deletion time: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;

    start = chrono::steady_clock::now();

    // Удаление значений из AVL
    for (int num : searchValues) {
        avl.delst(num);
    }

    end = chrono::steady_clock::now();
    diff = end - start;
    cout << "AVL deletion time: " << chrono::duration <double, milli>(diff).count() << " ms" << endl;
}

// Главная функция для тестирования
int main() {
    srand(time(nullptr));
    

    for (int i = 0; i < 5; ++i) {
        int size = pow(2, 10 + i);
        vector<int> randomArray;
        vector<int> sortedArray;
        vector<int> searchValues;

        fillRandomArray(randomArray, size);
        fillSortedArray(sortedArray, size);

        // Создаем экземпляры деревьев
        BST bst;
        AVLTree avl;

        cout << "Testing for array size: " << size << endl;
        cout << "----------------------------------" << endl;

        // Замер времени вставки массива в деревья
        measureInsertionTime(bst, avl, randomArray);

        // Генерируем случайные значения для поиска
        for (int j = 0; j < pow(2, 10 + i); ++j) {
            searchValues.push_back(generateRandom(1, size * 10));
        }
        /*for (int j = 0; j < pow(2, 10 + i); ++j) {
            searchValues.push_back(j);
        }*/
        // Замер времени поиска в деревьях
        measureSearchTime(bst, avl, searchValues);

        // Замер времени поиска в массиве
        measureArraySearchTime(randomArray, searchValues);

        // Замер времени удаления значений из деревьев
        measureDeletionTime(bst, avl, searchValues);

        cout << "----------------------------------" << endl;
    }


    return 0;
}