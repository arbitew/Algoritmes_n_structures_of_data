#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <fstream>

struct Node {
    int key;
    int priority;
    Node* left;
    Node* right;

    Node(int k, int p) : key(k), priority(p), left(nullptr), right(nullptr) {}
};

class DecartTree {
private:
    Node* root;

    // Методы для операций с деревом
    void split(Node* tree, int key, Node*& left, Node*& right) {
        if (!tree) {
            left = right = nullptr;
        }
        else if (key < tree->key) {
            split(tree->left, key, left, tree->left);
            right = tree;
        }
        else {
            split(tree->right, key, tree->right, right);
            left = tree;
        }
    }

    Node* merge(Node* left, Node* right) {
        if (!left || !right) {
            return left ? left : right;
        }
        else if (left->priority > right->priority) {
            left->right = merge(left->right, right);
            return left;
        }
        else {
            right->left = merge(left, right->left);
            return right;
        }
    }

    void insert(Node*& tree, Node* node) {
        if (!tree) {
            tree = node;
        }
        else if (node->priority > tree->priority) {
            split(tree, node->key, node->left, node->right);
            tree = node;
        }
        else {
            insert(node->key < tree->key ? tree->left : tree->right, node);
        }
    }

    void erase(Node*& tree, int key) {
        if (!tree) return;
        if (tree->key == key) {
            Node* temp = tree;
            tree = merge(tree->left, tree->right);
            delete temp;
        }
        else {
            erase(key < tree->key ? tree->left : tree->right, key);
        }
    }

    void clear(Node*& tree) {
        if (!tree) return;
        clear(tree->left);
        clear(tree->right);
        delete tree;
        tree = nullptr;
    }

    int depth(Node* tree) {
        if (!tree) return 0;
        int left_depth = depth(tree->left);
        int right_depth = depth(tree->right);
        return 1 + std::max(left_depth, right_depth);
    }

public:
    DecartTree() : root(nullptr) {}

    void insert(int key, int priority) {
        insert(root, new Node(key, priority));
    }

    void erase(int key) {
        erase(root, key);
    }

    bool find(int key) {
        Node* curr = root;
        while (curr) {
            if (curr->key == key) return true;
            if (key < curr->key) curr = curr->left;
            else curr = curr->right;
        }
        return false;
    }

    int maxDepth() {
        return depth(root);
    }

    void clear() {
        clear(root);
    }
};

// Функция для генерации N случайных значений
std::vector<int> generateRandomValues(int N) {
    std::vector<int> values;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1, 1000); // Диапазон случайных значений
    for (int i = 0; i < N; ++i) {
        values.push_back(dist(gen));
    }
    return values;
}

// Функция для заполнения дерева значениями
void fillTree(DecartTree& tree, const std::vector<int>& values) {
    for (int value : values) {
        tree.insert(value, rand());
    }
}

// Функция для выполнения серии тестов
void runTests(int N) {
    std::ofstream that_file;
    that_file.open("lab1file.txt", std::ios_base::app);
    std::vector<int> values = generateRandomValues(N);

    DecartTree tree1, tree2;

    fillTree(tree1, values);
    fillTree(tree2, values);

    // Замер максимальной глубины
    int max_depth_tree1 = tree1.maxDepth();
    int max_depth_tree2 = tree2.maxDepth();
    std::cout << "Max depth of tree 1: " << max_depth_tree1 << std::endl;
    std::cout << "Max depth of tree 2: " << max_depth_tree2 << std::endl;

    // Замер времени вставки
    auto start_insert1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree1.insert(rand(), rand());
    }
    auto end_insert1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_time1 = end_insert1 - start_insert1;
    std::cout << "Insert time for tree 1: " << insert_time1.count() << " seconds" << std::endl;

    auto start_insert2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree2.insert(rand(), rand());
    }
    auto end_insert2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> insert_time2 = end_insert2 - start_insert2;
    std::cout << "Insert time for tree 2: " << insert_time2.count() << " seconds" << std::endl;

    // Замер времени удаления
    auto start_erase1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree1.erase(values[i % N]);
    }
    auto end_erase1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> erase_time1 = end_erase1 - start_erase1;
    std::cout << "Erase time for tree 1: " << erase_time1.count() << " seconds" << std::endl;

    auto start_erase2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree2.erase(values[i % N]);
    }
    auto end_erase2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> erase_time2 = end_erase2 - start_erase2;
    std::cout << "Erase time for tree 2: " << erase_time2.count() << " seconds" << std::endl;

    // Замер времени поиска
    auto start_find1 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree1.find(rand());
    }
    auto end_find1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> find_time1 = end_find1 - start_find1;
    std::cout << "Find time for tree 1: " << find_time1.count() << " seconds" << std::endl;

    auto start_find2 = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 1000; ++i) {
        tree2.find(rand());
    }
    auto end_find2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> find_time2 = end_find2 - start_find2;
    std::cout << "Find time for tree 2: " << find_time2.count() << " seconds" << std::endl;

    // Замер глубин всех веток дерева
    // Это дополнительный функционал, который может быть реализован в классе DecartTree
    // Для примера, я просто выведу на экран максимальную глубину
    std::cout << "Max depth of branches in tree 1: " << tree1.maxDepth() << std::endl;
    std::cout << "Max depth of branches in tree 2: " << tree2.maxDepth() << std::endl;
    that_file << insert_time1.count() << " " << insert_time2.count() << " " << erase_time1.count() << " " << erase_time1.count() << " ";
    that_file << find_time1.count() << " " << find_time2.count() << " " << tree1.maxDepth() << " " << tree2.maxDepth() << " " << "\n";
    that_file.close();
}

int main() {
    std::ofstream that_file;
    that_file.open("lab1file.txt", std::ios_base::app);
    that_file << "insert_time1" << " " << "insert_time2" << " " << "erase_time1" << " " << "erase_time2" << " ";
    that_file << "find_time1" << " " << "find_time1" << " " << "Max_depth1" << " " << "Max_depth2" << " " << "\n";
    that_file.close();
    // Цикл по сериям тестов для разных размеров
    for (int i = 10; i <= 18; ++i) {
        int N = 1 << i; // Вычисляем N = 2^i
        std::ofstream that_file;
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << N << " " << "elements" << " " << "------" << " " << "------" << " ";
        that_file << "-----" << " " << "------" << " " << "-------" << " " << "-------" << " " << "\n";
        that_file.close();
        for (int j = 0; j < 50; ++j) { // 50 повторений
            runTests(N);
        }
    }

    return 0;
}