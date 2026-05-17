#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include <future>
#include <vector>

using std::string;
using std::vector;
using std::ref;
using std::future;
using std::async;
using sf::RenderWindow;
using sf::Event;
using sf::Keyboard;

struct CurrentGameState
{
    bool HasPlayerWon      = false;
    bool HasComputerWon    = false;
    bool IsHorizontal      = false;
    bool IsVertical        = false;
    bool IsDigonalTopLeft  = false;
    bool IsDigonalTopRight = false;
    short LinePlace          = 0;
};

vector<bool> StatusStringDecoder (string Status, CurrentGameState& state)
{
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
                state.LinePlace = LinePlace;
                break;
            
            case 'm':
                LinePlace = 2;
                state.LinePlace = LinePlace;
                break;
            
            case 'r':
                LinePlace = 3;
                state.LinePlace = LinePlace;
                break;
            }
        }
    }

    return {HasPlayerWon, HasComputerWon, IsHorizontal, IsVertical, IsDigonalTopLeft, IsDigonalTopRight};
}

void CurrentGameStateSetter (string status, CurrentGameState& state)
{
    vector<bool> decoded = StatusStringDecoder(status, state);
    state.HasPlayerWon      = decoded[0];
    state.HasComputerWon    = decoded[1];
    state.IsHorizontal      = decoded[2];
    state.IsVertical        = decoded[3];
    state.IsDigonalTopLeft  = decoded[4];
    state.IsDigonalTopRight = decoded[5];
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
        else return "0";
    }
}


bool PlayerMove(sf::Event& event, vector<char>& Piece) 
{
    if (event.type == sf::Event::KeyPressed) 
    {
        int index = -1;
        if (event.key.code >= sf::Keyboard::Num1 && event.key.code <= sf::Keyboard::Num9)
            index = event.key.code - sf::Keyboard::Num1;
        else if (event.key.code >= sf::Keyboard::Numpad1 && event.key.code <= sf::Keyboard::Numpad9)
            index = event.key.code - sf::Keyboard::Numpad1;

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