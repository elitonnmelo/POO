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

class Bubble{
    
    int x;
    int y;
    char letter;
    int speed;

    static const int radius {10};
    bool alive {true};

    public:
        Bubble( int x, int y, char letter, int speed) : x{x}, y{y}, letter{letter}, speed{speed} {     
        }

        void update() {
            this->y += this->speed;
        }

        void draw(sf::RenderWindow& window) {
            sf::CircleShape circle (Bubble::radius);
            circle.setPosition(x, y);
            circle.setFillColor(sf::Color::Blue);
            window.draw(circle);
            static Pencil pencil(window);
            pencil.write(std::string(1, letter), x + 0.2 * Bubble::radius, y, Bubble::radius * 1.5, sf::Color::Red);
        }
};

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
           static Bubble bubble(200, 100, 'B', 2);
           bubble.update();
           bubble.draw(window); 
            // static Pencil pencil(window);
            // pencil.write("Iniciando o jogo", 250, 250, 50, sf::Color::Blue);
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
