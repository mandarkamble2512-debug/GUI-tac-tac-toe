#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <atomic>
#include <chrono>
#include <vector>
#include "logic.hpp"

using std::ref;
using std::endl;
using std::cout;
using std::atomic;
using std::string;
using std::vector;
using sf::RenderWindow;
using sf::VideoMode;
using sf::Event;
using sf::Color;
using sf::RectangleShape;
using sf::Vector2f;
using std::chrono::milliseconds;  
using sf::Vector2u;
using sf::CircleShape;
using sf::Font;
using sf::Text;
using sf::Keyboard;

atomic<bool> running(true);

vector<bool> StatusStringDecoder (RenderWindow& window, Vector2f Pos, string Status)
{
    char character;
    short LinePlace        = 0;
    bool HasPlayerWon      = false;
    bool HasComputerWon    = false;
    bool IsHorizontal      = false;
    bool IsVertical        = false;
    bool IsDigonalTopLeft  = false;
    bool IsDigonalTopRight = false;

    for (short i = 0; i < Status.length(); i++)
    {
        if (i == 0)
        {
            if (Status.at(i) == '0')
            {
                switch (Status.at(i))
                {
                case '1':
                    HasPlayerWon = true;
                    break;
                
                case '2':
                    HasComputerWon = true;
                    break;
                    
                case '0':
                    // will make a function for this later
                    break;
                case '?':
                    // also will do something about this
                }
            }
        }

        if (i == 1)
        {
            switch (Status.at(i))
            {
            case 'V':
                IsVertical = true;
                break;
            
            case 'H':
                IsHorizontal = true;
                break;
            }
        }

        if (i == 1)
        {
            switch (Status.at(i))
            {
            case '/':
                IsDigonalTopRight = true;
                break;
            
            case '|':
                IsDigonalTopLeft = true;
                break;
            }
        }

        if(i == 2 && IsVertical)
        {
            switch (Status.at(i))
            {
            case 'l':
                LinePlace = 1;
                break;
            
            case 'm':
                LinePlace = 2;
                break;
            
            case 'r':
                LinePlace = 3;
            }
        }
    }

    return {HasPlayerWon, HasComputerWon, IsHorizontal, IsVertical, IsDigonalTopLeft, IsDigonalTopRight};
}

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

void PlayingState (RenderWindow& window,vector<char>& Piece ,const Vector2f Pos[],Event& event, Font font, string& status, bool& HasPlayerMoved, bool& HasComputerMoved)
{
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
        Drawbord(window);
        
        if (status == "?")
        {
        while (!HasPlayerMoved && status == "?" && window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (PlayerMove(event, Piece))
                {
                    HasPlayerMoved = true;
                    status = WinnerCheacker(Piece);               
                }
            }
        }

        while (!HasComputerMoved && status == "?")
        {
            if(ComputerMove(Piece))
            {
                HasComputerMoved = true;
                status = WinnerCheacker(Piece);
            }
        }
        }
  
        if (HasPlayerMoved && HasComputerMoved)
        {
            HasPlayerMoved   = false;
            HasComputerMoved = false; 
        }
}

int main() 
{
    srand(time(NULL));
    RenderWindow window(VideoMode(800, 800), "TIC");
    Vector2u size = window.getSize();
    Event event;
    Font font;
    string status = "?";
    bool HasPlayerMoved = false;
    bool HasComputerMoved = false;
    bool Isspaceleft = true;
    vector<char> Piece = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const Vector2f Pos[] = // for defining the cordinates for the X or O
        {
        Vector2f(130 , 130),                                           // 0
        Vector2f((Pos[0].x + (size.x * 1.0f/3.0f)), Pos[0].y),         // 1
        Vector2f(Pos[1].x + (size.x * 1.0f/3.0f), Pos[0].y),           // 2
        Vector2f(Pos[0].x, Pos[0].y + (1.0f/3.0f * size.y)),           // 3
        Vector2f(Pos[1].x, Pos[3].y),                                  // 4
        Vector2f(Pos[2].x, Pos[3].y),                                  // 5
        Vector2f(Pos[0].x, Pos[3].y + (size.x * 1.0f/3.0f)),           // 6
        Vector2f(Pos[1].x, Pos[6].y),                                  // 7
        Vector2f(Pos[2].x, Pos[6].y)                                   // 8
        };
    short LenthPos = std::size(Pos);
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
        
        PlayingState(window, Piece, Pos, event, font, status, HasPlayerMoved, HasComputerMoved);
        
        window.display();
    }

    running = false;
}