#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>

using std::string;
using sf::RenderWindow;
using sf::Event;
using sf::Keyboard;

string WinnerCheacker (char Piece[])
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

bool PlayerMove (RenderWindow& window, Event event, char Piece[]) // player uses X;
{
    short Value = inputHandler(event);

    if (Value >= 1 && Value <= 9)
    {
        if (Piece[Value - 1] != 'X' && Piece[Value -1] != 'O')
        {
            Piece[Value -1] = 'X';
            return true;
        }
    }

    return false;
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

void ComputerMove(char Piece[]) // computer uses O
{
    bool IsPlayed = false;
    bool Hasplayed = false;
    short randomMove;
    short num;
    if (Piece[0] == 'X' && !Hasplayed)
    {
        if (Piece[1] == 'X' && FindIsSpaceOccupied(2, Piece))
        {
            Piece[2] = 'O';
            Hasplayed = true;
        }
        else if (Piece[3] == 'X' && FindIsSpaceOccupied(6, Piece))
        {
            Piece[6] = 'O';
            Hasplayed = true;

        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(8, Piece))
        {
            Piece[8] = 'O';
            Hasplayed = true;
        }
    }
    else if (Piece[1] == 'X' && !Hasplayed)
        {
            if (Piece[0] == 'X' && FindIsSpaceOccupied(2, Piece))
            {
                Piece[2] = 'O';
                Hasplayed = true;
            }
            else if (Piece[2] == 'X' && FindIsSpaceOccupied(0, Piece))
            {
                Piece[0] = 'O';
                Hasplayed = true;
            }
            else if (Piece[4] == 'X' && FindIsSpaceOccupied(7, Piece))
            {
                Piece[7] = 'O';
                Hasplayed = true;
            }        
        }
    else if (Piece[2] == 'X' && !Hasplayed)
    {
        if (Piece[1] == 'X' && FindIsSpaceOccupied(0, Piece))
        {
            Piece[0] = 'O';
            Hasplayed = true;
        }
        else if (Piece[5] == 'X' && FindIsSpaceOccupied(8, Piece))
        {
            Piece[8] = 'O';
            Hasplayed = true;
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(6, Piece))
        {
            Piece[6] = 'O';
            Hasplayed = true;
        }
    }
    else if (Piece[3] == 'X' && !Hasplayed)
    {
        if (Piece[0] == 'X' && FindIsSpaceOccupied(6 ,Piece))
        {
            Piece[6] = 'O';
            Hasplayed = true;
        }
        else if (Piece[4] == 'X' && FindIsSpaceOccupied(5 ,Piece))
        {
            Piece[5] = 'O';
            Hasplayed = true;
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
    else 
    {
        
        
        while (!Hasplayed)
        {
            randomMove = rand() % 9;
            num = randomMove;
            if (FindIsSpaceOccupied(randomMove ,Piece))
            {
                Piece[randomMove] = 'O';
                Hasplayed = true;
            }
        }
    }
}