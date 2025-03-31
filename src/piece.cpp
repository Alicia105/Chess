#include <iostream>
#include "piece.hpp"

using namespace std;

Piece::Piece(){
    namePiece="";
    colorPiece="";
    casePiece="";
    isCaptured=false;
    coordinatesOnBoard=vector<int>(); 
}

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

vector<int> Piece::getCaseCoordinate(){
    return coordinatesOnBoard;
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

void Piece::initiatePiece(vector<int> coordinates){

    //coordinates in C++: coordinates[0]=row,coordinates[1]column;
    int row=coordinates[0];
    int column=coordinates[1];

    if(row==0 or row==1){
        setColorPiece("black");
        if(row==1){
            setNamePiece("pawn");
        }
    }
    if(row==6 or row==7){
        setColorPiece("white");
        if(row==6){
            setNamePiece("pawn");
        }
    }
    if(column==0 or column==7){
        setNamePiece("rook");
    }
    if(column==1 or column==6){
        setNamePiece("knight");
    }
    if(column==2 or column==5){
        setNamePiece("bishop");
    }
    if(column==3){
        setNamePiece("queen");
    }
    if(column==4){
        setNamePiece("king");
    }
    
    coordinatesOnBoard=coordinates;

}

void Piece::setCaseCoordinate(vector<int> coordinates){
    coordinatesOnBoard=coordinates;
}

