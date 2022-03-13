#ifndef SORT_HPP
#define SORT_HPP

#include <string> // std::string

// ----- Encoding UTF-8

class Sort {
    public:
        // ----- Construtor e Destrutor
        Sort(std::string arquivo, int tamanho);
        ~Sort();
        
        // ----- Métodos de Ordenação
        void insertionSort();
        void heapSort();
        void quickSort();
        void moddedQuickSort();
        void shellSort();

        // ----- Metódo de impressão dos vetores
        void print(int numLinhas);

    private:
        int _tamanho;
        int* _vetorInt; // Contém as distâncias dos planetas
        std::string* _vetorString; // Contém os nomes dos planetas

        // ----- Métodos Utilitários
        void insertion(int inicio, int fim);
        void refazHeap(int esq, int dir);
        void constroiHeap();
        void particao(int& esq, int& dir, int inicio, int fim);
        void ordena(int inicio, int fim);
        void moddedParticao(int& esq, int& dir, int inicio, int fim);
        void moddedOrdena(int inicio, int fim);
        int median(int x, int y, int z);
        int encontraInicio(int vetor[]);
};

#endif