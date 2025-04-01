#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <vector>
#include <map>
#include "piece.hpp"

class Board{

    private:
    std::vector<std::vector<std::string>> grid;//chess grid of 8x8, eac case contains a string representing the name of the case in traditional chess nomenclature
    std::map<std::string,Piece> piecesPostions;
    int numberOfTurn;

    public :
    Board();
    ~Board();

    //geters
    std::vector<std::vector<std::string>> getBoard();
    std::vector<int>getCase(string nameCaseInChess);//nameCaseInChess:name of the case in chess nomenclature 
    std::map<std::string,Piece> getPiecesPostions();


    //setters

    //coordinates in C++: coordinates[0]=row,coordinates[1]column;
    
    std::string setCase(vector<int> coordinates,string nameCaseInChess);//coordinates in C++,nameCaseInChess:name of the case in chess nomenclature-->name the case with nameInChess
    std::string generateNameCase(vector<int> coordinates);//coordinates in C++, return nameCaseInChess
    void initiateBoard();
};
#endif