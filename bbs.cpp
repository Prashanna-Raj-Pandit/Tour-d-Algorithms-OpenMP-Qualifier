#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <sstream>  // For converting command line arguments
#include <chrono>   // For measuring time

// Create an array of length size of random numbers
// Returns a pointer to the array
int* randNumArray(const int size, const int seed) {
    srand(seed);  // Seed the random number generator
    int* array = new int[size];  // Dynamically allocate memory for the array
    for (int i = 0; i < size; i++) {
        array[i] = std::rand() % 1000000;  // Random numbers between 0 and 999,999
    }
    return array;
}

// Bubble Sort function (serial version)
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                // Swap elements if they are in the wrong order
                std::swap(arr[j], arr[j + 1]);
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
    std::stringstream ss1(argv[1]);
    ss1 >> size;
    std::stringstream ss2(argv[2]);
    ss2 >> seed;

    // Generate the array of random numbers
    array = randNumArray(size, seed);

    // Start the timer
    auto start = std::chrono::high_resolution_clock::now();

    // Perform Bubble Sort
    bubbleSort(array, size);

    // Stop the timer
    auto stop = std::chrono::high_resolution_clock::now();
    
    // Calculate duration in microseconds
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
