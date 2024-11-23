#include <iostream>
#include <thread>
#include <algorithm>   
#include <vector>

using namespace  std;

void ordenar2(int* ini, int* fin) {
    std::sort(ini, fin);
}


void ordenar(int* ar, int rows, int cols, int t) {
    vector<thread> vec;
    int* id = ar;
    int suma = (rows * cols) / t;
    while (t > 0) {
        for (int i = 0; i < t; i++, ar = ar + suma) {
            if (i == t - 1) {
                vec.push_back(thread(ordenar2, ar, id + rows * cols));
            }
            else {
                vec.push_back(thread(ordenar2, ar, ar + suma));
            }
        }

        for (int i = 0; i < vec.size(); i++) {
            vec[i].join();
        }

        vec.clear();
        ar = id;
        t = t / 2;

        if (t != 0) {
            suma = (rows * cols) / t;
        }
    }
}


int main() {
    const int rows = 5;
    const int cols = 5;

    int matrix[rows][cols] = {
        {5, 12, 7, 3, 9},
        {15, 8, 21, 4, 11},
        {6, 14, 2, 10, 18},
        {20, 1, 13, 19, 16},
        {17, 22, 25, 23, 24}
    };

    std::cout << "Matriz 5x5 desordenada:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

    ordenar(*matrix, rows, cols, 3);

    std::cout << "Matriz 5x5 desordenada:" << std::endl;
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            std::cout << matrix[i][j] << "\t";
        }
        std::cout << std::endl;
    }

}
