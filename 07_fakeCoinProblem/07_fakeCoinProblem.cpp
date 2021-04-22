/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 3 - ATIVIDADES PRÁTICAS - EXERCÍCIO 07
                               Fake Coin Problem
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <cstdlib> // floor
#include <iomanip> // setw

using namespace std;

class classCoinBag {
    // Classe para armazenar e manipular sacos de moedas
private:
    // Tamanho do saco de moedas
    int bag_size;

    // Posição da moeda falsa: -1 se não tem, posição da moeda falsa otherwise
    int position;

    // Peso da moeda falsa: -1 se moeda é mais leve; 1 se é mais pesada
    int weight;

public:
    // Construtor da Classe
    // Inicializa seu tamanho 'n' e a posição da moeda falsa 'p'
    // Determina se a moeda falsa é mais leve ou mais pesada (default: leve)
    classCoinBag(int n, int p, int fake_weight = -1) {
        // Peso deve ser 1 OU -1, apenas
        if (fake_weight == -1 or fake_weight == 1) { weight = fake_weight; }
        else { weight = -1; }
        bag_size = n;
        position = p;
    }

    // Retorna a quantidade de moedas
    int size() { return bag_size; }

    // Retorna a posição da moeda falsa
    int fake_pos() { return position; }

    // Informa se moeda falsa é mais leve (-1) ou mais pesada (+1)
    int fake_weight() { return weight; }
        
    // Simula o resultado uma balança
    // ENTRADAS:
    // Início da amostra: sample_init
    // Tamanho da amostra: sample_size (deve ser PAR OBRIGATORIAMENTE)
    // PROCEDIMENTO:
    // Compara o peso da primeira metade da amostra com o peso da segunda metade
    // SAÍDA:
    // -1 se primaeira metade for mais pesada, 1 se segunda metade for mais pesada, 
    // 0 se metades tiverem o mesmo peso
    int balance(int sample_init, int sample_size) {
        // Se a posição da moeda falsa estiver fora do range da amostra, metades são iguais
        if (position < sample_init or position >= sample_init + sample_size) return 0;
        // Caso a moeda falsa estiver na primeira metade, o resultado da comparação 
        // será o contrário do peso da moeda (mais leve: segunda metade mais pesada)
        else if (position < sample_init + sample_size / 2) return -1 * weight;
        // Caso contrário, o resultado da comparação será o peso da moeda 
        // (mais leve: primeira metade mais pesada)
        else return weight;
    }
};

int fakeCoinProblem(classCoinBag& B, int sample_init, int sample_size, int fake_weight = -1) {
    /*  Implementação do algoritmo Fake Coin Problem
    * Retorna a posição da moeda falsa fazendo comparações em uma balança
    * ENTRADAS:
    * Ponteiro para classe B com saco de moedas
    * Início da amostra: sample_init
    * Tamanho da amostra: sample_size (pode ser ímpar)
    * Peso da moeda falsa: fake_weight (default: -1 ou mais leve)
    * SAÍDA:
    * Inteiro com a posição da moeda falsa
    */

    // Caso o tamanho da amostra seja zero: retorne posição 0
    if (sample_size == 0) { return 0; }

    // Iniciliza resultado das balanças
    int result;

    // Caso a amostra tenha tamanho ímpar
    if (sample_size % 2 == 1) {
        // Coloque na balança todos elementos, exceto o último
        result = B.balance(sample_init, sample_size - 1);
        // Caso as metades tenham mesmo tamanho, a moeda falsa é a última
        if (result == 0) { return sample_init + sample_size - 1; }
    }
    // Caso a amostra tenha tamanho par
    else {
        // Coloque na balança todos elementos
        result = B.balance(sample_init, sample_size);
    }

    // n é a metade do tamanho da amostra, arredondado para baixo e convertido em inteiro
    int n = (int)floor(sample_size / 2);

    // i é o novo início da amostra: resultados possíveis:
    // sample_init se moeda leve e 2a metade mais pesada ou moeda pesada e 2a metade mais leve 
    // sample_init + n se moeda leve e 2a metade mais leve ou moeda pesada e 2a metade mais pesada 
    int i = sample_init + n * abs((result + fake_weight) / 2);

    // Recursivamente, retorne o resultado para novo ínicio e metade da amostra
    return fakeCoinProblem(B, i, n, fake_weight);
}

int main() {

    // Vetor com quantidades de moeda para teste
    vector<int> v = { 1, 2, 3, 9, 12 };
    int pos;

    // Para cada quantidade de moedas no vetor v
    for (int n : v) {
        // Coloca a moeda falsa em cada uma das n posições
        // Busca e compara o resultado com o real

        // Imprime o número de moedas
        cout << n << " coins:" << endl;

        // Percorre cada posição
        for (int i = 0; i < n; i++) {
            // Inicia saco com n moedas e moeda falsa na posição i (mais leve)
            classCoinBag B(n, i);

            // Encontra a posição da moeda falsa
            pos = fakeCoinProblem(B, 0, n);

            // Posição da moeda: x >> Encontrada em: y.
            cout << "Coin position: " << setw(2) << B.fake_pos() << " >> ";
            cout << "Found at: " << setw(2) << pos << endl;
        }
        cout << endl;
    }

    return 0;
}