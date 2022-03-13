#include "CentroComunicacao.hpp"

#include <iostream> // std::cout
#include <sstream> // std::stringstream
#include <fstream> // std::ifstream
#include <stdlib.h> // rand()
#include <time.h> // time()

// ----- Encoding UTF-8

CentroComunicacao::CentroComunicacao(std::string arquivo) : _codex(new ArvorePesquisa()) {
    srand(time(nullptr));
    char letra, dummy;
    std::string linha;

    // ----- Abre o arquivo de mensagens para leitura
    std::ifstream stream(arquivo);

    // ----- Constroi a arvore de transliteracao a partir do arquivo de mensagens
    while(std::getline(stream, linha)) {
        
        // ----- Le linha a linha do arquivo para tratar corretamente o \n
        std::stringstream str(linha);

        // ----- Usa o dummy para ignorar os dois pontos
        str >> letra >> dummy;

        // ----- Como no comando A e C existem espacos em branco na linha, o std::noskipws serve para nao ignora-los
        
        if(letra == 'A') {
            
            // ----- Ignora o espaco em branco
            str >> letra;

            do {
                TipoItem item(letra);
                _codex->insere(item);
            } while(str >> std::noskipws >> letra);
        }

        if(letra == 'C') {
            str >> letra;

            do {
                codifica(letra);
            } while(str >> std::noskipws >> letra);
            std::cout << std::endl;
        }
        
        if(letra == 'D') {
            str >> dummy;

            // ----- decodifica() trata todos os possiveis casos internamente portanto nao precisa de um loop
            decodifica(str);
            std::cout << std::endl;
        }
    }
}

CentroComunicacao::~CentroComunicacao() {
    _codex->~ArvorePesquisa();
    delete _codex;
}

void CentroComunicacao::codifica(char letra) {
    std::cout << 'x';
    codificaRecursivo(_codex->_raiz, letra);
}

void CentroComunicacao::codificaRecursivo(TipoNo *no, char letra) {
    if(letra < no->_item.getChave()) {

        // ----- Gera um algarismo aleatorio impar
        std::cout << (rand() * 2 + 1) % 10;
        codificaRecursivo(no->_esq, letra);
    }
    if(letra > no->_item.getChave()) {

        // ----- Gera um algarismo aleatorio par
        std::cout << rand() * 2 % 10;
        codificaRecursivo(no->_dir, letra);
    }
}

void CentroComunicacao::decodifica(std::stringstream& str) {

    // ----- A stream e passada para que a leitura da linha possa ser feita internamente
    decodificaRecursivo(_codex->_raiz, str);
}

void CentroComunicacao::decodificaRecursivo(TipoNo *no, std::stringstream& str) {
    char letra;
    // ----- Tratamento de erro
    if(str.eof())
        return;

    str >> letra;

    // ----- Sempre que o proximo caracter e um x ou o fim da linha, deve se imprimir a chave do no atual
    if(letra == 'x' || str.eof()) {
        std::cout << no->_item.getChave();

        // ----- Reinicia a recursao da raiz
        decodificaRecursivo(_codex->_raiz, str);
    }
    else {
        if(int(letra) % 2 != 0) 
            decodificaRecursivo(no->_esq, str);
        else 
            decodificaRecursivo(no->_dir, str);
    }
}