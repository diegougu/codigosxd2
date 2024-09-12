#include <iostream>
using namespace std;

struct node {
	int valor;
	node* next;
	node(int v, node* n = nullptr) : valor(v), next(n) {}
};

class CForwardList {
private:
	node* head = nullptr;
public:
	void push_back(int v);
	void push_front(int v);
	void pop_front();
	void pop_back();
	void print();
	node* operator[](int v);
};

void CForwardList::push_front(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
	}
	else {
		temp->next = head;
		head = temp;
	}
}


void CForwardList::push_back(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
	}
	else {
		node* u = head;
		while (u->next != nullptr) {
			u = u->next;
		}
		u->next = temp;
	}
}

void CForwardList::pop_back() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		node* temp = head;
		head = nullptr;
		delete temp;
	}
	else {
		node* temp = head;
		node* p = nullptr;
		while (temp->next != nullptr) {
			p = temp;
			temp = temp->next;
		}
		p->next = nullptr;
		delete temp;
		
	}
}

void CForwardList::pop_front() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		node* temp = head;
		head = nullptr;
		delete temp;
	}
	else {
		node* temp = head;
		head = head->next;
		delete temp;
	}
}

node* CForwardList::operator[](int v) {
	node* p = head;
	int c = 0;
	while (p && c < v) {
		p = p->next;
		c++;
	}
	return p;
}


void CForwardList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}


int main() {
	CForwardList lis;
	for (int i = 1; i < 5; ++i) {
		lis.push_front(i);
	}

	for (int i = 10; i < 12; i++) {
		lis.push_back(i);
	}

	lis.print();

	lis.pop_front();
	lis.print();
	lis.pop_back();
	lis.print();

	node* val = lis[0];
	cout << val->valor << endl;
	val->valor = 1000;
	lis.print();


}
