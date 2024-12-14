#include <iostream>
#include <sstream>
#include <cstdlib>
#include <chrono>

int* randNumArray(const int size, const int seed) {
    srand(seed);
    int* array = new int[size];
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 1000000;
    }
    return array;
}

void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    int* L = new int[n1];
    int* R = new int[n2];

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }

    delete[] L;
    delete[] R;
}

void mergeSort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;

        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
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

    mergeSort(array, 0, size - 1);

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
