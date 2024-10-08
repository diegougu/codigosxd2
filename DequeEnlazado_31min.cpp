#include <iostream>
using namespace std;

template <class T>
struct arrnode {
	const static int tam = 5;
	T arr[tam];
	arrnode<T>* next = nullptr;
	arrnode<T>* prev = nullptr;
	arrnode(arrnode<T>* n = nullptr, arrnode<T>* p = nullptr) : next(n), prev(p) {}
};

template <class T>
class LinkedDeque {
private:
	arrnode<T>* head = nullptr;
	T* front_arr = nullptr;
	T* back_arr = nullptr;
	int elementos = 0;
public:
	void push_back(T v);
	void push_front(T v);
	void pop_back();
	void pop_front();
	T& operator[](int v);
	void print();
};

template <class T>
void LinkedDeque<T>::push_back(T v) {
	if (head == nullptr) {
		arrnode<T>* temp = new arrnode<T>;
		head = temp;
		front_arr = head->arr + (head->tam / 2);
		back_arr = head->arr + (head->tam / 2);
		*back_arr = v;
		elementos++;
	}
	else {
		arrnode<T>* u = head;
		while (u->next != nullptr) {
			u = u->next;
		}
		if (back_arr == u->arr + u->tam - 1) {
			arrnode<T>* temp = new arrnode<T>;
			u->next = temp;
			temp->prev = u;
			u = u->next;
			back_arr = u->arr;
			*back_arr = v;
			elementos++;
		}
		else {
			back_arr++;
			*back_arr = v;
			elementos++;
		}
	}
}

template <class T>
void LinkedDeque<T>::push_front(T v) {
	if (head == nullptr) {
		arrnode<T>* temp = new arrnode<T>;
		head = temp;
		front_arr = head->arr + (head->tam / 2);
		back_arr = head->arr + (head->tam / 2);
		*front_arr = v;
		elementos++;
	}
	else {
		arrnode<T>* f = head;
		while (f->prev != nullptr) {
			f = f->prev;
		}
		if (front_arr == f->arr) {
			arrnode<T>* temp = new arrnode<T>;
			temp->next = f;
			f->prev = temp;
			f = f->prev;
			front_arr = f->arr + f->tam - 1;
			*front_arr = v;
			elementos++;
		}
		else {
			front_arr--;
			*front_arr = v;
			elementos++;
		}
	}
}


template <class T>
void LinkedDeque<T>::pop_back() {
	if (head == nullptr || (back_arr == head->arr + (head->tam / 2) && front_arr != head->arr + (head->tam / 2))) {
		return;
	}
	else if (back_arr == head->arr + (head->tam / 2) && front_arr == head->arr + (head->tam / 2)) {
		arrnode<T>* temp = head;
		head = nullptr;
		front_arr = nullptr;
		back_arr = nullptr;
		elementos--;
		delete temp;
	}
	else {
		arrnode<T>* u = head;
		while (u->next != nullptr) {
			u = u->next;
		}
		if (back_arr == u->arr) {
			arrnode<T>* temp = u;
			u = u->prev;
			back_arr = u->arr + u->tam - 1;
			u->next = nullptr;
			delete temp;
			elementos--;
		}
		else {
			back_arr--;
			elementos--;
		}
	}
}

template <class T>
void LinkedDeque<T>::pop_front() {
	if (head == nullptr || (front_arr == head->arr + (head->tam / 2) && back_arr != head->arr + (head->tam / 2))) {
		return;
	}
	else if (front_arr == head->arr + (head->tam / 2) && back_arr == head->arr + (head->tam / 2)) {
		arrnode<T>* temp = head;
		head = nullptr;
		front_arr = nullptr;
		back_arr = nullptr;
		elementos--;
		delete temp;
	}
	else {
		arrnode<T>* f = head;
		while (f->prev != nullptr) {
			f = f->prev;
		}

		if (front_arr == f->arr + f->tam - 1) {
			arrnode<T>* temp = f;
			f = f->next;
			front_arr = f->arr;
			f->prev = nullptr;
			elementos--;
			delete temp;
		}
		else {
			front_arr++;
			elementos--;
		}

	}
}

template <class T>
T& LinkedDeque<T>::operator[](int v) {
	if (v >= elementos) {
		static T a;
		return a;
	}
	
	arrnode<T>* f = head;
	int c = 0;
	while (f->prev != nullptr) {
		f = f->prev;
	}
	T* i = front_arr;

	while (f->next != nullptr) {
		while (i <= f->arr + f->tam - 1 && i <= back_arr) {
			if (c == v) {
				return *i;
			}
			i++;
			c++;
		}
		f = f->next;
		i = f->arr;
	}
}

template <class T>
void LinkedDeque<T>::print() {
	arrnode<T>* p_a = head;
	while (p_a->prev != nullptr) {
		p_a = p_a->prev;
	}

	T* i = front_arr;
	arrnode<T>* p = p_a;

	while (p != nullptr) {
		cout << "[ ";
		while (i < p->arr + p->tam) {
			cout << *i << " ";
			if (i == back_arr) {
				cout << " ]->";
				cout << endl;
				return;
			}
			i++;
		}
		cout << " ] ";
		p = p->next;
		if (p != nullptr) {
			i = p->arr;
		}
	}

}

int main() {
	LinkedDeque<int> deq;
	int arr[5] = { 1,2,3,4,5 };
	int arr2[5] = { 6,7,8,9,10 };

	for (int i = 0; i < 5; i++) {
		deq.push_back(arr[i]);
	}

	for (int i = 0; i < 5; i++) {
		deq.push_front(arr2[i]);
	}


	deq.print();

	deq.pop_back();
	deq.pop_back();
	deq.pop_front();
	deq.pop_back();
	deq.pop_front();
	deq.pop_front();
	deq.print();

	int a = deq[3];
	cout << a << endl;
	deq[3] = 99;
	deq.print();
}
