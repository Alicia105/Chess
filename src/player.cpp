#include <iostream>
#include <vector>
#include <map>
#include "piece.hpp"
#include "player.hpp"

using namespace std;

Player::Player(){
    colorPlayer="";
    capturedPieces=vector<Piece>();
    playerPiecesPostions=map<string,Piece>();
    numberOfMove=0;
}

Player::Player(string colorplayer){
    colorPlayer=colorplayer;
    capturedPieces=vector<Piece>();
    playerPiecesPostions=map<string,Piece>();
    numberOfMove=0;
}

Player::~Player(){}

//getters

string Player::getColorPlayer(){
    return colorPlayer;
}

vector<Piece> Player::getCapturedPieces(){
    return capturedPieces;
}

map<string,Piece> Player::getPlayerPiecesPostions(){
    return playerPiecesPostions;
}

int Player::getNumberOfMove(){
    return numberOfMove;
}


//setters
void Player::initiatePlayer(std::map<std::string,Piece> allPiecesPositionsOnBoard){
    for(auto piece : allPiecesPositionsOnBoard){
        if(piece.second.getColorPiece()==colorPlayer){
            Piece p=piece.second;
            playerPiecesPostions.insert(pair<string,Piece>(p.getNamePiece(),p));
        } 
    }
}

void Player::playedAMove(){
    numberOfMove+=1;
}