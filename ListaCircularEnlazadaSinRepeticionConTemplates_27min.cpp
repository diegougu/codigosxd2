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
class CircularLinkedList {
private:
	node<T>* head = nullptr;
	bool find(node<T>*& pos, T v);
public:
	void add(T v);
	void del(T v);
	void print();
};


template <class T, class C>
bool CircularLinkedList<T, C>::find(node<T>*& pos, T v) {
	C comp;
	node<T>* p = head;
	do {
		p = pos;
		pos = pos->next;
	} while (pos->next != head && comp(v, pos->data));

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
void CircularLinkedList<T, C>::add(T v) {
	C comp;
	if (head == nullptr) {
		node<T>* temp = new node<T>(v);
		head = temp;
		head->next = head;
	}
	else if (v != head->data && !comp(v, head->data)) {
		node<T>* ult = head;
		do {
			ult = ult->next;
		} while (ult->next != head);
		node<T>* temp = new node<T>(v);
		temp->next = head;
		head = temp;
		ult->next = head;
	}
	else {
		node<T>* pos = head;
		if (find(pos, v)) {
			return;
		}
		node<T>* temp = new node<T>(v);
		node<T>* p = pos->next;
		if (p->next == head && comp(v, p->data)) {
			p->next = temp;
			temp->next = head;
		}
		else {
			pos->next = temp;
			temp->next = p;
		}

	}
}

template <class T, class C>
void CircularLinkedList<T, C>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (v == head->data && head->next != head) {
		node<T>* temp = head;
		node<T>* ult = head;
		do {
			ult = ult->next;
		} while (ult->next != head);
		head = head->next;
		ult->next = head;
		delete temp;
	}
	else {
		node<T>* pos = head;
		if (!find(pos, v)) {
			return;
		}
		node<T>* temp = pos->next;
		if (temp->next == head) {
			pos->next = head;
			delete temp;
		}
		else {
			pos->next = temp->next;
			delete temp;

		}


	}
}

template <class T, class C>
void CircularLinkedList<T, C>::print() {
	node<T>* p = head;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != head);

	cout << endl;

}


int main() {
	cout << "Lista Circular de enteros (DESC):" << endl;
	CircularLinkedList<int, DESC<int>> listaIntDesc;
	listaIntDesc.add(3);
	listaIntDesc.add(1);
	listaIntDesc.add(7);
	listaIntDesc.add(4);
	listaIntDesc.add(6);
	listaIntDesc.add(5);
	listaIntDesc.add(2);
	listaIntDesc.add(4);
	listaIntDesc.print();
	cout << "Lista Circular de caracteres (ASC):" << endl;
	CircularLinkedList<char, ASC<char>> listaCharAsc;
	listaCharAsc.add('d');
	listaCharAsc.add('a');
	listaCharAsc.add('f');
	listaCharAsc.add('b');
	listaCharAsc.add('e');
	listaCharAsc.add('c');
	listaCharAsc.add('g');
	listaCharAsc.print();

	cout << "Lista Circular de enteros (DESC): Borrado" << endl;
	listaIntDesc.del(1);
	listaIntDesc.del(7);
	listaIntDesc.del(5);
	listaIntDesc.del(3);
	listaIntDesc.print();

	cout << "Lista Circular de caracteres (ASC): Borrado" << endl;
	listaCharAsc.del('d');
	listaCharAsc.del('b');
	listaCharAsc.del('a');
	listaCharAsc.del('g');
	listaCharAsc.print();
}
