#include "TipoItem.hpp"

// ----- Encoding UTF-8

TipoItem::TipoItem() : _chave('\0') {}

TipoItem::TipoItem(TipoChave chave) : _chave(chave) {}

TipoChave TipoItem::getChave() {
    return _chave;
}

void TipoItem::setChave(TipoChave chave) {
    _chave = chave;
}