#include <iostream>
using namespace std;

template <class T>
struct node {
	T valor;
	node<T>* next;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T>
struct Pila {
	node<T>* top = nullptr;
	void push(T v);
	bool pop(T& v);
	void print();
};

template <class T>
void Pila<T>::push(T v) {
	node<T>* temp = new node<T>(v);
	if (top == nullptr) {
		top = temp;
	}
	else {
		temp->next = top;
		top = temp;
	}
}

template <class T>
bool Pila<T>::pop(T& v) {
	if (top == nullptr) {
		return false;
	}
	else {
		v = top->valor;
		node<T>* temp = top;
		top = top->next;
		delete temp;
		return true;
	}
}

template <class T>
void Pila<T>::print() {
	cout << "head->";
	for (node<T>* p = top; p; p = p->next) {
		cout << p->valor << "->";
	}
	cout << "null";
	cout << endl;
}

template <class T>
struct Cola {
	node<T>* head = nullptr;
	node<T>* tail = nullptr;
	void push(T v);
	bool pop(T& v);
	void print();
};

template <class T>
void Cola<T>::push(T v) {
	node<T>* temp = new node<T>(v);
	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		tail = tail->next;
	}
}

template <class T>
bool Cola<T>::pop(T& v) {
	if (head == nullptr) {
		return false;
	}
	else {
		v = head->valor;
		node<T>* temp = head;
		head = head->next;
		delete temp;
		return true;
	}
}

template <class T>
void Cola<T>::print() {
	cout << "head->";
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << "->";
	}
	cout << "null";
	cout << endl;
}


int main(){
    int pila_v = 0;
    int cola_v = 0;
    Pila<int> p;
    for(int i = 0; i < 10; i++){
        p.push(i);
    }
    
    p.print();
    p.pop(pila_v);
    cout << pila_v << endl;
    p.print();
    
    Cola<int> c;
    for(int i = 10; i < 20; i++){
        c.push(i);
    }
    c.print();
    c.pop(cola_v);
    cout << cola_v << endl;
    c.print();
    
    }

