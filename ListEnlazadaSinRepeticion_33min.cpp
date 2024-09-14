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
	node(T d, node<T>* n = nullptr) : data(d), next(n) {}
};

template <class T, class C>
class LinkedList {
private:
	node<T>* head = nullptr;
	bool find(node<T>*& pos, T v);
public:
	void add(T v);
	void del(T v);
	void print();
};

template <class T, class C>
bool LinkedList<T, C>::find(node<T>*& pos, T v) {
	node<T>* p = head;
	C comp;
	while (pos->next != nullptr && comp(v, pos->data)) {
		p = pos;
		pos = pos->next;
	}

	if (pos->data == v) {
		pos = p;
		return true;
	}
	else {
		pos = p;
		return false;
	}
}




template <class T, class C>
void LinkedList<T, C>::add(T v) {
	C comp;
	if (head == nullptr) {
		node<T>* temp = new node<T>(v);
		head = temp;
	}
	else if (v != head->data && !comp(v, head->data)) {
		node<T>* temp = new node<T>(v);
		temp->next = head;
		head = temp;
	}
	else {
		node<T>* pos = head;
		if (find(pos, v)) {
			return;
		}
		node<T>* temp = new node<T>(v);
		node<T>* p = pos->next;
		if (p != nullptr && p->next == nullptr && comp(v, p->data)) {
			p->next = temp;
		}
		else {
			temp->next = p;
			pos->next = temp;
		}
	}
}

template <class T, class C>
void LinkedList<T, C>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (head->data == v && head->next != nullptr) {
		node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	else if (head->data == v && head->next == nullptr) {
		node<T>* temp = head;
		head = nullptr;
		delete temp;
	}
	else {
		node<T>* pos = head;
		if (!find(pos, v)) {
			return;
		}
		node<T>* temp = pos->next;
		pos->next = temp->next;
		delete temp;
	}
}

template <class T, class C>
void LinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}

int main() {
	cout << "Lista de enteros (DESC):" << endl;
	LinkedList<int, DESC<int>> listaIntDesc;
	listaIntDesc.add(3);
	listaIntDesc.add(1);
	listaIntDesc.add(7);
	listaIntDesc.add(4);
	listaIntDesc.add(6);
	listaIntDesc.add(5);
	listaIntDesc.add(2);
	listaIntDesc.add(4);
	listaIntDesc.print();
	cout << "Lista de caracteres (ASC):" << endl;
	LinkedList<char, ASC<char>> listaCharAsc;
	listaCharAsc.add('d');
	listaCharAsc.add('a');
	listaCharAsc.add('f');
	listaCharAsc.add('b');
	listaCharAsc.add('e');
	listaCharAsc.add('c');
	listaCharAsc.add('g');
	listaCharAsc.print();

	cout << "Lista de enteros (DESC): Borrado" << endl;
	listaIntDesc.del(1);
	listaIntDesc.del(7);
	listaIntDesc.del(5);
	listaIntDesc.del(3);
	listaIntDesc.print();

	cout << "Lista de caracteres (ASC): Borrado" << endl;
	listaCharAsc.del('d');
	listaCharAsc.del('b');
	listaCharAsc.del('a');
	listaCharAsc.del('g');
	listaCharAsc.print();
}
