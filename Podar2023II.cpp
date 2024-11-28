// BinTree.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <vector>

using namespace std;

// Nodo del Arbol 
class Node
{
public:
	int key;
	Node* left;
	Node* right;
	int height;
};

//Calcula la altura del arbol 
int height(Node* N)
{
	if (N == NULL)
		return 0;
	return N->height;
}

//maximo de 2 enteros
int max(int a, int b)
{
	return (a > b) ? a : b;
}

//Crea nuevo nodo
Node* newNode(int key)
{
	Node* node = new Node();
	node->key = key;
	node->left = NULL;
	node->right = NULL;
	node->height = 1; // nuevo nodo 
	// añadido como hoja
	return(node);
}


// Otiene el factor de balance de N 
int getBalance(Node* N)
{
	if (N == NULL)
		return 0;
	return height(N->left) - height(N->right);
}

// Función recursiva que inserta la clave
// en el subarbol con raiz en node y 
// devuelve la nueva raiz del subarbol 
Node* insert(Node* node, int key)
{
	/* 1. Insersión normal en un arbol */
	if (node == NULL)
		return(newNode(key));

	if (key < node->key)
		node->left = insert(node->left, key);
	else if (key > node->key)
		node->right = insert(node->right, key);
	else // no permite valores duplicados 
		return node;

	/* 2. Actualiza la altura desde el ancestro */
	node->height = 1 + max(height(node->left),
		height(node->right));

	return node;
}


//Impresion de arbol en Pre Orden
void preOrder(Node* root)
{
	if (root != NULL)
	{
		cout << root->key << " H: " << root->height << " B: " << getBalance(root) << " HL(" << ((root->left) ? root->left->key : 0) << "): " << height(root->left) << " HR(" << ((root->right) ? root->right->key : 0) << "): " << height(root->right) << endl;
		preOrder(root->left);
		preOrder(root->right);
	}
}



void hojasmasprofundas(Node* root, vector<pair<Node**, int>>& hojasP, int& mayorprofu, Node** raiz) {
	if (root != nullptr) {
		if (root->left == nullptr && root->right == nullptr) {
			Node** temp = raiz;
			int i = 0;

			while (*raiz != root) {
				if ((*raiz)->key < root->key) {
					raiz = &((*raiz)->right);
				}
				else {
					raiz = &((*raiz)->left);
				}
				i++;
			}

			if (i >= mayorprofu) {
				mayorprofu = i;
			}
			hojasP.push_back(make_pair(raiz, i));
			raiz = temp;
		}
		hojasmasprofundas(root->left, hojasP, mayorprofu, raiz);
		hojasmasprofundas(root->right, hojasP, mayorprofu, raiz);
	}
}


void Podar(Node* root){
	vector<pair<Node**, int>> hojasp;
	int mayorprofu;
	Node** raiz = &root;
	hojasmasprofundas(root, hojasp, mayorprofu, raiz);

	vector<Node*> cam;

	for (int i = 0; i < hojasp.size(); i++) {
		if (mayorprofu == hojasp[i].second) {

			Node* bal = root;

			Node* temp = *hojasp[i].first;

			while (bal != temp) {
				cam.push_back(bal);
				if (bal->key < temp->key) {
					bal = bal->right;
				}
				else {
					bal = bal->left;
				}
			}
			*hojasp[i].first = nullptr;
			delete temp;

			while (!cam.empty()) {
				cam.back()->height = 1 + max(height(cam.back()->left), height(cam.back()->right));
				cam.pop_back();
			}
		}
	}

}

int main()
{
	Node* root = NULL;
	int A[] = { 50,30,80,20,40,60,90,10,25,5,15,28,38,53,65,85,95 };
	int n = sizeof(A) / sizeof(int);


	for (int i = 0; i < n; i++)
	{
		root = insert(root, A[i]);
	}


	cout << "Recorrido preorden del arbol contruido \n";
	preOrder(root);

	Podar(root);

	cout << "\n \n Recorrido preorden del arbol podado \n";
	preOrder(root);


	return 0;
}

