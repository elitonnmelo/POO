#include <SFML/Graphics.hpp>
#include  <iostream>

class Pencil{
    sf::RenderWindow& window;
    sf::Font font;
    sf:: Text text;

    Pencil(sf::RenderWindow& window)  : window(window){}

    void write(std::string str , int x, int y, int size = 20, sf::Color color = sf::Color::Black){

    }
};

class Bubble{};

class Board{};

class Game{};

void process_envents(sf::RenderWindow& window, Game &gmae){};

int main(){

     sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Bubbles!");

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }
        window.clear();
        window.display();
    }
    return 0;

}
