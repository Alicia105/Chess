#ifndef PIECE_HPP
#define PIECE_HPP

#include <iostream>
#include <string>
#include <vector>

class Piece{

    private:
    std::string namePiece; //name of the chess piece
    std::string colorPiece; //color of the chess piece
    std::string casePiece; //case name in Chess nomenclature (traditional coordinates (ex: a1)
    std::vector<int> coordinatesOnBoard; //coordinates on the board with numbers from 0 to 7 (ex: (0,7)= "a1")
    int numberOfMove; //number of times this piece was moved
    bool isCaptured; //flag to know if this piece has been captured
    bool isPromoted; //flag to know if this piece has been promoted (used only for pawns)
    std::string lastMove; //case name of the last position of this piece

    public:
    Piece();//good
    ~Piece();//good

    //getters

    std::string getNamePiece();//good
    std::string getColorPiece();//good
    std::string getCasePiece();//good
    std::vector<int> getCaseCoordinate();//good
    int getNumberOfMove();//good
    bool getIsCaptured();//good
    std::string getLastMove();
    bool getIsPromoted();
    

    //setters

    void setNamePiece(std::string namePiece);//good
    void setColorPiece(std::string colorPiece);//good
    void setCasePiece(std::string casePiece);//good
    void setIsCaptured(bool status);//good
    void initiatePiece(std::vector<int> coordinates);//good
    void setCaseCoordinate(std::vector<int> coordinates);//good
    void setNumberOfMove(int num);//good
    void wasMoved();//good
    void setLastMove(std::string last);
    void setIsPromoted(bool status);

    //piece moves
    
    bool isMoveLegal(std::vector<int> coordinates);//good
    bool pawnMove(std::vector<int> coordinates);//good
    bool pawnCapture(std::vector<int> coordinates);//good
    bool canBePromoted();
    void pawnPromotion();//good
    bool rookMove(std::vector<int> coordinates);//good
    bool knightMove(std::vector<int> coordinates);//good
    bool bishopMove(std::vector<int> coordinates);//good
    bool queenMove(std::vector<int> coordinates);//good
    bool kingMove(std::vector<int> coordinates);//good
    
};
#endif

