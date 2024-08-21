#include <iostream>
using namespace std;

struct node {
	int data;
	node* next = nullptr;
	node(int d, node* n = nullptr) : data(d), next(n) {}
};

class CircularLinkedList {
private:
	node* head = nullptr;
public:
	void add(int v);
	void print();
	void Josephus(int k);
};

void CircularLinkedList::add(int v) {
	if (head == nullptr) {
		node* temp = new node(v);
		head = temp;
		head->next = head;
	}
	else {
		node* temp = new node(v);
		node* p = head;
		do {
			p = p->next;
		} while (p->next != head);
		p->next = temp;
		temp->next = head;
	}
}


void CircularLinkedList::print() {
	node* p = head;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != head);

	cout << endl;
}

void CircularLinkedList::Josephus(int k) {
	if (head == nullptr) {
		return;
	}
	else {
		int contador = 0;
		node* p = head;

		while (head != nullptr) {
			if (contador == k) {
				if (p == head && head->next != head) {
					node* temp = p;
					node* u = head;
					do {
						u = u->next;
					} while (u->next != head);
					head = head->next;
					p = head; 
					u->next = head;
					delete temp;
					contador = 0;
				}
				else if (p == head && head->next == head) {
					node* temp = head;
					head = nullptr;
					p = nullptr;
					delete temp;
					break;
				}
				else if (p->next == head) {
					node* q = head;
					while (q->next != p) {
						q = q->next;
					}
					node* temp = p;
					p = p->next;
					q->next = head;
					delete temp;
					contador = 0;
				}
				else {
					node* q = head;
					while (q->next != p) {
						q = q->next;
					}
					node* temp = p;
					p = p->next;
					q->next = p;
					delete temp;
					contador = 0;
				}
				print();


			}
			contador++;
			p = p->next;

		}
	}
}


int main() {
	CircularLinkedList lista;
	lista.add(1);
	lista.add(2);
	lista.add(3);
	lista.add(4);
	lista.add(5);
	lista.print();


	lista.Josephus(3);

}
