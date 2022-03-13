#include "Robo.hpp"
#include "ItemComando.hpp"
#include "Base.hpp"

#include <iostream>
#include <sstream>

Robo::Robo() : _ativo(false), _eliminacoes(0), _recursos(0), _posicaoX(0), _posicaoY(0),
        _historico(new FilaPrioritaria()), _fila_de_comandos(new FilaPrioritaria()) {}

Robo::~Robo() {
    _historico->~FilaPrioritaria();
    _fila_de_comandos->~FilaPrioritaria();
}

bool Robo::getAtivo() {
    return _ativo;
}

unsigned int Robo::getEliminacoes() {
    return _eliminacoes;
}

unsigned int Robo::getRecursos() {
    return _recursos;
}

unsigned int Robo::getPosicaoX() {
    return _posicaoX;
}

unsigned int Robo::getPosicaoY() {
    return _posicaoY;
}

FilaPrioritaria* Robo::getHistorico() {
    return _historico;
}

FilaPrioritaria* Robo::getComandos() {
    return _fila_de_comandos;
}

void Robo::setAtivo(bool ativo) {
    _ativo = ativo;
}

void Robo::setEliminacoes(unsigned int eliminacoes) {
    _eliminacoes = eliminacoes;
}

void Robo::setRecursos(unsigned int recursos) {
    _recursos = recursos;
}

void Robo::setPosicaoX(unsigned int posicaoX) {
    _posicaoX = posicaoX;
}

void Robo::setPosicaoY(unsigned int posicaoY) {
    _posicaoY = posicaoY;
}

void Robo::moveRobo(std::string comando, MapReader& map1) {
        char dummy; // ----- Serve para ignorar os parenteses e a virgula
        unsigned int robo, posicaoX, posicaoY;
        std::string command;
        std::stringstream stream(comando);
        ItemComando item;

        stream >> command >> robo >> dummy >> posicaoX >> dummy >> posicaoY;

        if(map1.getBlock(posicaoX, posicaoY) == 'O')
            item.setComando(convertToString(robo, ": IMPOSSIVEL MOVER PARA (", posicaoX, posicaoY));
        else {
            item.setComando(convertToString(robo, ": MOVEU PARA (", posicaoX, posicaoY));
            _posicaoX = posicaoX;
            _posicaoY = posicaoY;
        }
        _historico->enfileira(item);
}

void Robo::coleta(std::string comando, MapReader& map1) {
        unsigned int robo;
        std::string command;
        std::stringstream stream(comando);
        ItemComando item;

        stream >> command >> robo;

        if(map1.getBlock(_posicaoX, _posicaoY) == 'R') {
            item.setComando(convertToString(robo, ": RECURSOS COLETADOS EM (", _posicaoX, _posicaoY));
            map1.setBlock(_posicaoX, _posicaoY, '.');
            _recursos++;
        }
        else
            item.setComando(convertToString(robo, ": IMPOSSIVEL COLETAR RECURSOS EM (", _posicaoX, _posicaoY));
        _historico->enfileira(item);
}

void Robo::elimina(std::string comando, MapReader& map1) {
        unsigned int robo;
        std::string command;
        std::stringstream stream(comando);
        ItemComando item;

        stream >> command >> robo;

        if(map1.getBlock(_posicaoX, _posicaoY) == 'H') {
            item.setComando(convertToString(robo, ": ALIEN ELIMINADO EM (", _posicaoX, _posicaoY));
            map1.setBlock(_posicaoX, _posicaoY, '.');
            _eliminacoes++;
        }
        else
            item.setComando(convertToString(robo, ": IMPOSSIVEL ELIMINAR ALIEN EM (", _posicaoX, _posicaoY));
        _historico->enfileira(item);
}

void Robo::executarComandos(MapReader& map1) {
    std::string command;
    std::stringstream stream;
    ItemComando item;

    // ----- Percorre por toda fila de comandos executando-os
    while(!_fila_de_comandos->estaVazia()) {
        item = _fila_de_comandos->desenfileira();
        stream.clear(); // ----- Evita erros quando se tenta ler uma stream que chegou ao fim
        stream.str(item.getComando());
        stream >> command;

        if(command == "MOVER" || command == "*MOVER")
            moveRobo(item.getComando(), map1);
        if(command == "COLETAR" || command == "*COLETAR")
            coleta(item.getComando(), map1);
        if(command == "ELIMINAR" || command == "*ELIMINAR")
            elimina(item.getComando(), map1);
    }
}

void Robo::imprimirRelatorio() {
    // ----- Percorre por todo o historico imprimindo-o
    while(!_historico->estaVazia())
        std::cout << _historico->desenfileira().getComando() << std::endl;
}

// ----- Funcao de conversao para string por motivos de escalabilidade
std::string Robo::convertToString(unsigned int robo, std::string saida, unsigned int posicaoX, unsigned int posicaoY) {
    return "ROBO " + std::to_string(robo) + saida + std::to_string(posicaoX) + "," + std::to_string(posicaoY) + ")";
}
