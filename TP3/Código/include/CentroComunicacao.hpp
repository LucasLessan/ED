#ifndef CentroComunicacao_HPP
#define CentroComunicacao_HPP

#include "ArvorePesquisa.hpp"

#include <string> // std::string

// ----- Encoding UTF-8

class CentroComunicacao {
    public:
        // ----- Construtores e Destrutores
        CentroComunicacao(std::string arquivo);
        ~CentroComunicacao();

        // ----- Funcionalidades
        void codifica(char letra);
        void decodifica(std::stringstream& str);

    private:
        ArvorePesquisa* _codex; // Arvore de transliteracao

        // ----- Metodos Utilitarios
        void codificaRecursivo(TipoNo *no, char letra);
        void decodificaRecursivo(TipoNo *no, std::stringstream& str);
};

#endif