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
	void push(int v);
	void print();
	void reverse();
};

void LinkedList::push(int v) {
	if (head == nullptr) {
		node* temp = new node(v);
		head = temp;
	}
	else {
		node* temp = new node(v);
		temp->next = head;
		head = temp;
	}
}


void LinkedList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}


void LinkedList::reverse() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		return;
	}
	else {
		node* p = head;
		node* q = head;
		for (; p->next != nullptr; p = p->next);
		node* temp_head = p;

		while (head != temp_head) {
			for (; q->next != p && q->next != nullptr; q = q->next);
			if (p == q) {
				head = temp_head;
			}
			else {
				p->next = q;
				p = q;
				q->next = nullptr;
				q = head;
			}
		}
	}
}




int main() {
	LinkedList lista;
	LinkedList lista2;
	lista.push(1);
	lista.push(2);
	lista.push(3);
	lista.push(4);
	lista.push(5);

	lista2.push(6);
	lista2.push(4);
	lista2.push(9);



	lista.print();
	lista2.print();

	lista.reverse();
	lista2.reverse();

	lista.print();
	lista2.print();


}
