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

    bool isCaptured;

    public:
    Piece();
    ~Piece();

    //getters
    std::string getNamePiece();
    std::string getColorPiece();
    std::string getCasePiece();
    std::vector<int> getCaseCoordinate();
    bool getIsCaptured();

    //setters
    void setNamePiece(std::string namePiece);
    void setColorPiece(std::string colorPiece);
    void setCasePiece(std::string casePiece);
    void setIsCaptured(bool status);
    void initiatePiece(std::vector<int> coordinates);
    void setCaseCoordinate(vector<int> coordinates);
    
};
#endif
