/* command to build program: g++ -std=c++17 -Wall -Wextra -Werror solver.cpp -lsfml-graphics -lsfml-window -lsfml-system
*/

#include <SFML/Graphics.hpp>
#include  <iostream>

class Pencil{
    sf::RenderWindow& window;
    sf::Font font;
    sf:: Text text;
    
    public:

        Pencil(sf::RenderWindow& window)  : window(window){
            if ( !font.loadFromFile("Rajdhani/Rajdhani-SemiBold.ttf")) {
                std::cout << "Fail: not loaded font" << std::endl;
            }
            text.setFont(font);
        }

        void write(std::string str , int x, int y, int size = 20, sf::Color color = sf::Color::Black){
            text.setString(str);
            text.setPosition(x, y);
            text.setCharacterSize(size);
            text.setOutlineColor(color);
            window.draw(text);
        }
};

// class Bubble{};

// class Board{};

class Game{
    sf::RenderWindow window;

    public:
        Game() : window(sf::VideoMode(800, 600), "bull"){
            window.setFramerateLimit(60);
        }

        void process_envets() {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
            }
        }

        void draw() {
            window.clear(sf::Color::Black);
            static Pencil pencil(window);
            pencil.write("Iniciando o jogo", 250, 250, 50, sf::Color::Blue);
            window.display();
        }

        void main_loop() {
            while( window.isOpen()) {
                process_envets();
                draw();
            }
        }
};

//void process_envents(sf::RenderWindow& window, Game &gmae){};

int main(){

     Game game;
     game.main_loop();
    return 0;

}
