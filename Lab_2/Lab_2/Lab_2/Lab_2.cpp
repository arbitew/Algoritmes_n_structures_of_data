// Lab_2.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

//#include <iostream>

#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cmath>
#include <random>
#include <chrono>

template <typename T>
void quickSort(std::vector<T>& arr, int left, int right, int& comparisons, int& swaps, int& call, int& deep, int& maxDeep) {
    if (left >= right) {
        if (deep > maxDeep)
        {
            maxDeep = deep;
            deep = 0;
        }
        return;
    }

    T pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
            comparisons++;
        }
        while (arr[j] > pivot) {
            j--;
            comparisons++;
        }
        if (i <= j) {
            std::swap(arr[i], arr[j]);
            i++;
            j--;
            swaps++;
        }
    }
    call++;
    deep++;
    quickSort(arr, left, j, comparisons, swaps, call, deep, maxDeep);
    call++;
    quickSort(arr, i, right, comparisons, swaps, call, deep, maxDeep);
}

template <typename T>
void quickSort(std::vector<T>& arr) {
    int comparisons = 0;
    int swaps = 0;
    int call = 0;
    int deep = 0;
    int maxDeep = 0;
    quickSort(arr, 0, arr.size() - 1, comparisons, swaps, call, deep, maxDeep);
    std::cout << swaps << " " << call << " " << maxDeep << " ";
}

int main() {
    std::vector <int> moi_vec = { 2, 5, 1, 5, 8, 33, 6, 0 };
    quickSort(moi_vec);
    std::cout << std::endl;
    for (int i = 0; i < moi_vec.size(); i++) {
        std::cout << moi_vec[i] << " ";
    }
    std::cout << std::endl;

    std::vector<int> sizes = { 1000, 2000, 4000, 8000, 16000, 32000, 64000, 128000 };

    std::cout << "Quick Sort Performance Test\n";

    for (int size : sizes) {
        std::vector<double> arr(size);

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(-1.0, 1.0);

        

        std::vector<long long> times;

        for (int i = 0; i < 20; ++i) {
            for (int i = 0; i < size; ++i) {
                arr[i] = dis(gen);
            }
            auto start = std::chrono::high_resolution_clock::now();

            quickSort(arr);
            
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> duration = end - start;
            std::cout << duration.count() * 1000 << std::endl;
            times.push_back(duration.count() * 1000);
        }

        std::cout << "Size: " << size << "\n";
        for (int i = 0; i < times.size(); ++i) {
            //std::cout << "Time " << i + 1 << ": " << times[i] << " ms\n";
        }
        std::cout << "\n";
    }

    return 0;
}
//int main()
//{
//    std::cout << "Hello World!\n";
//}

