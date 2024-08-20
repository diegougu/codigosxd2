#include <iostream>
using namespace std;

struct node {
	int valor;
	node* next = nullptr;
	node(int v, node* n = nullptr) : valor(v), next(n) {}
};

class LE {
private:
	node* head = nullptr;
public:
	bool find(int v);
	void add(int v);
	void del(int v);
	void print();
};

void LE::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}


bool LE::find(int v) {
	for (node* p = head; p; p = p->next) {
		if (p->valor == v) {
			return true;
		}
	}
	return false;
}


void LE::add(int v) {
	if (find(v)) {
		return;
	}
	node* temp = new node(v);
	if (head == nullptr || head->valor > v) {
		temp->next = head;
		head = temp;
	}
	else {
		node* p = head;
		while (p->next != nullptr && v > p->valor) {
			p = p->next;
		}
		if (p->next == nullptr && v > p->valor) {
			p->next = temp;
		}
		else {
			node* q = head;
			while (q->next != nullptr && q->next != p) {
				q = q->next;
			}
			q->next = temp;
			temp->next = p;
		}
	}

}


void LE::del(int v) {
	if (head == nullptr) {
		return;
	}
	else if (!find(v)) {
		return;
	}
	else {
		if (head->valor == v) {
			node* temp = head; 
			head = head->next;
			delete temp;
		}
		else {
			node* p = head;
			while (p->next != nullptr && p->valor != v) {
				p = p->next;
			}
			node* q = head;
			while (q->next != nullptr && q->next != p) {
				q = q->next;
			}
			q->next = p->next;
			delete p;

		}
	}

}


int main() {
	LE lista;

	lista.add(5);
	lista.add(2);
	lista.add(7);
	lista.add(1);
	lista.add(4);
	lista.add(3);
	lista.add(6);
	lista.add(5);

	lista.print();

	lista.del(4);
	lista.del(1);
	lista.del(7);

	lista.print();

	return 0;
}

