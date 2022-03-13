#include "FilaPrioritaria.hpp"
#include "ItemComando.hpp"
#include "CelulaComando.hpp"

FilaPrioritaria::FilaPrioritaria() : _tamanho(0), _frente(new CelulaComando()), _tras(_frente) {}

FilaPrioritaria::~FilaPrioritaria() {
    limpaFila();
    delete _frente;
}

bool FilaPrioritaria::estaVazia() {
    return _tamanho == 0;
}

unsigned int FilaPrioritaria::getTamanho() {
    return _tamanho;
}

void FilaPrioritaria::enfileira(ItemComando item) {
    CelulaComando* novaCelula;
    novaCelula = new CelulaComando();
    novaCelula->_item = item;

    _tras->_proximaCelula = novaCelula;
    _tras = novaCelula;
    _tamanho++;
}

void FilaPrioritaria::furaFila(ItemComando item) {
    CelulaComando *novaCelula, *celulaAuxiliar;
    novaCelula = new CelulaComando();
    novaCelula->_item = item;

    celulaAuxiliar = _frente->_proximaCelula;
    _frente->_proximaCelula = novaCelula;
    novaCelula->_proximaCelula = celulaAuxiliar;
    _tamanho++;
}

ItemComando FilaPrioritaria::desenfileira() {
    if(estaVazia())
        throw "Fila esta vazia!";

    CelulaComando* celulaAuxiliar;
    ItemComando item;

    celulaAuxiliar = _frente;
    _frente = _frente->_proximaCelula;
    item = _frente->_item;

    delete celulaAuxiliar;
    _tamanho--;

    return item;
}

void FilaPrioritaria::limpaFila(){
    while(!estaVazia()) {
        desenfileira();
    }
}
