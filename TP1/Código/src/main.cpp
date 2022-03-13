#include "Base.hpp"
#include "MapReader.hpp"

#include <iostream>

int main(int argc, char* argv[]) {
    if(argc != 3) {
        std::cout << "Quantidade de argumentos diferente de 3!" << std::endl;
        system("pause");
        return 1;
    }
    
    else {
        Base base(argv[1], argv[2]);

        //std::cout << base.getMap() << std::endl; // ----- Impressao do mapa na saida padrao para facilitar visualizacao
        base.executarOrdens();
        //std::cout << base.getMap() << std::endl; // ----- Impressao do mapa na saida padrao para facilitar visualizacao
        system("pause");
        return 0;
    }
}
