#include <iostream>
#include <queue>
#include <vector>
using namespace std;

bool nt[19][19] = { 0 };

char m[19][19] =
{
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','b','#','#','#','#','#','#',' ',' '},
    { ' ',' ',' ','#',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' '},
    { ' ',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#',' ','#',' ','#','#',' '},
    { ' ',' ','#',' ',' ','#','#',' ',' ','#','#',' ','#',' ','#',' ',' ','#',' '},
    { ' ',' ','#',' ',' ','#',' ',' ','#','#',' ',' ','#',' ','#','#',' ','#',' '},
    { ' ','#','#',' ','#','#',' ','#','#',' ',' ','#','#',' ',' ','#',' ','#',' '},
    { ' ','#',' ',' ','#',' ',' ','#','#',' ',' ','#',' ',' ',' ','#',' ','#',' '},
    { ' ','#',' ',' ','#','#',' ',' ','#',' ','#','#',' ','#','#','#',' ','#',' '},
    { ' ','#','#',' ',' ','#',' ',' ','#',' ','#',' ',' ','#',' ',' ',' ','#',' '},
    { ' ',' ','#','#',' ','#','#',' ','#',' ','#',' ',' ','#',' ',' ','#','#',' '},
    { ' ',' ',' ','#','#','#','#','#','#',' ','#','#','#','#','#','#','#',' ',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ','#',' ','#','#',' ',' ',' ',' ',' ',' ',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ','#','a','#',' ',' ',' ',' ',' ',' ',' ',' '},
    { ' ',' ','#','#','#','#',' ','#','#','#','#','#',' ',' ',' ',' ',' ',' ',' '},
    { ' ','#','#',' ',' ','#','#','#',' ','#',' ','#','#','#',' ',' ',' ',' ',' '},
    { ' ',' ','#',' ',' ',' ','#',' ',' ','#',' ',' ',' ','#','#',' ',' ',' ',' '},
    { ' ',' ','#',' ',' ',' ',' ',' ',' ','#','#',' ',' ',' ','#','#',' ',' ',' '},
    { ' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','#',' ',' ',' ',' ',' ',' ',' ',' '}
};



void printm()
{
    for (int j = 0; j < 19; j++)
    {
        for (int i = 0; i < 19; i++)
            std::cout << m[j][i] << " ";
        std::cout << "\n";
    }
}


void search() {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> min;
    min.push({ 13, 9 });
    nt[13][9] = true;
    while (!min.empty()) {
        pair<int, int> pos = min.top();
        min.pop();

        if (m[pos.first][pos.second] == 'b') {
            return;
        }

        vector<pair<int, int>> moverse;
        moverse.push_back(make_pair(pos.first + 1, pos.second));
        moverse.push_back(make_pair(pos.first - 1, pos.second));
        moverse.push_back(make_pair(pos.first, pos.second + 1));
        moverse.push_back(make_pair(pos.first, pos.second - 1));


        for (int i = 0; i < moverse.size(); i++) {
            int x = moverse[i].first;
            int y = moverse[i].second;

            if (x >= 0 && x < 19 && y >= 0 && y < 19 && !nt[x][y]) {
                if (m[x][y] == '#' || m[x][y] == 'b') {
                    nt[x][y] = true;          
                    min.push({ x, y });       
                }
            }
        }

        if (m[pos.first][pos.second] == '#') {
            m[pos.first][pos.second] = '*';
        }

    }

}

int main()
{
    printm();
    search();
    printm();
}
