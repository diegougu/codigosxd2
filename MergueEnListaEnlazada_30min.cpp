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
	bool find(int x, node**& p);
public:
	void Mergue(LinkedList& l2);
	void add(int x);
	void print();
};

bool LinkedList::find(int x, node**& p) {
	for (p = &head; *p && x > (*p)->valor; p = &((*p)->next));
	return *p && (*p)->valor == x;
}

void LinkedList::add(int x) {
	node** p;
	if (find(x, p)) {
		return;
	}
	node* temp = new node(x);
	temp->next = *p;
	*p = temp;
}

void LinkedList::print() {
	cout << "head->";
	for (node* p = head; p; p = p->next) {
		cout << p->valor << "->";
	}
	cout << "null";
	cout << endl;
}


void LinkedList::Mergue(LinkedList& l2) {
	node* p = head;
	node* q = l2.head;
	while (l2.head != nullptr) {
		if (p->valor > q->valor && p == head) {
			l2.head = l2.head->next;
			q->next = head;
			head = q;
			p = head;
			q = l2.head;
		}
		else if (p->valor > q->valor && p != head) {
			l2.head = l2.head->next;
			node* t = head;
			while (t->next != p) {
				t = t->next;
			}
			q->next = p;
			t->next = q;
			p = head;
			q = l2.head;

		}
		else if (p->next == nullptr) {
			p->next = l2.head;
			l2.head = nullptr;
		}
		p = p->next;
	}
}

int main() {
	LinkedList l1;
	LinkedList l2;
	l1.add(3);
	l1.add(6);
	l1.add(7);
	l1.add(15);

	l2.add(1);
	l2.add(8);
	l2.add(9);
	l2.add(10);

	l1.Mergue(l2);

	l1.print();
	l2.print();

}
