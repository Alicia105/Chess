#ifndef DEF_PLAYER
#define DEF_PLAYER

#include <iostream>
#include <vector>
#include <map>
#include "board.hpp"
#include "piece.hpp"

class Player
{
    private:
    std::string colorPlayer;
    std::vector<Piece> capturedPieces;
    std::map<std::string,Piece> playerPiecesPostions;
    int numberOfMove;

    public:

    Player();
    Player(std::string colorplayer);
    ~Player();

    //getters
    std::string getColorPlayer();
    
    std::vector<Piece> getCapturedPieces();
    
    std::map<std::string,Piece> getPlayerPiecesPostions();
    
    int getNumberOfMove();    

    //setters
    void setColorPlayer(std::string colorplayer);
    
    void setCapturedPieces();
    
    void setPlayerPiecesPostions();
    
    void setNumberOfMove(int number);    

    void initiatePlayer(std::map<std::string,Piece> allPiecesPositionsOnBoard);
    
    void playedAMove();

};

#endif