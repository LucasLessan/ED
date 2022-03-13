#include "ArvorePesquisa.hpp"
#include "TipoItem.hpp"
#include "TipoNo.hpp"

// ----- Encoding UTF-8

ArvorePesquisa::ArvorePesquisa() {
    _raiz = nullptr;
}

ArvorePesquisa::~ArvorePesquisa() {
    limpa();
}

void ArvorePesquisa::insere(TipoItem item) {
    insereRecursivo(_raiz, item);
}

void ArvorePesquisa::insereRecursivo(TipoNo* &no, TipoItem item) {
    if(no == nullptr) {
        no = new TipoNo();
        no->_item = item;
    }
    else {
        if(item.getChave() < no->_item.getChave())
            insereRecursivo(no->_esq, item);
        else
            insereRecursivo(no->_dir, item);
    }
}

void ArvorePesquisa::limpa() {
    apagaRecursivo(_raiz);
    _raiz = nullptr;
}

void ArvorePesquisa::apagaRecursivo(TipoNo *no) {
    if(no != nullptr) {
        apagaRecursivo(no->_esq);
        apagaRecursivo(no->_dir);
        delete no;
    }
}