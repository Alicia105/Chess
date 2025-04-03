#include <iostream>
#include <vector>
#include <map>
#include "../include/piece.hpp"
#include "../include/player.hpp"

using namespace std;

//good
Player::Player(){
    colorPlayer="";
    capturedPieces=vector<Piece>();
    playerPiecesPostions=map<string,Piece>();
    numberOfMove=0;
}

//good
Player::Player(string colorplayer){
    colorPlayer=colorplayer;
    capturedPieces=vector<Piece>();
    playerPiecesPostions=map<string,Piece>();
    numberOfMove=0;
}

//good
Player::~Player(){}

//getters

//good
string Player::getColorPlayer(){
    return colorPlayer;
}

//good-> return the reference to the variable instead of a tempoary copy 
vector<Piece>& Player::getCapturedPieces(){
    return capturedPieces;
}

//good-> return the reference to the variable instead of a tempoary copy 
map<string,Piece>& Player::getPlayerPiecesPositions(){
    return playerPiecesPostions;
}

//good
int Player::getNumberOfMove(){
    return numberOfMove;
}


//setters

//recheck--> need for a copy constructor
void Player::initiatePlayer(std::map<std::string,Piece> allPiecesPositionsOnBoard){
    for(auto piece : allPiecesPositionsOnBoard){
        //cout << "Checking piece at: " << piece.first << endl;
        if(piece.second.getColorPiece()==colorPlayer){
            Piece p=piece.second;//be carefull !
            //cout << "Adding " << piece.first << " to player pieces" << endl;
            playerPiecesPostions.insert(pair<string,Piece>(piece.first,p));
        }
        //for tests
        /*else{
            cout<<"Piece "<<piece.second.getNamePiece()<<" can't be added"<<endl;
        }*/
    }
}

//good
void Player::setColorPlayer(std::string color){
    colorPlayer=color;
}

//good
void Player::setCapturedPiece(Piece p){
    capturedPieces.push_back(p);
}

//good
void Player::setNumberOfMove(int number){
    numberOfMove=number;
}

//good
void Player::playedAMove(){
    numberOfMove+=1;
}

/*int main(){
    
    //initialisation "board"
    vector<int> v(2);//case a6
    v[0]=6;
    v[1]=0;

    vector<int> w(2);//c7
    w[0]=7;
    w[1]=2;

    vector<int> x(2);//e4
    x[0]=0;
    x[1]=4;

    vector<int> y(2);//e4
    y[0]=0;
    y[1]=7;

    map<string,Piece> allPiecesPositionsOnBoard;//simulate board
    
    //white pieces
    Piece a;
    a.initiatePiece(v); //pawn
    cout<<a.getNamePiece()<<endl;
    allPiecesPositionsOnBoard.insert(pair<string,Piece>("a6",a));

    Piece b;
    b.initiatePiece(w); //bishop
    cout<<b.getNamePiece()<<endl;
    allPiecesPositionsOnBoard.insert(pair<string,Piece>("c7",b));

    //black piece
    Piece p;
    p.initiatePiece(x); //king
    cout<<p.getNamePiece()<<endl;
    allPiecesPositionsOnBoard.insert(pair<string,Piece>("e4",p));

    Piece r;
    r.initiatePiece(y); //rook
    cout<<r.getNamePiece()<<endl;
   
    Player pl("white");
    pl.initiatePlayer(allPiecesPositionsOnBoard);
    cout<<"number of pieces : "<<pl.getPlayerPiecesPositions().size()<<endl;
    cout<<pl.getPlayerPiecesPositions().count("a6")<<endl;
    cout<<"name of piece a6: "<<pl.getPlayerPiecesPositions().at("a6").getNamePiece()<<endl;
    pl.getPlayerPiecesPositions().at("a6").setNamePiece("YOLO !");
    cout<<"new name of piece a6: "<<pl.getPlayerPiecesPositions().at("a6").getNamePiece()<<endl;


    cout<<"size : "<<pl.getCapturedPieces().size()<<endl;
    pl.setCapturedPiece(p);
    pl.setCapturedPiece(r);
    cout<<"new size : "<<pl.getCapturedPieces().size()<<endl;
    
    cout<<"first captured piece : "<<pl.getCapturedPieces()[0].getNamePiece()<<endl;
    cout<<"second captured piece : "<<pl.getCapturedPieces()[1].getNamePiece()<<endl;
    pl.getCapturedPieces()[0].setNamePiece("Yo");
    cout<<"new name first captured piece : "<<pl.getCapturedPieces()[0].getNamePiece()<<endl;

}*/