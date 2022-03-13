#include "Base.hpp"
#include "MapReader.hpp"
#include "Robo.hpp"

#include <iostream>
#include <sstream>
#include <fstream>

Base::Base(std::string mapFilename, std::string commandsFilename) : _eliminacoes(0), _recursos(0),
        _map(mapFilename), _fila_de_ordens(new FilaPrioritaria()) {

    std::string line;

    // ----- Abre o arquivo de comandos para leitura
    std::ifstream commandStream(commandsFilename);
    ItemComando item;

    // ----- Constroi a fila de ordens a partir do arquivo do comandos
    while(std::getline(commandStream, line)) {
        item.setComando(line);
        _fila_de_ordens->enfileira(item);
    }
}

Base::~Base() {
    _fila_de_ordens->~FilaPrioritaria();
}

MapReader& Base::getMap() {
    return _map;
}

// ----- O uso de std::to_string() por todo o metodo foi necessario para evitar erros
void Base::executarOrdens() {
    unsigned int robo;
    std::string command;
    std::stringstream stream;
    ItemComando item;

    // ----- Percorre por toda fila de ordens executando-as
    while(!_fila_de_ordens->estaVazia()) {
        item = _fila_de_ordens->desenfileira();
        stream.clear(); // ----- Evita erros quando se tenta ler uma stream que chegou ao fim
        stream.str(item.getComando());
        stream >> command >> robo;

        // ----- Ordens de Comando
        if(command == "MOVER" || command == "COLETAR" || command == "ELIMINAR")
            _robos[robo].getComandos()->enfileira(item);
        if(command == "*MOVER" || command == "*COLETAR" || command == "*ELIMINAR")
            _robos[robo].getComandos()->furaFila(item);
        if(command == "ATIVAR") {
            if(_robos[robo].getAtivo())
                std::cout << Base::convertToString(robo, " JA ESTA EM MISSAO") << std::endl;
            else {
                _robos[robo].setAtivo(true);
                std::cout << Base::convertToString(robo, " SAIU EM MISSAO") << std::endl;
            }
        }

        // ----- Ordens Diretas
        if(command == "EXECUTAR") {
            if(!_robos[robo].getAtivo())
                std::cout << Base::convertToString(robo, " NAO ESTA EM MISSAO") << std::endl;
            else
                // ----- A Base passa uma referencia do mapa para o robo a fim de reduzir o espaco utilizado
                _robos[robo].executarComandos(_map);
        }
        if(command == "RELATORIO")
            _robos[robo].imprimirRelatorio();
        if(command == "RETORNAR") {
            if(!_robos[robo].getAtivo())
                std::cout << Base::convertToString(robo, " NAO ESTA EM MISSAO") << std::endl;
            else {
                std::cout << "BASE: ROBO " << std::to_string(robo) << " RETORNOU ALIENS "
                        << std::to_string(_robos[robo].getEliminacoes()) << " RECURSOS "
                        << std::to_string(_robos[robo].getRecursos()) << std::endl;

                _eliminacoes += _robos[robo].getEliminacoes();
                _robos[robo].setEliminacoes(0);
                _recursos += _robos[robo].getRecursos();
                _robos[robo].setRecursos(0);
                _robos[robo].getHistorico()->limpaFila();
                _robos[robo].setPosicaoX(0);
                _robos[robo].setPosicaoY(0);
                _robos[robo].setAtivo(false);
            }
        }
    }

    std::cout << "BASE: TOTAL DE ALIENS " << std::to_string(_eliminacoes) << " RECURSOS "
            << std::to_string(_recursos) << std::endl;
}

// ----- Funcao de conversao para string por motivos de escalabilidade
std::string Base::convertToString(unsigned int robo, std::string saida) {
    return "BASE: ROBO " + std::to_string(robo) + saida;
}
