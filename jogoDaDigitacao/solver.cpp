/* command to build program: g++ -std=c++17 -Wall -Wextra -Werror solver.cpp -lsfml-graphics -lsfml-window -lsfml-system
*/

#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <functional>
#include <set>


int velocity = 5;
int freuqencyLetter = 30;
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
    bool alive {true};

    public: static const int radius {10};

    public:
        Bubble( int x, int y, char letter, int speed) : x{x}, y{y}, letter{letter}, speed{speed} {     
        }

        static int getRadius() {
            return radius;
        }

        int getX() {
            return this->x;
        }

        int getY() {
            return this->y;
        }

        int getSpeed() {
            return this->speed;
        }

        char getLetter() {
            return this->letter;
        }
    
        void update() {
            this->y += this->speed;
        }

        bool setAlive(bool value) {
            return this->alive = value;
        }

        bool getAlive() {
            return this->alive;
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

        int getMisses() {
            return misses;
        }

        int setMisses(int value) {
            return this->misses = value;
        }

        int getHits() {
            return hits;
        }

        int setHits(int value) {
            return this->hits = value;
        }

        void update() {
            if (this->check_new_bubble()) {
                this->add_new_bubble();
            }

            for (Bubble& bubble : bubbles){
                bubble.update();
            }
            this->mark_outside_bubbles();
            //this->mark_by_letter_incorret();
            this->remove_dead_bubbles();
        }

        void remove_dead_bubbles() {
            std::vector<Bubble> vivas;
            for (Bubble& bubble : bubbles) {
                if (bubble.getAlive()) {
                    vivas.push_back(bubble);
                }
            }
            this->bubbles = vivas;

        }

        void mark_outside_bubbles() {
            for (Bubble& bubble : bubbles) {
                if (bubble.getY() + 2 * Bubble::radius> (int) this->window.getSize().y) {
                    if (bubble.getAlive()) {
                        bubble.setAlive(false);
                        //bubble.alive = false;
                        this->misses++;
                    }
                }
            }
        }

        // void mark_by_letter_incorret() {
        //     int flag = 0;
        //     for (Bubble& bubble : bubbles) {
        //         for (int tecla = sf::Keyboard::A; tecla <= sf::Keyboard::Z; tecla++) {
        //             if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(tecla))) {
        //                 if (static_cast<sf::Keyboard::Key>(tecla) != bubble.getLetter()) {
        //                     this->misses++;
        //                     flag = 1;
        //                     break;
        //                 }
        //             }
        //         }
        //         if (flag) {
        //             break;
        //         }
        //     }
        // } 

        // std::set<sf::Keyboard::Key> teclasIncorretas;

        // void mark_by_letter_incorret() {
        //     for (Bubble& bubble : bubbles) {
        //         bool teclaIncorreta = true;
        //         for (int tecla = sf::Keyboard::A; tecla <= sf::Keyboard::Z; tecla++) {
        //             if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(tecla))) {
        //                 if (static_cast<sf::Keyboard::Key>(tecla) == bubble.getLetter()) {
        //                     teclaIncorreta = false;
        //                     break;
        //                 }
        //             }
        //         }
        //         if (teclaIncorreta && teclasIncorretas.find(bubble.getLetter()) == teclasIncorretas.end()) {
        //             this->misses++;
        //             teclasIncorretas.insert(bubble.getLetter());
        //         }
        //     }
        // }



        void mark_by_hit(char letter) {
            for (Bubble& bubble : bubbles) {
                if (bubble.getLetter() == letter) {
                    bubble.setAlive(false);
                    //bubble.alive = false;
                    this->hits++;
                    break;
                }
            }
        }

        bool  check_new_bubble() {
            static const int  new_bubble_timout {freuqencyLetter};
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
            int speed = rand() % velocity + 1;
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
    std::function<void()> on_update;

    public:
        Game() : window(sf::VideoMode(800, 600), "Bubbles"), board(window){
            this->on_update = [&]() {
                this->menu();
            };
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

        void gameplay() {
            board.update();
            window.clear(sf::Color::Black);
            board.draw();
            // static Pencil pencil(window);
            // pencil.write("Iniciando o jogo", 250, 250, 50, sf::Color::Blue);
            window.display();
            if (board.getMisses() > 5) {
                board.setMisses(0);
                board.setHits(0);
                this->on_update = [&]() {
                    this->game_over();
                };
            }
        }
        void game_over() {
            static Pencil pencil(window);
            window.clear(sf::Color::Red);
            pencil.write("Game Over", 300, 250, 50, sf::Color::White);
            window.display();
            sf::sleep(sf::milliseconds(2000));
                this->on_update = [&]() {
                    this->menu();
                };
        }

        void starting() {
            static Pencil pencil(window);
            window.clear(sf::Color::Black);
            pencil.write("Iniciar o jogo", 250, 250, 50, sf::Color::Blue);
            pencil.write("Precione a tecla Enter para iniciar o jogo", 200, 550, 25, sf::Color::Blue);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->on_update = [&]() {
                    this->gameplay();
                };
            }
            
        }

        void changeDifficulty(){
            static Pencil pencil(window);
            window.clear(sf::Color::Black);
            pencil.write("Alterar a dificuldade", 200, 80, 50, sf::Color::Blue);
            pencil.write(" 1 -  Facil.", 270, 200, 40, sf::Color::Blue);
            pencil.write(" 2 -  Medio.", 270, 270, 40, sf::Color::Blue);
            pencil.write(" 3 -  Dificil.", 270, 340, 40, sf::Color::Blue);
            pencil.write(" 4 -  Muito Dificil.", 270, 410, 40, sf::Color::Blue);
            pencil.write("Precione ESC para volta ao menu.", 240, 550, 25, sf::Color::Blue);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                this->on_update = [&]() {
                    this->menu();
                };
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                window.clear(sf::Color::Black);
                pencil.write("Dificuldade alterada para: Facil", 80,250, 50, sf::Color::Blue);
                velocity = 5;
                freuqencyLetter = 30;
                window.display();
                sf::sleep(sf::milliseconds(2000));
                this->on_update = [&]() {
                    this->menu();
                };
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                window.clear(sf::Color::Black);
                pencil.write("Dificuldade alterada para: Medio", 80,250, 50, sf::Color::Blue);
                velocity = 10;
                freuqencyLetter = 25;
                window.display();
                sf::sleep(sf::milliseconds(2000));
                this->on_update = [&]() {
                    this->menu();
                };
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                window.clear(sf::Color::Black);
                pencil.write("Dificuldade alterada para: Dificil", 80,250, 50, sf::Color::Blue);
                velocity = 15;
                freuqencyLetter = 20;
                window.display();
                sf::sleep(sf::milliseconds(2000));
                this->on_update = [&]() {
                    this->menu();
                };
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num4)) {
                window.clear(sf::Color::Black);
                pencil.write("Dificuldade alterada para: Muito dificil", 10,250, 50, sf::Color::Blue);
                velocity = 20;
                freuqencyLetter = 15;
                window.display();
                sf::sleep(sf::milliseconds(2000));
                this->on_update = [&]() {
                    this->menu();
                };
            }
        }

        void instruction() {
            static Pencil pencil(window);
            window.clear(sf::Color::Black);
            pencil.write("Instrucao para jogar", 250, 250, 50, sf::Color::Blue);
            pencil.write("voce deve teclar as letra que estao apaarecendo em sua tela antes que ela chegue ao final da tela", 250, 250, 50, sf::Color::Blue);
            pencil.write("Precione ESC para volta ao menu.", 250, 550, 25, sf::Color::Blue);
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
                this->on_update = [&]() {
                    this->menu();
                };
            }
        }

        bool isMouseOverButton(const sf::Vector2i& mousePosition, const sf::RectangleShape& button) {
            return button.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePosition));
        }

        void menu() {
            static Pencil pencil(window);
            window.clear(sf::Color::Black);
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

            // Método botão para jogar
            sf::RectangleShape buttonPlaying(sf::Vector2f(200, 40));
            buttonPlaying.setPosition(300, 150);
            buttonPlaying.setFillColor(sf::Color::Green);
            pencil.write("Iniciar o jogo", 300, 150, 40, sf::Color::Blue);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverButton(mousePosition, buttonPlaying)) {
                this->on_update = [&]() {
                    this->starting();
                };
            }

            // Método alterar dificuldade
            sf::RectangleShape buttonDifficulty(sf::Vector2f(500, 40));
            buttonDifficulty.setPosition(200, 250);
            buttonDifficulty.setFillColor(sf::Color::Green);
            pencil.write("Alterar dificuldade do jogo", 200, 250, 40, sf::Color::Blue);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverButton(mousePosition, buttonDifficulty)) {
                this->on_update = [&]() {
                    this->changeDifficulty();
                };
            }
            
            // Intruções do jogo
            sf::RectangleShape buttonInstruction(sf::Vector2f(400, 40));
            buttonInstruction.setPosition(250, 350);
            buttonInstruction.setFillColor(sf::Color::Green);
            pencil.write("Instrucoes do jogo", 250, 350, 40, sf::Color::Blue);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && isMouseOverButton(mousePosition, buttonInstruction)) {
                this->on_update = [&]() {
                    this->instruction();
                };
            }
            
            window.display();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
                this->on_update = [&]() {
                    this->starting();
                };
            }
        }

        

        void main_loop() {
            while( window.isOpen()) {
                process_envets();
                on_update();
            }
        }
};

int main(){

     Game game;
     game.main_loop();
    return 0;

}
