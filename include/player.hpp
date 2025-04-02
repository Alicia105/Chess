#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <iostream>
#include <vector>
#include <map>
#include "piece.hpp"

class Player
{
    private:
    std::string colorPlayer;
    std::vector<Piece> capturedPieces;
    std::map<std::string,Piece> playerPiecesPostions;
    int numberOfMove;

    public:

    Player();//good
    Player(std::string colorplayer);//good
    ~Player();//good

    //getters
    std::string getColorPlayer();//good
    
    std::vector<Piece>& getCapturedPieces();//good-> return the reference to the variable instead of a tempoary copy 
    
    std::map<std::string,Piece>& getPlayerPiecesPositions();//good-> return the reference to the variable instead of a tempoary copy 
    
    int getNumberOfMove();//good

    //setters
    void setColorPlayer(std::string color);//good
    
    void setCapturedPiece(Piece p);//good
    
    void setNumberOfMove(int number);//good   

    void initiatePlayer(std::map<std::string,Piece> allPiecesPositionsOnBoard);//good
    
    void playedAMove();//good

};

#endif