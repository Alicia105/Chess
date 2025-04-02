#include <iostream>
#include <string>
#include <vector>
#include "../include/piece.hpp"

using namespace std;

Piece::Piece(){
    namePiece="";
    colorPiece="";
    casePiece="";
    isCaptured=false;
    coordinatesOnBoard=vector<int>(2);
    numberOfMove=0;
}

Piece::~Piece(){}

//getters

//good
string Piece::getNamePiece(){
    return namePiece;
}

//good
string Piece::getColorPiece(){
    return colorPiece;
}

//good
string Piece::getCasePiece(){
    return casePiece;
}

//good
vector<int> Piece::getCaseCoordinate(){
    return coordinatesOnBoard;
}

//good
bool Piece::getIsCaptured(){
    return isCaptured;
}

//good
int Piece::getNumberOfMove(){
    return numberOfMove;
}


//setters

void Piece::setNamePiece(string namepiece){
    namePiece=namepiece;    
}
//good
void Piece::setColorPiece(string colorpiece){
    colorPiece=colorpiece;
}

void Piece::setCasePiece(string casepiece){
    casePiece=casepiece;
}

void Piece::setIsCaptured(bool status){
    isCaptured=status;
}

//good
void Piece::initiatePiece(vector<int> coordinates){

    //coordinates in C++: coordinates[0]=row,coordinates[1]column;
    int row=coordinates[0];
    int column=coordinates[1];

    if(row==0 || row==1){
        setColorPiece("black");
        if(row==1){
            setNamePiece("pawn");
            coordinatesOnBoard=coordinates;
            return;
        }
    }
    if(row==6 || row==7){
        setColorPiece("white");
        if(row==6){
            setNamePiece("pawn");
            coordinatesOnBoard=coordinates;
            return;
        }
    }
    if(column==0 || column==7){
        setNamePiece("rook");
        coordinatesOnBoard=coordinates;
        return;
    }
    if(column==1 || column==6){
        coordinatesOnBoard=coordinates;
        setNamePiece("knight");
        return;
    }
    if(column==2 || column==5){
        setNamePiece("bishop");
        coordinatesOnBoard=coordinates;
        return;
    }
    if(column==3){
        setNamePiece("queen");
        coordinatesOnBoard=coordinates;
        return;
    }
    if(column==4){
        setNamePiece("king");
        coordinatesOnBoard=coordinates;
        return;
    }
    
    

}

//good
void Piece::setCaseCoordinate(vector<int> coordinates){
    coordinatesOnBoard=coordinates;
}

void Piece::setNumberOfMove(int num){
    numberOfMove=num;
}
//good
void Piece::wasMoved(){
    numberOfMove+=1;
}


//piece moves

bool Piece::isMoveLegal(vector<int> coordinates){

    if(namePiece=="pawn"){
        //good
        return pawnMove(coordinates);
    }

    if(namePiece=="rook"){
        //good
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

//good
bool Piece::pawnMove(vector<int> coordinates){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;

    //stay on the board
    if(coordinatesOnBoard[0]+1<=7 || coordinatesOnBoard[0]-1>=0){
        if(coordinatesOnBoard[1]+1<=7 || coordinatesOnBoard[1]-1>=0){
            if (coordinatesOnBoard[1]!=coordinates[1]) {
                return false;
            }
            if(colorPiece=="white"){
                if(numberOfMove==0){
                    if(coordinates[0]==coordinatesOnBoard[0]-1 || coordinates[0]==coordinatesOnBoard[0]-2){
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
                    if(coordinates[0]==coordinatesOnBoard[0]+1 || coordinates[0]==coordinatesOnBoard[0]+2){
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

//good
void Piece::pawnPromotion(){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
    if (namePiece=="pawn"){
        int n;

        if(colorPiece=="white"){

            if(coordinatesOnBoard[0]==0){

                cout<<"Your pawn can be promoted !\n"<<endl;
                cout<<"Choose the type of piece you want to promote your pawn into :"<<endl;
                cout<<"1.Rook"<<endl;
                cout<<"2.Knight"<<endl;
                cout<<"3.Bishop"<<endl;
                cout<<"4.Queen"<<endl;
                cin>>n;
                cin.ignore();
            }
        }

        if(colorPiece=="black"){
            if(coordinatesOnBoard[0]==7){

                cout<<"Your pawn can be promoted !\n"<<endl;
                cout<<"Choose the type of piece you want to promote your pawn into :"<<endl;
                cout<<"1.Rook"<<endl;
                cout<<"2.Knight"<<endl;
                cout<<"3.Bishop"<<endl;
                cout<<"4.Queen"<<endl;
                cin>>n;
                cin.ignore();
            }
        }

        switch(n){
            case 1:
                setNamePiece("rook");
                break;
            case 2:
                setNamePiece("knight");
                break;
            case 3:
                setNamePiece("bishop");
                break;
            case 4:
                setNamePiece("queen");
                break;
            default:
                break;
        }

    }
    
}

//good
bool Piece::pawnCapture(vector<int> coordinates){
    //stay on the board
    if(coordinatesOnBoard[0]+1<=7 || coordinatesOnBoard[0]-1>=0){
        if(coordinatesOnBoard[1]+1<=7 || coordinatesOnBoard[1]-1>=0){
            if(colorPiece=="white"){
                //top left
                if(coordinates[0]==coordinatesOnBoard[0]-1 && coordinates[1]==coordinatesOnBoard[1]-1){
                    return true;
                }

                //top right
                if(coordinates[0]==coordinatesOnBoard[0]-1 && coordinates[1]==coordinatesOnBoard[1]+1){
                    return true;
                }
                
            }
            if(colorPiece=="black"){
                //bottom left
                if(coordinates[0]==coordinatesOnBoard[0]+1 && coordinates[1]==coordinatesOnBoard[1]-1){
                    return true;
                }

                //bottom right
                if(coordinates[0]==coordinatesOnBoard[0]+1 && coordinates[1]==coordinatesOnBoard[1]+1){
                    return true;
                }   
            }
        }
    }
    
    return false;
}

//good
bool Piece::rookMove(vector<int> coordinates){

    for(int x=0;x<=7;x++){
        //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
        
        //vertical move
        if(coordinatesOnBoard[0]+x<=7 || coordinatesOnBoard[0]-x>=0){
            if(coordinates[0]==coordinatesOnBoard[0]-x || coordinates[0]==coordinatesOnBoard[0]+x){
                 return true;
            }
        }
        
        //horizontal move
        if(coordinatesOnBoard[1]+x<=7 || coordinatesOnBoard[1]-x>=0){
            if(coordinates[1]==coordinatesOnBoard[1]-x || coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
            }
        }
    }
    
    return false;      
    
}

//good
bool Piece::knightMove(vector<int> coordinates){

    // Define possible knight moves
    vector<pair<int, int>> moves = {
        {-2, -1}, {-2, 1}, {2, -1}, {2, 1},
        {-1, -2}, {-1, 2}, {1, -2}, {1, 2}, 
    };

    // Iterate through possible moves
    for (auto move : moves) {
        int newX = coordinatesOnBoard[0] + move.first;
        int newY = coordinatesOnBoard[1] + move.second;

        // If the new coordinates match the given move, return true
        if (coordinates[0] == newX && coordinates[1] == newY) {
            return true;
        }
    }

    return false;
}

//good
bool Piece::bishopMove(vector<int> coordinates){

    for(int x=0;x<=7;x++){
        //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
        
        //stay on the board
        if(coordinatesOnBoard[0]+x<=7 || coordinatesOnBoard[0]-x>=0){
            if(coordinatesOnBoard[1]+x<=7 || coordinatesOnBoard[1]-x>=0){

                //diagonal moves

                //upper left diagonal
                if(coordinates[0]==coordinatesOnBoard[0]-x && coordinates[1]==coordinatesOnBoard[1]-x){
                    return true;
                }

                //upper right diagonal
                if(coordinates[0]==coordinatesOnBoard[0]-x && coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
                }

                //bottom left diagonal
                if(coordinates[0]==coordinatesOnBoard[0]+x && coordinates[1]==coordinatesOnBoard[1]-x){
                    return true;
                }

                //bottom right diagonal
                if(coordinates[0]==coordinatesOnBoard[0]+x && coordinates[1]==coordinatesOnBoard[1]+x){
                    return true;
                }
            }
        }
    }
    
    return false;     
}

//good
bool Piece::queenMove(vector<int> coordinates){
    for(int x=1;x<=7;x++){
        //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
        
        //stay on the board
        
        //diagonal moves

        //upper left diagonal
        if(coordinates[0]==coordinatesOnBoard[0]-x && coordinates[1]==coordinatesOnBoard[1]-x){
            return true;
        }

        //upper right diagonal
        if(coordinates[0]==coordinatesOnBoard[0]-x && coordinates[1]==coordinatesOnBoard[1]+x){
            return true;
        }

        //bottom left diagonal
        if(coordinates[0]==coordinatesOnBoard[0]+x && coordinates[1]==coordinatesOnBoard[1]-x){
            return true;
        }

        //bottom right diagonal
        if(coordinates[0]==coordinatesOnBoard[0]+x && coordinates[1]==coordinatesOnBoard[1]+x){
            return true;
        }

        //vertical move      
        if((coordinates[0]==coordinatesOnBoard[0]-x || coordinates[0]==coordinatesOnBoard[0]+x) && coordinates[1]==coordinatesOnBoard[1]){
            return true;
        }
                
                
        //horizontal move
        if((coordinates[1]==coordinatesOnBoard[1]-x || coordinates[1]==coordinatesOnBoard[1]+x) && coordinates[0]==coordinatesOnBoard[0]){
            return true;
        }
    }
    return false; 

}

//good
bool Piece::kingMove(vector<int> coordinates){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
        
        //stay on the board
        
        //diagonal moves

        //upper left diagonal
        if(coordinates[0]==coordinatesOnBoard[0]-1 && coordinates[1]==coordinatesOnBoard[1]-1){
            return true;
        }

        //upper right diagonal
        if(coordinates[0]==coordinatesOnBoard[0]-1 && coordinates[1]==coordinatesOnBoard[1]+1){
            return true;
        }

        //bottom left diagonal
        if(coordinates[0]==coordinatesOnBoard[0]+1 && coordinates[1]==coordinatesOnBoard[1]-1){
            return true;
        }

        //bottom right diagonal
        if(coordinates[0]==coordinatesOnBoard[0]+1 && coordinates[1]==coordinatesOnBoard[1]+1){
            return true;
        }

        //vertical move      
        if((coordinates[0]==coordinatesOnBoard[0]-1 || coordinates[0]==coordinatesOnBoard[0]+1) && coordinates[1]==coordinatesOnBoard[1]){
            return true;
        }
                
                
        //horizontal move
        if((coordinates[1]==coordinatesOnBoard[1]-1 || coordinates[1]==coordinatesOnBoard[1]+1) && coordinates[0]==coordinatesOnBoard[0]){
            return true;
        }
    return false; 
}

//to modify
/*void Piece::kingCastling(vector<int> coordKing,vector<int> coordRook1,vector<int> coordRook2,int selector){
    int n;
    if(selector==1){
        string kingNewPosition;
        string rookNewPosition;

        cout<<"Your can do a castling move !\n"<<endl;
        cout<<"Your king is in "<<coordKing<<".\n Your rook is in "<<coordRook1<<"."<<endl;
        cout<<"Do you want to do a castling ?"<<endl;
        cout<<"1.Yes"<<endl;
        cout<<"2.No"<<endl;
        cin>>n;

        if(n==1){

        }



        
        cout<<"3.Bishop"<<endl;
        cout<<"4.Queen"<<endl;
        cin>>n;
        cin.ignore();
            
    } 
    if(selector==2){
        cout<<"Your can do a castling !\n"<<endl;
        cout<<"Choose the type of piece you want to promote your pawn into :"<<endl;
        cout<<"1.Rook"<<endl;
        cout<<"2.Knight"<<endl;
        cout<<"3.Bishop"<<endl;
        cout<<"4.Queen"<<endl;
        cin>>n;
        cin.ignore();
            
    }
    else{
        return;
    }
}*/

/*int main(){
    vector<int> v(2);
    v[0]=7;
    v[1]=4;
    Piece p;
    p.initiatePiece(v);
   
    cout<<"name :"<<p.getNamePiece()<<endl;
    cout<<"color :"<<p.getColorPiece()<<endl;
   
    vector<int> z(2);
    z[0]=4;
    z[1]=3;
    p.setCaseCoordinate(z);

    vector<int> o(2);
    o[0]=4;
    o[1]=4;

    cout<<p.kingMove(o)<<endl;
}*/

