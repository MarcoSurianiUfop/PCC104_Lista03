/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                  LISTA 3 - ATIVIDADES PRÁTICAS - EXERCÍCIO 04
                               Generating Subsets
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <iomanip> // setw

using namespace std;

class classBRGC {
    // Classe para armazenar e manipular sequências de bits BRGC
private:
    // Cria um vetor de vetores de booleanos
    vector<vector<bool>> V;

    // Método para adicionar vaetor de booleanos à saída V
    void add_subset(vector<bool> S) { V.push_back(S); }

public:
    // Retorna a quantidade de subconjuntos armazenada
    int size() { return V.size(); }

    // Inicializa um nova sequência de booleanos
    // Primeira lista contém apenas false, segunda apenas true
    void initialize() {
        V.push_back({ false });
        V.push_back({ true });
    }

    // Retorna a k-ésima sequência de booleanos de V
    vector<bool> get_subset(int k) { return V[k]; }

    // Retorna os elementos de V em ordem reversa
    classBRGC get_reversed() {
        classBRGC R;
        for (int i = V.size() - 1 ; i >= 0; i--)
            R.add_subset(V[i]);
        return R;
    }

    // Adiciona bool b no início de todas sequências de V
    void add_front(bool b) { 
        // unsigned int por causa do size
        for (unsigned int i = 0; i < V.size(); i++)
            V[i].insert(V[i].begin(), b);
    }

    // Adiciona as sequências de L2 à lista de sequências de V
    void append_list(classBRGC L2) {
        for (int i = 0; i < L2.size(); i++)
            V.push_back(L2.get_subset(i));
    }
};

template <class T> void printSubsets(vector<vector<T>>& S);

classBRGC make_BRGC(int n) {
    /*  Constrói uma lista de binários na sequência binary reflected Gray code
    * ENTRADA:
    * Inteiro n com tamanho de cada número binário
    * SAÍDA:
    * Lista com sequências de booleanos (números binários)
    */

    // Cria listas de sequências L1 e L2
    classBRGC L1, L2;

    // Caso n = 1, L1 recaebe sequências false e true, nesta ordem
    if (n == 1) {
        L1.initialize();
    }
    else {
        // Caso contrário, constrói L1 com (n-1) elementos
        L1 = make_BRGC(n - 1);
        // Constrói L2 com elementos de L1 em ordem reversa
        L2 = L1.get_reversed();
        // Adiciona false no início de cada sequência de L1
        L1.add_front(false);
        // Adiciona true no início de cada sequência de L2
        L2.add_front(true);
        // Adiciona lista L2 no final da liasta L1
        L1.append_list(L2);
    }

    return L1;
}

template <class T> vector<vector<T>> make_Subsets(vector<T>& S) {
    /*  Constrói uma lista com todos subconjuntos de um conjunto S
    * ENTRADA:
    * Ponteiro para Vetor S com conjunto
    * SAÍDA:
    * Vetor de vetores com subconjuntos
    */

    // Cria uma sequência binary reflected Gray code do tamanho de S
    classBRGC L = make_BRGC(S.size());

    // Vetor com sequência BRGC de cada subconjunto 
    vector<bool> B;

    // Inicializa Vetor de vetores com subconjuntos
    vector<vector<T>> subsets;

    // Para cada sequência binary reflected Gray code
    for (int i = 0; i < L.size(); i++) {
        // Armazena sequência binary reflected Gray code atual em B
        B = L.get_subset(i);

        // Vetor V para armazenar subconjunto atual
        vector<T> V;

        // Para cada elemento de B
        // unsigned int por causa do size
        for (unsigned int j = 0; j < S.size(); j++) {
            // Se B é verdadeiro, adicione elemento equivalente em S ao vetor V
            if (B[j]) { V.push_back(S[j]); }
        }

        // Adicione sunconjunto atual V à lista de subconjuntos
        subsets.push_back(V);
    }

    return subsets;
}

int main() {
    // Cria um conjunto de caracteres
    vector<char> my_set = {'m', 'a', 'r', 'k'}; 

    // Imprime conjunt de caracteres
    cout << "Set: ";
    for (char c : my_set)
        cout << c << " , ";

    // Cria os subconjuntos
    vector<vector<char>> my_subsets = make_Subsets(my_set);

    // Imprime os subconjuntos
    cout << endl << endl << "Subsets:" << endl;
    printSubsets(my_subsets);

    return 0;
}

template <class T> void printSubsets(vector<vector<T>>& S) {
    /*  Função para Imprimir uma lista de subconjuntos
    * ENTRADA:
    * Ponteiro para lista de subconjuntos S com elementos de qualquer datatype
    */

    // Percorre todos subconjuntos de S
    // unsigned int por causa do size
    for (unsigned int i = 0; i < S.size(); i++) {
        // Imprime o número do subconjunto
        cout << setw(2) << i + 1 << " :\t";
        // Itera todos os elementos k do subvetor S[i]
        for (T k : S[i])
            // Imprime cada elemento de S[i]
            cout << k << " , ";
        cout << endl;
    }
}
