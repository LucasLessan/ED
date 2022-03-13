#ifndef BASE_HPP
#define BASE_HPP

#include "Robo.hpp"
#include "MapReader.hpp"
#include "FilaPrioritaria.hpp"

#include <iostream>

class Base {
    public:
        // ----- Construtores e Destrutores
        Base(std::string mapFilename, std::string commandsFilename);
        ~Base();

        // ----- Getter
        MapReader& getMap();

        // ----- Funcionalidades
        void executarOrdens();

        std::string convertToString(unsigned int robo, std::string saida);

    private:
        unsigned int _eliminacoes;
        unsigned int _recursos;
        Robo _robos[50];
        MapReader _map;
        FilaPrioritaria* _fila_de_ordens;
};

#endif // BASE_HPP
