#include <iostream>
#include <vector>

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

template <class T, class C>
class PriorityQueue {
private:
	vector<T> vec;
public:
	void push(T v);
	void pop();
	void print();
};


template <class T, class C>
void PriorityQueue<T, C>::push(T v) {
	if (vec.empty()) {
		vec.push_back(v);
	}
	else {
		vec.push_back(v);
		int i = vec.size() - 1;
		int j = 0;
		C comp;
		bool c = true;
		while (c == true)  {
			if (i % 2 != 0) {
				j = i / 2;
			}
			else if (i % 2 == 0) {
				j = (i / 2) - 1;
			}

			if (j >= 0 && comp(vec[i], vec[j])) {
				swap(vec[i], vec[j]);
				i = j;
			}
			else {
				c = false;
			}
		}
	}
}

template <class T, class C>
void PriorityQueue<T, C>::pop() {
	if (vec.empty()) {
		return;
	}
	else if (vec.size() == 1) {
		vec.pop_back();
	}
	else {
		swap(vec.front(), vec.back());
		vec.pop_back();

		bool c = true;
		int i = 0;
		int n1 = 0;
		int n2 = 0;
		C comp;

		while (c == true) {
			n1 = (i + 1) * 2 - 1;
			n2 = (i + 1) * 2;

			if (n1 <= vec.size() - 1 && n2 <= vec.size() - 1 && comp(vec[n1], vec[n2])) {
				swap(vec[i], vec[n1]);
				i = n1;
			}
			else if (n1 <= vec.size() - 1 && n2 <= vec.size() - 1 && comp(vec[n2], vec[n1])) {
				swap(vec[i], vec[n2]);
				i = n2;
			}
			else {
				c = false;
			}

		}
	}
}

template <class T, class C>
void PriorityQueue<T, C>::print() {
	for (int i = 0; i < vec.size(); i++) {
		cout << vec[i] << " ";
	}
	cout << endl;
}


int main() {
	PriorityQueue<int, ASC<int>> q;

	int array[9] = { 20,10,62,47,72,30,73,19,100 };
	for (int i = 0; i < 9; i++) {
		q.push(array[i]);
		q.print();
	}

	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();
	q.pop();
	q.print();

}

