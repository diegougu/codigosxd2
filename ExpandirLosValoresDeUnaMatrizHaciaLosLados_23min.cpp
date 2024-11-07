#include <iostream>	
#include <thread>
#include <queue>
#include <vector>
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


void rem(int a, int b) {
    queue<pair<int, int>> rec;
    int valor = m[a][b];
    rec.push(make_pair(a, b));

    while (!rec.empty()) {
        pair<int, int> act = rec.front();

        m[act.first][act.second] = valor;


        if (act.second + 1 < 10 && m[act.first][act.second + 1] == 0) {
            rec.push(make_pair(act.first, act.second + 1));
        }
        else if (act.second + 1 == 10 && act.first + 1 < 10 && m[act.first + 1][0] == 0) {
            rec.push(make_pair(act.first + 1, 0));
        }
        
        if (act.second - 1 >= 0 && m[act.first][act.second - 1] == 0) {
            rec.push(make_pair(act.first, act.second - 1));
        }
        else if (act.second - 1 < 0 && act.first - 1 >= 0 && m[act.first - 1][9] == 0) {
            rec.push(make_pair(act.first - 1, 9));

        }

        rec.pop();

    }
}


void sides() {
    thread T1(rem, 1, 5), T2(rem, 2, 1), T3(rem, 3, 7), T4(rem, 7, 4);
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
