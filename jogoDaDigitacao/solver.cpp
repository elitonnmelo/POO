/* command to build program: g++ -std=c++17 -Wall -Wextra -Werror solver.cpp -lsfml-graphics -lsfml-window -lsfml-system
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>


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
    
    public: int x;
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

class Board{
    sf::RenderWindow& window;
    std::vector<Bubble> bubbles;
    Pencil pencil;
    int hits {0};
    int misses {0};

    public:
        Board(sf::RenderWindow& window) : window{window}, pencil{window} {
        }

        void update() {
            if (this->check_new_bubble()) {
                this->add_new_bubble();
            }

            for (Bubble& bubble : bubbles){
                bubble.update();
            }
            this->mark_outside_bubbles();
            this->remove_dead_bubbles();
        }

        void remove_dead_bubbles() {
            std::vector<Bubble> vivas;
            for (Bubble& bubble : bubbles) {
                if (bubble.alive) {
                    vivas.push_back(bubble);
                }
            }
            this->bubbles = vivas;

        }

        void mark_outside_bubbles() {
            for (Bubble& bubble : bubbles) {
                if (bubble.y + 2 * Bubble::radius > (int) this->window.getSize().y) {
                    if (bubble.alive) {
                        bubble.alive = false;
                        this->misses++;
                    }
                }
            }
        }
        void mark_by_hit(char letter) {
            for (Bubble& bubble : bubbles) {
                if (bubble.letter == letter) {
                    bubble.alive = false;
                    this->hits++;
                    break;
                }
            }
        }

        bool  check_new_bubble() {
            static const int  new_bubble_timout {30};
            static int new_bubble_timer {0};

            new_bubble_timer--;
            if (new_bubble_timer <= 0) {
                new_bubble_timer = new_bubble_timout;
                return true;
            }
            return false;
        }

        void add_new_bubble() {
            int x = rand() % ((int) this->window.getSize().x - 2 * Bubble::radius);
            int y = -2 * Bubble::radius;
            int speed = rand() % 5 + 1;
            char letter = rand() % 26 + 'A';
            bubbles.push_back(Bubble(x, y, letter, speed));
        }

        void draw() {
            pencil.write("Hits: " + std::to_string(this->hits) + " Misses: " + std::to_string(this->misses), 10, 10, 20, sf::Color::White);
            pencil.write("Size: " + std::to_string(this->bubbles.size()), 10, 30, 20, sf::Color::White);
            for (Bubble& bubble : bubbles) {
                bubble.draw(window);
            }
        }
};

class Game{
    sf::RenderWindow window;
    Board board;

    public:
        Game() : window(sf::VideoMode(800, 600), "Bubbles"), board(window){
            window.setFramerateLimit(30);
        }

        void process_envets() {
            sf::Event event;
            while (window.pollEvent(event)) {
                if (event.type == sf::Event::Closed) {
                    window.close();
                }
                else if (event.type == sf::Event::TextEntered) {
                    char code = static_cast<char>(event.text.unicode);
                    code = toupper(code);
                    board.mark_by_hit(code);
                }
            }
        }

        void draw() {
            board.update();
            window.clear(sf::Color::Black);
            board.draw();
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
