#include "CentroComunicacao.hpp"

#include <iostream> // std::cout

int main(int argc, char* argv[]) {
    if(argc != 2) {
        std::cout << "Numero de argumentos invalido!";
        return 1;
    }

    CentroComunicacao centro(argv[1]);
}