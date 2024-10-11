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
    bool Insert(int x);
    bool Remove(int x);
    void Primos(int x);
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


void CBinTree::print() {
    Inorder(m_root);
    cout << endl;
}

void CBinTree::Primos(int x) {
    CBinNode** veri;
    if (m_root == nullptr || m_root->value == x || (m_root->nodes[0] != nullptr && m_root->nodes[0]->value == x) || (m_root->nodes[1] != nullptr && m_root->nodes[1]->value == x)) {
        cout << "el nodo no tiene primos " << endl;
        return;
    }
    else if (!find(x, veri)) {
        cout << "el nodo no existe " << endl;
        return;
    }

    CBinNode** p = &m_root;
    CBinNode** q = &m_root;

    bool a = (*p)->value < x;
    p = &((*p)->nodes[a]);
    q = &((*q)->nodes[!a]);

    while ((*p)->value != x && *p) {
        if ((*p)->nodes[0]->value == x && (*p)->nodes[0] != nullptr) {
            cout << "Sus primos son: ";
            if ((*q)->nodes[0] != nullptr) {
                cout << (*q)->nodes[0]->value << " ";
            }

            if ((*q)->nodes[1] != nullptr) {
                cout << (*q)->nodes[1]->value << " ";
            }
            cout << endl;
            return;
        }
        else if ((*p)->nodes[1]->value == x && (*p)->nodes[1] != nullptr) {
            cout << "Sus primos son: ";
            if ((*q)->nodes[0] != nullptr) {
                cout << (*q)->nodes[0]->value << " ";
            }

            if ((*q)->nodes[1] != nullptr) {
                cout << (*q)->nodes[1]->value << " ";
            }
            cout << endl;
            return;
        }
        else {
            q = p;
            a = (*p)->value < x;
            p = &((*p)->nodes[a]);
            q = &((*q)->nodes[!a]);
        }
    }
}

int main() {
    CBinTree t;
    t.Insert(50);
    t.Insert(30);
    t.Insert(70);
    t.Insert(10);
    t.Insert(40);
    t.Insert(60);
    t.Insert(80);
    t.Insert(5);
    t.Insert(15);
    t.Insert(35);
    t.Insert(45);

    t.print();
    t.Primos(30);
    t.Primos(50);
    t.Primos(10);
    t.Primos(15);
    t.Primos(35);
    t.Primos(900);
}
