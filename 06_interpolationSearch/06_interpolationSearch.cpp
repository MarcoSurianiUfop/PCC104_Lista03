/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 3 - ATIVIDADES PRÁTICAS - EXERCÍCIO 06
                              Interpolation Search
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

struct search {
    // Estrutura para armazenar o resultado de uma busca (posição encontrada)
    // junto com o número de iteraçõaes necessário para encontrar o resultado
    int position;
    int iteration;
};

template <class T> void printVector(vector<T>& v);
template <class T> void printResults(T k, search result);

template <class T> search interpolationSearchVector(vector<T>& A, T K) {
    /*  Implementação do INTERPOLATION SEARCH
    * Encontra um elemento em uma série em ordem crescente
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * Elemento K do mesmo datatype de A que será buscado
    */

    // Cria estrutura que contém posição e número de iteraçõaes necessárias
    search result;

    // Se valor buscado K estiver fora do range do vetor A, haverá extrapolação
    // Retorne posição -1 e o nro de iterações = 0 
    if (K < A[0] or K > A[A.size() - 1]) {
        result.position = -1;
        result.iteration = 0;
        return result;
    }

    // Inteiros com limitadores da busca: left = 0 e right = n-1
    // Inteiro com ponto x interpolado
    int left = 0, right = A.size() - 1, x;

    // Inicializa contador de iterações com 1
    int iter = 1;

    // Enquanto o limite infeior de busca for <= ao limite superior
    while (left <= right) {

        // Ponto x é a interpolação de K entre left e right arredondado p/ baixo e convertido em inteiro
        x = left + (int)floor((K - A[left]) * (right - left) / (A[right] - A[left]));

        // Se o valor interpolado for o valor buscado K
        if (A[x] == K) {
            // Resultado final é o índice interpolado, iterações é iter; retorna resultado 
            result.position = x;
            result.iteration = iter;
            return result;
        }
        // Caso contrário, se K estiver abaixo do valor médio, novo right = x - 1
        else if (K < A[x]) right = x - 1;
        // Caso contrário, se K estiver acima do valor médio, novo right = x + 1
        else left = x + 1;

        // Adicione uma iteração
        iter += 1;
    }

    // Se chegou aqui, K não foi encontrado. Retorne posição -1 e o nro de iterações
    result.position = -1;
    result.iteration = iter;
    return result;
}

int main() {
    // Cria um vetor com 21 números 4
    vector<int> v(21, 4);
    // Altera o i-ésimo elemento para (4 + i)²
    // Lista de quadrados: elementos em ordem crescente mas não-equidistantes
    // unsigned int por causa size
    for (unsigned int i = 0; i < v.size(); i++)
        v[i] = (v[i] + i) * (v[i] + i);

    // Imprime o vetor ordenado
    cout << "Sorted vector:" << endl;
    printVector(v);
    cout << endl;

    // Inicializa variável de resultados
    search result;

    // Procura cada elemento da lista de crescentes v para registrar nro de iterações

    // Para cada elemento k da lista de crescentes v
    for (int k : v) {
        // Procure tal elemento em v
        result = interpolationSearchVector(v, k);
        // Imprime posição e número de iterações
        printResults(k, result);
    }

    // Repete o procediemento para valores que não estão na lista
    // Um valor abaixo, um valor acima, e um valor dentro do range

    vector<int> w = { 0, 999, 50 };
    // Para cada elemento k da lista de ausentes w
    for (int k : w) {
        // Procure tal elemento em v
        result = interpolationSearchVector(v, k);
        // Imprime posição e número de iterações
        printResults(k, result);
    }

    return 0;
}

template <class T>
void printVector(vector<T>& v) {
    /*  Função para Imprimir vetores
    * ENTRADA:
    * Ponteiro para Vetor v com elementos de qualquer datatype
    */

    // Itera todos os elementos do vetor v
    for (T n : v)
        // Imprime cada elemento
        cout << n << " ";
    cout << endl;
}


template <class T>
void printResults(T k, search result) {
    /*  Função para Imprimir resultado de buscas
    * ENTRADA:
    * Elemento k buscado
    * Estrutura com posição e número de iterações necessárias
    */

    // Elemento 'k' na posição 'pos' com 'iter' iteraçõaes.
    cout << "Element " << setw(3) << k
        << " in position " << setw(2) << result.position
        << " with " << setw(1) << result.iteration << " iterations." << endl;
}