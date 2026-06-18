#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <thread>
#include <chrono>
#include "logic.hpp"
#include "RenderObjects.hpp"

using sf::RenderWindow;
using sf::Event;
using sf::Vector2f;
using sf::Font;
using std::string;
using std::vector;
using std::this_thread::sleep_for;
using std::chrono::milliseconds;


enum class GameState
{
    Menu,
    PlayingState,
};

enum class MenuScreenButton
{
    Play,
    Quite
};

void PlayingState (RenderWindow& window,vector<char>& Piece ,const Vector2f Pos[],Event& event, Font font, string& status, bool& HasPlayerMoved, bool& HasComputerMoved, CurrentGameState& state)
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

        if (status == "0")
        {
            DrawTieText(window, font);
        }
        else if (status != "?")
        {
            DrawWinningLines(window, state, Pos);
            DrawWinOrLoseText(window, font, state);
        }
        
        
        
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
                    StatusStringDecoder(status, state);        
                }
            }
        }

        while (!HasComputerMoved && status == "?") // for computer move
        {
            if(ComputerMove(Piece))
            {
                HasComputerMoved = true;
                status = WinnerCheacker(Piece);
                StatusStringDecoder(status, state);
            }
        }
        }
  
        if (HasPlayerMoved && HasComputerMoved)
        {
            HasPlayerMoved   = false;
            HasComputerMoved = false; 
        }
}

void MenuState (RenderWindow& window, Font& font, Vector2u& size, Event& event, MenuScreenButton& SelectedButton)
{
    bool IsPlayButtonSelected = true;
    bool IsQiteButtonSelected = false;

    Vector2f PlayButtonLocation(400, 400);
    Vector2f QuiteButtonLocation(400, 460);


    switch (SelectedButton)
    {
    case MenuScreenButton::Play:
        IsPlayButtonSelected = true;
        IsQiteButtonSelected = false;
        break;
    
    case MenuScreenButton::Quite:
        IsPlayButtonSelected = false;
        IsQiteButtonSelected = true;
    }


    if (IsDownKeyPressed(event) || IsUpKeyPressed(event))
    {
            switch (SelectedButton)
            {
            case MenuScreenButton::Play:
                SelectedButton = MenuScreenButton::Quite;
                break;
            
            case MenuScreenButton::Quite:
                SelectedButton = MenuScreenButton::Play;
                break;
            }
    }

    sleep_for(milliseconds(75));

    DrawTitle(window, font, size);
    DrawButton(window, font, "Play", PlayButtonLocation, IsPlayButtonSelected);
    DrawButton(window, font, "Quite", QuiteButtonLocation, IsQiteButtonSelected);
}