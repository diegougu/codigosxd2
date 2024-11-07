#include <iostream>
#include <thread>
#include <vector>
#include <deque>
#include <mutex>

using namespace std;

mutex mt;
deque<int> s;


const int rows = 4;
const int cols = 4;

int matriz[rows][cols] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};


void multM(int* c, int* r) {

    mt.lock();

    int move_c = 0;
    int move_r = rows;
    int suma = 0;

    while (move_c < cols) {
        suma = suma + (*r * *c);
        move_c++;
        c++;
        r = r + move_r;
    }


    s.push_back(suma);

    mt.unlock();
}

void multiplicar() {
    vector<thread> t;

    for (int i = 0; i < rows; i++) {
        int* c = *(matriz + i) + 0;
        for (int j = 0; j < cols; j++) {
            int* r = *(matriz + 0) + j;
            t.push_back(thread(multM, c, r));
        }
    }

    for (int i = 0; i < t.size(); i++) {
        t[i].join();
    }

    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            matriz[i][j] = s.front();
            s.pop_front();
        }
    }
    
}


void print() {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            cout << matriz[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}


int main() {
    print();
    multiplicar();
    print();
}
