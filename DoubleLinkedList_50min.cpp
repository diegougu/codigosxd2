#include <iostream>
using namespace std;

struct node {
	int data;
	node* next = nullptr;
	node* prev = nullptr;
	node(int d, node* n = nullptr, node* p = nullptr) : data(d), next(n), prev(p) {}
};


class DoubleLinkedList {
private:
	node* head = nullptr;
public:
	void add(int v);
	void del(int v);
	void print();
};

void DoubleLinkedList::add(int v) {
	if (head == nullptr) {
		node* temp = new node(v);
		head = temp;
	}
	else if (head->data > v) {
		node* temp = new node(v);
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
	else {
		node* temp = new node(v);
		node* p = head;
		while (p->next != nullptr && p->data < v) {
			p = p->next;
		}

		if (p->next == nullptr && v > p->data) {
			p->next = temp;
			temp->prev = p;
		}
		else {
			node* q = head;
			while (q->next != p && q->next != nullptr) {
				q = q->next;
			}
			q->next = temp;
			temp->prev = q;
			temp->next = p;
			p->prev = temp;
		}
	}
}

void DoubleLinkedList::del(int v) {
	if (head == nullptr) {
		return;
	}
	else if(head->next == nullptr && head->data == v){
		node* temp = head;
		head = nullptr;
		delete temp;
	}
	else if (head->next != nullptr && head->data == v) {
		node* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}
	else {
		node* p = head;
		while (p->next->data != v && p->next != nullptr) {
			p = p->next;
		}
		node* temp = p->next;
		if (temp->next == nullptr) {
			p->next = nullptr;
			delete temp;
		}
		else {
			node* q = temp->next;
			p->next = q;
			q->prev = p;
			delete temp;
		}
	}
}

void DoubleLinkedList::print() {
	for (node* a = head; a; a = a->next) {
		cout << a->data << " ";
	}
	cout << endl;
}

int main() {
	DoubleLinkedList lista;
	int array[4] = {2,3,4,5};
	int array2[4] = {5,3,2,4};

	for (int i = 0; i < 4; i++) {
		lista.print();
		lista.add(array[i]);
	}

	for (int i = 0; i < 4; i++) {
		lista.print();
		lista.del(array2[i]);
	}


}



