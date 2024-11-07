#include <iostream>
#include <thread>
#include <vector>
using namespace std;


const int rows = 4;
const int cols = 4;

int matriz[rows][cols] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 16}
};


void transM(int a, int b) {

    int move_r = b;
    int move_d = a;

    int* down = *(matriz + a) + move_r;
    int* right = *(matriz + move_d) + b;


    while (move_r < cols && move_d < rows) {
        swap(*down, *right);
        move_r++;
        move_d++;
        down = *(matriz + a) + move_r;
        right = *(matriz + move_d) + b;
    }
}



void transpuesta() {
    vector<thread> t;
    for (int i = 0; i < 4; i++) {
        t.push_back(thread(transM, i, i));
    }

    for (int i = 0; i < 4; i++) {
        t[i].join();
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
    transpuesta();
    print();
}
