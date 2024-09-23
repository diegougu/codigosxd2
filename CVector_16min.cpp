#include <iostream>
using namespace std;

class CVector {
public:
	int tam;
	CVector(int t) : tam(t) {}
	void push_back(int v);
	void push_front(int v);
	void pop_back();
	void pop_front();
	int& operator[](int v);
	void print();
private:
	int elementos = 0;
	int* arr = new int[tam];
	void ExpandOrColapse(int newtam);
};


void CVector::ExpandOrColapse(int newtam) {
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
	if (elementos == tam) {
		ExpandOrColapse(tam * 2);
	}
	arr[elementos] = v;
	elementos++;
}

void CVector::push_front(int v) {
	if (elementos == tam) {
		ExpandOrColapse(tam * 2);
	}
	for (int i = elementos; i > 0; i--) {
		arr[i] = arr[i - 1];
	}
	arr[0] = v;
	elementos++;
}

void CVector::pop_back() {
	if (elementos == tam / 2) {
		ExpandOrColapse(tam / 2);
	}
	elementos--;
}

void CVector::pop_front() {
	if (elementos == tam / 2) {
		ExpandOrColapse(tam / 2);
	}
	for (int i = 0; i < elementos; i++) {
		arr[i] = arr[i + 1];
	}
	elementos--;

}

int& CVector::operator[](int v) {
	if (v >= elementos) {
		cout << "out of range" << endl;
		int direccion_random = 0;
		return direccion_random;
	}
	else {
		return arr[v];
	}
}

void CVector::print() {
	for (int i = 0; i < elementos; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	CVector vec(5);
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

	vec.print();

	for (int i = 0; i < 3; i++) {
		vec[i] = i;
	}

	vec.print();


}
