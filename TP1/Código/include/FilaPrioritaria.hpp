#ifndef FILAPRIORITARIA_HPP
#define FILAPRIORITARIA_HPP

#include "ItemComando.hpp"
#include "CelulaComando.hpp"

class FilaPrioritaria {
    public:
        // ----- Construtores e Destrutores
        FilaPrioritaria();
        ~FilaPrioritaria();

        // ----- Getters
        bool estaVazia();
        unsigned int getTamanho();

        // ----- Funcionalidades
        void enfileira(ItemComando item);
        void furaFila(ItemComando item); // enfileira item na primeira posicao da fila
        ItemComando desenfileira();
        void limpaFila();

    private:
        unsigned int _tamanho;
        CelulaComando* _frente; // Célula cabeça
        CelulaComando* _tras;
};

#endif // FILAPRIORITARIA_HPP
