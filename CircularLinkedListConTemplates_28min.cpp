#include <iostream>
using namespace std;

template <class T>
struct ASC {
	bool operator()(T a, T b) {
		return a > b;
	}
};

template <class T>
struct DESC {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template <class T>
struct node {
	T data;
	node<T>* next;
	node(T d, node<T>* n = nullptr) : data(d), next(n) {}
};


template <class T, class C>
class CircularLinkedList {
private:
	node<T>* head = nullptr;
public:
	void add(T a);
	void del(T a);
	void print();
};

template <class T, class C>
void CircularLinkedList<T, C>::add(T v) {
	node<T>* temp = new node<T>(v);
	C comp;
	if (head == nullptr) {
		head = temp;
		head->next = head;
	}
	else if (!comp(v, head->data)) {
		node<T>* p = head;
		do {
			p = p->next;
		} while (p->next != head);
		temp->next = head;
		head = temp;
		p->next = head;
	}
	else {
		node<T>* p = head;
		node<T>* q = nullptr;
		do {
			q = p;
			p = p->next;
		} while (p->next != head && comp(v, p->data));

		if (p->next == head && comp(v, p->data)) {
			p->next = temp;
			temp->next = head;
		}
		else {
			q->next = temp;
			temp->next = p;
		}

	}
}

template <class T, class C>
void CircularLinkedList<T, C>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (head->next == head && v == head->data) {
		node<T>* temp = head;
		head = nullptr;
		delete temp;
	}
	else if (head->next != head && v == head->data) {
		node<T>* temp = head;
		node<T>* p = head;
		do {
			p = p->next;
		} while (p->next != head);

		head = head->next;
		p->next = head;
		delete temp;
	}
	else {
		node<T>* p = head;
		node<T>* q = nullptr;
		node<T>* temp = nullptr;
		do {
			q = p;
			p = p->next;
		} while (p->next != head && p->data != v);
		
		if (p->next == head && p->data == v) {
			temp = p;
			q->next = head;
			delete temp;
		}
		else {
			temp = p;
			q->next = p->next;
		}

	}


}

template <class T, class C>
void CircularLinkedList<T, C>::print() {
	node<T>* p = head;
	do {
		cout << p->data << " ";
		p = p->next;
	} while (p != head);

	cout << endl;
}

int main() {
	CircularLinkedList<int, DESC<int>> l1; //funciona con todo pero me da flojera poner todas las listas xd
	int arr[5] = { 4,1,2,5,3 };
	int delarr[5] = { 1,5,3,2,4 };

	for (int i = 0; i < 5; i++) {
		l1.add(arr[i]);
		l1.print();
	}

	l1.print();

	for (int i = 0; i < 5; i++) {
		l1.del(delarr[i]);
		l1.print();
	}

	l1.print();

}
