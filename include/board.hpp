#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <vector>
#include <map>
#include "piece.hpp"
#include "player.hpp"

class Board{

    private:
    std::vector<std::vector<std::string>> grid;//chess grid of 8x8, eac case contains a string representing the name of the case in traditional chess nomenclature
    std::map<std::string,Piece> piecesPositions;
    int numberOfTurn;

    public :
    Board();
    ~Board();

    //geters
    std::vector<std::vector<std::string>> getBoard();
    std::vector<int>getCase(std::string nameCaseInChess);//nameCaseInChess:name of the case in chess nomenclature 
    std::map<std::string,Piece> getPiecesPositions();


    //setters

    //coordinates in C++: coordinates[0]=row,coordinates[1]column;
    std::string setCase(vector<int> coordinates,string nameCaseInChess);//coordinates in C++,nameCaseInChess:name of the case in chess nomenclature-->name the case with nameInChess
    std::string generateNameCase(vector<int> coordinates);//coordinates in C++, return nameCaseInChess
    std::vector<int> generateCaseCoordinates(std::string nameCaseInChess);
    void initiateBoard();
    
    //visualization
    void printBoard();

    //for game logic
    bool isCaseOccupied(vector<int> coordinates);


    //bool isCaseUnderAttack();
    //bool Board::isKingUnderAttack
    void playerTurn(Player player1,Player player2);
    int  gameLogic(Player player1,Player player2);
    void playerTurn(Player player);
    int makeAMove(Player currentPlayer,Player adverser);
    int playerExit();
    
};
#endif