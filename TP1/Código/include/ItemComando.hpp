#ifndef ITEMCOMANDO_HPP
#define ITEMCOMANDO_HPP

#include <iostream>

class ItemComando {
    public:
        // ----- Construtores e Destrutores
        ItemComando();
        ItemComando(std::string comando);

        // ----- Getters e Setters
        std::string getComando();
        void setComando(std::string comando);

    private:
        std::string _comando;
};

#endif // ITEMCOMANDO_HPP
