#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <chrono>
#include "logic.hpp"

using std::ref;
using std::cout;
using std::endl;
using std::atomic;
using std::string;
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
using sf::Font;
using sf::Text;
using sf::Keyboard;

atomic<bool> running(true);


void DrawText (RenderWindow& window, Vector2f pos, char Piece, const Font& font) 
{
    Text text;
    short TextSize = 130;
    text.setFont(font);
    text.setString(Piece);
    text.setFillColor(Color::White);
    text.setCharacterSize(TextSize);
    text.setPosition(pos);
    window.draw(text);
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
    srand(time(NULL));
    RenderWindow window(VideoMode(800, 800), "TIC");
    Vector2u size = window.getSize();
    char Piece[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const Vector2f Pos[] = // for defining the cordinates for the X or O
        {
        Vector2f(130 , 130),                                           // 0
        Vector2f((Pos[0].x + (size.x * 1.0f/3.0f)), Pos[0].y),     // 1
        Vector2f(Pos[1].x + (size.x * 1.0f/3.0f), Pos[0].y),           // 2
        Vector2f(Pos[0].x, Pos[0].y + (1.0f/3.0f * size.y)),           // 3
        Vector2f(Pos[1].x, Pos[3].y),                                  // 4
        Vector2f(Pos[2].x, Pos[3].y),                                  // 5
        Vector2f(Pos[0].x, Pos[3].y + (size.x * 1.0f/3.0f)),           // 6
        Vector2f(Pos[1].x, Pos[6].y),                                  // 7
        Vector2f(Pos[2].x, Pos[6].y)                                   // 8
        };
    short LenthPos = std::size(Pos);
    Event event;
    Font font;
    bool HasPlayerMoved = false;
    if (!font.loadFromFile("/usr/share/fonts/gnu-free/FreeSans.ttf")) cout<<"Failed to load font from /usr/share/fonts/gnu-free/FreeSans.ttf"<<endl;

    while (running && window.isOpen()) 
    {
        while (window.pollEvent(event)) 
        {
            if (event.type == Event::Closed) 
            {
                running = false;
            }
        }
        window.clear(Color::Black); // put the rendering code ONLY after this
        
        /*
            Game Loop
        */

        for (short i = 0; i <= 8 ; i++)
        {
            switch (Piece[i])
            {
            case 'X':
                DrawX(window, Pos[i]);
                break;
            
            case 'O':
                DrawO(window, Pos[i]);
                break;

            default:
                DrawText(window, Pos[i], Piece[i], font);
                break;
            }
        }

        while (!HasPlayerMoved)
        {
            HasPlayerMoved = PlayerMove(window, event, Piece);
        }
        
        Drawbord(window);

        ComputerMove(Piece);
        window.display();
    }

    running = false;
}