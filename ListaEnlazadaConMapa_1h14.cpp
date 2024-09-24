#include <iostream>
using namespace std;

template <class T>
struct node {
    T valor;
    node<T>* next = nullptr;
    node(T v, node<T>* n = nullptr) : valor(v), next(n) {}
};

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
class LinkedListWithMap {
private:
    int tam = 5;
    node<T>* head = nullptr;
    node<T>** map = new node<T>*[tam];
    node<T>** fin = nullptr;
    void ExpandOrColapse(int newtam);
public:
    void add(T v);
    void del(T v);
    void print();
    node<T>* operator[](int v);
};

template <class T, class C>
void LinkedListWithMap<T, C>::ExpandOrColapse(int newtam) {
    node<T>** newmapa = new node<T>*[newtam];
    node<T>** i_map = map; 
    node<T>** j_newmap = newmapa;
    for (; i_map <= fin; i_map++, j_newmap++) {
        *j_newmap = *i_map;
    }
    fin = j_newmap - 1;
    node<T>** temp = map;
    map = newmapa;
    tam = newtam;
    delete[]temp;
}

template <class T, class C>
void LinkedListWithMap<T, C>::add(T v) {
    C comp;
    node<T>* temp = new node<T>(v);
    if (head == nullptr) {
        head = temp;
        fin = map;
        *fin = head;
    }
    else if (!comp(v, head->valor)) {
        if (fin == map + tam - 1) {
            ExpandOrColapse(tam * 2);
        }
        temp->next = head;
        head = temp;

        node<T>* ite_list = head;
        node<T>** ite_map = map;
        fin++;
        while (ite_list != nullptr && ite_map <= fin) {
            *ite_map = ite_list;       
            ite_map++;
            ite_list = ite_list->next;
        }
    }
    else if (comp(v, (*fin)->valor)) {
        if (fin == map + tam - 1) {
            ExpandOrColapse(tam * 2);
        }
        (*fin)->next = temp;
        fin++;
        *fin = temp;
    }
    else {
        node<T>* p = head;
        node<T>* q = head;

        while (p->next != nullptr && comp(v, p->valor)) {
            q = p;
            p = p->next;
        }
        q->next = temp;
        temp->next = p;

        node<T>* ite_list = head;
        node<T>** ite_map = map;
        fin++;
        while (ite_list != nullptr && ite_map <= fin) {
            *ite_map = ite_list;
            ite_map++;
            ite_list = ite_list->next;
        }

    }
}

template <class T, class C>
void LinkedListWithMap<T, C>::print() {
    cout << "print en LE: " << endl;

    for (node<T>* p = head; p; p = p->next) {
        cout << p->valor << " ";
    }
    cout << "print en MAPA: " << endl;

    for (node<T>** p = map; p <= fin; p++) {
        cout << (*p)->valor << " ";
    }
    cout << endl;

}

template <class T, class C>
void LinkedListWithMap<T, C>::del(T v) {
    if (head == nullptr) {
        return;
    }
    else if (v == head->valor && head->next == nullptr) {
        node<T>* temp = head;
        head = nullptr;
        fin = nullptr;
        delete temp;
    }
    else if (v == head->valor) {
        if (fin < map + (tam / 2)) {
            ExpandOrColapse(tam / 2);
        }
        node<T>* temp = head;
        head = head->next;
        delete temp;

        node<T>* ite_list = head;
        node<T>** ite_map = map;
        fin--;
        while (ite_list != nullptr && ite_map <= fin) {
            *ite_map = ite_list;
            ite_map++;
            ite_list = ite_list->next;
        }
    }
    else if (v == (*fin)->valor) {
        if (fin < map + (tam / 2)) {
            ExpandOrColapse(tam / 2);
        }
        node<T>* temp = *fin;
        fin--;
        (*fin)->next = nullptr;
        delete temp;
    }
    else {
        node<T>* temp = head;
        node<T>* pos = head;
        while (temp != nullptr && temp->valor != v) {
            pos = temp;
            temp = temp->next;
        }

        if (temp == nullptr) {
            return;
        }

        pos->next = temp->next;
        delete temp;
        
        node<T>* ite_list = head;
        node<T>** ite_map = map;
        fin--;
        while (ite_list != nullptr && ite_map <= fin) {
            *ite_map = ite_list;
            ite_map++;
            ite_list = ite_list->next;
        }
    }
}

template <class T, class C>
node<T>* LinkedListWithMap<T, C>::operator[](int v) {
    if (map + v > fin) {
        static node<T> x(5);
        return &x;
    }
    node<T>* a = *(map + v);
    return a;
}


int main(){
    LinkedListWithMap<int, ASC<int>> l1;
    int arr[13] = { 2,1,4,6,5,7,8,3,10,9,13,12,11 };
    for (int i = 0; i < 13; i++) {
        l1.add(arr[i]);
    }

    node<int>* p = l1[3];
    p->valor = 39;


    l1.print();

    int arr2[13] = {11,12,13,9,10,1,2,3,8,7,6,4,5};
    for (int i = 0; i < 13; i++) {
        l1.del(arr2[i]);
        l1.print();
    }
}
