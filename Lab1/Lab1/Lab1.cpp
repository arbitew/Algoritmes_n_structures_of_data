
#include <iostream>
#include <random>
#include <vector>
#include <chrono>
#include <fstream>
void bubbleSort(std::vector<double>& v) {
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
void cocktailShakerSort(std::vector<double>& v) {
    size_t left = 0;
    size_t right = v.size() - 1;
    bool swapped = true;

    while (left < right&& swapped) {
        swapped = false;

        // Ascending pass (left to right)
        for (size_t i = left; i < right; ++i) {
            if (v[i] > v[i + 1]) {
                std::swap(v[i], v[i + 1]);
                swapped = true;
            }
        }

        // Check if no swaps occurred in the ascending pass
        if (!swapped) {
            break; // List is already sorted
        }

        right--; // Decrement right boundary after ascending pass

        // Descending pass (right to left)
        swapped = false;
        for (size_t i = right; i > left; --i) {
            if (v[i] < v[i - 1]) {
                std::swap(v[i], v[i - 1]);
                swapped = true;
            }
        }

        left++; // Increment left boundary after descending pass
    }
}

void insertionSort(std::vector<double>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        double key = arr[i];
        int j = i - 1;

        // Shift elements of the sorted sub-array to the right while key is greater
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // Insert the key at its correct position
        arr[j + 1] = key;
    }
}

void selectionSort(std::vector<double>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        int minIdx = i; // Assume the first element is the minimum

        // Find the actual minimum element in the unsorted part
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }

        // Swap the minimum element with the first element in the unsorted part
        if (minIdx != i) {
            std::swap(arr[i], arr[minIdx]);
        }
    }
}

void timeMeasuring(void(*innerF)(std::vector <double>&), int N) {
    std::mt19937 engine(time(0));
    std::chrono::high_resolution_clock::time_point a[20];
    for (int i = 0; i < 20; i++) {
        std::vector <double> v(N);

        std::uniform_real_distribution<double> gen(-1.0, 1.0);
        for (auto& el : v)
            el = gen(engine);
        std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();
        innerF(v);
        std::chrono::high_resolution_clock::time_point end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> sec_diff = end - start;
        std::cout << std::endl;
        std::ofstream that_file;
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << sec_diff.count() << " ";
        that_file.close();
        std::cout << "Time: " << sec_diff.count() << "sec." << std::endl;
        /*for (auto& el : v) {
            std::cout << el << " ";
        }

        std::cout << std::endl;*/
    }
    

}
int main()
{
    int a [] { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };
    std::ofstream that_file;
    that_file.open("lab1file.txt", std::ios_base::app);
    that_file.clear();
    that_file.close();
    /*for (auto& i : a) {
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "bubble sort " << i << " el:";
        that_file.close();
        timeMeasuring(bubbleSort, i);
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "\n";
        that_file.close();
    }
    for (auto& i : a) {
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "cocktailShaker sort " << i << " el:";
        that_file.close();
        timeMeasuring(cocktailShakerSort, i);
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "\n";
        that_file.close();
    }
    for (auto& i : a) {
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "inserion sort " << i << " el:";
        that_file.close();
        timeMeasuring(insertionSort, i);
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "\n";
        that_file.close();
    }*/
    for (auto& i : a) {
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "selection sort " << i << " el:";
        that_file.close();
        timeMeasuring(selectionSort, i);
        that_file.open("lab1file.txt", std::ios_base::app);
        that_file << "\n";
        that_file.close();
    }
}

