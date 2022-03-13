#ifndef MAPREADER_HPP
#define MAPREADER_HPP

#include <iostream>

class MapReader {
    public:
        // ----- Construtores e Destrutores
        MapReader(std::string filename);
        ~MapReader();

        // ----- Getters e Setters
        int getRows();
        int getColumns();
        char getBlock(int posX, int posY);
        char** getMap();
        void setBlock(int posX, int posY, char blockType);

    private:
        int _rows, _columns;
        char** _map;
};

// Overloading do operador << para facilitar a visualização do mapa na saída padrão
std::ostream& operator<<(std::ostream& os, MapReader& map1);

#endif // MAPREADER_HPP
