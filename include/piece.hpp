#ifndef DEF_PIECE
#define DEF_PIECE

#include <iostream>
#include <string>
#include <vector>

class Piece{

    private:
    std::string namePiece;
    std::string colorPiece;
    std::string casePiece;//caseNameInChess nomenclature
    std::vector<int> coordinatesOnBoard;
    int numberOfMove;
    bool isCaptured;
    std::string lastMove;

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

    //piece moves
    
    bool isMoveLegal(std::vector<int> coordinates);//good
    bool pawnMove(std::vector<int> coordinates);//good
    bool pawnCapture(std::vector<int> coordinates);//good
    void pawnPromotion();//good
    bool rookMove(std::vector<int> coordinates);//good
    bool knightMove(std::vector<int> coordinates);//good
    bool bishopMove(std::vector<int> coordinates);//good
    bool queenMove(std::vector<int> coordinates);//good
    bool kingMove(std::vector<int> coordinates);//good
    
};
#endif

