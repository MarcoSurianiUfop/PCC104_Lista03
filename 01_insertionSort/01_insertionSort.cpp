/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 3 - ATIVIDADES PRÁTICAS - EXERCÍCIO 01
                                 INSERTION SORT
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

template <class T>
void printVector(vector<T>& v);

template <class T>
void insertionSortVector(vector<T>& A) {
    /*  Implementação do INSERTION SORT
    * Ordena os elementos de uma série em ordem crescente
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    */

    // Tamanho da entrada
    int n = A.size();

    // Valor atual (do tipo T)
    T v;

    // Contador j
    int j;

    // Cria sucessivos subarranjos cada vez menores
    for (int i = 1; i <= n - 1; i++) {

        // Valor atual é o primeiro do subarranjo seuperior, 
        // Contador parte do índice do último valor ao subarranjo inferior
        v = A[i];
        j = i - 1;

        // Percorre o subarranjo inferior do último ao primeiro, 
        // parando ao encontrar um valor menor que o valor atual v
        while (j >= 0 and A[j] > v) {
            
            // Caso o valor apontado por j seja maior ou igual ao valor atual v,
            // leve o valor apontado por j para a posição j + 1 e decremente j
            A[j + 1] = A[j];
            j--;
        }

        // Caso o contador j alcance o valor -1 ou o valor apontado por j seja 
        // menor que o valor atual v, atualize o valor na posição j + 1 com v
        A[j + 1] = v;
    }
}

int main() {
    // Cria um vetor de elementos não ordenados (inteiros) 
    vector<int> v = { 30, 64, 25, 12, 22, 35, 22, 11, 10 };

    // Imprime o vetor não ordenado
    cout << "Unsorted vector:" << endl;
    printVector(v);

    // Ordena o vetor usando o BUBBLE SORT
    insertionSortVector(v);

    // Imprime o vetor ordenado
    cout << endl << "Sorted vector (Insertion):" << endl;
    printVector(v);

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
