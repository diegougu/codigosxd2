#include <iostream>
#include <queue>
#include <math.h>
using namespace std;

#define VALORNULL -99;
int x = VALORNULL;


struct CBinNode {
    int value;
    int altura;
    CBinNode* nodes[2];

    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
    }
};

class CBinTree {
private:
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    int n_nodes = 0;
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
    void recalcular_altura(CBinNode* p, int alt, int& mayoraltura);
    int espaciado();
public:
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void printBinaryForm();
};


void CBinTree::recalcular_altura(CBinNode* p, int alt, int& mayoraltura) {
    if (!p) return;
    p->altura = alt;

    if (p->altura > mayoraltura) {
        mayoraltura = p->altura;
    }

    recalcular_altura(p->nodes[0], alt + 1, mayoraltura);
    recalcular_altura(p->nodes[1], alt + 1, mayoraltura); 
}

int CBinTree::espaciado() {
    int n = n_nodes;
    int r = 0;
    int i = 0;
    while (r == 0) {
        if (pow(2, i) >= n) {
            r = pow(2, i + 1);
        }
        i++;
    }
    return r;
}

void CBinTree::printBinaryForm() {
    int mayoraltura = 0;
    recalcular_altura(m_root, 1, mayoraltura);
    int esp = espaciado();
    queue<CBinNode*> rec;
    rec.push(m_root);
    int altura_ant = 1;
    int altura_act = 1;
    int mismnodes = 1;
    while (!rec.empty() && rec.front()->altura <= mayoraltura) {
        altura_ant = altura_act;
        CBinNode* act = rec.front();
        altura_act = act->altura;
        rec.pop();

        if (altura_ant != altura_act) {
            cout << endl;
            esp = esp / 2;
            mismnodes = 1;
        }
        else {
            mismnodes++;
        }

        for (int i = 0; i < esp; i++) {
            cout << " ";
        }

        if (act->value != x) {
            cout << act->value;
        }
        else {
            cout << " ";
        }

        for (int i = 0; i < esp / mismnodes; i++) {
            cout << " ";
        }


        if (act->nodes[0] != nullptr) {
            rec.push(act->nodes[0]);
        }
        else {
            CBinNode* n = new CBinNode(x);
            n->altura = act->altura + 1;
            rec.push(n);
        }

        if (act->nodes[1] != nullptr) {
            rec.push(act->nodes[1]);
        }
        else {
            int x = VALORNULL;
            CBinNode* n = new CBinNode(x);
            n->altura = act->altura + 1;
            rec.push(n);
        }


    }
}


bool CBinTree::find(int x, CBinNode**& p) {
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x) {
    CBinNode** p;
    if (find(x, p)) {
        return false;
    }
    *p = new CBinNode(x);
    n_nodes++;
    return true;
}

CBinNode** CBinTree::Rep(CBinNode** p) {
    m_b = !m_b;
    p = &((*p)->nodes[!m_b]);
    while ((*p)->nodes[m_b]) {
        p = &((*p)->nodes[m_b]);
    }
    return p;
}

bool CBinTree::Remove(int x) {
    CBinNode** p;
    if (!find(x, p)) {
        return false;
    }

    if ((*p)->nodes[0] && (*p)->nodes[1]) {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }

    CBinNode* temp = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    n_nodes--;
    delete temp;
    return true;
}

void CBinTree::Inorder(CBinNode* p) {
    if (!p) return;
    Inorder(p->nodes[0]);
    cout << p->value << " ";
    Inorder(p->nodes[1]);
}


void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}


int main() {
    CBinTree t;
    int arr[10] = { 3,1,2,10,8,9,5,4,6,7 };
    for (int i = 0; i < 10; i++) {
        t.Insert(arr[i]);
    }

    t.printBinaryForm();
}
