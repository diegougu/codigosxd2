#include <iostream>
using namespace std;

struct node {
	int valor;
	node* next;
	node* prev;
	node(int v, node* n = nullptr, node* p = nullptr) : valor(v), next(n), prev(p) {}
};

class CList {
private:
	node* head = nullptr;
	node* tail = nullptr;
public:
	void push_back(int v);
	void push_front(int v);
	void pop_back();
	void pop_front();
	node* operator[](int v);
	void print();
};


void CList::push_back(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		temp->prev = tail;
		tail = tail->next;
	}

}

void CList::push_front(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
}

void CList::pop_front() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		node* temp = head;
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		node* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}
}

void CList::pop_back() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		node* temp = head;
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		node* temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
	}
}

node* CList::operator[](int v) {
	node* p = head;
	int c = v;
	while (p && c < v) {
		p = p->next;
		c++;
	}
	return p;
}


void CList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

int main() {
	CList list;
	for (int i = 5; i < 10; i++) {
		list.push_back(i);
	}
	for (int i = 0; i < 5; i++) {
		list.push_front(i);
	}

	list.print();
	list.pop_back();
	list.pop_back();
	list.pop_back();
	list.print();
	list.pop_front();
	list.pop_front();
	list.print();
	node* p = list[0];
	p->valor = 1000;
	list.print();
}
