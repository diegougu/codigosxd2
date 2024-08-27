#include <iostream>	
using namespace std;

struct node {
	int data;
	node* next;
	node* prev;
	node(int d, node* n = nullptr, node* p = nullptr) : data(d), next(n), prev(p) {}
};

class DoubleLinkedList {
private:
	node* head = nullptr;
public:
	void push(int v);
	void print();
	void turn(int n);
};

void DoubleLinkedList::push(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
	}
	else {
		node* p = head;
		while (p->next != nullptr) {
			p = p->next;
		}
		p->next = temp;
		temp->prev = p;
	}
}

void DoubleLinkedList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}

void DoubleLinkedList::turn(int n) {
	if (head == nullptr || n == 0) {
		return;
	}
	else {
		int contador = 0;
		node* u = head;
		while (u->next != nullptr) {
			u = u->next;
		}
		head->prev = u;
		u->next = head;

		while (contador != n) {
			head = head->next;
			u = u->next;
			contador++;
		}
		head->prev = nullptr;
		u->next = nullptr;
	}
}



int main() {
	DoubleLinkedList lista;
	int arr[5] = { 1,2,3,4,5 };
	for (int i = 0; i < 5; i++) {
		lista.push(arr[i]);
	}
	lista.print();

	lista.turn(2);

	lista.print();



}
