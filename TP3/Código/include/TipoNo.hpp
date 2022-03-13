#ifndef TIPONO_HPP
#define TIPONO_HPP

#include "TipoItem.hpp"

// ----- Encoding UTF-8

class TipoNo {
    public:
        // ----- Construtor
        TipoNo();

    private:
        TipoItem _item;
        TipoNo *_esq;
        TipoNo *_dir;

    friend class ArvorePesquisa;
    friend class CentroComunicacao; // Necessario para acessar os atributos privados
};

#endif