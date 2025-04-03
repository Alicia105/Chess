#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
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
    std::vector<std::vector<std::string>> getBoard();//good
    std::vector<int> getCase(std::string nameCaseInChess);//nameCaseInChess:name of the case in chess nomenclature 
    std::map<std::string,Piece>& getPiecesPositions();//good
    int getNumberOfTurn();//good


    //setters

    //coordinates in C++: coordinates[0]=row,coordinates[1]column;
    void setCase(std::vector<int> coordinates,std::string nameCaseInChess);//good ->coordinates in C++,nameCaseInChess:name of the case in chess nomenclature-->name the case with nameInChess
    std::string generateNameCase(std::vector<int> coordinates);//good ->coordinates in C++, return nameCaseInChess
    std::vector<int> generateCaseCoordinates(std::string nameCaseInChess);//good
    void initiateBoard();//good
    
    //visualization
    void printBoard();//good

    //for game logic
    bool isCaseOccupied(std::vector<int> coordinates);//good
    bool isPathClear(std::string startPosition,std::string endPosition);//good


    //bool isCaseUnderAttack();
    //bool Board::isKingUnderAttack
    int  gameLogic(Player player1,Player player2);//good
    void playerTurn(Player player1,Player player2);//good
    int makeAMove(Player currentPlayer,Player adverser);//good
    int playerExit();
    bool checkIfCorrectMoveInput(std::string moveInput);//good
    std::string processMoveInput(std::string moveInput);//good
    
};

#endif