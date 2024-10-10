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
class DoubleLinkedList {
private:
	node<T>* head = nullptr;
	bool find(node<T>*& pos, T v);
public:
	void add(T v);
	void del(T v);
	void print();
};

template <class T, class C>
bool DoubleLinkedList<T, C>::find(node<T>*& pos, T v) {
	C comp;
	while (pos->next != nullptr && comp(v, pos->data)) {
		pos = pos->next;
	}

	return pos->data == v;
}


template <class T, class C>
void DoubleLinkedList<T, C>::add(T v) {
	C comp;
	if (head == nullptr) {
		node<T>* temp = new node<T>(v);
		head = temp;
	}
	else if (!comp(v, head->data) && v != head->data) {
		node<T>* temp = new node<T>(v);
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	else {
		node<T>* pos = head;
		if (find(pos, v)) {
			return;
		}
		node<T>* temp = new node<T>(v);
		if (comp(v, pos->data) && pos->next == nullptr) {
			pos->next = temp;
			temp->prev = pos;
		}
		else {
			node<T>* temp = new node<T>(v);
			temp->prev = pos->prev;
			pos->prev->next = temp;
			pos->prev = temp;
			temp->next = pos;
		}
	}
}

template <class T, class C>
void DoubleLinkedList<T, C>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (v == head->data) {
		node<T>* temp = head;
		if (head->next == nullptr) {
			head = nullptr;
			delete temp;
		}
		else {
			head = head->next;
			head->prev = nullptr;
			delete temp;
		}
	}
	else {
		node<T>* pos = head;
		if (!find(pos, v)) {
			return;
		}

		node<T>* temp = pos;
		pos = pos->prev;

		if (temp->next == nullptr) {
			pos->next = temp->next;
			delete temp;
		}
		else {
			pos->next = temp->next;
			temp->next->prev = pos;
			delete temp;
		}
	}
}



template <class T, class C>
void DoubleLinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}

int main() {
	cout << "Lista de enteros (ASC):" << endl;
	DoubleLinkedList<int, ASC<int>> listaIntDesc;
	listaIntDesc.add(3);
	listaIntDesc.add(1);
	listaIntDesc.add(7);
	listaIntDesc.add(4);
	listaIntDesc.add(6);
	listaIntDesc.add(5);
	listaIntDesc.add(2);
	listaIntDesc.add(4);
	listaIntDesc.print();

	listaIntDesc.del(1);
	listaIntDesc.del(7);
	listaIntDesc.del(5);
	listaIntDesc.del(3);
	listaIntDesc.print();

}
