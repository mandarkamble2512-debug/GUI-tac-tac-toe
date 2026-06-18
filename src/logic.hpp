#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include <future>
#include <vector>

using std::ref;
using std::this_thread::sleep_for;
using std::async;
using std::string;
using std::vector;
using std::chrono::milliseconds;
using sf::RenderWindow;
using sf::Event;
using sf::Keyboard;
using sf::Font;

struct CurrentGameState
{
    bool HasPlayerWon      = false;
    bool HasComputerWon    = false;
    bool IsHorizontal      = false;
    bool IsVertical        = false;
    bool IsDigonalTopLeft  = false;
    bool IsDigonalTopRight = false;
    bool IsTie             = false;
    short LinePlace          = 0;
};


void StatusStringDecoder (string Status, CurrentGameState& state)
{
    state = CurrentGameState();  // reset to defaults first

    switch (Status[0])
    {
        case '1':
            state.HasPlayerWon = true; 
            break;
        case '2': 
            state.HasComputerWon = true; 
            break;
        case '0': state.IsTie = true; 
            return;
        case '?': 
            return;
    }

    if (Status.length() > 1)
    {
        if      (Status[1] == 'H') state.IsHorizontal     = true;
        else if (Status[1] == 'V') state.IsVertical        = true;
        else if (Status[1] == '/') state.IsDigonalTopRight = true;
        else if (Status[1] == '|') state.IsDigonalTopLeft  = true;
    }

    if (Status.length() > 2 && (state.IsVertical || state.IsHorizontal))
    {
        if      (Status[2] == 'l' || Status[2] == 't') state.LinePlace = 1;
        else if (Status[2] == 'm')                      state.LinePlace = 2;
        else if (Status[2] == 'r' || Status[2] == 'b') state.LinePlace = 3;
    }
}

string WinnerCheacker (vector<char>& Piece)
{
    bool Hasplayed  = false;
    bool IsBordFull = false; 
    bool hasNumbers = false;
    // 0 for draw
    // 1 for player win
    // 2 for computer win
    // ? for nothing

    // Vm for middle vertical
    // Vl for left   vertical
    // Vr for right  vertical

    // Ht for horizontal top
    // Hm for horizontal middle
    // Hb for horizontal bottem

    // "/" for diognal 
    // "|" also for digonal

    static const int HorizontalWinningConditions[3][3] = 
    {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}
    };

    static const int VerticalWinningConditions[3][3] = 
    {
           {0, 3, 6}, {1, 4, 7}, {2, 5, 8},
    };

    static const int DigonalWinningConditions[2][3] =
    {
        {0, 4, 8}, {2, 4, 6},
    };

    for (int i = 0; i < 3 && !Hasplayed; i++) // for horizontal
    {
        if(Piece.at(HorizontalWinningConditions[i][0]) == 'X' && Piece.at(HorizontalWinningConditions[i][1]) == 'X' && Piece.at(HorizontalWinningConditions[i][2]) == 'X' && !Hasplayed)
        {
            if (i == 0)
            {
                Hasplayed = true;
                return "1Ht";
            }
            else if (i == 1)
            {
                Hasplayed = true;
                return "1Hm";

            }
            else if (i == 2)
            {
                Hasplayed = true;
                return "1Hb";

            }
        }
        else if (Piece.at(HorizontalWinningConditions[i][0]) == 'O' && Piece.at(HorizontalWinningConditions[i][1]) == 'O' && Piece.at(HorizontalWinningConditions[i][2]) == 'O' && !Hasplayed)
        {
            if (i == 0)
            {
                Hasplayed = true;
                return "2Ht";
            }
            else if (i == 1)
            {
                Hasplayed = true;
                return "2Hm";
            }
            else if (i == 2)
            {
                Hasplayed = true;
                return "2Hb";
            }
        }
        
    }
    
    for (int i = 0; i < 3 && !Hasplayed; i++) //for vertical 
    {
        if(Piece.at(VerticalWinningConditions[i][0]) == 'X' && Piece.at(VerticalWinningConditions[i][1]) == 'X' && Piece.at(VerticalWinningConditions[i][2]) == 'X' && !Hasplayed)
        {
            if (i == 0)
            {
                Hasplayed = true;
                return "1Vl";
            }
            else if (i == 1)
            {
                Hasplayed = true;
                return "1Vm";
            }
            else if (i == 2)
            {
                Hasplayed = true;
                return "1Vr";
            }
        }
        else if (Piece.at(VerticalWinningConditions[i][0]) == 'O' && Piece.at(VerticalWinningConditions[i][1]) == 'O' && Piece.at(VerticalWinningConditions[i][2]) == 'O' && !Hasplayed)
        {
            if (i == 0)
            {
                Hasplayed = true;
                return "2Vl";
            }
            else if (i == 1)
            {
                Hasplayed = true;
                return "2Vm";
            }
            else if (i == 2)
            {
                Hasplayed = true;
                return "2Vr";
            }
        }
    }
    
    for (int i = 0; i < 2 && !Hasplayed; i++) // for digonal
    {
        if (Piece.at(DigonalWinningConditions[i][0]) == 'X' && Piece.at(DigonalWinningConditions[i][1])  == 'X' && Piece.at(DigonalWinningConditions[i][2])  == 'X' && !Hasplayed)
        {
            if (i == 0)
            {
                Hasplayed = true;
                return "1|";
            }
            else 
            {
                Hasplayed = true;
                return "1/";
            }
        }
        if (Piece.at(DigonalWinningConditions[i][0]) == 'O' && Piece.at(DigonalWinningConditions[i][1])  == 'O' && Piece.at(DigonalWinningConditions[i][2])  == 'O' && !Hasplayed)
        {
            if (i == 0)
            {
                Hasplayed = true;
                return "2|";
            }
            else 
            {
                Hasplayed = true;
                return "2/";
            }
        }
    }
    
    if (!Hasplayed)
    {
        for (short i = 0; i <= 8; i++)
        {
            if (Piece[i] != 'X' && Piece[i] != 'O')
            {
                hasNumbers = true;
                break;
            }
        }
        if (hasNumbers)
        {
            return "?";
        }
    }
    return "0";
}


bool PlayerMove(Event& event, vector<char>& Piece) 
{
    if (event.type == sf::Event::KeyPressed) 
    {
        int index = -1;
        if (event.key.code >= Keyboard::Num1 && event.key.code <= Keyboard::Num9)
            index = event.key.code - Keyboard::Num1;
        else if (event.key.code >= Keyboard::Numpad1 && event.key.code <= Keyboard::Numpad9)
            index = event.key.code - Keyboard::Numpad1;

        if (index != -1 && Piece[index] != 'X' && Piece[index] != 'O') 
        {
            Piece.at(index) = 'X';
                return true;
        }
    }
    return false;
}

bool FindIsSpaceOccupied (short index, vector<char>& Piece)
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

bool ComputerMove(vector<char>& Piece) // computer uses O
{

    bool HasPlayed = false;
    bool HasFreeSpace = true;
    static const int WinningConditions[8][3] =
    {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // horizontal
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // vertical
        {0, 4, 8}, {2, 4, 6},            // Digonal
    };

    for (short i = 0; i < 8 && !HasPlayed; i++) // attack
    {
        if (!HasPlayed && Piece.at(WinningConditions[i][0]) == 'O' && Piece.at(WinningConditions[i][1]) == 'O' && FindIsSpaceOccupied(WinningConditions[i][2], Piece))
        {
            Piece.at(WinningConditions[i][2]) = 'O';
            HasPlayed = true;
            return HasPlayed;
        }
        else if (!HasPlayed && Piece.at(WinningConditions[i][0]) == 'O' && Piece.at(WinningConditions[i][2]) == 'O' && FindIsSpaceOccupied(WinningConditions[i][1], Piece))
        {
            Piece.at(WinningConditions[i][1]) = 'O';
            HasPlayed = true;
            return HasPlayed;
        }
        else if (!HasPlayed && Piece.at(WinningConditions[i][1]) == 'O' && Piece.at(WinningConditions[i][2]) == 'O' && FindIsSpaceOccupied(WinningConditions[i][0], Piece))
        {
            Piece.at(WinningConditions[i][0]) = 'O';
            HasPlayed = true;
            return HasPlayed;
        }
    }
    

    for (short i = 0; i < 8 && !HasPlayed; i++) // Defence
    {
        if (!HasPlayed && Piece.at(WinningConditions[i][0]) == 'X' && Piece.at(WinningConditions[i][1]) == 'X' && FindIsSpaceOccupied(WinningConditions[i][2], Piece))
        {
            Piece.at(WinningConditions[i][2]) = 'O';
            HasPlayed = true;
            return HasPlayed;
        }
        else if (!HasPlayed && Piece.at(WinningConditions[i][1]) == 'X' && Piece.at(WinningConditions[i][2]) == 'X' && FindIsSpaceOccupied(WinningConditions[i][0], Piece))
        {
            Piece.at(WinningConditions[i][0]) = 'O';
            HasPlayed = true;
            return HasPlayed;
        }
        else if (!HasPlayed && Piece.at(WinningConditions[i][0]) == 'X' && Piece.at(WinningConditions[i][2]) == 'X' && FindIsSpaceOccupied(WinningConditions[i][1], Piece))
        {
            Piece.at(WinningConditions[i][1]) = 'O';
            HasPlayed = true;
            return HasPlayed;
        }
    }

    if (!HasPlayed) // if nothing then just random
    {
        for (short i = 0; i < 9; i++)
        {
            if (Piece.at(i) != 'O' && Piece.at(i) != 'X')
            {
                HasFreeSpace = true;
                break;
            }
            else
            {
                HasFreeSpace = false;
            }
        }
        
        while(!HasPlayed && HasFreeSpace)
        {
            int random = rand() % 9;
            if (FindIsSpaceOccupied(random, Piece))
            {
                Piece.at(random) = 'O';
                HasPlayed = true;
                return HasPlayed;
            }
        }
    }
    return HasPlayed;
}

bool IsUpKeyPressed (Event& event) 
{
    if (event.type == Event::KeyPressed) 
    {
        if (event.key.code == Keyboard::Up)
        {
            return true;
        }
    }
    return false;
}

bool IsDownKeyPressed (Event& event)
{
    if (event.type == Event::KeyPressed)
    {
        if (event.key.code == Keyboard::Down)
        {
            return true;
        }
    }
    return false;
}