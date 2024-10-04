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
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T, class C>
class CircularLinkedList {
private:
	node<T>* head = nullptr;
	bool find(T v, node<T>*& p);
public:
	void add(T v);
	void del(T v);
	void print();
};

template <class T, class C>
bool CircularLinkedList<T, C>::find(T v, node<T>*& p) {
	C comp;
	node<T>* q = head;
	do {
		q = p;
		p = p->next;
	} while (p->next != head && comp(v, p->valor));

	if (p->valor == v) {
		p = q;
		return true;
	}
	else {
		p = q;
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
	else if (!comp(v, head->valor) && v != head->valor) {
		node<T>* temp = new node<T>(v);
		node<T>* p = head;
		do {
			p = p->next;
		} while (p->next != head);
		
		temp->next = head;
		head = temp;
		p->next = head;
	}
	else {
		node<T>* p = head;
		if (find(v, p)) {
			return;
		}
		node<T>* temp = new node<T>(v);
		node<T>* q = p->next;

		if (comp(v, q->valor) && q->next == head) {
			q->next = temp;
			temp->next = head;
		}
		else {
			p->next = temp;
			temp->next = q;
		}
	}
}


template <class T, class C>
void CircularLinkedList<T, C>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (head->valor == v) {
		node<T>* temp = head;
		if (head->next == head) {
			head = nullptr;
			delete temp;
		}
		else {
			node<T>* p = head;
			do {
				p = p->next;
			} while (p->next != head);
			head = head->next;
			p->next = head;
			delete temp;
		}
	}
	else {
		node<T>* p = head;
		if (!find(v, p)) {
			return;
		}
		node<T>* temp = p->next;
		p->next = temp->next;
		delete temp;
	}
}

template <class T, class C>
void CircularLinkedList<T, C>::print() {
	node<T>* p = head;
	do {
		cout << p->valor << " ";
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
