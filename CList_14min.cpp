#include <iostream>
using namespace std;

struct node {
	int valor;
	node* next;
	node(int v, node* n = nullptr) : valor(v), next(n) {}
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
		head = temp;
	}
}

void CList::pop_back() {
	if (head == nullptr) {
		return;
	}
	else if (head == tail) {
		node* temp = head;
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		node* prev = head;
		while (prev->next != tail) {
			prev = prev->next;
		}
		node* temp = tail;
		tail = prev;
		tail->next = nullptr;
		delete temp;

	}

}

void CList::pop_front() {
	if (head == nullptr) {
		return;
	}
	else if (head == tail) {
		node* temp = head;
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		node* temp = head;
		head = head->next;
		delete temp;
	}
}

void CList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

node* CList::operator[](int v) {
	node* p = head;
	for (int i = 0; i != v && p; i++, p = p->next);
	return p;
	
}

int main() {
	CList lis;
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
	cout << val->valor;


}








