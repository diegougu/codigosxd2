#include <iostream>
using namespace std;

template <class T>
struct arrnode {
	T arr[5];
	T* top = arr;
	arrnode<T>* next = nullptr;
};

template <class T>
class LinkedArray {
private:
	arrnode<T>* head = nullptr;
	arrnode<T>* tail = nullptr;
	bool find(arrnode<T>*& pos, T*& pos_arr, T v);
public:
	void add(T v);
	void del(T v);
	void print();
};

template <class T>
bool LinkedArray<T>::find(arrnode<T>*& pos, T*& pos_arr, T v) {
	while (pos != nullptr) {
		while (pos_arr <= pos->top) {
			if (*pos_arr >= v) {
				return true;
			}
			pos_arr++;
		}
		pos = pos->next;
		if (pos != nullptr) {
			pos_arr = pos->arr;
		}
	}
	return false;
}


template <class T>
void LinkedArray<T>::add(T v) {
	if (head == nullptr) {
		arrnode<T>* temp = new arrnode<T>;
		head = temp;
		tail = temp;
		*tail->top = v;
	}
	else if (v > *tail->top && tail->top != tail->arr + 4) {
		tail->top++;
		*tail->top = v;
	}
	else if (v > *tail->top && tail->top == tail->arr + 4) {
		arrnode<T>* temp = new arrnode<T>;
		tail->next = temp;
		tail = tail->next;
		*tail->top = v;
	}
	else {
		arrnode<T>* pos = head;
		T* pos_arr = pos->arr;

		if (find(pos, pos_arr, v)) {
			T temp1 = *pos_arr;
			*pos_arr = v;
			T temp2 = temp1;
			*pos_arr++;

			while (pos != nullptr) {
				while (pos_arr <= pos->top) {
					temp2 = *pos_arr;
					*pos_arr = temp1;
					temp1 = temp2;
					pos_arr++;
				}

				pos = pos->next;
				if (pos != nullptr) {
					pos_arr = pos->arr;
				}
			}
			if (tail->top != tail->arr + 4) {
				tail->top++;
				*tail->top = temp1;
			}
			else {
				arrnode<T>* temp = new arrnode<T>;
				tail->next = temp;
				tail = tail->next;
				*tail->top = temp1;
			}
		}

	}
}


template <class T>
void LinkedArray<T>::del(T v) {
	if (head == nullptr) {
		return;
	}
	else if (*tail->top == v && tail->top != tail->arr) {
		tail->top--;
	}
	else if (*tail->top == v && tail->top == tail->arr) {
		arrnode<T>* temp = tail;
		arrnode<T>* p = head;
		while (p->next != tail) {
			p = p->next;
		}
		tail = p;
		tail->next = nullptr;
		delete temp;
	}
	else {
		arrnode<T>* pos = head;
		T* pos_arr = pos->arr;
		if (find(pos, pos_arr, v) && *pos_arr == v) {
			while (pos != nullptr) {
				while (pos_arr <= pos->top) {
					if (pos_arr != pos->top) {
						*pos_arr = *(pos_arr + 1);
					}
					else if (pos_arr == pos->top && pos->next != nullptr) {
						T* pos_next_arr = pos->next->arr;
						*pos_arr = *pos_next_arr;
					}
					pos_arr++;
				}
				pos = pos->next;
				if (pos != nullptr) {
					pos_arr = pos->arr;
				}

			}
			if (tail->top != tail->arr) {
				tail->top--;
			}
			else if (tail->top == tail->arr) {
				arrnode<T>* temp = tail;
				arrnode<T>* p = head;
				while (p->next != tail) {
					p = p->next;
				}
				tail = p;
				tail->next = nullptr;
				delete temp;
			}
		}


	}
}

template <class T>
void LinkedArray<T>::print() {
	for (arrnode<T>* p = head; p; p = p->next) {
		cout << "[ ";
		for (T* q = p->arr; q <= p->top; q++) {
			cout << *q << " ";
		}
		cout << " ]->";
	}
	cout << endl;
}

int main() {
	LinkedArray<int> l1;
	int arr[13] = { 3,2,11,6,4,5,7,8,10,9,1,13,12 };
	int del_arr[5] = { 1,13,6,4,10 };

	for (int i = 0; i < 13; i++) {
		l1.add(arr[i]);
	}
	l1.print();

	for (int i = 0; i < 5; i++) {
		l1.del(del_arr[i]);
		l1.print();
	}

	l1.del(1);
	l1.print();
}
