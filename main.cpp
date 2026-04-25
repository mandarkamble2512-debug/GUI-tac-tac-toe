#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include <thread>
#include <atomic>
#include <chrono>

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

short inputHandler(Event event)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code >= Keyboard::Num1 && event.key.code <= Keyboard::Num9)
        {
            return (event.key.code - Keyboard::Num1) + 1;
        }
        
        if (event.key.code >= Keyboard::Numpad1 && event.key.code <= Keyboard::Numpad9)
        {
            return (event.key.code - Keyboard::Numpad1) + 1;
        }
    }

    return 0;
}

bool FindIsSpaceOccupied (short index, char Piece[])
{
    if (Piece[index] != 'X' && Piece[index] != 'O')
    {
        return true;
    }
    else 
    {
        return false;
    }
}

void ComputerMove(RenderWindow& window, Event event, char Piece[]) // computer uses O
{
    bool IsPlayed = false;
    if (Piece[0] == 'X')
    {
        if (Piece[1] == 'X' && FindIsSpaceOccupied(2, Piece))
        {
            Piece[2] = 'O';
        }
        else if (Piece[3] == 'X' && FindIsSpaceOccupied(6, Piece))
        {
            Piece[6] = 'O';
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(8, Piece))
        {
            Piece[8] = 'O';
        }
    }
    else if (Piece[1] == 'X')
        {
            if (Piece[0] == 'X' && FindIsSpaceOccupied(2, Piece))
            {
                Piece[2] = 'O';
            }
            else if (Piece[2] == 'X' && FindIsSpaceOccupied(0, Piece))
            {
                Piece[0] = 'O';
            }
            else if (Piece[4] == 'X' && FindIsSpaceOccupied(7, Piece))
            {
                Piece[7] = 'O';
            }        
        }
    else if (Piece[2] == 'X')
    {
        if (Piece[1] == 'X' && FindIsSpaceOccupied(0, Piece))
        {
            Piece[0] = 'O';
        }
        else if (Piece[5] == 'X' && FindIsSpaceOccupied(8, Piece))
        {
            Piece[8] = 'O';
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(6, Piece))
        {
            Piece[6] = 'O';
        }
    }
    else if (Piece[3] == 'X')
    {
        if (Piece[0] == 'X' && FindIsSpaceOccupied(6 ,Piece))
        {
            Piece[6] = 'O';
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(5 ,Piece))
        {
            Piece[5] = 'O';
        }
        else if (Piece[6] == 'X' && FindIsSpaceOccupied(0 , Piece))
        {
            Piece[0] = 'O';
        }
    }
    else  if (Piece[4] == 'X')
    {
        if (Piece[1] == 'X' && FindIsSpaceOccupied(7, Piece))
        {
            Piece[7] = 'O';
        }
        else if (Piece[7] == 'X' && FindIsSpaceOccupied(1 ,Piece))
        {
            Piece[1] = 'O';
        }
        else if (Piece[3] == 'X' && FindIsSpaceOccupied(5, Piece))
        {
            Piece[5] = 'O';
        }
        else if (Piece[5] == 'X' && FindIsSpaceOccupied(3, Piece))
        {
            Piece[3] = 'O';
        }  
    } 
    else if (Piece[5] == 'X')
    {
        if (Piece[2] == 'X' && FindIsSpaceOccupied(8 , Piece))
        {
            Piece[8] = 'O';
        }
        else if (Piece[8] == 'X' && FindIsSpaceOccupied(2, Piece))
        {
            Piece[2] = 'O';
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(3 ,Piece))
        {
            Piece[3] = 'O';
        }
    }
    else if (Piece[6] == 'X')
    {
        if (Piece[3] == 'X' && FindIsSpaceOccupied(0 ,Piece))
        {
            Piece[0] = 'O';   
        }
        else if (Piece[7] == 'X' && FindIsSpaceOccupied(8 ,Piece))
        {
            Piece[8] = 'O';
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(2 ,Piece))
        {
            Piece[2] = 'O';
        }
            
    }
    else if (Piece[7] == 'X')
    {
        if (Piece[6] == 'X' && FindIsSpaceOccupied(8 ,Piece))
        {
            Piece[8] = 'O';
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(1 ,Piece))
        {
            Piece[1] = 'O';
        }
        else if (Piece[8] == 'X' && FindIsSpaceOccupied(6, Piece))
        {
            Piece[6] = 'O';
        }
        
    }
    else if (Piece[8] == 'X')
    {
        if (Piece[5] == 'X' && FindIsSpaceOccupied(2 ,Piece))
        {
            Piece[2] = 'O';
        }
        else if (Piece[7] == 'X' && FindIsSpaceOccupied(6 ,Piece))
        {
            Piece[6] = 'O';
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(0 ,Piece))
        {
            Piece[0] = 'O';
        }
    }
}

void PlayerMove (RenderWindow& window, Event event, char Piece[]) // player uses X;
{
    short Value = 0;
    while (Value == 0)
    {
        Value = inputHandler(event);
        if (Piece[Value - 1] != 'X' && Piece[Value -1] != 'O')
        {
            Piece[Value -1] = 'X';
        }
        else 
        {
            Value = 0;
        }
    }
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

int main() 
{
    RenderWindow window(VideoMode(800, 800), "TIC");
    Vector2u size = window.getSize();
    char Piece[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
    const Vector2f Pos[9] = // for defining the cordinates for the X or O
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
        for (short i = 0; i <= 8; i++)
        {
            DrawText(window, Pos[i], Piece[i], font);
        }
        
        Drawbord(window);
        window.display();
    }

    running = false;
}