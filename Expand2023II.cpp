#include <iostream>
#include <thread>
#include <mutex>
#include <queue>

using namespace std;

mutex mt[10][10];

int m[10][10] =
{
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,1,0,0,0,0,},
    {0,2,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,1,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,2,0,0,0,0,0,},
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
                std::cout << m[j][i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "---------------------------\n";
}


void expand(int x, int y) {
    queue<pair<int, int>> pos;
    pos.push(make_pair(x, y));
    while (!pos.empty()) {
        pair<int, int> act = pos.front();

        if (act.first - 1 >= 0 && act.second >= 0 && m[act.first - 1][act.second] == 0) {
            pos.push(make_pair(act.first - 1, act.second));
            mt[act.first - 1][act.second].lock();
            int valor = m[act.first][act.second];
            m[act.first - 1][act.second] = valor + 1;
            mt[act.first - 1][act.second].unlock();
        }

        if (act.first >= 0 && act.second - 1 >= 0 && m[act.first][act.second - 1] == 0) {
            pos.push(make_pair(act.first, act.second - 1));
            mt[act.first][act.second - 1].lock();
            int valor = m[act.first][act.second];
            m[act.first][act.second - 1] = valor + 1;
            mt[act.first][act.second - 1].unlock();
        }

        if (act.first >= 0 && act.second + 1 <= 9 && m[act.first][act.second + 1] == 0) {
            pos.push(make_pair(act.first, act.second + 1));
            mt[act.first][act.second + 1].lock();
            int valor = m[act.first][act.second];
            m[act.first][act.second + 1] = valor + 1;
            mt[act.first][act.second + 1].unlock();
        }

        if (act.first + 1 <= 9 && act.second >= 0 && m[act.first + 1][act.second] == 0) {
            pos.push(make_pair(act.first + 1, act.second));
            mt[act.first + 1][act.second].lock();
            int valor = m[act.first][act.second];
            m[act.first + 1][act.second] = valor + 1;
            mt[act.first + 1][act.second].unlock();
        }
        pos.pop();
    }
}

void levels()
{
    vector<thread> vec;
    vec.push_back(thread(expand, 1, 5));
    vec.push_back(thread(expand, 2, 1));
    vec.push_back(thread(expand, 3, 7));
    vec.push_back(thread(expand, 7, 4));

    for (int i = 0; i < vec.size(); i++) {
        vec[i].join();
    }

}

int main()
{
    printm();
    levels();
    printm();
}


int main()
{
    printm();
    levels();
    printm();
}
