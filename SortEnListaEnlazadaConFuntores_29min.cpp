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
	if (head == nullptr) {
		return;
	}

	if (head != nullptr && head->next == nullptr) {
		return;
	}

	C comp;
	node<T>* p = head;
	node<T>* q = p;
	while (p != nullptr) {
		q = p->next;
		while (q != nullptr) {
			if (p == head && comp(p->valor, q->valor)) {
				node<T>* s = head;
				while (s->next != q) {
					s = s->next;
				}
				s->next = q->next;
				q->next = p;
				head = q;
				p = q;
			}
			else if (p != head && comp(p->valor, q->valor)){
				node<T>* r = head;
				while (r->next != p) {
					r = r->next;
				}
				node<T>* s = head;
				while (s->next != q) {
					s = s->next;
				}
				r->next = q;
				s->next = q->next;
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
