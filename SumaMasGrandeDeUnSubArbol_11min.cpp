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
public:
    bool Insert(int x);
    bool Remove(int x);
    void SubtreeSum();
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

void CBinTree::SubtreeSum() {
    if (m_root == nullptr) {
        return;
    }
    int sumsubtreeact = 0;
    int temp = 0;
    queue<CBinNode*> subtree;
    CBinNode* i = m_root;
    subtree.push(i);

    while (!subtree.empty()) {
        i = subtree.back();
        subtree.pop();
        temp = i->value;
        if (i->nodes[0] != nullptr) {
            temp = temp + i->nodes[0]->value;
            subtree.push(i->nodes[0]);

        }
        if (i->nodes[1] != nullptr) {
            temp = temp + i->nodes[1]->value;
            subtree.push(i->nodes[1]);
        }

        if (temp > sumsubtreeact) {
            sumsubtreeact = temp;
        }

    }

    cout << "la suma mas grande del arbol es: " << sumsubtreeact << endl;

}

int main() {
    CBinTree t;
    int arr[10] = { 24,83,57,89,27,74,98,31,12,66};
    for (int i = 0; i < 10; i++) {
        t.Insert(arr[i]);
    }
    t.print();
    t.SubtreeSum();
}
