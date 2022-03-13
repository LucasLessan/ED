#ifndef ARVOREPESQUISA_HPP
#define ARVOREPESQUISA_HPP

#include "TipoNo.hpp"
#include "TipoItem.hpp"

// ----- Encoding UTF-8

class ArvorePesquisa {
    public:
        // ----- Construtor e Destrutor
        ArvorePesquisa();
        ~ArvorePesquisa();

        // ----- Funcionalidades
        void insere(TipoItem item);
        void limpa();

    private:
        TipoNo *_raiz;

        // ----- Métodos Utilitarios
        void insereRecursivo(TipoNo* &no, TipoItem item);
        void apagaRecursivo(TipoNo* p);

    friend class CentroComunicacao; // Necessario para acessar o atributo privado
};

#endif
