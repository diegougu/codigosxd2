#include <iostream>
using namespace std;

struct node {
	int data;
	node* next = nullptr;
	node(int d, node* n = nullptr) : data(d), next(n) {}
};

class LinkedList {
private:
	node* head = nullptr;
public:
	void add(int v);
	void print();
	void eleminar_repetidos();
};

void LinkedList::add(int v) {
	if (head == nullptr) {
		node* temp = new node(v);
		head = temp;
	}
	else if (head->data > v || head->data == v) {
		node* temp = new node(v);
		temp->next = head;
		head = temp;
	}
	else {
		node* temp = new node(v);
		node* p = head;
		while (p->next != nullptr && p->data < v) {
			p = p->next;
		}
		if (p->data < v && p->next == nullptr ) {
			p->next = temp;
		}
		else {
			node* q = head;
			while (q->next != p && q->next != nullptr) {
				q = q->next;
			}
			q->next = temp;
			temp->next = p;
		}
	}
}


void LinkedList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}


void LinkedList::eleminar_repetidos() {
	node* p = head;
	node* q = head;

	while (q->next != nullptr) {
		q = q->next;
		if (p->data == q->data) {
			node* temp = q;
			p->next = q->next;
			q = p;
			delete temp;
		}
		else {
			p = q;
		}
	}

}


int main() {
	LinkedList lista;
	int arr[14] = { 4,4,2,1,5,6,3,3,5,2,1,1,5,6 };
	for (int i = 0; i < 14; i++) {
		lista.add(arr[i]);
		lista.print();
	}

	lista.eleminar_repetidos();
	lista.print();

}
