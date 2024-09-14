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
bool CircularDoubleLinkedList<T, C>::find(node<T>*& pos, T v) {
	C comp;
	do {
		pos = pos->next;
	} while (pos->next != head && comp(v, pos->data));

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
	else if (v != head->data && !comp(v, head->data)) {
		node<T>* ult = head->prev;
		node<T>* temp = new node<T>(v);
		temp->next = head;
		head->prev = temp;
		head = temp;
		ult->next = head;
	}
	else {
		node<T>* pos = head;
		if (find(pos, v)) {
			return;
		}
		node<T>* temp = new node<T>(v);
		if (pos->next == head && comp(v, pos->data)) {
			pos->next = temp;
			temp->prev = pos;
			temp->next = head;
			pos->prev = temp;
		}
		else {
			node<T>* p = pos->prev;
			p->next = temp;
			temp->prev = p;
			temp->next = pos;
			pos->prev = temp;
		}

	}
}


template <class T, class C>
void CircularDoubleLinkedList<T, C>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (head->data == v && head->next == head) {
		node<T>* temp = head;
		head = nullptr;
		delete temp;
	}
	else if (head->data == v && head->next != head) {
		node<T>* temp = head;
		node<T>* ult = head->prev;
		head = head->next;
		head->prev = ult;
		ult->next = head;
		delete temp;
	}
	else {
		node<T>* temp = head;
		if (!find(temp, v)) {
			return;
		}
		node<T>* p = temp->prev;

		if (temp->next == head) {
			p->next = head;
			head->prev = p;
			delete temp;
		}
		else {
			p->next = temp->next;
			temp->next->prev = p;
			delete temp;
		}


	}
}

template <class T, class C>
void CircularDoubleLinkedList<T, C>::print() {
	node<T>* p = head;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}




int main() {
	cout << "Lista de enteros (DESC):" << endl;
	CircularDoubleLinkedList<int, DESC<int>> listaIntDesc;
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


