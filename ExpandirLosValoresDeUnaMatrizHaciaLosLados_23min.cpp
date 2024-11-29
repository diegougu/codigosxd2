#include <iostream>
#include <queue>
#include <vector>
#include <thread>
#include <mutex>

using namespace std;

mutex mt[10][10];
bool visited[10][10] = { false };

int m[10][10] =
{
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,10,0,0,0,0,},
    {0,30,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,5,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,0,0,0,0,0,0,},
    {0,0,0,0,50,0,0,0,0,0,},
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

void expandizder(int x, int y) {
    queue<pair<int, int>> pos;
    pos.push(make_pair(x, y));
    visited[x][y] = true;

    while (!pos.empty()) {
        pair<int, int> current = pos.front();
        pos.pop();
        int valor = m[current.first][current.second];
        vector<pair<int, int>> newpos;
        if (current.second == 9) {
            newpos.push_back(make_pair(current.first + 1, 0));
        }
        else {
            newpos.push_back(make_pair(current.first, current.second + 1));
        }
        if (current.second == 0) {
            newpos.push_back(make_pair(current.first - 1, 9));
        }
        else {
            newpos.push_back(make_pair(current.first, current.second - 1));
        }

        for (int i = 0; i < newpos.size(); i++) {
            int xm = newpos[i].first;
            int ym = newpos[i].second;

            if (xm >= 0 && xm < 10 && ym >= 0 && ym < 10) {
                mt[xm][ym].lock();
                if (m[xm][ym] == 0 && visited[xm][ym] == false) {
                    int* pointer = *m + (xm + ym);
                    int* pointeract = *m + (current.first + current.second);
                    if (pointer < pointeract) {
                        m[xm][ym] = valor - 1;
                    }
                    else {
                        m[xm][ym] = valor + 1;
                    }
                    visited[xm][ym] = true;
                    pos.push(make_pair(xm, ym));
                }
                mt[xm][ym].unlock();
            }
        }
    }
}


void levels()
{
    vector<thread> vec;
    vec.push_back(thread(expandizder, 1, 5));
    vec.push_back(thread(expandizder, 2, 1));
    vec.push_back(thread(expandizder, 3, 7));
    vec.push_back(thread(expandizder, 7, 4));

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
