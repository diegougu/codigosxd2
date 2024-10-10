#include <iostream>
using namespace std;
class XVector
{
public:
    XVector(int size_map, int size_vec);
    ~XVector();
    void push_back(int v);
    void push_front(int v);
    int& operator[](int v);
    void Expand(int newsize_map);
    int** fin_map;
    int* fin_arr = nullptr;
    int** map;
    int size_map, size_vec;
    int elementos = 0;
};

XVector::XVector(int sm, int sv)
{
    size_map = sm;
    size_vec = sv;
    map = new int* [size_map];
    fin_map = map;
    fin_arr = nullptr;
    for (int i = 0; i < size_map; i++) {
        map[i] = nullptr;
    }
}

XVector::~XVector()
{}

void XVector::Expand(int newsize_map) {
    int** newmap = new int* [newsize_map];
    for (int i = 0; i < size_map; i++) {
        newmap[i] = map[i];
    }
    fin_map = newmap + size_map - 1;
    int** temp = map;
    map = newmap;
    delete[]temp;
}

void XVector::push_back(int v) {
    if (fin_arr == nullptr) {
        *fin_map = new int[size_vec];
        fin_arr = *fin_map;
        *fin_arr = v;
        elementos++;
    }
    else if (fin_arr == *fin_map + size_vec - 1) {
        if (fin_map == map + size_map - 1) {
            Expand(size_map * 2);
        }
        fin_map++;
        *fin_map = new int[size_vec];
        fin_arr = *fin_map;
        *fin_arr = v;
        elementos++;
    }
    else {
        fin_arr++;
        *fin_arr = v;
        elementos++;
    }
}

void XVector::push_front(int v) {
    if (fin_arr == nullptr) {
        *fin_map = new int[size_vec];
        fin_arr = *fin_map;
        *fin_arr = v;
        elementos++;
    }
    else {
        int** i = fin_map;
        int* j = fin_arr;
        if (j == *i + size_vec - 1) {
            if (fin_map == map + size_map - 1) {
                Expand(size_map * 2);
                i = fin_map;
            }
            fin_map++;
            *fin_map = new int[size_vec];
            fin_arr = *fin_map;
            *fin_arr = *j;
        }
        else {
            fin_arr++;
            *fin_arr = *j;
        }

        while (i >= map) {
            if (j == *i && i == map) {
                *j = v;
                elementos++;
                return;
            }
            else if (j == *i && i != map) {
                i--;
                *j = *(*i + size_vec - 1);
                j = *i + size_vec - 1;
            }
            else {
                *j = *(j - 1);
                j--;
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
    int pos_arr = v % size_vec;
    int** pm = map + pos_map;
    int* pa = *pm + pos_arr;
    return *pa;
}

void print(XVector* p)
{ //no modificar esta función
    for (int i = 0; i < p->size_vec; i++)
        std::cout << (*p)[i] << " ";
    std::cout << "\n";
}

int main()
{
    //no modificar esta función main
    XVector v(4, 3);
    v.push_back(3); v.push_back(8); v.push_back(1);
    v.push_back(4); v.push_back(9); v.push_back(6);
    v.push_back(7);
    print(&v);
    v.push_front(5); v.push_front(2);
    print(&v);
    v.push_front(11); v.push_front(17);
    v.push_back(22);
    print(&v);
    v.push_front(33); v.push_back(77);
    print(&v);
}
