#include <iostream>
#include <thread>
#include <vector>
using namespace std;


int matrix[10][10] = {
    {1, 2, 3, 3, 2, 2, 3, 2, 3, 2},
    {2, 5, 2, 3, 3, 2, 3, 2, 3, 2},
    {3, 2, 3, 2, 3, 3, 2, 3, 2, 3},
    {3, 3, 2, 9, 2, 2, 3, 3, 3, 2},
    {2, 3, 2, 2, 4, 3, 3, 3, 2, 2},
    {2, 2, 3, 2, 3, 7, 2, 3, 3, 3},
    {3, 3, 2, 3, 3, 2, 6, 3, 2, 3},
    {2, 3, 3, 3, 3, 3, 3, 8, 2, 3},
    {3, 3, 2, 3, 3, 2, 3, 2, 5, 3},
    {2, 3, 3, 3, 2, 2, 3, 3, 3, 4}
};


void levelsdiagonal(int* ini, int* diagonal, int* fin) {
    while (ini < fin) {
        if (ini != diagonal) {
            *diagonal += *ini;
            *ini = 0;
        }
        ini++;
    }
}

void diagonalsummatrix() {
    int n_threads = 10;
    vector<thread> vec;

    for (int i = 0; i < n_threads; i++) {
        int* ini = *(matrix + i);
        int* fin = *(matrix + i) + 10;
        int* diagonal = *(matrix + i) + i;
        vec.push_back(thread(levelsdiagonal, ini, diagonal, fin));
    }

    for (int i = 0; i < vec.size(); i++) {
        vec[i].join();
    }
    

}

int main() {


    diagonalsummatrix();

    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10; j++) {
            std::cout << matrix[i][j] << " ";
        }
        std::cout << std::endl;
    }
}
