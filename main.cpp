#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <chrono>

using std::atomic;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Event;
using sf::Color;
using sf::RectangleShape;
using sf::Vector2f;
using std::thread;
using std::chrono::milliseconds;  
using sf::Vector2u;
using sf::CircleShape;

atomic<bool> running(true);

void workerThread() {
    while (running) {
        std::this_thread::sleep_for(milliseconds(100));
    }
}

void DrawX ()
{
    RectangleShape Line(Vector2f(2, 5));
    RectangleShape Line1(Vector2f(2, 5));
}

void DrawO (RenderWindow& window, Vector2f Pos)
{
    int Radius = 100;
    CircleShape OLetter(Radius);
    OLetter.setPosition(Pos);
    OLetter.setFillColor(Color::Black);
    OLetter.setOutlineThickness(10);
    OLetter.setOutlineColor(Color::White);
    window.draw(OLetter);
}

void Drawbord(RenderWindow& window)
{
    Vector2u size = window.getSize();

    RectangleShape bord(Vector2f(10, size.y - 20));
    RectangleShape bord1(Vector2f(10, size.y - 20));
    RectangleShape bord2(Vector2f(size.x -20,10));
    RectangleShape bord3(Vector2f(size.x -20,10));

    bord.setFillColor(Color::White);
    bord.setPosition(size.x * 1/3, 10);
    bord1.setFillColor(Color::White);
    bord1.setPosition((size.x * 1/3) * 2, 10);
    bord2.setFillColor(Color::White);
    bord2.setPosition(10, size.y * 1/3);
    bord3.setFillColor(Color::White);
    bord3.setPosition(10,(size.y * 1/3) * 2);

    window.draw(bord1);
    window.draw(bord);
    window.draw(bord2);
    window.draw(bord3);
}

int main() {
    RenderWindow window(VideoMode(800, 800), "PIX");

    Vector2u size = window.getSize();
    Vector2f Pos[] = {Vector2f(35 ,30), Vector2f(35 + 1/3 * size.x, 30), Vector2f()};

    thread worker(workerThread);  
    Event event;
    while (running && window.isOpen()) {
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                running = false;
            }
        }

        window.clear(Color::Black);
        Drawbord(window);
        DrawO(window, Pos[1]);
        // DrawO(window, Pos[2]);
        window.display();
    }

    running = false;
    worker.join();
    return 0;
}