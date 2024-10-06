#include <iostream>
using namespace std;

struct node {
	int valor;
	node* next = nullptr;
	node(int v, node* n = nullptr) : valor(v), next(n) {}
};

class LinkedList {
private:
	node* head = nullptr;
public:
	void push(int v);
	void print();
	void Reverse();
};

void LinkedList::push(int v) {
	node** p = &head;
	node* temp = new node(v);
	temp->next = *p;
	*p = temp;
}

void LinkedList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

void LinkedList::Reverse() {
	if (head == nullptr && head->next == nullptr) {
		return;
	}
	else {
		node* ult = head;
		for (; ult->next != nullptr; ult = ult->next);

		node* p = ult;
		while (p != head) {
			node* q = head;
			while (q->next != p) {
				q = q->next;
			}
			p->next = q;
			p = q;
		}

		head->next = nullptr;
		head = ult;
	}
}


int main() {
	LinkedList l1;
	for (int i = 0; i <= 30; i++) {
		l1.push(i);
	}
	l1.print();
	l1.Reverse();
	l1.print();
}

