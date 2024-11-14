#include <iostream>
using namespace std;

struct node {
    int valor;
    int y;
    node* down = nullptr;
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
            if (find_d(p,y)) {
                if (v == 0) {
                    node* temp = *p;
                    *p = temp->down;
                    delete temp;
                }
                else {
                    (*p)->valor = v;
                }
            }
            else{
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

    cout << m.get(0, 0) << endl;
    cout << m.get(2, 2) << endl;
    cout << m.get(1, 0) << endl;


    return 0;
}
