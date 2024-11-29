#include <iostream>
#include <list>
using namespace std;

class CSparseMatrix;
struct obj;


struct CSNode
{
    CSNode(int _x, int _y, int _v);
    int x, y;
    int value;
};

CSNode::CSNode(int _x, int _y, int _v)
{
    x = _x; y = _y; value = _v;
}


class CSparseMatrix
{
public:
    obj operator()(int x, int y);
    CSparseMatrix(int xdim = 0, int ydim = 0);
    ~CSparseMatrix();
    bool Set(int x, int y, int value);
    int Get(int x, int y);
    void Print();
    int XDim, YDim;
    list<CSNode> smatrix;
};

CSparseMatrix::CSparseMatrix(int _xdim, int _ydim)
{
    XDim = _xdim; YDim = _ydim;
}

CSparseMatrix::~CSparseMatrix()
{
}

struct obj {
    CSparseMatrix* ox = nullptr;
    obj(CSparseMatrix* n = nullptr) : ox(n) {}
    int x;
    int y;

    obj operator=(int v) {
        ox->Set(x, y, v);
        return *this;
    }

    operator int() {
        return ox->Get(x, y);
    }

};



bool CSparseMatrix::Set(int x, int y, int value)
{
    if (x >= XDim || y >= YDim) {
        return false;
    }
    else if (smatrix.empty() && value != 0) {
        CSNode* temp = new CSNode(x, y, value);
        smatrix.push_back(*temp);
    }
    else {
        auto ite = smatrix.begin();
        for (; ite != smatrix.end() && (ite->x != x || ite->y != y); ite++);

        if (ite != smatrix.end()) {
            if (value == 0) {
                smatrix.erase(ite);
            }
            else {
                ite->value = value;
            }
        }
        else {
            if (value == 0) {
                return false;
            }
            else {
                CSNode* temp = new CSNode(x, y, value);
                smatrix.push_back(*temp);
            }
        }
    }
}

int CSparseMatrix::Get(int x, int y)
{
    if (x >= XDim || y >= YDim) {
        return 0;
    }
    else {
        auto ite = smatrix.begin();
        for (; ite != smatrix.end() && (ite->x != x || ite->y != y); ite++);
        
        if (ite != smatrix.end()) {
            return ite->value;
        }
        else {
            return 0;
        }
    }
}

obj CSparseMatrix::operator()(int x, int y) {
    obj ox(this);
    ox.x = x;
    ox.y = y;
    return ox;
 }


void CSparseMatrix::Print()
{
    cout << "\n--------------------\n";
    for (int f = 0; f < XDim; f++) {
        for (int c = 0; c < YDim; c++) {
            cout << Get(f, c) << "  ";
        } cout << endl;
    }
    cout << endl;
}

int main(void)
{
    CSparseMatrix m(5, 5);

    m.Set(0, 0, 3);
    m.Set(2, 1, 5);
    m.Set(1, 2, 1);
    m.Set(4, 3, 8);
    m.Set(0, 4, 6);
    //----------------------
    m.Set(1, 2, 7);
    m.Set(4, 3, 0);
    m.Set(0, 4, 0);
    m.Print();
    
        m(0,0) = 0;
        m(4,0) = 1;
        m(4,4) = 2;
        m(0,4) = 3;
        m.Print();
        cout << "\n 0,0 => " << m(0, 0);
        cout << "\n 3,5 => " << m(4, 1);
        cout << "\n 7,3 => " << m(1, 2);

    return 0;
}

