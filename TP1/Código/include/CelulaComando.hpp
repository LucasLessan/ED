#ifndef CELULACOMANDO_HPP
#define CELULACOMANDO_HPP

#include "ItemComando.hpp"

class CelulaComando {
    public:
        CelulaComando();

    private:
        ItemComando _item;
        CelulaComando* _proximaCelula;

    friend class FilaPrioritaria;
};

#endif // CELULACOMANDO_HPP
