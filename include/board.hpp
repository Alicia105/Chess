#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <vector>
#include <map>
#include "piece.hpp"

class Board{

    std::vector<std::vector<std::string>> grid;//chess grid of 8x8, eac case contains a string representing the name of the case in traditional chess nomenclature
    std::map<std::string,Piece> piecesPostions;

    Board();
    ~Board();

    //geters
    std::vector<std::vector<std::string>> getBoard();
    std::vector<int>Board::getCase(string nameCase); //nameCase:name of the case in chess in nomenclature
    std::map<std::string,Piece> getPiecesPostions();


    //setters
    std::vector<std::vector<std::string>> setBoard();
    
    std::string Board::setCase(vector<int> coordinates);
    std::string generateNameCase(vector<int> coordinates);
    

};
#endif