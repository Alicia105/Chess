#include <iostream>
#include <string>

class Piece{

    std::string namePiece;
    std::string colorPiece;
    std::string casePiece;
    bool isCaptured;

    Piece();
    ~Piece();

    //getters
    std::string getNamePiece();
    std::string getColorPiece();
    std::string getCasePiece();
    bool getIsCaptured();

    //setters
    void setNamePiece(std::string namePiece);
    void setColorPiece(std::string colorPiece);
    void setCasePiece(std::string casePiece);
    void setIsCaptured(bool status);
    
};
