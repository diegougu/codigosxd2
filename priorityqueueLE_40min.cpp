#include <iostream>
using namespace std;

template <class T>
struct ASC {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct DESC {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct node {
	T data;
	node<T>* next = nullptr;
	node<T>* prev = nullptr;
	node(T d, node<T>* n = nullptr, node<T>* p = nullptr) : data(d), next(n), prev(p) {}
};

template <class T, class C>
class PriorityQueueLE {
private:
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
	int nodes_c = 0;
public:
	void push(T v);
	void pop();
	void print();
};

template <class T, class C>
void PriorityQueueLE<T, C>::push(T v) {
	node<T>* newnode = new node<T>(v);
	C comp; 
	nodes_c++;
	if (head == nullptr) {
		head = newnode;
		tail = newnode;
	}
	else {
		tail->next = newnode;
		newnode->prev = tail;
		tail = tail->next;
		int pos = nodes_c - 1;
		node<T>* pos_node = tail;
		bool ch = true;

		while (pos_node != nullptr && ch == true) {
			int dif = 0;
			if (pos % 2 == 0) {
				dif = pos / 2 - 1;
			}
			else {
				dif = pos / 2;
			}

			node<T>* c_node = pos_node;
			for (int k = dif; k < pos; k++) {
				c_node = c_node->prev;
			}

			if (c_node != nullptr && pos_node != nullptr && comp(pos_node->data, c_node->data)) {
				swap(pos_node->data, c_node->data);
				pos_node = c_node;
				pos = dif;
			}
			else {
				ch = false;
			}
		}
	}
}

template <class T, class C>
void PriorityQueueLE<T, C>::pop() {
	node<T>* temp = tail;
	if (head == nullptr) {
		return;
	}
	else if (head == tail) {
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		C comp;
		swap(tail->data, head->data);
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
		int pos = 0;
		node<T>* pos_node = head;
		bool ch = true;
		while (pos_node != nullptr && pos < nodes_c && ch == true) {
			int izquierda = (pos + 1) * 2 - 1;
			int derecha = (pos + 1) * 2;

			node<T>* iz_node = pos_node;
			node<T>* der_node = pos_node;


			for (int k = pos; iz_node != nullptr && k < izquierda; k++) {
				iz_node = iz_node->next;
			}

			for (int k = pos; der_node != nullptr && k < derecha; k++) {
				der_node = der_node->next;
			}

			if (iz_node != nullptr && der_node != nullptr && comp(iz_node->data, der_node->data)) {
				if (comp(iz_node->data, pos_node->data)) {
					swap(iz_node->data, pos_node->data);
					pos = izquierda;
					pos_node = iz_node;
				}
				else {
					ch = false;
				}
			}
			else if (iz_node != nullptr && der_node != nullptr && comp(der_node->data, iz_node->data)) {
				if (comp(der_node->data, pos_node->data)) {
					swap(der_node->data, pos_node->data);
					pos = derecha;
					pos_node = der_node;
				}
				else {
					ch = false;
				}
			}
			else {
				ch = false;
			}

		}

	}
}


template <class T, class C>
void PriorityQueueLE<T, C>::print() {
	for (node<T>* t = head; t; t = t->next) {
		cout << t->data << " ";
	}
	cout << endl;
}

int main() {
	PriorityQueueLE<int, ASC<int>> a;
	a.push(70);
	a.print();
	a.push(100);
	a.print();
	a.push(90);
	a.print();
	a.push(10);
	a.print();
	a.push(120);
	a.print();
	a.push(110);
	a.print();
	a.push(94);
	a.print();
	a.push(30);
	a.print();
	a.push(200);
	a.print();
	a.push(180);
	a.print();
	a.push(67);
	a.print();

	a.pop();
	a.print();
	a.pop();
	a.print();
	a.pop();
	a.print();
}
