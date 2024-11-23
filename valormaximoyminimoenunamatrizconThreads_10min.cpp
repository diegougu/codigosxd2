#include <iostream>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

int arr_maximo_minimo[2] = {INT_MAX, INT_MIN};

mutex mt;

void mn(int* ini, int* fin) {
    mt.lock();
    while (ini < fin) {
        if (*ini < arr_maximo_minimo[0]) {
            arr_maximo_minimo[0] = *ini;
        }

        if (*ini > arr_maximo_minimo[1]) {
            arr_maximo_minimo[1] = *ini;
        }
        ini++;
    }
    mt.unlock();
}

void maximoYminimo(int* ar, int n, int m, int t) {
    int suma = (m * n) / t;
    int* temp = ar;
    vector<thread> vec;
    for (int i = 0; i < t; i++, ar += suma) {
        if (i == t - 1) {
            vec.push_back(thread(mn, ar, temp + (m * n)));
        }
        else {
            vec.push_back(thread(mn, ar, ar + suma));
        }
    }

    for (int i = 0; i < vec.size(); i++) {
        vec[i].join();
    }
}

int main() {
    const int N = 6;  // Número de filas
    const int M = 4;  // Número de columnas
    const int THREAD_COUNT = 2; // Número de threads
    int matrix[N][M] = {
        {5, 8, 1, 7},
        {9, 3, 4, 2},
        {6, 12, 15, 10},
        {11, 14, 18, 13},
        {2, 7, 6, 8},
        {9, 10, 4, 1}
    };


    cout << "el minimo es: " << arr_maximo_minimo[0] << endl;
    cout << "el maximo es: " << arr_maximo_minimo[1] << endl;

    maximoYminimo(*matrix, N, M, 10);

    cout << "el minimo es: " << arr_maximo_minimo[0] << endl;
    cout << "el maximo es: " << arr_maximo_minimo[1] << endl;
}
