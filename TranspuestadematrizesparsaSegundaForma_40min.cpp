#include <iostream>
using namespace std;

struct node {
    int valor;
    int y;
    node* down = nullptr;
    bool swaped = 0;
    node(int v, int _y, node* d = nullptr) : valor(v), y(_y), down(d) {}
};

class SparseMatrix {
private:
    bool find_d(node**& p, int y) {
        while (*p && (*p)->y < y) {
            p = &((*p)->down);
        }
        return *p && (*p)->y == y;
    }

public:
    int eje_x;
    int eje_y;
    node** x_x;

    SparseMatrix(int _x, int _y) : eje_x(_x), eje_y(_y) {
        x_x = new node * [eje_x];
        for (int i = 0; i < eje_x; i++) {
            x_x[i] = nullptr;
        }
    }

    void set(int x, int y, int v) {
        if (x >= eje_x || y >= eje_y) {
            return;
        }
        else {
            node** p = &x_x[x];
            if (find_d(p, y)) {
                if (v == 0) {
                    node* temp = *p;
                    *p = temp->down;
                    delete temp;
                }
                else {
                    (*p)->valor = v;
                }
            }
            else {
                if (v == 0) {
                    return;
                }
                node* temp = new node(v, y);
                temp->down = *p;
                *p = temp;
            }
        }
    }

    int get(int x, int y) {
        if (x >= eje_x || y >= eje_y) {
            cout << "out of range " << endl;
            return 0;
        }
        else {
            x_x[x];
            node** p = &x_x[x];
            if (find_d(p, y)) {
                return (*p)->valor;
            }
            else {
                return 0;
            }
        }
    }

    void transpuesta() {
        for (int i = 0; i < eje_x; i++) {
            node** current = &x_x[i];
            while (*current != nullptr) {
                node* other = x_x[(*current)->y];
                if (other->y != (*current)->y) {
                    node** p = &other;
                    if (find_d(p, i)) {
                        if ((*current)->swaped != 1 && (*p)->swaped != 1) {
                            swap((*current)->valor, (*p)->valor);
                            (*current)->swaped = 1;
                            (*p)->swaped = 1;
                        }
                        current = &((*current)->down);
                    }
                    else {
                        if ((*current)->swaped != 1) {
                            node* temp = *current;
                            *current = temp->down;
                            temp->down = *p;
                            *p = temp;
                            (*p)->y = i;
                            (*p)->swaped = 1;
                        }
                    }
                }
                else {
                    current = &((*current)->down);
                }
            }
        }
    }

    void print() {
        for (int i = 0; i < eje_x; i++) {
            node* current = x_x[i];
            while (current) {
                cout << "(" << i << "," << current->y << "): " << current->valor << " ";
                current = current->down;
            }
            cout << endl;
        }
    }
};

int main() {
    SparseMatrix m(4, 4);

    m.set(0, 0, 10);
    m.set(0, 2, 20);
    m.set(1, 0, 30);
    m.set(2, 2, 40);
    m.set(0, 1, 15);
    m.set(2, 1, 35);


    m.print();

    m.transpuesta();
    m.print();

    return 0;
}
