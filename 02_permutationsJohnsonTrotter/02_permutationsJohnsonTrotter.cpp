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

        // Índice do maior móvel e maior valor móvel
        ik = largest_mobile(p, M);
        k = p[ik];

        // x
        s = M[ik];
        swapPositions(p[ik], p[ik + s]);
        swapPositions(M[ik], M[ik + s]);
        
        // x
        reverseDirections(p, M, k);

        // Acrescenta a permutação p atual à saída P
        P.push_back(p);
    }

    return P;
}

int main() {
    // 
    int n;

    // Pede o número dea elementos
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
    int n = p.size();
    int s;

    for (int i = 0; i < n; i++) {
        s = M[i];
        if (i + s >= 0 and i + s < n)
            if (p[i] > p[i + s])
                return true;
    }

    return false;
}

int largest_mobile(vector<int>& p, vector<int>& M) {
    int n = p.size();

    int k = 0, ik;

    int s;

    for (int i = 0; i < n; i++) {
        s = M[i];
        if (i + s >= 0 and i + s < n)
            if (p[i] > p[i + s])
                if (p[i] > k) {
                    k = p[i];
                    ik = i;
                }
    }

    return ik;
}

void reverseDirections(vector<int>& p, vector<int>& M, int k) {
    int n = p.size();

    for (int i = 0; i < n; i++)
        if (p[i] > k)
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
