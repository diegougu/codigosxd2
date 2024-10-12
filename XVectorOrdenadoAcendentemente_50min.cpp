#include <iostream>
using namespace std;
class XVector
{
public:
    XVector(int size_map, int size_vec);
    ~XVector();
    void add(int v);
    void del(int v);
    void print();
    int& operator[](int v);
    bool find(int**& pos_map, int*& pos_vec, int v);
    void Expand(int newsize_map);
    int** map;
    int size_map, size_vec;
    int** fin_map;
    int* fin_vec = nullptr;
    int elementos = 0;
    int arrays = 0;
};

XVector::XVector(int sm, int sv)
{
    size_map = sm;
    size_vec = sv;
    map = new int* [size_map];
    for (int i = 0; i < size_map; i++) {
        map[i] = nullptr;
    }
    fin_map = map;
    fin_vec = nullptr;
}

XVector::~XVector()
{}

bool XVector::find(int**& pos_map, int*& pos_vec, int v) {
    while (pos_map <= fin_map) {
        while (pos_vec <= *pos_map + size_vec - 1) {
            if (*pos_vec >= v) {
                return true;
            }
            pos_vec++;
        }
        pos_map++;
        pos_vec = *pos_map;
    }
    return false;
}


void XVector::Expand(int newsize_map) {
    int** newmap = new int* [newsize_map];
    for (int i = 0; i < size_map; i++) {
        newmap[i] = map[i];
    }
    fin_map = newmap + arrays - 1;
    int** temp = map;
    map = newmap;
    size_map = newsize_map;
    delete[]temp;
}


void XVector::add(int v) {
    if (fin_vec == nullptr) {
        *fin_map = new int[size_vec];
        fin_vec = *fin_map;
        *fin_vec = v;
        elementos++;
        arrays++;
    }
    else if (v >= *fin_vec && fin_vec != *fin_map + size_vec - 1) {
        fin_vec++;
        *fin_vec = v;
        elementos++;
    }
    else if (v >= *fin_vec && fin_vec == *fin_map + size_vec - 1) {
        if (fin_map == map + size_map - 1) {
            Expand(size_map * 2);
        }
        fin_map++;
        *fin_map = new int[size_vec];
        fin_vec = *fin_map;
        *fin_vec = v;
        elementos++;
        arrays++;
    }
    else {
        if (fin_map == map + size_map - 1) {
            Expand(size_map * 2);
        }

        int** pos_map = map;
        int* pos_vec = *pos_map;
        if (find(pos_map, pos_vec, v)) {

            int** i = fin_map;
            int* j = fin_vec;

            if (fin_vec == *fin_map + size_vec - 1) {
                fin_map++;
                *fin_map = new int[size_vec];
                fin_vec = *fin_map;
                *fin_vec = *j;
                arrays++;
            }
            else {
                fin_vec++;
                *fin_vec = *j;
            }

            while (j != pos_vec) {
                if (j == *i) {
                    i--;
                    *j = *(*i + size_vec - 1);
                    j = *i + size_vec - 1;
                }
                else {
                    *j = *(j - 1);
                    j--;
                }
            }

            *pos_vec = v;
            elementos++;
        }
    }
}



void XVector::del(int v) {
    if (fin_vec == nullptr) {
        return;
    }
    else if (fin_map == map && fin_vec == *map && *fin_vec == v) {
        int* temp = *fin_map;
        fin_vec = nullptr;
        elementos--;
        arrays--;
        delete[] temp;
        fin_map = map;
    }
    else if (*fin_vec == v && fin_vec != *fin_map) {
        fin_vec--;
        elementos--;
    }
    else if (*fin_vec == v && fin_vec == *fin_map) {
        if (arrays < size_map / 2) {
            Expand(size_map / 2);
        }
        int* temp = *fin_map;
        fin_map--;
        fin_vec = *fin_map + size_vec - 1;
        elementos--;
        arrays--;
        delete[]temp;
    }
    else {
        if (arrays < size_map / 2) {
            Expand(size_map / 2);
        }


        int** pos_map = map;
        int* pos_vec = *pos_map;

        if (find(pos_map, pos_vec, v) && *pos_vec == v) {
            while (pos_map <= fin_map && pos_vec != fin_vec) {
                if (pos_vec == *pos_map + size_vec - 1) {
                    pos_map++;
                    *pos_vec = *(*pos_map);
                    pos_vec = *pos_map;
                }
                else {
                    *pos_vec = *(pos_vec + 1);
                    pos_vec++;
                }
            }


            if (fin_vec != *fin_map) {
                fin_vec--;
                elementos--;
            }
            else {
                int* temp = *fin_map;
                fin_map--;
                fin_vec = *fin_map + size_vec - 1;
                elementos--;
                arrays--;
            }
        }
    }
}

int& XVector::operator[](int v) {
    if (v >= elementos) {
        static int random = 0;
        return random;
    }
    int pos_map = v / size_vec;
    int pos_vec = v % size_vec;

    int** pa = map + pos_map;
    int* p = *pa + pos_vec;
    return *p;
}

void XVector::print() {
    for (int** i = map; i <= fin_map; i++) {
        for (int* j = *i; j <= *i + size_vec - 1; j++) {
            cout << *j << " ";
            if (j == fin_vec) {
                cout << endl;
                return;
            }
        }
    }
}

void print(XVector* p)
{ //no modificar esta función
    for (int i = 0; i < p->elementos; i++)
        std::cout << (*p)[i] << " ";
    std::cout << "\n";
}

int main()
{
    XVector v(4, 3);

    v.add(10);
    v.add(11);
    v.add(12);
    v.add(1);
    v.add(3);
    v.add(4);
    v.add(5);
    v.add(7);
    v.add(9);
    v.add(16);
    v.add(8);
    v.add(6);
    v.add(13);
    v.add(2);

    v.print();

    v.del(1);
    v.del(16);
    v.del(13);
    v.del(12);
    v.del(11);
    v.del(4);
    v.del(7);
    v.print();

}
