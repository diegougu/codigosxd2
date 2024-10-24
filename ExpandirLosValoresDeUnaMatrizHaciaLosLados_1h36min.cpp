#include <iostream>	
#include <thread>
#include <queue>   
#include <tuple>
using namespace std;

int m[10][10] =
{
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,1,0,0,0,0,},
    {0,2,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,3,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,4,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
};

void printm()
{
    for (int j = 0; j < 10; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            if (m[j][i] == 0)
                std::cout << "  ";
            else
                std::cout << m[j][i];
        }
        cout << "\n";
    }
    cout << "---------------------------\n";
}


void eps(int a, int b) {
    queue<pair<int, int>> q;
    int valor = m[a][b];
    q.push(make_pair(a, b));

    while (!q.empty()) {
        pair<int, int> pos = q.front();
        q.pop();

        if (m[pos.first][pos.second] == 0) {
            m[pos.first][pos.second] = valor;
        }

        if (pos.second + 1 < 10 && pos.first < 10 && m[pos.first][pos.second + 1] == 0 ) {
            q.push(make_pair(pos.first, pos.second + 1));
        }

        if (pos.second + 1 > 9 && pos.first + 1 < 10 && m[pos.first + 1][0] == 0) {
            q.push(make_pair(pos.first + 1, 0));
        }

        if (pos.second - 1 >= 0 && pos.first < 10 && m[pos.first][pos.second -1] == 0) {
            q.push(make_pair(pos.first, pos.second - 1));
        }

        if (pos.second - 1 < 0 && pos.first - 1 >= 0 && m[pos.first - 1][9] == 0) {
            q.push(make_pair(pos.first - 1, 9));
        }


    }
}


void sides() {

    thread T1(eps, 1, 5);
    thread T2(eps, 2, 1);
    thread T3(eps, 3, 7);
    thread T4(eps, 7, 4);

    T1.join();
    T2.join();
    T3.join();
    T4.join();


}



int main() {
    printm();
    sides();
    printm();
}
