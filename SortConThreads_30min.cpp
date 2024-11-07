#include <iostream>
#include <thread>
#include <algorithm>
#include <vector>
using namespace std;


const static int tam = 70;
int arr[tam] = {
    34, 7, 23, 32, 5, 62, 45, 12, 18, 39,
    28, 54, 76, 1, 88, 56, 91, 0, 67, 73,
    21, 99, 48, 26, 36, 82, 19, 58, 90, 11,
    14, 77, 84, 64, 13, 50, 30, 92, 43, 71,
    25, 8, 96, 15, 57, 22, 70, 86, 33, 40,
    3, 65, 60, 41, 74, 17, 97, 42, 20, 59,
    27, 75, 49, 66, 83, 2, 46, 87, 38, 4
};

void print() {
    for (int i = 0; i < tam; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}


void ordenar(int* ini, int* fin) {
    sort(ini, fin);
}

void OrdenarThreading() {
    int n = thread::hardware_concurrency();
    int* pos = arr;
    int suma = tam / n;
    vector<thread> t;
    while (n > 0) {

        for (int i = 0; i < n; i++) {

            if (i != n) {
                t.push_back(thread(ordenar, pos, pos + suma));
                pos = pos + n;
            }
            else {
                t.push_back(thread(ordenar, pos, arr + tam - 1));
            }
        }


        for (int i = 0; i < t.size(); i++) {
            t[i].join();
        }

        pos = arr;

        n = n / 2;

        if (n != 0) {
            suma = tam / n;
        }

        t.clear();

        print();

    }
}


int main() {

    print();

    OrdenarThreading();

    print();

}
