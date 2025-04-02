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

    public:
    Piece();
    ~Piece();

    //getters
    std::string getNamePiece();
    std::string getColorPiece();
    std::string getCasePiece();
    std::vector<int> getCaseCoordinate();
    int getNumberOfMove();
    bool getIsCaptured();

    //setters
    void setNamePiece(std::string namePiece);
    void setColorPiece(std::string colorPiece);
    void setCasePiece(std::string casePiece);
    void setIsCaptured(bool status);
    void initiatePiece(std::vector<int> coordinates);
    void setCaseCoordinate(std::vector<int> coordinates);
    void setNumberOfMove(int num);
    void wasMoved();

    //piece moves
    bool isMoveLegal(std::vector<int> coordinates);
    bool pawnMove(std::vector<int> coordinates);
    bool pawnCapture(vector<int> coordinates);
    void pawnPromotion();
    bool rookMove(std::vector<int> coordinates);
    bool knightMove(std::vector<int> coordinates);
    bool bishopMove(std::vector<int> coordinates);
    bool queenMove(std::vector<int> coordinates);
    bool kingMove(std::vector<int> coordinates);
    
};
#endif

