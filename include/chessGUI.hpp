#ifndef DEF_CHESSGUI
#define DEF_CHESSGUI

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <iostream>
#include "board.hpp" 
#include "piece.hpp"

sf::Vector2f getTilePosition(int row, int col);
std::map<std::string, std::string> stateBoard(Board b);
bool askOpponentType();
char promptPromotion(sf::RenderWindow& window, const map<string, sf::Sprite>& pieceSprites, const string& color);
int displayChessBoard(Board& b, Player& p1, Player& p2, bool playAI);

#ifndef
