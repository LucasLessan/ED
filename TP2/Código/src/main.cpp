#include "Sort.hpp"

#include <iostream>

// ----- Encoding UTF-8

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Argumentos invalidos.";
        return 1;
    }

    Sort extracaoZ(argv[1], std::stoi(argv[2]));

    // extracaoZ.insertionSort();
    // extracaoZ.heapSort();
    extracaoZ.quickSort();
    // extracaoZ.moddedQuickSort();
    // extracaoZ.shellSort();

    extracaoZ.print(7);

    return 0;
}

