#include <iostream>
using namespace std; 

struct node {
	int data;
	node* next;
	node* prev;
	node(int d, node* n = nullptr, node* p = nullptr) : data(d), next(n), prev(p) {}
};

class CircularDoubleLinkedList {
private:
	node* head = nullptr;
public:
	void add(int v);
	void del(int v);
	void print();
};

void CircularDoubleLinkedList::add(int v) {
	if (head == nullptr) {
		node* temp = new node(v);
		head = temp;
		head->next = head;
		head->prev = head;
	}
	else if (head->data > v) {
		node* temp = new node(v);
		node* u = head->prev;
		temp->next = head;
		head->prev = temp;
		temp->prev = u;
		u->next = temp;
		head = temp;
	}
	else {
		node* temp = new node(v);
		node* p = head;
		do {
			p = p->next;
		} while (p->next != head && p->data < v);
		if (p->next == head && v > p->data) {
			p->next = temp;
			temp->prev = p;
			head->prev = temp;
			temp->next = head;
		}
		else {
			node* q = p->prev;
			q->next = temp;
			temp->prev = q;
			temp->next = p;
			p->prev = temp;
		}
	}
}

void CircularDoubleLinkedList::del(int v) {
	if (head == nullptr) {
		return;
	}
	else if (head->data == v && head->next == head) {
		node* temp = head;
		head = nullptr;
		delete temp;
	}
	else if (head->data == v && head->next != head) {
		node* temp = head;
		node* u = head->prev;
		head = head->next;
		head->prev = u;
		u->next = head;
		delete temp;
	}
	else {
		node* temp = head;
		do {
			temp = temp->next;
		} while (temp->data != v);

		if (temp->next == head) {
			node* p = temp->prev;
			p->next = head;
			head->prev = p;
			delete temp;
		}
		else {
			node* p = temp->prev;
			node* q = temp->next;
			p->next = q;
			q->prev = p;
			delete temp;
		}
	}
}

void CircularDoubleLinkedList::print() {
	node* p = head;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}



int main() {
	CircularDoubleLinkedList lista;
	int arr[5] = { 5,4,2,1,3 };
	for (int i = 0; i < 5; i++) {
		lista.add(arr[i]);
		lista.print();
	}

	cout << endl;

	int arr2[5] = { 1,3,2,5,4 };
	for (int i = 0; i < 5; i++) {
		lista.del(arr2[i]);
		lista.print();
	}
	
}


