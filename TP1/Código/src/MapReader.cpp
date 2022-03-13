#include "MapReader.hpp"

#include <fstream>

MapReader::MapReader(std::string filename) {
    char buffer;

    // ----- Abre o arquivo do mapa para leitura
    std::ifstream mapStream(filename);
    mapStream >> _rows >> _columns;

    // ----- Aloca memoria para o mapa
    _map = new char*[_rows];
    for(int i = 0; i < _rows; i++)
        _map[i] = new char[_columns];

    // ----- Preenche o mapa char a char
    for(int i = 0; i < _rows; i++) {
        for(int j = 0; j < _columns; j++) {
            mapStream >> buffer;
            _map[i][j] = buffer;
        }
    }
    mapStream.close();
}

MapReader::~MapReader() {
    for(int i = 0; i < _rows; i++)
        delete[] _map[i];
    delete[] _map;
}

int MapReader::getRows() {
    return _rows;
}

int MapReader::getColumns() {
    return _columns;
}

char MapReader::getBlock(int posX, int posY) {
    return _map[posX][posY];
}

char** MapReader::getMap() {
    return _map;
}

void MapReader::setBlock(int posX, int posY, char blockType) {
    _map[posX][posY] = blockType;
}

// ----- Overloading do operador <<
std::ostream& operator<<(std::ostream& os, MapReader& map1) {
    for(int i = 0; i < map1.getRows(); i++) {
        for(int j = 0; j < map1.getColumns(); j++) {
            os << map1.getBlock(i, j) << " ";
        }
        os << std::endl;
    }
    return os;
}
