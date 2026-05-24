#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <atomic>
#include <chrono>
#include "logic.hpp"

using std::string;
using std::vector;
using sf::FloatRect;
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

void DrawTieText (RenderWindow& window, Font font)
{
    string draw = "Draw";
    Text text;
    short TextSize = 260;
    text.setCharacterSize(TextSize);
    text.setFont(font);
    text.setString(draw);
    text.setPosition(Vector2f(Vector2f(400, 400)));
    text.setFillColor(Color(128, 128, 128));

    FloatRect TextBoundryes = text.getLocalBounds();
    text.setOrigin(Vector2f(TextBoundryes.left + TextBoundryes.width/2, TextBoundryes.top + TextBoundryes.height/2));

    window.draw(text);
}

void DrawWinningLines (RenderWindow& window, CurrentGameState& State, const Vector2f Pos[])
{
    Vector2u size = window.getSize();
    RectangleShape WinningLineHorizontal(Vector2f(size.x - 20, 10));
    RectangleShape WinningLineVertical(Vector2f(10, size.y - 20));
    RectangleShape WinningLineDigonal(Vector2f(size.x - 20, 1130));

    WinningLineHorizontal.setFillColor(Color(128, 128, 128));
    WinningLineVertical.setFillColor(Color(128,128,128));

    if (State.IsHorizontal)
    {
        if (State.LinePlace == 1)
        {
            WinningLineHorizontal.setPosition(Vector2f(10, 65));
            window.draw(WinningLineHorizontal);
        }
        else if (State.LinePlace == 2)
        {
            WinningLineHorizontal.setPosition(Vector2f(10, 65 + size.y * (1.0f/3.0f)));
            window.draw(WinningLineHorizontal);
        }
        else if (State.LinePlace == 3)
        {
            WinningLineHorizontal.setPosition(Vector2f(10, 65 + 2 * (size.y * (1.0f/3.0f))));
            window.draw(WinningLineHorizontal);
        }
    }
    else if (State.IsVertical)
    {
        if (State.LinePlace == 1)
        {
            WinningLineVertical.setPosition(Vector2f(65, 10));
            window.draw(WinningLineVertical);
        }
        else if (State.LinePlace == 2)
        {
            WinningLineVertical.setPosition(Vector2f(65 + size.x * (1.0f/3.0f), 10));
            window.draw(WinningLineVertical);
        }
        else if (State.LinePlace == 3)
        {
            WinningLineVertical.setPosition(Vector2f(65 + 2 * (size.x * (1.0f/3.0f)), 10));
            window.draw(WinningLineVertical);
        }
    }
    else if (State.IsDigonalTopLeft)
    {
        WinningLineDigonal.setPosition(Vector2f(size.x / 2.0f, size.y / 2.0f));
        WinningLineDigonal.setOrigin(Vector2f(5, 565));
        WinningLineDigonal.setRotation(-45);
        window.draw(WinningLineDigonal);
    }
    else if (State.IsDigonalTopRight)
    {
        WinningLineDigonal.setPosition(Vector2f(size.x / 2.0f, size.y / 2.0f));
        WinningLineDigonal.setOrigin(Vector2f(5, 565));
        WinningLineDigonal.setRotation(45);
        window.draw(WinningLineDigonal);
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
    window.draw(bord );
    window.draw(bord2);
    window.draw(bord3);
}


