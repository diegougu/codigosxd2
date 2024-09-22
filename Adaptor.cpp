#include <iostream>
using namespace std;

class CVector {
public:
	int tam = 5;
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
	if (v > elementos) {
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

struct node {
	int valor;
	node* next;
	node* prev;
	node(int v, node* n = nullptr, node* p = nullptr) : valor(v), next(n), prev(p) {}
};

class CList {
private:
	node* head = nullptr;
	node* tail = nullptr;
public:
	void push_back(int v);
	void push_front(int v);
	void pop_back();
	void pop_front();
	node* operator[](int v);
	void print();
};


void CList::push_back(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		tail->next = temp;
		temp->prev = tail;
		tail = tail->next;
	}

}

void CList::push_front(int v) {
	node* temp = new node(v);
	if (head == nullptr) {
		head = temp;
		tail = temp;
	}
	else {
		temp->next = head;
		head->prev = temp;
		head = temp;
	}
}

void CList::pop_front() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		node* temp = head;
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		node* temp = head;
		head = head->next;
		head->prev = nullptr;
		delete temp;
	}
}

void CList::pop_back() {
	if (head == nullptr) {
		return;
	}
	else if (head->next == nullptr) {
		node* temp = head;
		head = nullptr;
		tail = nullptr;
		delete temp;
	}
	else {
		node* temp = tail;
		tail = tail->prev;
		tail->next = nullptr;
		delete temp;
	}
}

node* CList::operator[](int v) {
	node* p = head;
	int c = v;
	while (p && c < v) {
		p = p->next;
		c++;
	}
	return p;
}


void CList::print() {
	for (node* p = head; p; p = p->next) {
		cout << p->valor << " ";
	}
	cout << endl;
}

class Deque {
private:
	int map_tam = 3;
	int arr_tam = 5;
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

};

void Deque::ExpandOrColapse(int newmapa_tam) {
	int** newmap = new int* [newmapa_tam];
	int** ite = inicio_mapa;
	int** ite_newmap = newmap + (newmapa_tam / 2) - 1;
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
	else if (fin_arr == *fin_mapa + arr_tam - 1 && fin_mapa != map + (map_tam - 1)) {
		fin_mapa++;
		*fin_mapa = new int[arr_tam];
		fin_arr = *fin_mapa;
		*fin_arr = v;
		elementos++;
		arr_count++;
	}
	else if (fin_arr == *fin_mapa + arr_tam - 1 && fin_mapa == map + (map_tam - 1)) {
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
	int** temp_ini = inicio_mapa;
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
		int random = 0;
		return random;
	}
	int espacios_vacios = inicio_arr - *inicio_mapa;
	int pos_mapa = v / 5;
	int pos_arr = (v % 5) + espacios_vacios;

	int** m_pos = inicio_mapa + pos_mapa;
	int* a_pos = *m_pos + pos_arr;
	return *a_pos;
}


template<class K>
struct CStack {
	K ctnr;
	void push(int val) {
		ctnr.push_back(val);
	}
	void pop() {
		ctnr.pop_back();
	}
	void print() {
		ctnr.print();
	}
};

template<class K>
struct CQueue {
	K ctnr;
	void push(int val) {
		ctnr.push_front(val);
	}
	void pop() {
		ctnr.pop_front();
	}
	void print() {
		ctnr.print();
	}
};

int main() {
	CStack<CVector> d;
	d.push(3);
	d.push(2);
	d.push(1);
	d.push(5);
	d.push(4);
	d.print();

	CQueue<Deque> d2;
	d2.push(3);
	d2.push(2);
	d2.push(1);
	d2.push(5);
	d2.push(4);
	d2.print();

}
