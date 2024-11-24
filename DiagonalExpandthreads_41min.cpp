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
            std::cout << m[j][i] << " ";
        }
        std::cout << "\n";
    }
    std::cout << "---------------------------\n";
}

void diagonal_expand(int x, int y) {

    queue<pair<int, int>> exp;

    exp.push(make_pair(x, y));

    while (!exp.empty()) {
        pair<int, int> act = exp.front();
        exp.pop();
        int* actptr = *(m + act.first) + act.second;
        if (act.first - 1 >= 0 && act.second - 1 >= 0 && *(*(m + act.first - 1) + act.second - 1) == 0) {
            int* pushptr = *(m + act.first - 1) + act.second - 1;

            if (*pushptr == 0) {
                *pushptr = *actptr + 1;
                exp.push(make_pair(act.first - 1, act.second - 1));
            }
        }

        if (act.first + 1 < 10 && act.second + 1 < 10 && *(*(m + act.first + 1) + act.second + 1) == 0) {
            int* pushptr = *(m + act.first + 1) + act.second + 1;
            if (*pushptr == 0) {
                *pushptr = *actptr + 1;
                exp.push(make_pair(act.first + 1, act.second + 1));
            }
        }
    }
}


void levels(){
    vector<thread> t;
    t.push_back(thread(diagonal_expand, 1, 5));
    t.push_back(thread(diagonal_expand, 2, 1));
    t.push_back(thread(diagonal_expand, 3, 7));
    t.push_back(thread(diagonal_expand, 7, 4));
    

    for (int i = 0; i < t.size(); i++) {
        t[i].join();
    }
}

int main()
{
    printm();
    levels();
    printm();
}
