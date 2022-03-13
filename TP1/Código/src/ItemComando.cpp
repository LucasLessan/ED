#include "ItemComando.hpp"

#include <iostream>

ItemComando::ItemComando() : _comando("") {}

ItemComando::ItemComando(std::string comando) : _comando(comando) {}

std::string ItemComando::getComando() {
    return _comando;
}

void ItemComando::setComando(std::string comando) {
    _comando = comando;
}
