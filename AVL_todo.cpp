#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

struct CBinNode {
    int value;
    CBinNode* nodes[2];
    int altura;
    CBinNode(int v) {
        value = v;
        nodes[0] = nullptr;
        nodes[1] = nullptr;
    }
};

class AvlTree {
private:
    CBinNode* m_root = nullptr;
    bool m_b = 0;
    bool find(int x, CBinNode**& p, vector<CBinNode*>& rec);
    int calcularaltura(CBinNode* p);
    int diferenciadealtura(CBinNode* p);
    void Avl(vector<CBinNode*>& rec);
    CBinNode** Rep(CBinNode** p);
    void draw(CBinNode* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY);
public:
    bool Remove(int x);
    bool Insert(int x);
    void print(sf::RenderWindow& window);
};

CBinNode** AvlTree::Rep(CBinNode** p) {
    m_b = !m_b; 
    p = &((*p)->nodes[!m_b]); 
    while ((*p)->nodes[m_b]) {
        p = &((*p)->nodes[m_b]); 
    }
    return p;
}



int AvlTree::calcularaltura(CBinNode* p) {
    if (!p) return 0;
    int left = p->nodes[0] ? p->nodes[0]->altura : 0;
    int right = p->nodes[1] ? p->nodes[1]->altura : 0;
    return 1 + max(left, right);
}

int AvlTree::diferenciadealtura(CBinNode* p) {
    int left = p->nodes[0] ? p->nodes[0]->altura : 0;
    int right = p->nodes[1] ? p->nodes[1]->altura : 0;

    return right - left;
}

bool AvlTree::find(int x, CBinNode**& p, vector<CBinNode*>& rec) {
    for (p = &m_root; *p && (*p)->value != x; p = &((*p)->nodes[(*p)->value < x])) {
        if (*p != nullptr) {
            rec.push_back(*p);
        }
    }
    return *p && (*p)->value == x;
}

void AvlTree::Avl(vector<CBinNode*>& rec) {
    int diferenciaActual = 0;
    int diferenciaAnterior = 0;
    int i = rec.size() - 1;
    bool avl = false;

    while (i >= 0 && !avl) {
        diferenciaAnterior = diferenciaActual;
        CBinNode* act = rec[i];
        act->altura = calcularaltura(act);
        diferenciaActual = diferenciadealtura(act);

        if (diferenciaActual == 2 || diferenciaActual == -2) {
            CBinNode* hijo = (diferenciaActual == 2) ? act->nodes[1] : act->nodes[0];
            int dirHijo = (diferenciaActual == 2) ? 1 : 0;

            if (diferenciadealtura(hijo) == dirHijo * 2 - 1) {
                act->nodes[dirHijo] = hijo->nodes[1 - dirHijo];
                hijo->nodes[1 - dirHijo] = act;
                act->altura = calcularaltura(act);
                hijo->altura = calcularaltura(hijo);

                if (i == 0) {
                    m_root = hijo;
                }
                else {
                    CBinNode* padre = rec[i - 1];
                    padre->nodes[padre->nodes[1] == act] = hijo;
                }
            }
            else {
                CBinNode* nieto = hijo->nodes[1 - dirHijo];
                hijo->nodes[1 - dirHijo] = nieto->nodes[dirHijo];
                nieto->nodes[dirHijo] = hijo;
                act->nodes[dirHijo] = nieto->nodes[1 - dirHijo];
                nieto->nodes[1 - dirHijo] = act;

                hijo->altura = calcularaltura(hijo);
                act->altura = calcularaltura(act);
                nieto->altura = calcularaltura(nieto);

                if (i == 0) {
                    m_root = nieto;
                }
                else {
                    CBinNode* padre = rec[i - 1];
                    padre->nodes[padre->nodes[1] == act] = nieto;
                }
            }
            avl = true;
        }
        i--;
    }
}


bool AvlTree::Insert(int x) {
    CBinNode** p;
    vector<CBinNode*> rec;
    if (find(x, p, rec)) {
        return false;
    }
    *p = new CBinNode(x);
    rec.push_back(*p);
    Avl(rec);
    return true;
}

bool AvlTree::Remove(int x) {
    CBinNode** p;
    vector<CBinNode*> rec;
    if (!find(x, p, rec)) {
        return false; 
    }

    CBinNode* target = *p; 

    if (target->nodes[0] == nullptr && target->nodes[1] == nullptr) {
        delete target;
        *p = nullptr;
    }
    else if (target->nodes[0] == nullptr || target->nodes[1] == nullptr) {
        CBinNode* child = (target->nodes[0]) ? target->nodes[0] : target->nodes[1];
        delete target;
        *p = child;
    }
    else {
        CBinNode** successor = Rep(&target); 
        target->value = (*successor)->value; 
        CBinNode* toDelete = *successor;
        *successor = (*successor)->nodes[1]; 
        delete toDelete;
    }

    for (int i = rec.size() - 1; i >= 0; --i) {
        rec[i]->altura = calcularaltura(rec[i]);
        Avl(rec); 
    }

    return true;
}




void AvlTree::draw(CBinNode* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY) {
    if (n == nullptr) return;

    sf::CircleShape circle(30);
    circle.setFillColor(sf::Color::Red);
    circle.setPosition(x, y);

    sf::Font font;
    if (!font.loadFromFile("C:/Windows/Fonts/arial.ttf")) {
        cout << "Error al cargar la fuente\n";
        return;
    }

    sf::Text text;
    text.setFont(font);
    text.setString(to_string(n->value));
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition(x + 10, y + 5);

    window.draw(circle);
    window.draw(text);

    if (n->nodes[0] != nullptr) {
        sf::Vertex lineaIzquierda[] = {
            sf::Vertex(sf::Vector2f(x + 30, y + 30)),
            sf::Vertex(sf::Vector2f(x - offsetX + 30, y + offsetY + 30))
        };
        window.draw(lineaIzquierda, 2, sf::Lines);
        draw(n->nodes[0], window, x - offsetX, y + offsetY, offsetX / 2, offsetY);
    }

    if (n->nodes[1] != nullptr) {
        sf::Vertex lineaDerecha[] = {
            sf::Vertex(sf::Vector2f(x + 30, y + 30)),
            sf::Vertex(sf::Vector2f(x + offsetX + 30, y + offsetY + 30))
        };
        window.draw(lineaDerecha, 2, sf::Lines);
        draw(n->nodes[1], window, x + offsetX, y + offsetY, offsetX / 2, offsetY);
    }
}

void AvlTree::print(sf::RenderWindow& window) {
    if (m_root == nullptr) {
        return;
    }
    draw(m_root, window, 400, 50, 200, 100);

}

int main() {
    AvlTree t;

    t.Insert(1);
    t.Insert(8);
    t.Insert(3);
    t.Insert(7);
    t.Insert(2);
    t.Insert(9);
    t.Insert(4);
    t.Insert(5);

    t.Remove(2);
    t.Remove(8);
    t.Remove(4);
    t.Remove(5);
    sf::RenderWindow window(sf::VideoMode(800, 600), "Visualización del Árbol AVL");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        t.print(window);
        window.display();
    }

    return 0;
}
