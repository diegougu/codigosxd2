#include <iostream>
#include <functional>
#include <vector>
using namespace std;

template <class S, class T>
class hashtable {
private:
    int size;
    S** arr;
public:
    hashtable(int s) : size(s) {
        arr = new S*[size];
        for (int i = 0; i < size; i++) {
            arr[i] = nullptr; 
        }
    }

    void insert(T x) {
        int pos = std::hash<T>{}(x) % size; 
        if (arr[pos] == nullptr) {
            arr[pos] = new S; 
        }
        arr[pos]->push_back(x); 
    }

    void print() {
        for (int i = 0; i < size; i++) {
            cout << "Bucket " << i << ": ";
            if (arr[i] != nullptr) {
                for (const T& val : *arr[i]) {
                    cout << val << " ";
                }
            }
            cout << endl;
        }
    }

};

int main() {
    hashtable<vector<int>, int> t(7);
    for (int i = 0; i < 10; i++) {
        t.insert(i); 
    }
    t.print(); 
    return 0;
}
