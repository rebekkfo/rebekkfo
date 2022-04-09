#include <cassert>
#include <iostream>

void fillInFibonacciNumbers(int* result, int length) {
    assert(length >= 1);
    result[0] = 0; //initialbetingelse 1
    if (length == 1) {
        return; // kun for å hoppe ut av koden tidligere, skal ikke legge sammen noe om 1 element
    }
    result[1] = 1; // initialbetingelse 2
    for (int i = 2; i < length; i++) {
        result[i] = result[i - 1] + result[i - 2]; // rekursiv definisjon
    }
}

void printArray(int* arr, int length) {
    assert(length >= 1);
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << '\n';
}

void createFibonacci() {
    std::cout << "How many Fibonacci numbers should be generated? ";
    int length;
    std::cin >> length;

    int *result = new int[length]; // allokerer plass til length antall heltall
    fillInFibonacciNumbers(result, length);
    std::cout << "The Fibonacci nubers:\n";
    printArray(result, length);

    delete[] result; // Frigjør minnet når det ikke trengs lenger
}