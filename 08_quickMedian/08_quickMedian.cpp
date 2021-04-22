/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 3 - ATIVIDADES PRÁTICAS - EXERCÍCIO 08
                     MEDIAN with QUICK SELECT (QUICK MEDIAN)
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

template <class T> void printVector(vector<T>&);
template <class T> void swapPositions(T&, T&);

template <class T> int LomutoPartition(vector<T>& A, int left, int right) {
    /*  Implementação do algoritmo Lomuto Partition
    * Particiona um subarranjo usando o primeiro elemaento como pivô
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * Inteiros com o range do subarranjo (left e right)
    * SAÍDA:
    * Vetor A[left ... range] particionado
    * Inteiro s com índice do novo pivô
    */

    // Pivô é primeiro elemento 
    int p = A[left];

    // Índice do novo pivô começa no primeiro elemento
    int s = left;

    // Percorre todos elementos do subarranjo, exceto o primeiro
    for (int i = left + 1; i <= right; i++) {
        // Para cada elemento menor que o pivô
        if (A[i] < p) {
            // Novo pivô avança uma posição
            s += 1;

            // Troca elemento atual de posição com pivô atual
            swapPositions(A[s], A[i]);
        }
    }

    // Troca o pivô inicial com novo pivô
    swapPositions(A[left], A[s]);

    // Retorne o novo pivô
    return s;
}

template <class T> int quickSelect(vector<T>& A, int left, int right, int k) {
    /*  Implementação do QUICK SELECT   
    * Seleciona o k-ésimo elemento com o auxílio de um algoritmo de partição
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * Inteiros com o range do subarranjo (left e right)
    * Cardinalidade k do elemento a ser seleacionado
    * SAÍDA:
    * Elemento selecionado
    */

    // Realiza a Partição de Lomuto
    int s = LomutoPartition(A, left, right);

    // Se o novo pivô é igual à cardinalidade k, retorne o elemento em tal posição
    if (s == k) { return A[s]; }
    // Caso a cardinalidade seja menor que o novo pivô, faça uma recursão
    // atualizando o limite superior para s - 1
    else if (k < s) { return quickSelect(A, left, s - 1, k); }
    // Caso a cardinalidade seja maior ou igual que o novo pivô, faça uma recursão
    // atualizando o limite inferior para s + 1
    else { return quickSelect(A, s + 1, right, k); }
}

template <class T> double quickMedian(vector<T>& A) {
    /*  Implementação da MEDIANA com auxílio do QUICK SELECT
    * Seleciona a mediana com o auxílio de um algoritmo de partição
    * ENTRADAS:
    * Ponteiro para Vetor A com elementos de qualquer datatype
    * SAÍDA:
    * Mediana do tipo double
    */
    
    // Tamanho da lista de elementos
    int n = A.size();

    // Se tamanho for ímpar
    if (n % 2 == 1) {
        // Seleciona o elemento (n-1)/2 -ésimo com QUICK SELECT 
        return 1.0 * quickSelect(A, 0, n - 1, (n - 1) / 2);
    }
    // Se tamanho for par
    else {
        // Seleciona os elementos n/2 e n/2 - 1 -ésimos com QUICK SELECT 
        int a = quickSelect(A, 0, n - 1, n / 2);
        int b = quickSelect(A, 0, n - 1, n / 2 - 1);
        // Retorna a média entre os elementos selecionados
        return (a + b) / 2.0;
    }
    
}

int main() {
    // Cria um vetor de elementos não ordenados (inteiros) tamanho ÍMPAR
    vector<int> v = {8, 9, 3, 2, 1, 5, 4, 7, 6}; // 

    // Imprime o vetor não ordenado
    cout << "Unsorted vector (1 a 9):" << endl;
    printVector(v);

    // Encontra a mediana
    double med = quickMedian(v);

    // Imprime o resultado
    cout << endl << "Median: " << med << endl << endl;

    // Cria um vetor de elementos não ordenados (inteiros) tamanho PAR
    v = { 7, 9, 2, 5, 4, 1, 10, 3, 6, 8 }; 

    // Imprime o vetor não ordenado
    cout << "Unsorted vector (1 a 10):" << endl;
    printVector(v);

    // Encontra a mediana
    med = quickMedian(v);

    // Imprime o resultado
    cout << endl << "Median: " << med << endl;

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
void swapPositions(T& xp, T& yp) {
    /*  Função para Trocar os valores de duas variáveis
    * ENTRADAS:
    * Ponteiros xp, yp para elementos de qualquer datatype
    */

    T temp = xp;    // Guarda o conteúdo apontado por xp em temp
    xp = yp;        // Guarda o conteúdo apontado por yp na pos. apontada por xp
    yp = temp;      // Guarda o conteúdo temp na posição apontada por yp
}