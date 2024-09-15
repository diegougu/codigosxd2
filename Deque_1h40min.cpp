#include <iostream>
using namespace  std;

class Deque {
private:
	int map_tam;
	int arr_tam;
	int** map = new int* [map_tam];
	int** inicio_mapa = map + (map_tam / 2);
	int** fin_mapa = map + (map_tam / 2);
	int* inicio_arr = nullptr;
	int* fin_arr = nullptr;
	int elementos = 0;
	int arr_count = 0;
	void ExpandOrColapse(int newmap_tam);
public:
	void push_back(int v);
	void push_front(int v);
	void pop_back();
	void pop_front();
	int& operator[](int v);
	void print();
	Deque(int m_t, int a_t) : map_tam(m_t), arr_tam(a_t) {}

};

void Deque::ExpandOrColapse(int newmapa_tam) {
	int** newmap = new int* [newmapa_tam];
	int** ite = inicio_mapa;
	int** ite_newmap = newmap + (newmapa_tam / 2) -1;
	while (ite <= fin_mapa) {
		if (ite == inicio_mapa) {
			inicio_mapa = ite_newmap;
		}
		if (ite == fin_mapa) {
			fin_mapa = ite_newmap;
			*ite_newmap = *ite;
			break;
		}
		*ite_newmap = *ite;
		ite++;
		ite_newmap++;
	}
	int** temp = map;
	map_tam = newmapa_tam;
	map = newmap;
	delete[]temp;
}

void Deque::push_back(int v) {
	if (inicio_arr == nullptr && fin_arr == nullptr) {
		*fin_mapa = new int[arr_tam];
		inicio_arr = *fin_mapa + (arr_tam / 2);
		fin_arr = *fin_mapa + (arr_tam / 2);
		*fin_arr = v;
		elementos++;
		arr_count++;
	}
	else if (fin_arr == *fin_mapa + arr_tam-1 && fin_mapa != map + (map_tam - 1)) {
		fin_mapa++;
		*fin_mapa = new int[arr_tam];
		fin_arr = *fin_mapa;
		*fin_arr = v;
		elementos++;
		arr_count++;
	}
	else if (fin_arr == *fin_mapa + arr_tam-1 && fin_mapa == map + (map_tam - 1)) {
		ExpandOrColapse(map_tam * 2);
		fin_mapa++;
		*fin_mapa = new int[arr_tam];
		fin_arr = *fin_mapa;
		*fin_arr = v;
		elementos++;
		arr_count++;
	}
	else {
		fin_arr++;
		*fin_arr = v;
		elementos++;
	}
}

void Deque::push_front(int v) {
	if (inicio_arr == nullptr && fin_arr == nullptr) {
		*inicio_mapa = new int[arr_tam];
		inicio_arr = *inicio_mapa + (arr_tam / 2);
		fin_arr = *inicio_mapa + (arr_tam / 2);
		*inicio_arr = v;
		elementos++;
		arr_count++;
	}
	else if (inicio_arr == *inicio_mapa && inicio_mapa != map) {
		inicio_mapa--;
		*inicio_mapa = new int[arr_tam];
		inicio_arr = *inicio_mapa + (arr_tam - 1);
		*inicio_arr = v;
		elementos++;
		arr_count++;
	}
	else if (inicio_arr == *inicio_mapa && inicio_mapa == map) {
		ExpandOrColapse(map_tam * 2);
		inicio_mapa--;
		*inicio_mapa = new int[arr_tam];
		inicio_arr = *inicio_mapa + (arr_tam - 1);
		*inicio_arr = v;
		elementos++;
		arr_count;
	}
	else {
		inicio_arr--;
		*inicio_arr = v;
		elementos++;
	}
}


void Deque::pop_back() {
	if (inicio_arr == nullptr && fin_arr == nullptr) {
		return;
	}
	else if (elementos == 1 && arr_count == 1) {
		int* temp = *fin_mapa;
		fin_arr = nullptr;
		inicio_arr = nullptr;
		elementos--;
		arr_count--;
		delete temp;
	}
	else if (fin_arr == *fin_mapa && arr_count >= map_tam / 2) {
		int* temp = *fin_mapa;
		fin_mapa--;
		fin_arr = *fin_mapa + (map_tam - 1);
		elementos--;
		arr_count--;
		delete temp;
	}
	else if (fin_arr == *fin_mapa && arr_count == map_tam / 2) {
		ExpandOrColapse(map_tam / 2);
		int* temp = *fin_mapa;
		fin_mapa--;
		fin_arr = *fin_mapa + (map_tam - 1);
		elementos--;
		arr_count--;
		delete temp;
	}
	else {
		fin_arr--;
		elementos--;
	}
}

void Deque::pop_front() {
	if (inicio_arr == nullptr && fin_arr == nullptr) {
		return;
	}
	else if (inicio_arr == *inicio_mapa + (arr_tam - 1) && arr_count > map_tam / 2) {
		int* temp = *inicio_mapa;
		inicio_mapa++;
		inicio_arr = *inicio_mapa;
		elementos--;
		arr_count--;
		delete temp;
	}
	else if (inicio_arr == *inicio_mapa + (arr_tam - 1) && arr_count == map_tam / 2) {
		ExpandOrColapse(map_tam / 2);
		int* temp = *inicio_mapa;
		inicio_mapa++;
		inicio_arr = *inicio_mapa;
		elementos--;
		arr_count--;
		delete temp;
	}
	else {
		inicio_arr++;
		elementos--;
	}
}

void Deque::print() {
	int** temp_ini = inicio_mapa	;
	int* ini_array_temp = inicio_arr;
	while (temp_ini <= fin_mapa) {
		cout << "[ ";
		while (ini_array_temp <= *temp_ini + arr_tam - 1) {
			cout << *ini_array_temp << " ";
			if (ini_array_temp == fin_arr) {
				break;
			}
			ini_array_temp++;
		}
		cout << " ] ";
		temp_ini++;
		ini_array_temp = *temp_ini;
	}
	cout << endl;
}

int& Deque::operator[](int v) {
	if (v > elementos) {
		int dirreccion_random = 0;
		return dirreccion_random;
	}
	int vacios = (*inicio_mapa - inicio_arr) + (fin_arr - *fin_mapa + map_tam - 1);
	int pos = v % arr_tam;

}


int main() {
	Deque d(3, 5);
	d.push_front(5);
	d.push_back(6);
	d.push_back(7);
	d.push_back(8);
	d.push_back(9);
	d.push_back(10);
	d.push_back(11);
	d.push_back(12);
	d.push_back(13);
	d.push_back(14);
	d.push_front(4);
	d.push_front(3);
	d.push_front(2);
	d.push_front(1);
	d.print();

	d.pop_back();
	d.print();
	d.pop_back();
	d.print();

	d.pop_front();
	d.print();
	d.pop_front();
	d.print();
}

