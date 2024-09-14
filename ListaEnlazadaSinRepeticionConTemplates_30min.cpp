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
	bool find(T v, node<T>*& pos);
public:
	void add(T v);
	void del(T v);
	void print();
};

template <class T, class C>
bool LinkedList<T, C>::find(T v, node<T>*& pos) {
	C comp;
	while (comp(v, pos->data) && pos->next != nullptr) {
		pos = pos->next;
	}
	return pos->data == v && pos != nullptr;
}

template <class T, class C>
void LinkedList<T, C>::add(T v) {
	C comp;
	if (head == nullptr) {
		node<T>* temp = new node<T>(v);
		head = temp;
	}
	else if (!comp(v, head->data) && v != head->data) {
		node<T>* temp = new node<T>(v);
		temp->next = head;
		head = temp;
	}
	else {
		node<T>* pos = head;
		if (find(v, pos)) {
			return;
		}
		node<T>* temp = new node<T>(v);
		node<T>* q = head;
		while (q->next != pos && q->next != nullptr) {
			q = q->next;
		}

		if (comp(v, pos->data) && pos->next == nullptr) {
			pos->next = temp;
		}
		else {
			q->next = temp;
			temp->next = pos;
		}
	}
}

template <class T, class C>
void LinkedList<T, C>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (v == head->data && head->next != nullptr) {
		node<T>* temp = head;
		head = head->next;
		delete temp;
	}
	else if (v == head->data && head->next == nullptr){
		node<T>* temp = head;
		head = nullptr;
		delete temp;
	}
	else {
		node<T>* temp = head;
		if (!find(v, temp)) {
			return;
		}
		node<T>* q = head;
		while (q->next != temp) {
			q = q->next;
		}

		q->next = temp->next;
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

	cout << "Lista de enteros (ASC):" << endl;
	LinkedList<int, ASC<int>> listaIntAsc;
	listaIntAsc.add(3);
	listaIntAsc.add(1);
	listaIntAsc.add(7);
	listaIntAsc.add(4);
	listaIntAsc.add(6);
	listaIntAsc.add(5);
	listaIntAsc.add(2);
	listaIntAsc.add(4);
	listaIntAsc.print();

	cout << "Lista de caracteres (DESC):" << endl;
	LinkedList<char, DESC<char>> listaCharDesc;
	listaCharDesc.add('d');
	listaCharDesc.add('a');
	listaCharDesc.add('f');
	listaCharDesc.add('b');
	listaCharDesc.add('e');
	listaCharDesc.add('c');
	listaCharDesc.add('g');
	listaCharDesc.print();

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
}
