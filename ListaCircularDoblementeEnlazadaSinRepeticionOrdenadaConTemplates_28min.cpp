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
	node<T>* next;
	node<T>* prev;
	node(T d, node<T>* n = nullptr, node<T>* p = nullptr) : data(d), next(n), prev(p) {}
};

template <class T, class C>
class CircularDoubleLinkedList {
private:
	node<T>* head = nullptr;
	bool find(node<T>*& pos, T v);
public:
	void add(T v);
	void del(T v);
	void print();
};

template <class T, class C>
void CircularDoubleLinkedList<T, C>::print() {
	node<T>* p = head;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}

template <class T, class C>
bool CircularDoubleLinkedList<T, C>::find(node<T>*& pos, T v) {
	C comp;
	do {
		pos = pos->next;
	} while (comp(v, pos->data) && pos->next != head);

	return pos->data == v;
}



template <class T, class C>
void CircularDoubleLinkedList<T, C>::add(T v) {
	C comp;
	if (head == nullptr) {
		node<T>* temp = new node<T>(v);
		head = temp;
		head->next = head;
		head->prev = head;
	}
	else if (!comp(v, head->data) && head->data != v) {
		node<T>* temp = new node<T>(v);
		node<T>* u = head->prev;
		temp->next = head;
		temp->prev = u;
		head->prev = temp;
		u->next = temp;
		head = temp;
	}
	else {
		node<T>* pos = head;
		if (find(pos, v)) {
			return;
		}
		node<T>* temp = new node<T>(v);
		if (pos->next == head && comp(v, pos->data)) {
			temp->next = head;
			head->prev = temp;
			pos->next = temp;
			temp->prev = pos;
		}
		else {
			node<T>* ant = pos->prev;
			temp->next = pos;
			ant->next = temp;
			temp->prev = ant;
			pos->prev = temp;
		}
	}
}


template <class T, class C>
void CircularDoubleLinkedList<T, C>::del(T v) {
	C comp;
	if (head == nullptr) {
		return;
	}
	else if (v == head->data) {
		node<T>* temp = head;
		if (head->next == head) {
			head = nullptr;
			delete temp;
		}
		else {
			node<T>* u = head->prev;
			head = head->next;
			head->prev = u;
			u->next = head;
			delete temp;
		}
	}
	else {
		node<T>* temp = head;
		if (!find(temp, v)) {
			return;
		}

		node<T>* ant = temp->prev;
		node<T>* pos = temp->next;

		pos->prev = ant;
		ant->next = pos;
		delete temp;
	}
}


int main() {
	cout << "Lista de enteros (DESC):" << endl;
	CircularDoubleLinkedList<int, ASC<int>> listaIntDesc;
	listaIntDesc.add(3);
	listaIntDesc.add(1);
	listaIntDesc.add(7);
	listaIntDesc.add(4);
	listaIntDesc.add(6);
	listaIntDesc.add(5);
	listaIntDesc.add(2);
	listaIntDesc.print();

	listaIntDesc.del(1);
	listaIntDesc.del(7);
	listaIntDesc.del(5);
	listaIntDesc.del(3);
	listaIntDesc.print();


}
