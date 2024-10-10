
#include <iostream>
using namespace std;


struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};


class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    bool Remove(int x);
    void Print();
    void Sobrinos(int x);
private:
    bool Find(int x, CBinNode**& p);
    CBinNode** Rep(CBinNode** p);
    void InOrder(CBinNode* n);
    CBinNode* m_root;
    bool m_b;
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
    // ?
}

bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}
bool CBinTree::Remove(int x)
{
    CBinNode** p;
    if (!Find(x, p)) return 0;
    if ((*p)->nodes[0] && (*p)->nodes[1])
    {
        CBinNode** q = Rep(p);
        (*p)->value = (*q)->value;
        p = q;
    }
    CBinNode* t = *p;
    *p = (*p)->nodes[(*p)->nodes[0] == 0];
    delete t;
    return 1;
}

CBinNode** CBinTree::Rep(CBinNode** q)
{
    m_b = !m_b;
    q = &((*q)->nodes[!m_b]);
    while ((*q)->nodes[m_b])
        q = &((*q)->nodes[m_b]);
    return q;
}

void CBinTree::InOrder(CBinNode* n)
{
    if (!n) return;
    InOrder(n->nodes[0]);
    cout << n->value << " ";
    InOrder(n->nodes[1]);
}

void CBinTree::Print()
{
    InOrder(m_root);
    cout << endl;
}


void CBinTree::Sobrinos(int x) {
    if (m_root == nullptr || m_root->value == x) {
        return;
    }

    CBinNode** p = &m_root;
    CBinNode** q = &m_root;

    for (; (*p)->value != x; p = &((*p)->nodes[(*p)->value < x])) {
        if ((*p)->nodes[0]->value == x) {
            q = &((*p)->nodes[1]);
        }
        else if ((*p)->nodes[1]->value == x) {
            q = &((*p)->nodes[0]);

        }
    }

    if ((*q)->nodes[0] != nullptr) {
        cout << (*q)->nodes[0]->value << " ";
    }

    if ((*q)->nodes[1] != nullptr) {
        cout << (*q)->nodes[1]->value << " ";
    }
    cout << endl;
}


int main()
{
    CBinTree t;
    t.Insert(60);
    t.Insert(30);
    t.Insert(20);
    t.Insert(40);
    t.Insert(10);
    t.Insert(24);
    t.Insert(39);
    t.Insert(45);
    t.Insert(70);
    t.Insert(68);
    t.Insert(85);
    t.Insert(63);
    t.Insert(69);
    t.Insert(80);
    t.Insert(90);

    t.Print();

    t.Sobrinos(85);
    t.Sobrinos(30);
    t.Sobrinos(70);
    t.Sobrinos(40);
    t.Sobrinos(20);


}
