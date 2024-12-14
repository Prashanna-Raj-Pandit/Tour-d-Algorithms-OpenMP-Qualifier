#include <iostream>
#include <cstdlib>
#include <sstream>
#include <chrono>

int* randNumArray(const int size, const int seed) {
    srand(seed);
    int* array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 1000000;
    }
    return array;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main(int argc, char** argv) {
    int* array;
    int size, seed;

    if (argc < 3) {
        std::cerr << "usage: " << argv[0] << " [amount of random nums to generate] [seed value for rand]" << std::endl;
        exit(-1);
    }

    {
        std::stringstream ss1(argv[1]);
        ss1 >> size;
    }
    {
        std::stringstream ss2(argv[2]);
        ss2 >> seed;
    }

    array = randNumArray(size, seed);

    auto start = std::chrono::high_resolution_clock::now();
    quickSort(array, 0, size - 1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Sorted Array: ";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;

    delete[] array;

    return 0;
}
