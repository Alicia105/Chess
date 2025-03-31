#include <iostream>
#include "piece.hpp"

using namespace std;

Piece::Piece(){}
Piece::~Piece(){}

//getters
string Piece::getNamePiece(){
    return namePiece;
}

string Piece::getColorPiece(){
    return colorPiece;
}

string Piece::getCasePiece(){
    return casePiece;
}

bool Piece::getIsCaptured(){
    return isCaptured;
}

//setters
void Piece::setNamePiece(string namepiece){
    namePiece=namepiece;    
}

void Piece::setColorPiece(string colorpiece){
    colorPiece=colorpiece;
}

void Piece::setCasePiece(string casepiece){
    casePiece=casepiece;
}

void Piece::setIsCaptured(bool status){
    isCaptured=status;
}