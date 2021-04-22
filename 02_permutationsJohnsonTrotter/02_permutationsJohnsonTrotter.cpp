/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 3 - ATIVIDADES PRÁTICAS - EXERCÍCIO 02
                                 JohnsonTrotter
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

bool has_mobile(vector<int>& p, vector<int>& M);
int largest_mobile(vector<int>& p, vector<int>& M);
void reverseDirections(vector<int>& p, vector<int>& M, int k);
void swapPositions(int& xp, int& yp);
void printPermutations(vector<vector<int>>& P);

vector<vector<int>> permutationsJohnsonTrotter(int n) {
    /*  Implementação do JohnsonTrotter para gerar permutações
    * ENTRADA:
    * Um inteiro positivo n com o tamanho da permutação
    * SAÍDA:
    * Um vetor de vetores de inteiros com as permutações
    */

    // Inicializa a saída
    vector<vector<int>> P;

    // Inicializa a permutação atual em ordem crescente
    vector<int> p;
    for (int i = 0; i < n; i++)
        p.push_back(i+1);

    // Inicializa o vetor de mobilidade, inicialmente todos para esquerda
    // -1: mobilidade para esquerda
    // +1: mobilidade para direita
    vector<int> M;
    for (int i = 0; i < n; i++)
        M.push_back(-1);

    // Acrescenta a permutação p atual à saída P
    P.push_back(p);

    // Maior elemento móvel k e seu índice ik
    int k, ik;

    // Somador
    int s;

    // Enquanto a permutação atual contiver um elemento móvel
    while (has_mobile(p, M)) {

        // Índice do maior móvel (ik) e maior valor móvel (k)
        ik = largest_mobile(p, M);
        k = p[ik];

        // Troca k com elemento para o qual k aponta (índices e valores)
        // s é a mobilidade do elemento k
        // Se s = 1, troca com o próximo
        // Se s = -1, ttroca com anterior
        s = M[ik];
        swapPositions(p[ik], p[ik + s]);
        swapPositions(M[ik], M[ik + s]);
        
        // Reverte a direção de todos elementos maiores que k
        reverseDirections(p, M, k);

        // Acrescenta a permutação p atual à saída P
        P.push_back(p);
    }

    return P;
}

int main() {
    // Inicializa número de elementos
    int n;

    // Pede o número de elementos
    cout << "Enter the number of elements (integer): ";
    cin >> n;

    // Cria as permutações
    vector<vector<int>> P = permutationsJohnsonTrotter(n);

    // Imprime as permutações
    cout << endl << "Permutations:" << endl;
    printPermutations(P);

    return 0;
}

bool has_mobile(vector<int>& p, vector<int>& M) {
    /*  Verifica se uma permutação possui algum valor móvel
    * Um elemento é móvel se aponta para um adjacente menor do que ele.
    * ENTRADAS:
    * Ponteiro para Vetor p com permutação
    * Ponteiro para Vetor M com respectivas mobilidades
    * SAÍDA:
    * Um booleano indicando true caso haja valor móvel, e falso caso contrário
    */
    
    // Tamanho da permutação
    int n = p.size();

    // Inicializa somador
    int s;

    // Testa cada um dos elementos do vetor p
    for (int i = 0; i < n; i++) {
        // s é a mobilidade do elemento i
        // Se s = 1, troca com o próximo ; Se s = -1, troca com anterior
        s = M[i];
        // Caso primeiro não aponte p/ esquerda nem último aponte p/ direita
        if (i + s >= 0 and i + s < n)
            // Se elemento atual é maior do que elemento para o qual aponta,
            // então tal elemento é movel -> retorne true
            if (p[i] > p[i + s])
                return true;
    }
    
    // Se chegou aqui, então testou todos elementos e naenhum é móvel
    return false;
}

int largest_mobile(vector<int>& p, vector<int>& M) {
    /*  Retorna o maior elemento móvel da permutação
    * Um elemento é móvel se aponta para um adjacente menor do que ele.
    * ENTRADAS:
    * Ponteiro para Vetor p com permutação
    * Ponteiro para Vetor M com respectivas mobilidades
    * SAÍDA:
    * Um inteiro contendo o ÍNDICE do maior elemento móvel da permutação
    * Retorna -1 caso não haja elemento móvel
    */

    // Tamanho da permutação
    int n = p.size();

    // Índice do maior móvel (ik) e maior valor móvel (k)
    int k = 0, ik = -1;

    // Inicializa somador
    int s;

    // Testa cada um dos elementos do vetor p
    for (int i = 0; i < n; i++) {
        // s é a mobilidade do elemento i
        // Se s = 1, troca com o próximo ; Se s = -1, troca com anterior
        s = M[i];
        // Caso primeiro não aponte p/ esquerda nem último aponte p/ direita
        if (i + s >= 0 and i + s < n)
            // Se elemento atual é maior do que elemento para o qual aponta,
            // então tal elemento é movel
            if (p[i] > p[i + s])
                // Se elemento móvel superar o maior elemento móvel até aqui
                if (p[i] > k) {
                    // Atualiza o maior elemento móvel (k) e seu índice (ik)
                    k = p[i];
                    ik = i;
                }
    }
    
    // Retorna o índice ik (caso não encontre nenhum móvel, retorna -1)
    return ik;
}

void reverseDirections(vector<int>& p, vector<int>& M, int k) {
    /*  Reverte a direção de todos elementos maiores que k
    * ENTRADAS:
    * Ponteiro para Vetor p com permutação
    * Ponteiro para Vetor M com respectivas mobilidades
    * Inteiro k de referência
    * SAÍDA:
    * Altera vetor de marcações M
    */

    // Tamanho da permutação
    int n = p.size();

    // Percorre cada um dos elementos do vetor p
    for (int i = 0; i < n; i++)
        // Se elemento atual for maior do que k
        if (p[i] > k)
            // Inverta sua marcação
            M[i] = -M[i];
}


void swapPositions(int& xp, int& yp) {
    /*  Função para Trocar os valores de duas variáveis
    * ENTRADAS:
    * Ponteiros xp, yp para elementos de qualquer datatype
    */

    int temp = xp;  // Guarda o conteúdo apontado por xp em temp
    xp = yp;        // Guarda o conteúdo apontado por yp na pos. apontada por xp
    yp = temp;      // Guarda o conteúdo temp na posição apontada por yp
}


void printPermutations(vector<vector<int>>& P) {
    /*  Função para Imprimir uma lista de Permutações
    * ENTRADA:
    * Ponteiro para Matriz P com elementos de qualquer datatype
    */

    // Itera todos os subvetores p do vetor P
    for (vector<int> p : P) {
        // Itera todos os elementos k do subvetor p
        for (int k : p)
            // Imprime cada elemento
            cout << k << " ";
        cout << endl;
    }
}
