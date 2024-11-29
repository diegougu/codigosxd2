#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
using namespace std;

mutex mt;

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
    bool Insert(int x);
    void Print();
private:
    void printLevelOrder(CBinNode* root);
    void printCurrentLevel(CBinNode* root, int level);
    int  height(CBinNode* node);
    CBinNode* m_root = nullptr;
    vector<CBinNode*> rep;
    CBinNode* posi = nullptr;
};

CBinTree::CBinTree()
{
    m_root = 0;
}


bool CBinTree::Insert(int x){

    CBinNode* temp = new CBinNode(x);
    rep.push_back(temp);
    if (rep.size() == 2) {
        CBinNode* nuevo = new CBinNode(rep[0]->value + rep[1]->value);
        nuevo->nodes[0] = rep[0];
        nuevo->nodes[1] = rep[1];

        if (m_root == nullptr) {
            m_root = nuevo;
            posi = nuevo;
        }
        else {
            int alturaposi = height(posi);
            int alturanuevo = height(nuevo);

            if (m_root == posi && alturaposi == alturanuevo) {
                CBinNode* ultra = new CBinNode(m_root->value + nuevo->value);
                ultra->nodes[0] = posi;
                ultra->nodes[1] = nuevo;
                m_root = ultra;
                posi = m_root;
            }
            else if (m_root == posi && alturaposi != alturanuevo) {
                CBinNode* ultra = new CBinNode(m_root->value + nuevo->value);
                ultra->nodes[0] = posi;
                ultra->nodes[1] = nuevo;
                m_root = ultra;
                posi = nuevo;
            }
            else if (posi != m_root) {
                CBinNode* mini = new CBinNode(posi->value + nuevo->value);
                mini->nodes[0] = posi;
                mini->nodes[1] = nuevo;
                m_root->nodes[1] = mini;
                m_root->value = mini->value + m_root->nodes[0]->value;
                posi = m_root;
            }
        }

        rep.clear();
        return true;
    }
    return false;
}

void CBinTree::printLevelOrder(CBinNode* root)
{
    int h = height(root);
    int i;
    for (i = 1; i <= h; i++)
    {
        cout << i << ": ";
        printCurrentLevel(root, i);
        cout << endl;
    }
}

void CBinTree::printCurrentLevel(CBinNode* root, int level)
{
    if (root == NULL)
        return;
    if (level == 1)
        cout << root->value << " ";
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

////////////////////////////////////////////////////////////////////////////////////////////////////////

void inst(CBinTree* t, int* ini, int* fin) {
    mt.lock();
    for (; ini < fin; ini++) {
        t->Insert(*ini);
    }

    mt.unlock();
}



int main()
{
    CBinTree t;
    int Leafs[128] = { 94,38,69,61,46,31,85,23,34,17,54,22,75,100,97,62,58,47,34,3,98,57,66,67,99,17,69,46,14,36,96,83,8,97,53,58,33,94,79,67,4,3,21,63,7,15,89,14,63,80,94,17,62,18,32,71,15,22,75,47,21,24,86,27,39,59,7,62,84,93,93,62,55,27,50,34,94,93,14,20,6,82,49,58,2,98,74,36,71,60,63,46,71,89,56,66,37,18,37,99,79,26,93,68,67,96,48,80,51,8,27,51,53,54,12,22,98,26,60,92,25,81,24,67,74,21,30,55 };
    vector<thread> v;
    int suma = 128 / 4;
    int* ar = Leafs;
    for (int i = 0; i < 4; i++, ar+= suma) {
        v.push_back(thread(inst, &t, ar, ar + suma));
    }

    for (int i = 0; i < v.size(); i++) {
        v[i].join();
    }

    t.Print();
    

}
