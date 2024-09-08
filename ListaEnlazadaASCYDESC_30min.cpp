#include <iostream>
using namespace std;

template <class T>
struct node {
	T valor;
	node<T>* next;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

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


template <class T, class C>
struct LE {
	node<T>* head = nullptr;
	bool find(T v, node<T>*& Pos);
	void add(T v);
	void del(T v);
	void print();
};

template <class T, class C>
bool LE<T, C>::find(T v, node<T>*& Pos) {
	C comparar;
	while (Pos->next != nullptr && !comparar(Pos->valor, v) && Pos->valor != v) {
		Pos = Pos->next;
	}
	if (Pos->valor == v) 
		return true;
	else 
		return false;
}

template <class T, class C>
void LE<T, C>::add(T v) {
	if (head == nullptr) {
		node<T>* temp = new node<T>(v);
		head = temp;
	}
	else {
		node<T>* pos = head;
		C comparar;
		node<T>* temp = new node<T>(v);
		if (find(v, pos)) {
			return;
		}
		else {
			if (pos == head && !comparar(v, head->valor)) {
				temp->next = head;
				head = temp;
			}
			else if (pos == head && pos->next == nullptr && comparar(v, head->valor)) {
				head->next = temp;
			}
			else {
				node<T>* ant = head;
				while (ant->next != pos) {
					ant = ant->next;
				}

				if (pos->next == nullptr && comparar(v, pos->valor)) {
					pos->next = temp;
				}
				else {
					ant->next = temp;
					temp->next = pos;
				}
			}
		}
	}
}

template <class T, class C>
void LE<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

template <class T, class C>
void LE<T, C>:: del(T v) {
	if (head == nullptr) {
		return;
	}
	else {
		node<T>* p = head;
		if (!find(v, p)) {
			return;
		}
		else {
			if (p == head && head->valor == v && head->next != nullptr) {
				node<T>* temp = head;
				head = head->next;
				delete temp;
			}
			else if (p == head && head->valor == v && head->next == nullptr) {
				node<T>* temp = head;
				head = nullptr;
				delete temp;
			}
			else {
				node<T>* q = head;
				while (q->next != p) {
					q = q->next;
				}
				q->next = p->next;
				delete p;

			}
		}
	}
}

int main() {
	cout << "Lista de enteros (DESC):" << endl;
	LE<int, DESC<int>> listaIntDesc;
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
	LE<int, ASC<int>> listaIntAsc;
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
	LE<char, DESC<char>> listaCharDesc;
	listaCharDesc.add('d');
	listaCharDesc.add('a');
	listaCharDesc.add('f');
	listaCharDesc.add('b');
	listaCharDesc.add('e');
	listaCharDesc.add('c');
	listaCharDesc.add('g');
	listaCharDesc.print();

	cout << "Lista de caracteres (ASC):" << endl;
	LE<char, ASC<char>> listaCharAsc;
	listaCharAsc.add('d');
	listaCharAsc.add('a');
	listaCharAsc.add('f');
	listaCharAsc.add('b');
	listaCharAsc.add('e');
	listaCharAsc.add('c');
	listaCharAsc.add('g');
	listaCharAsc.print(); 
}



