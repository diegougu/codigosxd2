#include <iostream>
#include <queue>
using namespace std;

#define VALORNULL -99

struct CBinNode {
    int value;
    int altura;
    int size;
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
    int inputsize(CBinNode* n, int lvl, int& max_atl);
public:
    bool Insert(int x);
    bool Remove(int x);
    void print();
    void printBinaryForm();
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


void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}

int CBinTree::inputsize(CBinNode* n, int lvl, int& max_alt) {
    if (!n) return 1;
    n->size = inputsize(n->nodes[0], lvl + 1, max_alt) + 1 + inputsize(n->nodes[1], lvl + 1, max_alt);
    n->altura = lvl;
    if (n->altura > max_alt) {
        max_alt = n->altura;
    }
    return n->size;
}

void CBinTree::printBinaryForm() {
    int lvl = 0;
    int max_alt = 1;
    inputsize(m_root, lvl, max_alt);
    queue<CBinNode*> rec;
    rec.push(m_root);
    int altura_ant = m_root->altura;
    int altura_act = m_root->altura;
    while (!rec.empty() && rec.front()->altura <= max_alt) {
        altura_ant = altura_act;
        CBinNode* act = rec.front();
        rec.pop();
        altura_act = act->altura;

        if (altura_act != altura_ant) {
            cout << endl;
        }

        for (int i = 0; i < act->size; i++) {
            cout << " ";
        }

        if (act->value != VALORNULL) {
            cout << act->value;
        }
        else {
            cout << " ";
        }

        for (int i = 0; i < act->size; i++) {
            cout << " ";
        }


        if (act->nodes[0] != nullptr) {
            rec.push(act->nodes[0]);
        }
        else {
            CBinNode* n = new CBinNode(VALORNULL);
            n->altura = act->altura + 1;

            n->size = floor(act->size / 2);
            rec.push(n);
        }

        if (act->nodes[1] != nullptr) {
            rec.push(act->nodes[1]);
        }
        else {
            CBinNode* n = new CBinNode(VALORNULL);
            n->altura = act->altura + 1;
            n->size = floor(act->size / 2);
            rec.push(n);
        }


    }
}

int main() {
    CBinTree t;
    t.Insert(7);
    t.Insert(3);
    t.Insert(10);
    t.Insert(1);
    t.Insert(4);
    t.Insert(8);
    t.Insert(12);

    t.printBinaryForm();

}
