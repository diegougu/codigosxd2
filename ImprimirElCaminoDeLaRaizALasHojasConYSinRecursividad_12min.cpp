#include <iostream>
#include <queue>
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
    void LeafsRecursividad(CBinNode* p);
public:
    bool Insert(int x);
    bool Remove(int x);
    void PrintRootToLeafsPathSinRecursividad();
    void PrintRooToLeafsPathConRecursividad();
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

void CBinTree::PrintRootToLeafsPathSinRecursividad() {
    if (m_root == nullptr) {
        return;
    }
    CBinNode* p = m_root;
    queue<CBinNode*> q;
    q.push(p);

    while (!q.empty()) {
        p = q.front();
        q.pop();

        if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
            for (CBinNode** path = &m_root; (*path)->value != p->value; path = &((*path)->nodes[(*path)->value < p->value])){
                cout << (*path)->value << " ";
            }
            cout << p->value;
            cout << endl;
        }

        if (p->nodes[0] != nullptr) {
            q.push(p->nodes[0]);
        }

        if (p->nodes[1] != nullptr) {
            q.push(p->nodes[1]);
        }

    }

}

void CBinTree::LeafsRecursividad(CBinNode* p) {
    if (!p) return;
    LeafsRecursividad(p->nodes[0]);

    if (p->nodes[0] == nullptr && p->nodes[1] == nullptr) {
        for (CBinNode** path = &m_root; (*path)->value != p->value; path = &((*path)->nodes[(*path)->value < p->value])) {
            cout << (*path)->value << " ";
        }
        cout << p->value;
        cout << endl;
    }
    LeafsRecursividad(p->nodes[1]);


}


void CBinTree::PrintRooToLeafsPathConRecursividad() {
    LeafsRecursividad(m_root);
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

    t.PrintRooToLeafsPathConRecursividad();
    cout << "---------------------------------------------------------" << endl;
    t.PrintRootToLeafsPathSinRecursividad();
    
}
