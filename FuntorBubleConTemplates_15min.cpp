#include <iostream>
using namespace std;

template<class T>
struct ASC{
	bool operator()(T a, T b) {
		return a > b;
	}
};

template<class T>
struct DESC {
	bool operator()(T a, T b) {
		return a < b;
	}
};

template<class T, class O>
struct buble {
	void operator()(T* ini, T* fin) {
		bool sigue = true;
		O op;
		while ((ini < fin) && sigue) {
			sigue = false;
			for (T* p = ini; p < fin; p++) {
				if (op(*p, *(p + 1))) {
					swap(*p, *(p + 1));
					sigue = true;
				}
			}
			fin--;
		}
	}
};


int main() {
	int A[6] = { 6,5,4,3,2,1 };
	float B[6] = { 0.2,1.3,2.4,5.5 };
	char C[6] = { 'a','b','c','d','e','g' };


	buble<int, ASC<int>> x;
	buble<float, DESC<float>> x2;
	buble<char, DESC<char>> x3;



	x(A, A + 5);
	x2(B, B + 5);
	x3(C, C + 5);


	for (int i = 0; i < 6; i++) {
		cout << A[i] << " ";
	}

	cout << endl;

	for (int i = 0; i < 6; i++) {
		cout << B[i] << " ";
	}

	cout << endl;
	
	for (int i = 0; i < 6; i++) {
		cout << C[i] << " ";
	}

}







