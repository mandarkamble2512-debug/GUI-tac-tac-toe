#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <atomic>
#include <chrono>
#include <vector>
#include "logic.hpp"
#include "RenderObjects.hpp"

using std::endl;
using std::cout;
using std::atomic;
using std::string;
using std::vector;
using std::chrono::milliseconds;  

atomic<bool> running(true);

void PlayingState (RenderWindow& window,vector<char>& Piece ,const Vector2f Pos[],Event& event, Font font, string& status, bool& HasPlayerMoved, bool& HasComputerMoved)
{
    for (short i = 0; i <= 8 ; i++) // for drawing bord
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
        
        if (status == "?") // for Player move
        {
        while (!HasPlayerMoved && status == "?" && window.pollEvent(event))
        {
            if (event.type == Event::KeyPressed)
            {
                if (PlayerMove(event, Piece))
                {
                    HasPlayerMoved = true;
                    status = WinnerCheacker(Piece);        
                    // CurrentGameStateSetter(window, status, CurrentGameState, font, StatusStringDecoder(window, status, CurrentGameState, font));       
                }
            }
        }

        while (!HasComputerMoved && status == "?") // for computer move
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
        
        // DrawTieText(window, font);
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
    if (!font.loadFromFile("./Assets/Fonts/HomeVideo.ttf")) cout<<"Failed to load font from ./Assets/Fonts/HomeVideo-BLG6G.ttf"<<endl;

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