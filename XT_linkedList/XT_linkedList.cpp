/******************************************************************************
                    PCC104 - PROJETO E ANÁLISE DE ALGORITMOS
                     LISTA 3 - ATIVIDADES PRÁTICAS - EXTRA
                                  LINKED LIST
    Aluno: MARCO AURÉLIO MOURA SURIANI - 2021.10177
*******************************************************************************/

#include <iostream>
#include <vector>
#include <iomanip> 

using namespace std;

class classNode {
    // Classe para armazenar uma lista com pontos no plano
private:
    // Cria um vetor com pares de inteiros
    int value;
    classNode* next = nullptr;
    bool head = false;
    int link_size = 0;

public:
    classNode(int k) { 
        value = k; 
        link_size += 1;
    }
    void set_head() { head = true;  }

    void set_value(int k) { value = k; }

    void set_next(classNode* ptr) { next = ptr; }

    int size() { return link_size; }

    int get_value() { return value; }

    void insert(int k) {
        if (next == nullptr) { next = new classNode(k); }
        else { next->insert(k); }

        if (head) { link_size += 1; }
    }
    
    classNode* get_next_address() { return next; };

    void delete_next() { next = next->get_next_address(); }

    bool delete_val(int k) {

        if (head and value == k) {
            value = next->get_value();
            link_size -= 1;
            delete_next();
            return true;
        }
         
        bool done = false;

        if (next == nullptr) { return false; }

        if (next->get_value() == k)
        {
            delete_next();
            if (head) { link_size -= 1; }
            return true;
        }
        else { 
            done = next->delete_val(k); 
            if (!head) { return done; }
        }

        if (head and done) { link_size -= 1; }
        return done;
    }

    void emplace(int k, int n) {
        if (head and n > link_size) { return; }
        else if (head) { link_size += 1; }

        if (head and n == 0) { 
            classNode* ptr = next;
            next = new classNode(value);
            next->set_next(ptr);
            value = k;
            return; 
        }
        
        if (n == 0) {
            classNode* ptr = next;
            next = new classNode(value);
            next->set_next(ptr);
            value = k;
            return;
        }
        else { next->emplace(k, n - 1); }
    }

    void print_node() {
        if (!head) cout << " , ";
        cout << setw(2) << value;
        if (next == nullptr) { cout << endl; }
        else { next->print_node(); }
    }
};


int main() {
    classNode no(5);
    no.set_head();
    no.insert(10);
    no.insert(15);
    no.insert(20);
    no.insert(25);
    no.print_node();
    cout << no.size() << endl;
    no.delete_val(35);
    no.print_node();
    cout << no.size() << endl;
    no.delete_val(20);
    no.print_node();
    cout << no.size() << endl;
    no.delete_val(5);
    no.print_node();
    cout << no.size() << endl;
    no.delete_val(25);
    no.print_node();
    cout << no.size() << endl;
    no.emplace(99, 0);
    no.print_node();
    cout << no.size() << endl;
    no.emplace(50, 2);
    no.print_node();
    cout << no.size() << endl;
    return 0;
}