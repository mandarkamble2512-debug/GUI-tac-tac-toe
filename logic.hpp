#include <SFML/Graphics.hpp>

using sf::RenderWindow;
using sf::Event;
using sf::Keyboard;


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