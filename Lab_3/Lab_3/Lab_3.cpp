// Lab_3.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#include <iostream>
#include <ctime>
#include <cstdlib>
#include <chrono>
#include <random>

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node* prev;
    Node(T d) : data(d), next(nullptr), prev(nullptr) {}
};


template <typename T>
class DoublyLinkedList {
private:
    Node<T>* head;
    Node<T>* tail;
    int size;

public:
    class Iterator {
    public:
        Node <T>* current;

        Iterator(Node <T>* node) : current(node) {}

        T& operator*() {
            return current->data;
        }

        Iterator& operator++() {
            if (current) {
                current = current->next;
            }
            return *this;
        }

        bool operator!=(const Iterator& other) const {
            return current != other.current;
        }
    };
    Iterator begin() {
        return Iterator(head);
    }

    Iterator end() {
        return Iterator(nullptr);
    }
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    void addAtBeginning(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        size++;
    }
    T start() {
        if (head) {
            T a = head->data;
            return a;
        }
    }
    T endof() {
        if (tail) {
            T a = tail->data;
            return a;
        }
    }
    T itLength() {
        if (size) {
            return size;
        }
    }

    void addAtEnd(T data) {
        Node<T>* newNode = new Node<T>(data);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }
    

    void addAtPosition(T data, int pos) {
        if (pos < 0 || pos > size) {
            std::cout << "Invalid position" << std::endl;
            return;
        }

        if (pos == 0) {
            addAtBeginning(data);
        }
        else if (pos == size) {
            addAtEnd(data);
        }
        else {
            Node<T>* temp = head;
            for (int i = 1; i < pos; i++) {
                temp = temp->next;
            }
            Node<T>* newNode = new Node<T>(data);
            newNode->next = temp->next;
            newNode->prev = temp;
            temp->next->prev = newNode;
            temp->next = newNode;
            size++;
        }
    }



    void removeAtPosition(int pos) {
        if (pos < 0 || pos >= size) {
            std::cout << "Invalid position" << std::endl;
            return;
        }

        Node<T>* temp = head;
        if (pos == 0) {
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
            delete temp;
        }
        else {
            for (int i = 0; i < pos; i++) {
                temp = temp->next;
            }
            if (temp == tail) {
                tail = tail->prev;
                tail->next = nullptr;
            }
            else {
                temp->prev->next = temp->next;
                temp->next->prev = temp->prev;
            }
            delete temp;
        }
        size--;
    }

    bool isEmpty() {
        return size == 0;
    }
    void bubbleSort() {
        if (size <= 1) {
            return;
        }
        size_t n = this->size;
        bool swapped;
        Node <T>* this_el = head;
        Node <T>* next_el = head;
        // Continue iterations while at least one swap occurs
        do {
            swapped = false;
            for (size_t i = 0; i < n - 1; ++i) {
                // Compare adjacent elements

                this_el = head;
                next_el = head;
                for (int j = 0; j < i; j++) {
                    if (next_el->next != nullptr) {
                        next_el = next_el->next;
                    }
                }
                for (int j = 0; j < i+1; j++) {
                    if(this_el->next != nullptr){
                        this_el = this_el->next;
                    }
                }
                if (this_el->data < next_el->data) {
                    // Swap if they are in the wrong order
                    Node<T> a(NAN);
                    a.data = this_el->data;
                    this_el->data = next_el->data;
                    next_el->data = a.data;
                    swapped = true;
                }
            }
            // Decrement n each time no swaps occur to avoid unnecessary comparisons
            n--;
        } while (swapped);
    }
    int countElements() {
        return size;
    }

    void printList() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    void shuffle() {
        if (size <= 1) {
            return;
        }

        Node<T>* temp = head;
        for (int i = 0; i < size; i++) {
            int randPos = rand() % size;

            Node<T>* randNode = head;
            for (int j = 0; j < randPos; j++) {
                randNode = randNode->next;
            }

            T tempData = temp->data;
            temp->data = randNode->data;
            randNode->data = tempData;

            temp = temp->next;
        }
    }

    ~DoublyLinkedList() {
        Node<T>* temp = head;
        Node<T>* nextNode;
        while (temp != nullptr) {
            nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

class Person {
public:
    std::string name;
    std::string surname;
    std::string patronymic;
    int age;
    Person(std::string name, std::string surname, std::string patronymic, int age): 
        name(name), 
        surname(surname), 
        patronymic(patronymic),
        age(age)
    {}
};
void bubbleSort(std::vector<int>& v) {
    size_t n = v.size();
    bool swapped;

    // Continue iterations while at least one swap occurs
    do {
        swapped = false;
        for (size_t i = 0; i < n - 1; ++i) {
            // Compare adjacent elements
            if (v[i] > v[i + 1]) {
                // Swap if they are in the wrong order
                std::swap(v[i], v[i + 1]);
                swapped = true;
            }
        }
        // Decrement n each time no swaps occur to avoid unnecessary comparisons
        n--;
    } while (swapped);
}
int main() {
    DoublyLinkedList<int> list;
    std::cout << list.isEmpty() << std::endl;
    for (int i = 0; i < 10; i++) {
        list.addAtEnd(i);
    }

    std::cout << list.isEmpty() << std::endl;
    list.printList();
    list.addAtBeginning(100);
    list.addAtPosition(50, 5);
    list.removeAtPosition(2);

    list.printList();
    for (auto &i : list) {
        i++;
    }
    list.printList();
    std::cout << "List is empty: " << list.isEmpty();


    DoublyLinkedList<int> num_list;
    for (int i = -1000; i < 1000; i++) {
        num_list.addAtBeginning(i);
    }
    num_list.shuffle();

    num_list.printList();
    int max = num_list.start();
    int min = num_list.start();
    int avg = 0;

    for (auto& i : num_list) {
        avg += i;
        //std::cout << avg << std::endl;
        max = max > i ? max : i;
        min = min < i ? min : i;
    }

    std::cout << avg << ":" << num_list.itLength() << std::endl;
    avg /= num_list.itLength();
    std::cout << max << " " << min << " " << avg;

    std::string* names = new std::string [5];// person
    names[0] = "Vasya";
    names[1] = "Dima";
    names[2] = "Evgeny";
    names[3] = "Vanya";
    names[4] = "Kolya";
    std::string* surnames = new std::string[3];
    surnames[0] = "Gorbov";
    surnames[1] = "Shjukin";
    surnames[2] = "Sergeev";
    std::string* patronymics = new std::string[3];
    patronymics[0] = "Sergeyevich";
    patronymics[1] = "Dmitriyevic";
    patronymics[2] = "-";

    DoublyLinkedList<Person*> person_list;
    DoublyLinkedList<Person*> person_listl20;
    DoublyLinkedList<Person*> person_listb30;

    for (int i = 0; i < 100; i++) {
        person_list.addAtEnd(new Person(names[rand() % 5], surnames[rand() % 3], patronymics[rand() % 3], rand() % 100));
    }
    for (auto& i : person_list) {
        if (i->age < 20) {
            person_listl20.addAtEnd(i);
        }
        if (i->age > 30) {
            person_listb30.addAtEnd(i);
        }
        //std::cout << i->name << " " << i->surname << " " << i->patronymic << " " << i->age << std::endl;
    }

    std::cout << "\nlower\n";
    for (auto& i : person_listl20) {
        std::cout << i->name << " " << i->surname << " " << i->patronymic << " " << i->age << std::endl;
    }
    std::cout << "bigger\n";
    for (auto& i : person_listb30) {
        std::cout << i->name << " " << i->surname << " " << i->patronymic << " " << i->age << std::endl;
    }

    DoublyLinkedList<int> list_for_sort; // sort
    for (int i = 0; i < 1000; i++) {
        list_for_sort.addAtEnd(i);
    }
    list_for_sort.printList();
    std::cout << std::endl;
    list_for_sort.shuffle();
    list_for_sort.printList();
    std::cout << std::endl;

    std::mt19937 engine(time(0));
    std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

    list_for_sort.bubbleSort();
    std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> sec_diff = end - start;
    list_for_sort.printList();
    std::cout << "list time: " << sec_diff.count() << std::endl;

    std::vector <int> v(1000);

    for (auto& el : v) {
        el = rand() % 1000;
        std::cout << el << " ";
    }
    std::cout << "\n" << std::endl;
    start = std::chrono::high_resolution_clock::now();
    bubbleSort(v);
    end = std::chrono::high_resolution_clock::now();
    sec_diff = end - start;
    for (auto& el : v) {
        std::cout << el << " ";
    }
    std::cout << "vector time: " << sec_diff.count() << std::endl;



}
// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
