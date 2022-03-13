#ifndef TIPOITEM_HPP
#define TIPOITEM_HPP

typedef char TipoChave;

// ----- Encoding UTF-8

class TipoItem {
    public:
        // ----- Construtores
        TipoItem();
        TipoItem(TipoChave chave);

        // ----- Getter e Setter
        TipoChave getChave();
        void setChave(TipoChave chave);

    private:
        TipoChave _chave;
};

#endif
