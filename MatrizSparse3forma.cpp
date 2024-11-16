#include <iostream>
using namespace std;

template <class T>
class SparseMatrix;

template <class T>
struct objx;

template <class T>
struct node {
	T valor;
	int x;
	int y;
	node<T>* right = nullptr;
	node<T>* bottom = nullptr;
	node(T v, int _x, int _y, node<T>* r = nullptr, node<T>* b = nullptr) : valor(v), x(_x), y(_y), right(r), bottom(b) {}
};

template <class T>
class SparseMatrix {
public:
	int tamx;
	int tamy;
	node<T>** x_x;
	node<T>** y_y;
	SparseMatrix(int tx, int ty) : tamx(tx), tamy(ty) {
		x_x = new node<T>*[tamx];
		y_y = new node<T>*[tamy];
		for (int i = 0; i < tamx; i++) {
			x_x[i] = nullptr;
		}

		for (int i = 0; i < tamy; i++) {
			y_y[i] = nullptr;
		}
	}
	objx<T> operator()(int x, int y);
	void set(int x, int y, T v);
	T get(int x, int y);
	void print();
private:
	bool find_bottom(node<T>**& pb, int x, int y);
	bool find_right(node<T>**& pr, int x, int y);
};

template<class T>
struct objx {
	SparseMatrix<T>* m = nullptr;
	objx(SparseMatrix<T>* _m = nullptr) : m(_m) {}
	int x;
	int y;
	objx<T> operator=(T v) {
		m->set(x, y, v);
		return *this;
	}

	operator T() {
		return m->get(x, y);
	}

	objx<T> operator=(objx<T>& ox) {
		m->set(x, y, ox.m->get(ox.x, ox.y));
		return *this;
	}

};



template <class T>
bool SparseMatrix<T>::find_right(node<T>**& pr, int x, int y) {
	while (*pr && ((*pr)->y < y || (*pr)->x < x)) {
		pr = &((*pr)->right);
	}
	return *pr && (*pr)->y == y;
}


template <class T>
bool SparseMatrix<T>::find_bottom(node<T>**& pb, int x, int y) {
	while (*pb && ((*pb)->y < y || (*pb)->x < x)) {
		pb = &((*pb)->bottom);
	}
	return *pb && (*pb)->x == x;
}

template <class T>
void SparseMatrix<T>::set(int x, int y, T v) {
	if (x >= tamx || y >= tamy) {
		return;
	}
	else {
		node<T>** pb = &x_x[x];
		node<T>** pr = &y_y[y];

		bool fb = find_bottom(pb, x, y);
		bool fr = find_right(pr, x, y);

		if (fb && fr) {
			if (v == 0) {
				node<T>* temp = *pb;
				*pb = temp->bottom;
				*pr = temp->right;
				delete temp;
			}
			else {
				(*pb)->valor = v;
			}
		}
		else {
			if (v == 0) {
				return;
			}
			else {
				node<T>* newNode = new node<T>(v, x, y);

				newNode->right = *pr;
				*pr = newNode;

				newNode->bottom = *pb;
				*pb = newNode;
			}
		}
	}
}


template <class T>
T SparseMatrix<T>::get(int x, int y) {
	if (x >= tamx || x >= tamy) {
		static T dummy = 0;
		return dummy;
	}
	else {
		node<T>** pb = &x_x[x];
		node<T>** pr = &y_y[y];
		if (find_bottom(pb, x, y) && find_right(pr, x, y)) {
			return (*pb)->valor;
		}
		else {
			static T dummy = 0;
			return dummy;
		}

	}
}

template <class T>
void SparseMatrix<T>::print() {
	cout << "eje x" << endl;
	for (int i = 0; i < tamx; i++) {
		for (node<T>** p = &x_x[i]; *p; p = &((*p)->bottom)) {
			cout << (*p)->valor << "( " << (*p)->x << " " << (*p)->y << " ) ";
		}
	}
	cout << endl;
	cout << "eje y" << endl;
	for (int i = 0; i < tamy; i++) {
		for (node<T>** p = &y_y[i]; *p; p = &((*p)->right)) {
			cout << (*p)->valor << "( " << (*p)->x << " " << (*p)->y << " ) ";
		}
	}
}

template <class T >
objx<T> SparseMatrix<T>::operator()(int x, int y) {
	objx<T> ox(this);
	ox.x = x;
	ox.y = y;
	return ox;
}


int main() {
	SparseMatrix<int> m(4, 4);
	objx<int> val1 = m(0, 1);
	objx<int> val2 = m(0, 2);
	objx<int> val3 = m(0, 0);
	objx<int> val4 = m(1, 1);
	objx<int> val5 = m(1, 3);
	objx<int> val6 = m(1, 2);
	objx<int> val7 = m(3, 1);
	objx<int> val8 = m(3, 2);

	cout << (int)val1 << endl;
	cout << (int)val2 << endl;
	cout << (int)val3 << endl;
	cout << (int)val4 << endl;
	cout << (int)val5 << endl;
	cout << (int)val6 << endl;
	cout << (int)val7 << endl;
	cout << (int)val8 << endl;

	cout << "------------------------------" << endl;

	m(0, 1) = 10;
	m(0, 2) = 20;
	m(0, 0) = 30;
	m(1, 1) = 40;
	m(1, 3) = 50;
	m(1, 2) = 60;
	m(3, 1) = 70;
	m(3, 2) = 80;

	cout << (int)m(0, 1) << endl;
	cout << (int)m(0, 2) << endl;
	cout << (int)m(0, 0) << endl;
	cout << (int)m(1, 1) << endl;
	cout << (int)m(1, 3) << endl;
	cout << (int)m(1, 2) << endl;
	cout << (int)m(3, 1) << endl;
	cout << (int)m(3, 2) << endl;


	m(0, 1) = 900;
	m(0, 2) = 1000;
	m(0, 0) = 1100;
	cout << "------------------------------" << endl;
	cout << (int)m(0, 1) << endl;
	cout << (int)m(0, 2) << endl;
	cout << (int)m(0, 0) << endl;

	m(0, 1) = m(3, 2);
	cout << "------------------------------" << endl;
	cout << (int)m(0, 1) << endl;

	m.print();

}
