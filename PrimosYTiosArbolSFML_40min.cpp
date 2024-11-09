#include <SFML/Graphics.hpp>
#include <queue>
#include <iostream>

using namespace std;

struct CBinNode
{
    int value;
    int color;
    CBinNode* nodes[2];
    CBinNode(int _v)
    {
        value = _v; nodes[0] = nodes[1] = 0; color = 0;
    }

};

class CBinTree
{
public:
    CBinTree();
    ~CBinTree();
    bool Insert(int x);
    void drawprimosytios(int x, sf::RenderWindow& window);
private:
    bool primosytios(int x);
    void imprimir_arbol_pt(CBinNode* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY);
    bool Find(int x, CBinNode**& p);
    CBinNode* m_root;
    bool m_b;
};

CBinTree::CBinTree()
{
    m_root = 0;
    m_b = 0;
}

CBinTree::~CBinTree()
{
}


bool CBinTree::primosytios(int x) {
    if (x == m_root->value || (m_root->nodes[0] != nullptr && x == m_root->nodes[0]->value) || (m_root->nodes[1] != nullptr && x == m_root->nodes[1]->value)) {
        return false;
    }
    CBinNode** p = &m_root;
    queue<CBinNode*> primos;
    queue<CBinNode*> tios;

    while (*p && (*p)->value != x) {
        CBinNode* q = *p;
        q = q->nodes[!((*p)->value < x)];
        p = &((*p)->nodes[(*p)->value < x]);

        if (*p && (*p)->value != x) {
            tios.push(q);
        }

        if (!tios.empty() && *p && (*p)->value != x) {

            int olds = tios.size() - 1;

            if (tios.front()->nodes[0] != nullptr) {

                tios.push(tios.front()->nodes[0]);
            }

            if (tios.front()->nodes[1] != nullptr) {
                tios.push(tios.front()->nodes[1]);
            }
            
            for (int i = 0; i < olds; i++) {
                tios.pop();
            }
        }
    }

    for (int i = 0; i < tios.size(); i++) {
        if (tios.front()->nodes[0] != nullptr) {
            tios.front()->nodes[0]->color = 1;
            primos.push(tios.front()->nodes[0]);
        }

        if (tios.front()->nodes[1] != nullptr) {
            tios.front()->nodes[1]->color = 1;
            primos.push(tios.front()->nodes[1]);
        }

        tios.front()->color = 2;
        tios.push(tios.front());
        tios.pop();
    }

    return *p && (*p)->value == x;
}


void CBinTree::imprimir_arbol_pt(CBinNode* n, sf::RenderWindow& window, float x, float y, float offsetX, float offsetY) {
    if (n == nullptr) return;

    sf::CircleShape circle(30);
    if (n->color == 0) {
        circle.setFillColor(sf::Color::Green);
    }
    else if (n->color == 1) {
        circle.setFillColor(sf::Color::Red);
    }
    else if (n->color == 2) {
        circle.setFillColor(sf::Color::Blue);
    }
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
        imprimir_arbol_pt(n->nodes[0], window, x - offsetX, y + offsetY, offsetX / 2, offsetY); 
    }

    if (n->nodes[1] != nullptr) {
        sf::Vertex lineaDerecha[] = {
            sf::Vertex(sf::Vector2f(x + 30, y + 30)),
            sf::Vertex(sf::Vector2f(x + offsetX + 30, y + offsetY + 30))
        };
        window.draw(lineaDerecha, 2, sf::Lines);
        imprimir_arbol_pt(n->nodes[1], window, x + offsetX, y + offsetY, offsetX / 2, offsetY); 
    }
}


void CBinTree::drawprimosytios(int x, sf::RenderWindow& window) {
    if (!primosytios(x)) {
        return;
    }
    imprimir_arbol_pt(m_root, window, 400, 50, 200, 100);
}


bool CBinTree::Find(int x, CBinNode**& p)
{
    for (p = &m_root;
        *p && (*p)->value != x;
        p = &((*p)->nodes[(*p)->value < x]));
    return *p && (*p)->value == x;
}

bool CBinTree::Insert(int x)
{
    CBinNode** p;
    if (Find(x, p)) return 0;
    *p = new CBinNode(x);
    return 0;
}

int main()
{
    CBinTree t;
    t.Insert(8);
    t.Insert(4);
    t.Insert(12);
    t.Insert(2);
    t.Insert(6);
    t.Insert(10);
    t.Insert(14);
    t.Insert(1);
    t.Insert(3);
    t.Insert(5);
    t.Insert(7);
    t.Insert(9);
    t.Insert(11);
    t.Insert(13);
    t.Insert(15);

    sf::RenderWindow window(sf::VideoMode(800, 600), "Visualización del Árbol Binario");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        window.clear();
        t.drawprimosytios(3,window);
        window.display();
    }

    return 0;
}
