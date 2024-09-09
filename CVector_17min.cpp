#include <iostream>
using namespace std;

class CVector {
public:
	int tam = 5;
	void push_back(int v);
	void push_front(int v);
	void pop_back();
	void pop_front();
	void print();
	int& operator[](int v);
private:
	void expand(int newtam);
	void colapse(int newtam);
	int elements = 0;
	int* arr = new int[tam];

};


void CVector::expand(int newtam) {
	int* arrnew = new int[newtam];
	for (int i = 0; i < tam; i++) {
		arrnew[i] = arr[i];
	}
	tam = newtam;
	int* temp = arr;
	arr = arrnew;
	delete temp;
}

void CVector::colapse(int newtam) {
	int* arrnew = new int[newtam];
	for (int i = 0; i < tam; i++) {
		arrnew[i] = arr[i];
	}
	tam = newtam;
	int* temp = arr;
	arr = arrnew;
	delete temp;
}


void CVector::push_back(int v) {
	if (elements == tam) {
		expand(tam * 2);
	}
	arr[elements] = v;
	elements++;
}

void CVector::push_front(int v) {
	if (elements == tam) {
		expand(tam * 2);
	}

	for (int i = elements; i > 0; i--) {
		arr[i] = arr[i-1];
	}
	arr[0] = v;
	elements++;
}

void CVector::pop_back() {
	if (elements == 0) {
		return;
	}
	else if (elements == tam / 2) {
		colapse(tam / 2);
	}
	elements--;
}

void CVector::pop_front() {
	if (elements == 0) {
		return;
	}
	else if (elements == tam / 2) {
		colapse(tam / 2);
	}

	for (int i = 0; i < elements; i++) {
		arr[i] = arr[i + 1];
	}
	elements--;
}

int& CVector:: operator[](int v) {
	return arr[v];
}


void CVector::print() {
	for (int i = 0; i < elements; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	CVector vec;
	vec.push_back(8);
	vec.push_back(4);
	vec.push_back(1);
	vec.push_back(2);
	vec.push_back(3);
	vec.print();

	vec.push_front(12);
	vec.push_front(34);
	vec.push_front(13);
	vec.push_front(5);
	vec.print();

	vec.pop_back();
	vec.print();
	vec.pop_front();
	vec.print();

	for (int i = 0; i < 3; i++) {
		cout << vec[i] << endl;
	}



}
