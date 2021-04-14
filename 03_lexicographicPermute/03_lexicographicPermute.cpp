/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 3 - ATIVIDADES PRÁTICAS - EXERCÍCIO 03
                               LexicographicPermute
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>

using namespace std;

bool has_2consec_increasing(vector<int>& p);
void nextLexicographicPermute(vector<int>& p);
int find_i(vector<int>& p);
int find_j(vector<int>& p, int i);
void reverse_greater_i(vector<int>& p, int i);
void swapPositions(int& xp, int& yp);
void printPermutations(vector<vector<int>>& P);

vector<vector<int>> lexicographicPermute(int n) {
    /*  Implementação do LexicographicPermute para gerar permutações
    *   em ordem lexicográfica
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
        p.push_back(i + 1);

    // Acrescenta a permutação p atual à saída P
    P.push_back(p);

    // Enquanto a permutação atual contiver um elemento móvel
    while (has_2consec_increasing(p)) {
        // Transforma p na próxima permutação
        nextLexicographicPermute(p);

        // Acrescenta a permutação p atual à saída P
        P.push_back(p);
    }

    return P;
}

void nextLexicographicPermute(vector<int>& p) {
    /*  Implementação do LexicographicPermute para gerar permutações
    *   em ordem lexicográfica
    * ENTRADA:
    * Um vetor de inteiros com uma permutação
    * SAÍDA:
    * Um vetor de inteiros com a próxima permutação lexicográfica
    */

    int i, j;

    // Enquanto a permutação atual contiver um elemento móvel
    if (has_2consec_increasing(p)) {

        // Quebra a sequencia decrescente
        i = find_i(p);

        // Maior índice de um elemento maior que p[i] na sequencia decrescente
        j = find_j(p, i);

        // Troca posição
        swapPositions(p[i], p[j]);

        // x
        reverse_greater_i(p, i);
    }
}

int main() {
    // 
    int n;

    // Pede o número de elementos
    cout << "Enter the number of elements (integer): ";
    cin >> n;

    // Cria as permutações
    vector<vector<int>> P = lexicographicPermute(n);

    // Imprime as permutações
    cout << endl << "Lexicographic Permutations:" << endl;
    printPermutations(P);

    vector<int> p = { 5, 4, 1, 3, 2 };
    cout << endl << "Exemplo: ";
    for (int x : p) cout << x << " , ";

    nextLexicographicPermute(p);
    cout << endl << "Proxima: ";
    for (int x : p) cout << x << " , ";

    return 0;
}

bool has_2consec_increasing(vector<int>& p) {
    int n = p.size();

    for (int i = 0; i < n - 1; i++) {
        if (p[i + 1] > p[i])
            return true;
    }

    return false;
}

int find_i(vector<int>& p) {
    int n = p.size();

    for (int i = n - 1; i > 1; i--)
        if (p[i] > p[i - 1])
            return i - 1;

    return 0;
}

int find_j(vector<int>& p, int i) {
    int n = p.size();

    for (int j = n - 1; j >= i + 1; j--)
        if (p[j] > p[i])
            return j;
}

void reverse_greater_i(vector<int>& p, int i) {
    int n = p.size();

    vector<int> aux;

    
    for (int j = i + 1; j < n; j++)
        aux.push_back(p[j]);

    for (int j = i + 1; j < n; j++)
        p[j] = aux[n - j - 1];
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
