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

void DrawX (RenderWindow& window, Vector2f pos)
{
    Vector2f LineSize(10, 300);
    RectangleShape Line(LineSize);
    RectangleShape Line1(LineSize);

    Line.rotate(45);
    Line1.rotate(-45);

    Line.setOrigin(LineSize.x / 2.0f, LineSize.y / 2.0f);
    Line1.setOrigin(LineSize.x / 2.0f, LineSize.y / 2.0f);
    Line.setFillColor(Color::White);
    Line1.setFillColor(Color::White);
    Line.setPosition(pos);
    Line1.setPosition(pos);
    window.draw(Line);
    window.draw(Line1);
}

void DrawO (RenderWindow& window, Vector2f Pos)
{
    int Radius = 100;
    CircleShape OLetter(Radius);
    OLetter.setPosition(Pos);
    OLetter.setOrigin(Radius, Radius);
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

int main() 
{
    RenderWindow window(VideoMode(800, 800), "PIX");

    Vector2u size = window.getSize();
    Vector2f Pos[9] = // for defining the cordinates for the X or O
        {
        Vector2f(130 , 130),                                           // 0
        Vector2f((Pos[0].x + (size.x * 1.0f/3.0f)) + 8, Pos[0].y),     // 1
        Vector2f(Pos[1].x + (size.x * 1.0f/3.0f), Pos[0].y),           // 2
        Vector2f(Pos[0].x, Pos[0].y + (1.0f/3.0f * size.y)),           // 3
        Vector2f(Pos[1].x, Pos[3].y),                                  // 4
        Vector2f(Pos[2].x, Pos[3].y),                                  // 5
        Vector2f(Pos[0].x, Pos[3].y + (size.x * 1.0f/3.0f)),           // 6
        Vector2f(Pos[1].x, Pos[6].y),                                  // 7
        Vector2f(Pos[2].x, Pos[6].y)                                   // 8
        };
    short LenthPos = std::size(Pos);

    thread worker(workerThread);  
    Event event;
    while (running && window.isOpen()) 
    {
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
            {
                running = false;
            }
        }

        window.clear(Color::Black);
        Drawbord(window);
        window.display();
    }

    running = false;
    worker.join();
    return 0;
}