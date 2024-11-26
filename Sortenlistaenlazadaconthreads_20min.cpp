#include <iostream>
#include <thread>
#include <vector>
using namespace std;

struct node {
	int data;
	node* next = nullptr;
	node(int d, node* n = nullptr) : data(d), next(n) {}
};

class LE {
private:
	node* head = nullptr;
	int nodes = 0;
	void sorting(node* inicio, node* fin);
public:
	void push(int v);
	void print();
	void sort();
};


void LE::push(int v) {
	node** p = &head;
	node* temp = new node(v);
	temp->next = head;
	*p = temp;
	nodes++;
}


void LE::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->data << " ";
	}
	cout << endl;
}

void LE::sorting(node* inicio, node* fin) {
	while (inicio != fin) {
		node* ite = inicio;
		while (ite != fin) {
			if (inicio->data > ite->data) {
				swap(inicio->data, ite->data);
			}
			else {
				ite = ite->next;
			}
		}
		inicio = inicio->next;
	}
}


void LE::sort() {
	if (head == nullptr) {
		return;
	}
	int n_threads = thread::hardware_concurrency();
	int suma_pos = nodes / n_threads;
	vector<thread> vec;
	while (n_threads > 0) {

		node* inicio = head;
		node* fin = head;
		for (int i = 0; i < n_threads; i++) {
			for (int c = 0; c < suma_pos && fin != nullptr; c++, fin = fin->next);
			vec.push_back(thread([this, inicio, fin]() {
				sorting(inicio, fin); }));
			inicio = fin;
		}

		for (int i = 0; i < vec.size(); i++) {
			vec[i].join();
		}

		n_threads = n_threads / 2;

		if (n_threads != 0) {
			suma_pos = nodes / n_threads;
		}

		vec.clear();
	}
}


int main() {
	LE l;
	int arr[70] = {
	34, 7, 23, 32, 5, 62, 45, 12, 18, 39,
	28, 54, 76, 1, 88, 56, 91, 0, 67, 73,
	21, 99, 48, 26, 36, 82, 19, 58, 90, 11,
	14, 77, 84, 64, 13, 50, 30, 92, 43, 71,
	25, 8, 96, 15, 57, 22, 70, 86, 33, 40,
	3, 65, 60, 41, 74, 17, 97, 42, 20, 59,
	27, 75, 49, 66, 83, 2, 46, 87, 38, 4
	};

	for (int i = 0; i < 70; i++) {
		l.push(arr[i]);
	}

	l.print();

	l.sort();

	l.print();

}

