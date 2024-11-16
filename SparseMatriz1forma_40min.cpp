#include <iostream>
using namespace std;

template <class T>
struct node {
	T valor;
	int x; 
	int y;
	node<T>* next = nullptr;
	node(T v, int _x, int _y, node<T>* n = nullptr) : valor(v), x(_x), y(_y), next(n) {}
};

template <class T>
class SparseMatriz {
private:
	node<T>* head = nullptr;
	bool find(node<T>**& p, int x, int y);
public:
	int xx;
	int yy;
	SparseMatriz(int _xx, int _yy) : xx(_xx), yy(_yy) {}
	void set(int x, int y, T v);
	T get(int x, int y);
	void print();
};


template <class T>
bool SparseMatriz<T>::find(node<T>**& p, int x, int y) {
	while (*p && ((*p)->x + (*p)-> y < x + y)) {
		p = &((*p)->next);
	}
	return *p && (*p)->x == x && (*p)->y == y;
}

template <class T>
void SparseMatriz<T>::set(int x, int y, T v) {
	if (x >= xx || y >= yy) {
		return;
	}
	else {
		node<T>** p = &head;
		if (find(p, x, y)) {
			if (v == 0) {
				node<T>* temp = *p;
				*p = temp->next;
				delete temp;
			}
			else {
				(*p)->valor = v;
			}
		}
		else {
			node<T>* newnode = new node<T>(v, x, y);
			newnode->next = *p;
			*p = newnode;
		}
	}
}

template <class T>
T SparseMatriz<T>::get(int x, int y) {
	if (head == nullptr || x >= xx || y >= yy) {
		return 0;
	}
	else {
		node<T>** p = &head;
		if (!find(p, x, y)) {
			return 0;
		}
		else {
			return (*p)->valor;
		}
	}
}

template <class T>
void SparseMatriz<T>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << "( " << p->x << " " << p->y << " ) ";
	}
	cout << endl;
}

int main() {
	SparseMatriz<int> m(4, 4);
	m.set(0, 1, 10);
	m.set(2, 1, 20);
	m.set(3, 1, 30);
	m.set(0, 0, 5);
	m.set(0, 2, 15);
	m.set(0, 3, 80);
	m.set(2, 2, 90);
	m.print();

}
