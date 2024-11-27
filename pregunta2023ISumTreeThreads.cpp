#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mt;

////////////////////////////////////////////////////////////////////////////////////////////////////////

struct CBinNode
{
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0;
    }
    int value;
    CBinNode* nodes[2];
};

////////////////////////////////////////////////////////////////////////////////////////////////////////

class CBinTree
{
public:
    CBinTree();
    bool Insert(int x);
    void Print();
    void print();
private:
    void Inorder(CBinNode* p);
    void printLevelOrder(CBinNode* root);
    void printCurrentLevel(CBinNode* root, int level);
    int  height(CBinNode* node);
    CBinNode* m_root = nullptr;
    vector<CBinNode*> almacen;
};

CBinTree::CBinTree()
{
    m_root = 0;
}


bool CBinTree::Insert(int x)
{
    if (almacen.empty() || almacen.size() != 1) {
        CBinNode* temp = new CBinNode(x);
        almacen.push_back(temp);
        return false;
    }
    else {
        CBinNode* temp = new CBinNode(x);
        almacen.push_back(temp);

        int suma_node = almacen[0]->value + almacen[1]->value;
        CBinNode* nuevo = new CBinNode(suma_node);

        nuevo->nodes[0] = almacen[0];
        nuevo->nodes[1] = almacen[1];

        if (m_root == nullptr) {
            m_root = nuevo;
        }
        else {
            CBinNode* newraiz = new CBinNode(m_root->value + nuevo->value);
            newraiz->nodes[0] = m_root;
            newraiz->nodes[1] = nuevo;
            m_root = newraiz;
        }
        almacen.clear();
        return true;
    }
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

void CBinTree::printLevelOrder(CBinNode* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
    {
        cout << i << ":  ";
        printCurrentLevel(root, i);
        cout << endl;
    }
}

void CBinTree::printCurrentLevel(CBinNode* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        cout << root->value << "  ";
    else if (level > 1) {
        printCurrentLevel(root->nodes[0], level - 1);
        printCurrentLevel(root->nodes[1], level - 1);
    }
}

int CBinTree::height(CBinNode* node)
{
    if (node == NULL)
        return 0;
    else {
        int lheight = height(node->nodes[0]);
        int rheight = height(node->nodes[1]);

        // Use the larger one
        if (lheight > rheight) {
            return (lheight + 1);
        }
        else {
            return (rheight + 1);
        }
    }
}

void CBinTree::Print()
{
    printLevelOrder(m_root);
    cout << endl;
}

void ins(CBinTree* t, int* ini, int* fin) {
    mt.lock();
    while (ini < fin) {
        t->Insert(*ini);
        ini++;
    }
    mt.unlock();
}

int main()
{
    CBinTree t;
    int Leafs[128] = { 94,38,69,61,46,31,85,23,34,17,54,22,75,100,97,62,58,47,34,3,98,57,66,67,99,17,69,46,14,36,96,83,8,97,53,58,33,94,79,67,4,3,21,63,7,15,89,14,63,80,94,17,62,18,32,71,15,22,75,47,21,24,86,27,39,59,7,62,84,93,93,62,55,27,50,34,94,93,14,20,6,82,49,58,2,98,74,36,71,60,63,46,71,89,56,66,37,18,37,99,79,26,93,68,67,96,48,80,51,8,27,51,53,54,12,22,98,26,60,92,25,81,24,67,74,21,30,55 };

    int* ar = Leafs;
    vector<thread> vec;
    int suma = 128 / 4;

    for (int i = 0; i < 4; i++, ar+= suma) {
        vec.push_back(thread(ins, &t, ar, ar + suma));
    }

    for (int i = 0; i < vec.size(); i++) {
        vec[i].join();
    }
    t.Print();
    
}
