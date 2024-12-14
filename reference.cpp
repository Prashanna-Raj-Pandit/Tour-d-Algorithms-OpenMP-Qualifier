#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm>
#include <chrono>

int* generateRandomNumbers(const int count, const int seed) {
    srand(seed);
    int* randomNumbers = new int[count];
    for (int i = 0; i < count; i++) {
        randomNumbers[i] = std::rand() % 1000000;
    }
    return randomNumbers;
}

int main(int argc, char** argv) {
    int* randomNumberArray;
    int arraySize, randomSeed;

    if (argc < 3) {
        std::cerr << "Usage: " << argv[0] << " [number of random numbers to generate] [seed value for random number generator]" << std::endl;
        exit(-1);
    }

    {
        std::stringstream sizeStream(argv[1]);
        sizeStream >> arraySize;
    }
    {
        std::stringstream seedStream(argv[2]);
        seedStream >> randomSeed;
    }

    randomNumberArray = generateRandomNumbers(arraySize, randomSeed);

    auto start = std::chrono::high_resolution_clock::now();
    std::sort(randomNumberArray, randomNumberArray + arraySize);
    auto stop = std::chrono::high_resolution_clock::now();
    
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

    std::cout << "Sorted Array: ";
    for (int i = 0; i < arraySize; i++) {
        std::cout << randomNumberArray[i] << " ";
    }
    std::cout << std::endl;

    std::cout << "Execution Time: " << duration.count() << " microseconds" << std::endl;

    delete[] randomNumberArray;

    return 0;
}
