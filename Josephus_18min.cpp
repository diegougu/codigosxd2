#include<iostream>
using namespace std;

template <class T>
struct node {
	T valor;
	node<T>* next = nullptr;
	node<T>* prev = nullptr;
	node(T v, node<T>* n = nullptr, node<T>* p = nullptr) : valor(v), next(n), prev(p) {}
};

template <class T>
class CirularDoubleLinkedList {
private:
	node<T>* head = nullptr;
public:
	void push(T v);
	void print();
	void Josephus(int K);
};

template<class T>
void CirularDoubleLinkedList<T>::push(T v) {
	node<T>* temp = new node<T>(v);
	if (head == nullptr) {
		head = temp;
		head->next = head;
		head->prev = head;
	}
	else {
		node<T>* p = head->prev;
		temp->next = head;
		head->prev = temp;
		p->next = temp;
		temp->prev = p;
		head = temp;
	}
}

template<class T>
void CirularDoubleLinkedList<T>::print() {
	node<T>* p = head;
	do {
		cout << p->valor << " ";
		p = p->next;
	} while (p != head);
	cout << endl;
}

template <class T>
void CirularDoubleLinkedList<T>::Josephus(int K) {
	if (head == nullptr) {
		return;
	}
	int c = 1;
	node<T>* p = head;

	while (head != nullptr) {
		if (c == K) {
			node<T>* temp = p;
			node<T>* q = p->prev;
			if (p == head) {
				if (head->next == head) {
					head = nullptr;
					delete temp;
					return;
				}
				else {
					head = head->next;
					p = p->next;
					head->prev = q;
					q->next = head;
					delete temp;
				}

			}
			else {
				p = p->next;
				q->next = p;
				p->prev = q;
				delete temp;
			}
			c = 1;
			print();
		}
		c++;
		p = p->next;
	}

}


int main() {
	CirularDoubleLinkedList<int> l;
	for (int i = 5; i >= 1; i--) {
		l.push(i);
	}
	l.print();
	l.Josephus(3);
	l.print();
}
