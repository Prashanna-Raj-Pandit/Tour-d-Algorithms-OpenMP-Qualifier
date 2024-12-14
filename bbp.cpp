#include <iostream>
#include <sstream>
#include <cstdlib>
#include <omp.h>     // For OpenMP
#include <chrono>    // For measuring time

// create an array of length size of random numbers
// returns a pointer to the array
int* randNumArray(const int size, const int seed) {
    srand(seed);  // Seed the random number generator
    int* array = new int[size];  // Dynamically allocate memory for the array
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 1000000;  // Random numbers between 0 and 999,999
    }
    return array;
}

// Parallel Bubble Sort (Odd-Even Transposition Sort) using OpenMP
void parallelBubbleSort(int arr[], int n) {
    bool sorted = false;

    // Keep running until the array is sorted
    while (!sorted) {
        sorted = true;

        // Odd phase
        #pragma omp parallel for
        for (int i = 1; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }

        // Even phase
        #pragma omp parallel for
        for (int i = 0; i < n - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                std::swap(arr[i], arr[i + 1]);
                sorted = false;
            }
        }
    }
}

int main(int argc, char** argv) {
    int* array;  // Pointer to the array of random numbers
    int size, seed;  // Size of the array and seed for random number generation

    // Check if the correct number of arguments is provided
    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [number of random numbers] [seed]" << std::endl;
        exit(-1);
    }

    // Convert command-line arguments to integers
    {
        std::stringstream ss1(argv[1]);
        ss1 >> size;
    }
    {
        std::stringstream ss2(argv[2]);
        ss2 >> seed;
    }

    // Generate the array of random numbers
    array = randNumArray(size, seed);

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // Perform Parallel Bubble Sort
    parallelBubbleSort(array, size);

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();
    
    // Calculate the duration in microseconds
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    // Optionally, print the sorted array (for testing purposes)
    std::cout << "Sorted Array: ";
    for (int i = 0; i < size; i++) {
        std::cout << array[i] << " ";
    }
    std::cout << std::endl;

    // Print the execution time in microseconds
    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;

    // Delete the heap memory allocated for the array
    delete[] array;

    return 0;
}
