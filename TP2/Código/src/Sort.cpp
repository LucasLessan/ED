#include "Sort.hpp"

#include <string> // std::string
#include <fstream> // std::ifstream
#include <iostream> // std::cout
#include <cmath> // std::pow

// ----- Encoding UTF-8

int ciura[] = {90927, 40412, 17961, 7983, 3548, 1577, 701, 301, 132, 57, 23, 10, 4, 1}; // Sequência de incrementos de Marcin Ciura

Sort::Sort(std::string arquivo, int tamanho) : _tamanho(tamanho) {
    _vetorInt = new int[_tamanho];
    _vetorString = new std::string[_tamanho];

    if(_vetorInt == nullptr || _vetorString == nullptr) {
        std::cout << "Nao foi possivel alocar espaco!";
        exit(1);
    }

    std::ifstream stream(arquivo);

    if(!stream) {
        std::cout << "Nao foi possivel abrir o arquivo!";
        exit(1);
    }

    for(int i = 0; i < _tamanho; i++) 
        stream >> _vetorString[i] >> _vetorInt[i];

    stream.close(); 
}

Sort::~Sort() {
    delete[] _vetorInt;
    delete[] _vetorString;
}

void Sort::insertion(int inicio, int fim) {
    int itExt, itInt, intTemp;
    std::string stringTemp;
    
    itExt = inicio;
    
    // ----- Executa loop principal do método de Inserção, colocando o elemento no subvetor anterior a ele, já ordenado
    // ----- A variável início é usada como o tamanho do salto a ser dado (1 para Inserção e dependente da sequência para ShellSort)
    for(; itExt < fim; itExt++) {
        
        // ----- Separa o elemento atual para colocá-lo na posição correta quando a achar
        intTemp = _vetorInt[itExt];
        stringTemp = _vetorString[itExt];
        itInt = itExt; // Começa da posição do elemento atual
        
        // ----- Encontra um valor maior que o elemento atual e para nessa posição
        // ----- Move os elementos uma posição à frente enquanto não encontra a posição correta do elemento
        // -----    que está sendo ordenado
        while((itInt >= inicio) && (intTemp > _vetorInt[itInt - inicio])) {
            _vetorInt[itInt] = _vetorInt[itInt - inicio];
            _vetorString[itInt] = _vetorString[itInt - inicio];
            itInt -= inicio;
        }

        // ----- Faz a troca do elemento da posição atual com o que se busca ordenar
        _vetorInt[itInt] = intTemp;
        _vetorString[itInt] = stringTemp;
    }
}

void Sort::insertionSort() {
    
    // ----- O valor de inicio é 1 pois inicio é usado como o inicio do subvetor a ser ordenado
    // -----    e o tamanho do salto
    insertion(1, _tamanho);
}

void Sort::refazHeap(int esq, int dir){
    int pai, filho, intTemp;
    std::string stringTemp;

    pai = esq;
    filho = pai * 2; // Primeiro filho de pai, o segundo está na posição (pai * 2) + 1

    // ----- Separa o elemento atual para colocá-lo na posição correta quando a achar
    intTemp = _vetorInt[pai];
    stringTemp = _vetorString[pai];

    // ----- Percorre até o fim do vetor procurando um filho menor do que o pai para colocar como pai
    // ----- Procura um filho menor pois o vetor está sendo ordenado de maneira decrescente
    while (filho <= dir){
        
        // ----- Verifica se não é última posição do vetor para não haver um SegFault em _vetorInt[filho + 1]
        if (filho < dir)
        
            // ----- Escolhe o menor dos dois filhos
            if (_vetorInt[filho] > _vetorInt[filho + 1])
                filho++;
        
        // ----- Termina a iteração caso o filho não seja menor que o pai
        if (intTemp <= _vetorInt[filho])
            break;

        // ----- Troca o pai e o filho de posição caso a verificação anterior seja falsa
        _vetorInt[pai] = _vetorInt[filho];
        _vetorString[pai] = _vetorString[filho];
        
        // ----- Segue a "linhagem" do pai até que a iteração seja interrompida pelo break ou filho > dir
        pai = filho;
        filho = pai * 2;
    }

    // ----- Coloca o elemento separado antes do loop na posição correta
    _vetorInt[pai] = intTemp;
    _vetorString[pai] = stringTemp;
}

void Sort::constroiHeap() {
    int esq;
    
    // ----- Começa a construir o Heap do fim da primeira metade já que por definição
    // -----    todos os filhos respeitam as restrições
    esq = _tamanho / 2;

    // ----- Vai montando o Heap até chegar no começo do vetor
    while (esq > 0) {
        esq--;
        refazHeap(esq, _tamanho - 1);
    }
}

void Sort::heapSort() {
    int esq, dir, intTemp;
    std::string stringTemp;

    constroiHeap();

    esq = 0;
    dir = _tamanho - 1; // dir é usada pra acessar os vetores então deve ser _tamanho - 1 para evitar SegFault

    // ----- Coloca o menor elemento (que é o primeiro do Heap) no final
    // -----    assim ordena o vetor de forma decrescente
    while(dir > 0) {
        
        // ----- Troca a distância
        intTemp = _vetorInt[0];
        _vetorInt[0] = _vetorInt[dir];
        _vetorInt[dir] = intTemp;

        // ----- Troca o planeta
        stringTemp = _vetorString[0];
        _vetorString[0] = _vetorString[dir];
        _vetorString[dir] = stringTemp;
        
        dir--;
        refazHeap(esq, dir);
    }
}

void Sort::particao(int& esq, int& dir, int inicio, int fim) {
    int intTemp, pivo;
    std::string stringTemp;

    // ----- esq e direta são passados por referência para serem usados para chamar ordena() recursivamente
    esq = inicio;
    dir = fim;

    // ----- Escolha padrão de pivô como o elemento central do vetor
    pivo = _vetorInt[(esq + dir) / 2];

    // ----- Prossegue colocando os elementos na partição correta até esq e dir se cruzarem
    do {
        
        // ----- Para esq no primeiro elemento menor ou igual ao pivô
        while(pivo < _vetorInt[esq])
            esq++;
        
        // ----- Para dir no primeiro elemento maior ou igual ao pivô
        while(pivo > _vetorInt[dir])
            dir--;
        
        // ----- Troca os valores de partição caso esq e dir não tiverem se cruzado ainda
        if (esq <= dir) {
            
            // ----- Troca a distância
            intTemp = _vetorInt[esq];
            _vetorInt[esq] = _vetorInt[dir];
            _vetorInt[dir] = intTemp;
    
            // ----- Troca o planeta
            stringTemp = _vetorString[esq];
            _vetorString[esq] = _vetorString[dir];
            _vetorString[dir] = stringTemp;

            esq++;
            dir--;
        }
    } while(esq <= dir);
}

void Sort::ordena(int inicio, int fim) {
    int esq, dir;
    
    particao(esq, dir, inicio, fim);
    
    // ----- Chama ordena() recursivamente até que inicio == fim, porque um vetor de um elemento
    // -----    já está ordenado por definição
    
    if (inicio < dir)
        
        // ----- O intervalo [inicio, dir] é a partição da esquerda da chamada atual de ordena(), após a execução de particao()
        ordena(inicio, dir); 

    if (esq < fim)
        
        // ----- O intervalo [esq, fim] é a partição da direita da chamada atual de ordena(), após a execução de particao()    
        ordena(esq, fim);
}

void Sort::quickSort() {
    
    // ----- fim é usado para acessar os vetores em ordena(), portanto deve ser passado _tamanho - 1
    ordena(0, _tamanho - 1);
}

int Sort::median(int x, int y, int z) {
    
    // ----- Retorna a mediana entre 3 valores
    if(x < y) {
        if(y < z)
            return y;
        if(x < z)
            return z;
        return x;
    }
    if(x < z)
        return x;
    if(y < z)
        return z;
    return y;
}

void Sort::moddedParticao(int& esq, int& dir, int inicio, int fim) {
    int intTemp, pivo;
    std::string stringTemp;
    
    // ----- esq e direta são passados por referência para serem usados para chamar moddedOrdena() recursivamente
    esq = inicio;
    dir = fim;

    // ----- Escolha de pivô por mediana de 3
    pivo = median(_vetorInt[inicio], _vetorInt[(inicio + fim) / 2], _vetorInt[fim]);
    
    // ----- Prossegue colocando os elementos na partição correta até esq e dir se cruzarem
    do {

        // ----- Para esq no primeiro elemento menor ou igual ao pivô
        while(pivo < _vetorInt[esq])
            esq++;

        // ----- Para dir no primeiro elemento maior ou igual ao pivô
        while(pivo > _vetorInt[dir])
            dir--;

        // ----- Troca os valores de partição caso esq e dir não tiverem se cruzado ainda
        if (esq <= dir) {

            // ----- Troca a distância
            intTemp = _vetorInt[esq];
            _vetorInt[esq] = _vetorInt[dir];
            _vetorInt[dir] = intTemp;

            // ----- Troca o planeta
            stringTemp = _vetorString[esq];
            _vetorString[esq] = _vetorString[dir];
            _vetorString[dir] = stringTemp;

            esq++;
            dir--;
        }
    } while(esq <= dir);
}

void Sort::moddedOrdena(int inicio, int fim) {
    int esq, dir;

    moddedParticao(esq, dir, inicio, fim);

    // ----- Chama moddedOrdena() recursivamente até que inicio == fim, porque um vetor de um elemento
    // -----    já está ordenado por definição

    if (inicio < dir)

        // ----- O intervalo [inicio, dir] é a partição da esquerda da chamada atual de moddedOrdena(),
        // -----    após a execução de moddedParticao()
        moddedOrdena(inicio, dir);

    if (esq < fim)

        // ----- O intervalo [esq, fim] é a partição da direita da chamada atual de moddedOrdena(),
        // -----    após a execução de moddedParticao()    
        moddedOrdena(esq, fim);
}

void Sort::moddedQuickSort() {

    // ----- fim é usado para acessar os vetores em moddedOrdena(), portanto deve ser passado _tamanho - 1
    moddedOrdena(0, _tamanho - 1);
}

int Sort::encontraInicio(int vetor[]) {
    int inicio = 0;
    
    // ----- Encontra e retorna a posição do maior valor em vetor[] menor que _tamanho
    // ----- Usado em shellSort para encontrar apenas os valores válidos da sequência de Ciura
    for(; vetor[inicio] >= _tamanho; inicio++);
    
    return inicio;
}

void Sort::shellSort() {

    // ----- Forma padrão, proposta pelo autor do método ShellSort, de se encontrar uma sequência de saltos
    // for(int gap = _tamanho / 2; gap > 0; gap /= 2) {
    //     insertion(gap, _tamanho, _vetorInt, _vetorString);
    // }

    // ----- Sequência descoberta por acaso que apresentou boa eficiência
    // int i = 2, gap = 1;

    // ----- Encontra o maior tamanho de salto permitido
    // for(; gap < int(_tamanho / 4.5); i++)
    //     gap = (std::pow(4, i) - 3 * std::pow(2, i) + 1);

    // ----- Executa o método ShellSort com os saltos obtidos pelo loop anterior
    // for(; gap > 0; gap = int(gap / 4.5))
    //     insertion(gap, _tamanho, _vetorInt, _vetorString);

    // ----- Utiliza a sequência de Marcin Ciura, a mais eficiente conhecida, através do vetor ciura[],
    // -----    que contém a sequência "hardcoded"
    int inicio = encontraInicio(ciura);
    
    for(; inicio < int(sizeof(ciura) / sizeof(ciura[0])); inicio++)
        insertion(ciura[inicio], _tamanho);

}

void Sort::print(int numLinhas) {
    if(numLinhas < 0) {
        std::cout << "Valor de linhas invalido!";
        return;
    }

    if(numLinhas > _tamanho)
        for(int i = 0; i < _tamanho; i++)
            std::cout << _vetorString[i] << " " << _vetorInt[i] << std::endl;

    else
        for(int i = 0; i < numLinhas; i++)
            std::cout << _vetorString[i] << " " << _vetorInt[i] << std::endl;
}