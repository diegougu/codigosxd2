#include <iostream>
using namespace std;

template <class T>
struct arrnode {
	static const int tam = 5;
	T arr[tam];
	T* top = arr;
	arrnode<T>* next = nullptr;
};

template <class T>
class ColaArray {
private:
	arrnode<T>* head = nullptr;
	arrnode<T>* tail = nullptr;
public:
	void push(T v);
	bool pop(T& v);
	void print();
};

template <class T>
void ColaArray<T>::push(T v) {
	if (head == nullptr) {
		arrnode<T>* temp = new arrnode<T>;
		head = temp;
		tail = temp;
		*tail->top = v;
	}
	else if (tail->top == tail->arr + tail->tam - 1) {
		arrnode<T>* temp = new arrnode<T>;
		tail->next = temp;
		tail = tail->next;
		*tail->top = v;
	}
	else {
		tail->top++;
		*tail->top = v;
	}
}

template <class T>
bool ColaArray<T>::pop(T& v) {
	if (head == nullptr) {
		return false;
	}
	else if (head == tail && tail->top == tail->arr) {
		v = *head->arr;
		arrnode<T>* temp = head;
		head = nullptr;
		tail = nullptr;
		delete temp;
		return true;
	}
	else {
		v = *head->arr;
		arrnode<T>* p = head;
		T* pa = p->arr;

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

		if (tail->top != tail->arr) {
			tail->top--;
			return true;
		}
		else {
			arrnode<T>* temp = head;
			while (temp->next != tail) {
				temp = temp->next;
			}
			tail = temp;
			temp = temp->next;
			tail->next = nullptr;
			delete temp;
			return true;
		}

	}
}

template <class T>
void ColaArray<T>::print() {
	for (arrnode<T>* p = head; p; p = p->next) {
		cout << "[ ";
		for (T* pa = p->arr; pa <= p->top; pa++) {
			cout << *pa << " ";
		}
		cout << " ]->";
	}
	cout << endl;
}

int main() {
	ColaArray<int> c;
	for (int i = 0; i <= 27; i++) {
		c.push(i);
		c.print();
	}

	int v = 0;
	for (int i = 0; i <= 11; i++) {
		c.pop(v);
		cout << v << endl;
		c.print();
	}
}
