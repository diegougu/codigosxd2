#include <iostream>
#include <thread>
#include <queue>
#include <mutex>

using namespace std;

mutex mt[10][10];
bool visited[10][10] = { 0 };

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
    queue<pair<int, int>> rec;
    visited[x][y] = true;
    rec.push(make_pair(x, y));
    
    while (!rec.empty()) {
        pair<int, int> current = rec.front();
        rec.pop();
        int valor = m[current.first][current.second];
        vector<pair<int, int>> newpos;
        newpos.push_back(make_pair(current.first + 1, current.second));
        newpos.push_back(make_pair(current.first - 1, current.second));
        newpos.push_back(make_pair(current.first, current.second + 1));
        newpos.push_back(make_pair(current.first, current.second - 1));

        for (int i = 0; i < newpos.size(); i++) {
            int nx = newpos[i].first;
            int ny = newpos[i].second;

            if (nx >= 0 && nx < 10 && ny >= 0 && ny < 10) {
                mt[nx][ny].lock();
                if (m[nx][ny] == 0 && visited[nx][ny] == false) {
                    m[nx][ny] = valor + 1;
                    visited[nx][ny] = true;
                    rec.push(make_pair(nx, ny));
                }
                mt[nx][ny].unlock();
            }
        }

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
