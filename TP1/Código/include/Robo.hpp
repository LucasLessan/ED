#ifndef ROBO_HPP
#define ROBO_HPP

#include "FilaPrioritaria.hpp"
#include "MapReader.hpp"

#include <iostream>

class Robo {
    public:
        // ----- Construtores e Destrutores
        Robo();
        ~Robo();

        // ----- Getter e Setters
        bool getAtivo();
        unsigned int getEliminacoes();
        unsigned int getRecursos();
        unsigned int getPosicaoX();
        unsigned int getPosicaoY();
        FilaPrioritaria* getHistorico();
        FilaPrioritaria* getComandos();
        void setAtivo(bool ativo);
        void setEliminacoes(unsigned int eliminacoes);
        void setRecursos(unsigned int recursos);
        void setPosicaoX(unsigned int posicaoX);
        void setPosicaoY(unsigned int posicaoY);

        // ----- Funcionalidades
        void moveRobo(std::string comando, MapReader& map1);
        void coleta(std::string comando, MapReader& map1);
        void elimina(std::string comando, MapReader& map1);
        void executarComandos(MapReader& map1);
        void imprimirRelatorio();

        std::string convertToString(unsigned int robo, std::string saida, unsigned int posicaoX, unsigned int posicaoY);

    private:
        bool _ativo;
        unsigned int _eliminacoes;
        unsigned int _recursos;
        unsigned int _posicaoX;
        unsigned int _posicaoY;
        FilaPrioritaria* _historico;
        FilaPrioritaria* _fila_de_comandos;
};

#endif // ROBO_HPP
