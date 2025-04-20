#ifndef DEF_CHESSGUI
#define DEF_CHESSGUI

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include "board.hpp" 

sf::Vector2f getTilePosition(int row, int col);
int displayChessBoard(Board b, Player p1, Player p2, bool playAI);

#ifndef
