#include <iostream>
using namespace std;

void convertMaxHeap(int* arr, int sizen) {
	int rec = sizen - 1;
	while (rec >= 0) {
		int pos = rec;
		bool ch = true;
		while (ch == true) {
			int move = 0;
			if (pos % 2 == 0) {
				move = pos / 2 - 1;
			}
			else {
				move = pos / 2;
			}

			if (move >= 0 && pos >= 0 && *(arr + pos) > *(arr + move)) {
				swap(*(arr + pos), *(arr + move));
				pos = move;
			}
			else {
				ch = false;
			}

		}
		rec--;
	}
}


int main() {
	int arr[10] = { 3, 5, 9, 6, 8, 20, 10, 12, 18, 9 };

	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;

	convertMaxHeap(arr, 10);

	for (int i = 0; i < 10; i++) {
		cout << arr[i] << " ";
	}
	
}
