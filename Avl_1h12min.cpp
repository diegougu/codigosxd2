#include <iostream>
#include <vector>
using namespace std;

struct CBinNode {
    int value;
    CBinNode* nodes[2];
    int altura;
    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
    }
};

class AvlTree {
private:
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p, vector<CBinNode*>& rec);
    void Inorder(CBinNode* p);
    int calcularaltura(CBinNode* p);
    int diferenciadealtura(CBinNode* p);
    void Avl(vector<CBinNode*>& rec);
public:
    bool Insert(int x);
    void print();
};

int AvlTree::calcularaltura(CBinNode* p) {
    if (!p) return 0;
    int left = p->nodes[0] ? p->nodes[0]->altura : 0;
    int right = p->nodes[1] ? p->nodes[1]->altura : 0;
    return 1 + max(left, right);
}

int AvlTree::diferenciadealtura(CBinNode* p) {
    int left = p->nodes[0] ? p->nodes[0]->altura : 0;
    int right = p->nodes[1] ? p->nodes[1]->altura : 0;

    return right - left;
}

bool AvlTree::find(int x, CBinNode**& p, vector<CBinNode*>& rec) {
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x])) {
        if (*p != nullptr) {
            rec.push_back(*p);
        }
    }
    return *p && (*p)->value == x;
}

void AvlTree::Avl(vector<CBinNode*>& rec) {
    int diferenciaActual = 0;
    int diferenciaAnterior = 0;
    int i = rec.size() - 1;
    bool avl = false;
    while (i >= 0 && avl == false){
        diferenciaAnterior = diferenciaActual;
        CBinNode* act = rec[i];
        act->altura = calcularaltura(act);
        diferenciaActual = diferenciadealtura(act);

        if (diferenciaActual == 2 || diferenciaActual == -2) {

            CBinNode* ant = rec[i + 1];
            if (act->nodes[1] == ant && diferenciaAnterior == 1) {
                act->nodes[1] = ant->nodes[0];
                ant->nodes[0] = act;

                if (act == m_root) {
                    m_root = ant;
                }
                else {
                    CBinNode* padre = rec[i - 1];
                    padre->nodes[0] == act ? padre->nodes[0] = ant : padre->nodes[1] = ant;
                }

                avl = true;
            }
            else if (act->nodes[0] == ant && diferenciaAnterior == -1) {

                act->nodes[0] = ant->nodes[1];
                ant->nodes[1] = ant;

                if (act == m_root) {
                    m_root = ant;
                }
                else {
                    CBinNode* padre = rec[i - 1];
                    padre->nodes[0] == act ? padre->nodes[0] = ant : padre->nodes[1] = ant;
                }
                
                avl = true;
            }
            else if (act->nodes[0] == ant && diferenciaAnterior == 1) {
                CBinNode* c = ant->nodes[1];
                act->nodes[1] = c->nodes[1];
                ant->nodes[1] = c->nodes[0];
                c->nodes[0] = ant;
                c->nodes[1] = act;

                if (act == m_root) {
                    m_root = c;
                }
                else {
                    CBinNode* padre = rec[i - 1];
                    padre->nodes[0] == act ? padre->nodes[0] = c : padre->nodes[1] = c;
                }
                
                avl = true;
            }
            else if (act->nodes[1] == ant && diferenciaAnterior == -1) {
                CBinNode* c = ant->nodes[0];
                act->nodes[1] = c->nodes[0];
                ant->nodes[0] = c->nodes[1];
                c->nodes[0] = act;
                c->nodes[1] = ant;

                if (act == m_root) {
                    m_root = c;
                }
                else {
                    CBinNode* padre = rec[i - 1];
                    padre->nodes[0] == act ? padre->nodes[0] = c : padre->nodes[1] = c;
                }

                avl = true;
            }
        }
        i--;
    }
}



bool AvlTree::Insert(int x) {
    CBinNode** p;
    vector<CBinNode*> rec;
    if (find(x, p, rec)) {
        return false;
    }
    *p = new CBinNode(x);
    rec.push_back(*p);
    Avl(rec);
    return true;
}

void AvlTree::Inorder(CBinNode* p) {
    if (!p) return;
    Inorder(p->nodes[0]);
    cout << p->value << " ";
    Inorder(p->nodes[1]);
}


void AvlTree::print() {
    Inorder(m_root);
    cout << endl;
}


int main() {
    AvlTree t;
    t.Insert(1);
    t.Insert(8);
    t.Insert(9);
    t.Insert(4);
    t.Insert(7);
    t.Insert(6);
    t.Insert(2);
    t.Insert(3);

    t.print();
}
