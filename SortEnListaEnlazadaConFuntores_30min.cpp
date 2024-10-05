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
	T valor;
	node<T>* next = nullptr;
	node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

template <class T, class C>
class LinkedList {
private:
	node<T>* head = nullptr;
public:
	void push(T v);
	void print();
	void sort();
};

template <class T, class C>
void LinkedList<T, C>::push(T v) {
	node<T>** p = &head;
	node<T>* temp = new node<T>(v);
	temp->next = *p;
	*p = temp;
}

template <class T, class C>
void LinkedList<T, C>::print() {
	for (node<T>* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

template <class T, class C>
void LinkedList<T, C>::sort() {
	C comp;
	if (head == nullptr || head->next == nullptr) {
		return;
	}
	node<T>* p = head;
	while (p != nullptr) {
		node<T>* q = p->next;
		while (q != nullptr) {
			if (comp(p->valor, q->valor) && p == head) {
				node<T>* a = p;
				while (a->next != q) {
					a = a->next;
				}
				a->next = q->next;
				q->next = p;
				p = q;
				head = p;
			}
			else if (comp(p->valor, q->valor) && p != head) {
				node<T>* a = p;
				node<T>* b = head;
				while (a->next != q) {
					a = a->next;
				}
				while (b->next != p) {
					b = b->next;
				}
				b->next = q;
				a->next = q->next;
				q->next = p;
				p = q;

			}
			q = q->next;
		}
		p = p->next;
	}

}


int main() {
	LinkedList<int, ASC<int>> l1;
	int arr[13] = { 3,2,1,4,6,5,7,8,10,9,12,13,11 };
	for (int i = 0; i < 13; i++) {
		l1.push(arr[i]);
	}
	l1.print();

	l1.sort();
	l1.print();
}

