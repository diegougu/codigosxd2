#include <iostream>
using namespace std;

template <class T>
struct CGreaster {
	inline bool operator()(T a, T b){
		return a > b;
	}
};

template <class T>
struct CLess {
	inline bool operator()(T a, T b) {
		return a < b;
	}
};

class Comparator {
public:
	virtual bool comp(int a, int b) = 0;
};

class CGreaster_Poli : public Comparator {
public:
	bool comp(int a, int b) override { return a > b; }
};

class CLess_Poli : public Comparator{
public:
	bool comp(int a, int b) override { return a < b; }
};


bool FLess(int a, int b) {
	return a < b;
}

bool FGreaster(int a, int b) {
	return a > b;
}

template <class T> 
void sort(int* arr, int n, T k) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (k(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}



void sort2(int* arr, int n, Comparator* p) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (p->comp(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}



void sort3(int* arr, int n, bool (*PF)(int,int)) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n - i - 1; j++) {
			if (PF(arr[j], arr[j + 1])) {
				swap(arr[j], arr[j + 1]);
			}
		}
	}
}

int main() {
	bool (*PF)(int, int);
	PF = &FLess;
	bool (*PF2)(int, int);
	PF2 = &FGreaster;
	CGreaster<int> g;
	CLess<int> l;
	CLess_Poli l2;
	CGreaster_Poli g2;
	
	int arr[10] =  { 3, 2, 4, 5, 1, 7, 8, 10, 9 };
	int arr2[10] = { 8, 10, 4, 3, 5, 7, 1, 9, 2 };
	int arr3[10] = { 1, 5, 7, 3, 10, 9, 2, 8, 4 };
	int arr4[10] = { 9, 4, 3, 2, 7, 8, 10, 1, 5 };
	int arr5[10] = { 7, 2, 9, 4, 1, 8, 3, 10, 5 };
	int arr6[10] = { 6, 1, 9, 4, 8, 3, 2, 10, 5 };


	sort(arr, 10, g);
	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	sort(arr2, 10, l);
	for (int i = 0; i < 10; i++) {
		cout << arr2[i] << " ";
	}
	cout << endl;

	sort2(arr3, 10, &l2);
	for (int i = 0; i < 10; i++) {
		cout << arr3[i] << " ";
	}
	cout << endl;

	sort2(arr4, 10, &g2);
	for (int i = 0; i < 10; i++) {
		cout << arr4[i] << " ";
	}
	cout << endl;

	sort3(arr5, 10, PF);
	for (int i = 0; i < 10; i++) {
		cout << arr5[i] << " ";
	}
	cout << endl;

	sort3(arr6, 10, PF2);
	for (int i = 0; i < 10; i++) {
		cout << arr6[i] << " ";
	}
	cout << endl;
}




