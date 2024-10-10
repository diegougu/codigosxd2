#include <iostream>	
using namespace std;

template <class T>
struct arrnode {
	const static int tam = 5;
	T arr[tam];
	T* top = arr;
	arrnode<T>* next = nullptr;
};

template<class T>
class PilaArray {
private:
	arrnode<T>* head = nullptr;
public:
	void push(T v);
	bool pop(T& v);
	void print();
};

template <class T>
void PilaArray<T>::push(T v) {
	if (head == nullptr) {
		arrnode<T>* temp = new arrnode<T>;
		head = temp;
		*head->arr = v;
	}
	else {
		arrnode<T>* p = head;
		T* pa = p->arr;

		T temp1 = *pa;
		T temp2 = *pa;
		*pa = v;
		pa++;
		while (p != nullptr) {
			while (pa <= p->top) {
				temp1 = *pa;
				*pa = temp2;
				temp2 = temp1;
				pa++;
			}
			p = p->next;
			if (p != nullptr) {
				pa = p->arr;
			}
		}
		arrnode<T>* u = head;
		while (u->next != nullptr) {
			u = u->next;
		}

		if (u->top != u->arr + u->tam - 1) {
			u->top++;
			*u->top = temp1;
		}
		else {
			arrnode<T>* temp = new arrnode<T>;
			u->next = temp;
			u = u->next;
			*u->top = temp1;
		}
	}
}

template <class T>
bool PilaArray<T>::pop(T& v) {
	if (head == nullptr) {
		return false;
	}
	else if (head->next == nullptr && head->top == head->arr) {
		arrnode<T>* temp = head;
		v = *head->top;
		head = nullptr;
		delete temp;
		return true;
	}
	else {
		v = *head->arr;
		arrnode<T>* p = head;
		T* pa = head->arr;

		while (p != nullptr) {
			while (pa <= p->top) {
				if (pa == p->top && p->next != nullptr) {
					*pa = *p->next->arr;
				}
				else {
					*pa = *(pa + 1);
				}
				pa++;
			}
			p = p->next;
			if (p != nullptr) {
				pa = p->arr;
			}
		}
		arrnode<T>* temp = head;
		arrnode<T>* prev = head;
		while (temp->next != nullptr) {
			prev = temp;
			temp = temp->next;
		}

		if (temp->top == temp->arr) {
			prev->next = nullptr;
			delete temp;
			return true;
		}
		else {
			temp->top--;
			return true;
		}
	}
}

template <class T>
void PilaArray<T>::print() {
	arrnode<T>* p = head;
	while (p != nullptr) {
		T* pa = p->arr;
		cout << "[ ";
		while (pa <= p->top) {
			cout << *pa << " ";
			pa++;
		}
		p = p->next;
		cout << " ]->";
	}
	cout << endl;
}

int main() {
	PilaArray<int> p;
	for (int i = 0; i < 17; i++) {
		p.push(i);
		p.print();
	}

	int v = 0;
	for (int i = 0; i < 9; i++) {
		p.pop(v);
		cout << v << endl;
		p.print();
	}
}
