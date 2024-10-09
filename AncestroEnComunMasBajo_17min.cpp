#include <iostream>
using namespace std;

struct CBinNode {
    int value;
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
    bool find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void Inorder(CBinNode* p);
public:
    void AncestroEnComunMasBajo(int x1, int x2);
    bool Insert(int x);
    bool Remove(int x);
    void print();
};

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
    delete temp;
    return true;
}

void CBinTree::Inorder(CBinNode* p) {
    if (!p) return;
    Inorder(p->nodes[0]);
    cout << p->value << " ";
    Inorder(p->nodes[1]);
}


void CBinTree::AncestroEnComunMasBajo(int x1, int x2) {
    CBinNode** x1node = &m_root;
    CBinNode** x2node = &m_root;
    CBinNode* an = nullptr;

    while (an == nullptr) {
        do {

            if ((*x1node)->value == (*x2node)->value && (*x1node)->value != x1 && (*x2node)->value != x2) {
                an = *x2node;
            }

            if ((*x1node)->value != x1) {
                x1node = &((*x1node)->nodes[(*x1node)->value < x1]); 
            }

            if ((*x2node)->value != x2) {
                x2node = &((*x2node)->nodes[(*x2node)->value < x2]);
            }


            if (*x1node == nullptr || *x2node == nullptr) {
                cout << "alguno de los nodos no existe intenta denuevo " << endl;
                return;
            }


        } while ((*x1node)->value != x1 || (*x2node)->value != x2);
    }
    cout << "el ancestro mas bajo de " << x1 << " y " << x2 << " es: " << an->value << " " << endl;
}



void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}


int main() {
    CBinTree t;
    t.Insert(50);
    t.Insert(30);
    t.Insert(70);
    t.Insert(27);
    t.Insert(20);
    t.Insert(10);
    t.Insert(15);
    t.Insert(43);
    t.Insert(65);
    t.Insert(90);
    t.Insert(100);

    t.AncestroEnComunMasBajo(43, 65);
    t.AncestroEnComunMasBajo(27, 20);
    t.AncestroEnComunMasBajo(65, 100);
    t.AncestroEnComunMasBajo(1, 65);
}
