#include <iostream>
#include "piece.hpp"

using namespace std;

Piece::Piece(){
    namePiece="";
    colorPiece="";
    casePiece="";
    isCaptured=false;
    coordinatesOnBoard=vector<int>();
    numberOfMove=0;
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

int Piece::getNumberOfMove(){
    return numberOfMove;
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

void Piece::setNumberOfMove(int num){
    numberOfMove=num;
}

//piece moves

bool Piece::isMoveLegal(vector<int> coordinates,string option){

    if(namePiece=="pawn"){
        return pawnMove(coordinates);
    }

    if(namePiece=="rook"){
        return rookMove(coordinates);
    }

    if(namePiece=="knight"){
        return knightMove(coordinates);
    }

    if(namePiece=="bishop"){

        return bishopMove(coordinates);
    }

    if(namePiece=="queen"){
        return queenMove(coordinates);
    }

    if(namePiece=="king"){
        return kingMove(coordinates);
    }

    return false;
}

//missing promotion option and check board boundaries
bool Piece::pawnMove(vector<int> coordinates){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;

    //stay on the board
    if(coordinatesOnBoard[0]+1<=7 or coordinatesOnBoard[0]-1>=0){
        if(coordinatesOnBoard[0]+1<=7 or coordinatesOnBoard[0]-1>=0){
            if(colorPiece=="white"){
                if(numberOfMove==0){
                    if(coordinates[0]==coordinatesOnBoard[0]-1 or coordinates[0]==coordinatesOnBoard[0]-2){
                        return true;
                    }
                }
                else{
                    if(coordinates[0]==coordinatesOnBoard[0]-1){
                        return true;
                    }
                }
                
            }
        
            if(colorPiece=="black"){
                if(numberOfMove==0){
                    if(coordinates[0]==coordinatesOnBoard[0]+1 or coordinates[0]==coordinatesOnBoard[0]+2){
                        return true;
                    }
                }
                else{
                    if(coordinates[0]==coordinatesOnBoard[0]+1){
                        return true;
                    }
                }
            }
        }
    }
    
    return false;
   
}

bool Piece::rookMove(vector<int> coordinates){

    for(int x=0;x<=7;x++){
        //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
        
        //vertical move
        if(coordinatesOnBoard[0]+x<=7 or coordinatesOnBoard[0]-x>=0){
            if(coordinates[0]==coordinatesOnBoard[0]-x or coordinates[0]==coordinatesOnBoard[0]+x){
                 return true;
            }
        }
        
        //horizontal move
        if(coordinatesOnBoard[1]+x<=7 or coordinatesOnBoard[1]-x>=0){
            if(coordinates[1]==coordinatesOnBoard[1]-x or coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
            }
        }
    }
    
    return false;      
    
}

bool Piece::knightMove(vector<int> coordinates){

    if (coordinatesOnBoard[0]+2<=7 or coordinatesOnBoard[0]-2>=0){
        if(coordinates[1]==coordinatesOnBoard[1]-1 or coordinates[1]==coordinatesOnBoard[1]+1){
            return true;
        }
    }
    
    if (coordinatesOnBoard[1]+2<=7 or coordinatesOnBoard[1]-2>=0){
        if(coordinates[0]==coordinatesOnBoard[0]-1 or coordinates[0]==coordinatesOnBoard[0]+1){
            return true;
        }
    }
    return false;
}

bool Piece::bishopMove(vector<int> coordinates){

    for(int x=0;x<=7;x++){
        //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
        
        //stay on the board
        if(coordinatesOnBoard[0]+x<=7 or coordinatesOnBoard[0]-x>=0){
            if(coordinatesOnBoard[1]+x<=7 or coordinatesOnBoard[1]-x>=0){

                //diagonal moves

                //upper left diagonal
                if(coordinates[0]==coordinatesOnBoard[0]-x and coordinates[1]==coordinatesOnBoard[1]-x){
                    return true;
                }

                //upper right diagonal
                if(coordinates[0]==coordinatesOnBoard[0]-x and coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
                }

                //bottom left diagonal
                if(coordinates[0]==coordinatesOnBoard[0]+x and coordinates[1]==coordinatesOnBoard[1]-x){
                    return true;
                }

                //bottom right diagonal
                if(coordinates[0]==coordinatesOnBoard[0]+x and coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
                }
            }
        }
    }
    
    return false;     
}

bool Piece::queenMove(vector<int> coordinates){
    for(int x=0;x<=7;x++){
        //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
        
        //stay on the board
        if(coordinatesOnBoard[0]+x<=7 or coordinatesOnBoard[0]-x>=0){
            if(coordinatesOnBoard[1]+x<=7 or coordinatesOnBoard[1]-x>=0){

                //diagonal moves

                //upper left diagonal
                if(coordinates[0]==coordinatesOnBoard[0]-x and coordinates[1]==coordinatesOnBoard[1]-x){
                    return true;
                }

                //upper right diagonal
                if(coordinates[0]==coordinatesOnBoard[0]-x and coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
                }

                //bottom left diagonal
                if(coordinates[0]==coordinatesOnBoard[0]+x and coordinates[1]==coordinatesOnBoard[1]-x){
                    return true;
                }

                //bottom right diagonal
                if(coordinates[0]==coordinatesOnBoard[0]+x and coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
                }

                //vertical move
                if(coordinatesOnBoard[0]+x<=7 or coordinatesOnBoard[0]-x>=0){
                    if(coordinates[0]==coordinatesOnBoard[0]-x or coordinates[0]==coordinatesOnBoard[0]+x){
                        return true;
                    }
                }
                
                //horizontal move
                if(coordinatesOnBoard[1]+x<=7 or coordinatesOnBoard[1]-x>=0){
                    if(coordinates[1]==coordinatesOnBoard[1]-x or coordinates[1]==coordinatesOnBoard[1]+x){
                            return true;
                    }
                }
            }
        }
    }
    
    return false;     

}

//missing castling option
bool Piece::kingMove(vector<int> coordinates){

    //stay on the board
    if(coordinatesOnBoard[0]+1<=7 or coordinatesOnBoard[0]-1>=0){
        if(coordinatesOnBoard[1]+1<=7 or coordinatesOnBoard[1]-1>=0){

            //diagonal moves

            //upper left diagonal
            if(coordinates[0]==coordinatesOnBoard[0]-1 and coordinates[1]==coordinatesOnBoard[1]-1){
                return true;
            }

            //upper right diagonal
            if(coordinates[0]==coordinatesOnBoard[0]-1 and coordinates[1]==coordinatesOnBoard[1]+1){
                return true;
            }

            //bottom left diagonal
            if(coordinates[0]==coordinatesOnBoard[0]+1 and coordinates[1]==coordinatesOnBoard[1]-1){
                return true;
            }

            //bottom right diagonal
            if(coordinates[0]==coordinatesOnBoard[0]+1 and coordinates[1]==coordinatesOnBoard[1]+1){
                return true;
            }

            //vertical move
            if(coordinatesOnBoard[0]+1<=7 or coordinatesOnBoard[0]-1>=0){
                if(coordinates[0]==coordinatesOnBoard[0]-1 or coordinates[0]==coordinatesOnBoard[0]+1){
                    return true;
                }
            }
            
            //horizontal move
            if(coordinatesOnBoard[1]+1<=7 or coordinatesOnBoard[1]-1>=0){
                if(coordinates[1]==coordinatesOnBoard[1]-1 or coordinates[1]==coordinatesOnBoard[1]+1){
                        return true;
                }
            }
        }
    }

    return false;

}

