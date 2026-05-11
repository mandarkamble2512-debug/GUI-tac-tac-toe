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

string WinnerCheacker (vector<char>& Piece)
{
    bool IsBordFull = false; 
    bool hasNumbers = false;
    // 0 for draw
    // 1 for player in
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

    // for vertical
    if (Piece[1] == 'X' && Piece[4] == 'X' && Piece[7] == 'X')
    {
        return "1Vm";
    }
    else if (Piece[1] == 'O' && Piece[4] == 'O' && Piece[7] == 'O')
    {
        return "2Vm";
    }
    else if (Piece[0] == 'X' && Piece[3] == 'X' && Piece[6] == 'X')
    {
        return "1Vl";
    }
    else if (Piece[0] == 'O' && Piece[3] == 'O' && Piece[6] == 'O')
    {
        return "2Vl";
    }
    else if (Piece[2] == 'X' && Piece[5] == 'X' && Piece[8] == 'X')
    {
        return "1Vr";
    }
    else if (Piece[2] == 'O' && Piece[5] == 'O' && Piece[8] == 'O')
    {
        return "2Vr";
    }

    // for horizontal
    else if (Piece[0] == 'X' && Piece[1] == 'X' && Piece[2] == 'X')
    {
        return "1Ht";
    }
    else if (Piece[0] == 'O' && Piece[1] == 'O' && Piece[2] == 'O')
    {
        return "2Ht";
    }
    else if (Piece[3] == 'X' && Piece[4] == 'X' && Piece[5] == 'X')
    {
        return "1Hm";
    }
    else if (Piece[3] == 'O' && Piece[4] == 'O' && Piece[5] == 'O')
    {
        return "2Hm";
    }
    else if (Piece[6] == 'X' && Piece[7] == 'X' && Piece[8] == 'X')
    {
        return "1Hb";
    }
    else if (Piece[6] == 'O' && Piece[7] == 'O' && Piece[8] == 'O')
    {
        return "2Hb";
    }
    

    // for Digonal
    else if (Piece[2] == 'X' && Piece[4] == 'X' && Piece[6] == 'X')
    {
        return "1/";
    }
    else if (Piece[2] == 'O' && Piece[4] == 'O' && Piece[6] == 'O')
    {
        return "2/";
    }
    else if (Piece[0] == 'X' && Piece[4] == 'X' && Piece[8] == 'X')
    {
        return "1|";
    }
    else if (Piece[0] == 'O' && Piece[4] == 'O' && Piece[8] == 'O')
    {
        return "2|";
    }
    else
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

// short inputHandler(RenderWindow& window,Event evente)
// {
//     while (window.pollEvent(evente))
//     {
//         if (evente.type == Event::KeyPressed)
//             {
//                 if (evente.key.code >= Keyboard::Num1 && evente.key.code <= Keyboard::Num9)
//                 {
//                     return (evente.key.code - Keyboard::Num1) + 1;
//                 }
                
//                 if (evente.key.code >= Keyboard::Numpad1 && evente.key.code <= Keyboard::Numpad9)
//                 {
//                     return (evente.key.code - Keyboard::Numpad1) + 1;
//                 }
//             }
//     }
//     return 0;
// }

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
        while(!HasPlayed)
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
}