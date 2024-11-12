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
	node(T d, node<T>*n = nullptr, node<T>* p = nullptr) : data(d), next(n), prev(p) {}
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

		node<T>* act = tail;
		int subir = nodes_c - 1;
		bool ch = true;

		while (ch == true && act != nullptr) {
			int t = subir;
			if (t % 2 == 0) {
				t = subir / 2 - 1;
			}
			else {
				t = subir / 2;
			}

			node<T>* p = act;
			
			for (int i = subir; i > t && p != nullptr; i--) {
				p = p->prev;
			}

			if (p != nullptr && act != nullptr && comp(act->data, p->data)) {
				swap(p->data, act->data);
				act = p;
				subir = t;
			}
			else {
				ch = false;
			}
		}
	}
}

template <class T, class C>
void PriorityQueueLE<T, C>::pop() {
	C comp;
	node<T>* temp = tail;
	nodes_c--;
	if (head == nullptr) {
		return;
	}
	else if (head == tail) {
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		swap(head->data, tail->data);
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;

		node<T>* act = head;
		int bajar = 0;
		bool ch = true;
		int der = 0;
		int iz = 0;
		while (der < nodes_c && iz < nodes_c && act != nullptr && ch == true) {
			der = (bajar + 1) * 2;
			iz = (bajar + 1) * 2 - 1;

			node<T>* p = act;
			node<T>* q = act;

			for (int i = bajar ; i < der && p != nullptr; i++) {
				p = p->next;
			}

			for (int i = bajar; i < iz && p != nullptr; i++) {
				q = q->next;
			}

			if (p != nullptr && q != nullptr && comp(q->data, p->data)) {
				if (act != nullptr && comp(q->data, act->data)) {
					swap(q->data, act->data);
					bajar = iz;
					act = q;
				}
				else {
					ch = false;
				}
			}
			else if (p != nullptr && q != nullptr && comp(p->data, q->data)) {
				if (act != nullptr && comp(p->data, act->data)) {
					swap(p->data, act->data);
					bajar = der;
					act = p;
				}
				else {
					ch = false;
				}
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
