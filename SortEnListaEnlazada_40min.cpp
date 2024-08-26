#include <iostream>	
using namespace std;

struct node {
	int data;
	node* next;
	node(int d, node* n = nullptr) : data(d), next(n) {}
};

class LinkedList {
private:
	node* head = nullptr;
public:
	void push(int v);
	void print();
	void sort();
};


void LinkedList::push(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
	}
	else {
		temp->next = head;
		head = temp;
	}
}

void LinkedList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}

void LinkedList::sort() {
	if (head == nullptr || (head != nullptr && head->next == nullptr)) {
		return;
	}
	else {
		node* p = head;

		while (p != nullptr) {
			node* q = p->next;
			while (q != nullptr) {
				if (p == head && p->data > q->data) {
					node* r = p;
					while (r->next != q) {
						r = r->next;
					}
					r->next = q->next;
					q->next = p;
					head = q;
					p = q;
					q = q->next;

				}
				else if(p != head && p->data > q->data) {
					node* t = head;
					while (t->next != p) {
						t = t->next;
					}
					node* r = p;
					while (r->next != q) {
						r = r->next;
					}

					t->next = q;
					r->next = q->next;
					q->next = p;
					p = q;
					q = q->next;
				}
				q = q->next;
			}
			p = p->next;
		}
	}
}


int main() {
	LinkedList lista;
	int arr[11] = {0,2,3,1,4,6,5,7,9,10,8};
	for (int i = 0; i < 11; i++) {
		lista.push(arr[i]);
	}
	lista.print();
	lista.sort();
	lista.print();

}
