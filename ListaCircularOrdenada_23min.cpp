#include <iostream>

using namespace std;

class node
{
public:
    int data;
    node* next;
    node(int d, node* n = nullptr) : data(d), next(n) {}
};

class CircularLinkedList{
    node* head = NULL;
public:
    void add(int value)
    {
        if (head == nullptr) {
            node* temp = new node(value);
            head = temp;
            head->next = head;
        }
        else if (head != nullptr && head->data > value) {
            node* temp = new node(value);
            node* p = head;
            do {
                p = p->next;
            } while (p->next != head);
            temp->next = head;
            p->next = temp;
            head = temp;
        }
        else {
            node* p = head;
            node* temp = new node(value);
            do {
                p = p->next;
            } while (p->next != head && p->data < value);

            if (p->next == head && value > p->data) {
                p->next = temp;
                temp->next = head;
            }
            else {
                node* q = head;
                while (q->next != p) {
                    q = q->next;
                }
                q->next = temp;
                temp->next = p;
            }

        }


    }

    void del(int value)
    {
        if (head == nullptr) {
            return;
        }
        else if (head->data == value && head->next != head) {
            node* temp = head;
            node* ult = head;
            do {
                ult = ult->next;
            } while (ult->next != head);
            head = head->next;
            ult->next = head;
            delete temp;
        }
        else if (head->data == value && head->next == head) {
            node* temp = head;
            head = nullptr;
            delete temp;
        }
        else {
            node* p = head;
            do {
                p = p->next;
            } while (p->next != head && p->data != value);

            node* q = head;
            while (q->next != p) {
                q = q->next;
            }

            if (p->next == head) {
                q->next = head;
                delete p;
            }
            else {
                q->next = p->next;
                delete p;
            }
        }
    }

    void print()
    {
        int cont = 0;
        node* ptr = head;
        cout << "head->";
        while (head && cont < 1)
        {
            cout << ptr->data << " -> ";
            ptr = ptr->next;
            if (ptr == head) cont++;
        }
        if (head) cout << ptr->data;
        cout << " <- head \n ";

    }
};

int main()
{
    int ADD[10] = { 2,4,6,8,10,1,3,5,7,9 };
    int DEL[10] = { 9,7,5,3,1,10,8,6,4,2 };
    CircularLinkedList CLL;
    for (int i = 0; i < 10; i++)
    {
        cout << "ADD " << ADD[i] << endl;
        CLL.add(ADD[i]);
        CLL.print();
    }

    for (int i = 0; i < 10; i++)
    {
        cout << "DEL " << DEL[i] << endl;
        CLL.del(DEL[i]);
        CLL.print();
    }
}
