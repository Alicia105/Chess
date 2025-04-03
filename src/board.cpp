#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <string>
#include "../include/board.hpp"
#include "../include/piece.hpp"
#include "../include/player.hpp"

using namespace std;

Board::Board(){
    grid=vector<vector<string>>(8,vector<string>(8));
    piecesPositions=map<string,Piece>();
    numberOfTurn=0;
}

Board::~Board(){}

//getters

//good
vector<vector<string>> Board::getBoard(){
    return grid;
}

vector<int> Board::getCase(string nameCase){

    //coordinates in C++: coordinates[0]=row,coordinates[1]column;
    vector<int> coordinateCase(2);

    for (int i=0; i<grid.size(); i++){
        for(int j=0;j<grid[i].size();j++){
            if(grid[i][j]==nameCase){
                coordinateCase[0]=i;
                coordinateCase[1]=j;
                return coordinateCase;               
            }

        }
    }

    return coordinateCase;

}

map<string,Piece>& Board::getPiecesPositions(){
    return piecesPositions;
}

//setters

//good
void Board::setCase(vector<int> coordinates,string nameCase){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
    int row=coordinates[0];
    int column=coordinates[1];   

    grid[row][column]=nameCase;
}

//good
string Board::generateNameCase(vector<int> coordinates){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;    
    int i=coordinates[0];
    int j=coordinates[1];

    char column;

    switch(j){
        case 0:
            column='a';
            break;
        case 1:
            column='b';
            break;
        case 2:
            column='c';
            break;
        case 3:
            column='d';
            break;
        case 4:
            column='e';
            break;
        case 5:
            column='f';
            break;
        case 6:
            column='g';
            break;
        case 7:
            column='h';
            break;
        default:
            break;
    }

    int numRow=-i+8;
    
    string nameCase=string(1,column)+to_string(numRow);

    return nameCase;
}

//good
vector<int> Board::generateCaseCoordinates(string nameCaseInChess){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
    char c=tolower(nameCaseInChess[0]);
    char r=nameCaseInChess[1];
    
    vector<int> coord(2);

    int column;
    int convertRow=stoi(string(1,r));;

    switch(c){
        case 'a':
            column=0;
            break;
        case 'b':
            column=1;
            break;
        case 'c':
            column=2;
            break;
        case 'd':
            column=3;
            break;
        case 'e':
            column=4;
            break;
        case 'f':
            column=5;
            break;
        case 'g':
            column=6;
            break;
        case 'h':
            column=7;
            break;
        default:
            break;
    }

    int row=-convertRow+8;
    
    coord[0]=row;
    coord[1]=column;

    return coord;
}

//good
void Board::initiateBoard(){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;

    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            
            vector<int> coord(2);
            coord[0]=i;
            coord[1]=j;
            string s=generateNameCase(coord);

            //Board
            grid[i][j]=s;


            if(i==0 or i==1 or i==6 or i==7){
                //Piece
                Piece p;
                p.initiatePiece(coord);
                p.setCasePiece(s);
                piecesPositions.insert(pair<string,Piece>(s,p));
            }                  

        }
    }
}

//vizualisation
//good
void Board::printBoard(){
    //print header
    cout<<"X a b c d e f g h"<<endl;
    for(int i=0; i<grid.size();i++){

        //print column name
        int row=-i+8;            
        string line=to_string(row)+" ";

        //print rest of the board
        for(int j=0; j<grid[0].size();j++){
            vector<int> coordinates(2);
            coordinates[0]=i;
            coordinates[1]=j;

            string nameCase=generateNameCase(coordinates);
            if (piecesPositions.count(nameCase)){
                string namePiece=piecesPositions.at(nameCase).getNamePiece();
                string colorPiece=piecesPositions.at(nameCase).getColorPiece();

                if(colorPiece=="black"){
                    if(namePiece=="knight"){
                        char currentPiece = toupper('n');
                        line += currentPiece;
                    }
                    else{
                        char currentPiece = toupper(namePiece[0]);
                        line += currentPiece;
                    }
                }
                else{
                    if(namePiece=="knight"){
                        line +='n';
                    }
                    else{
                        line += namePiece[0];
                    }
                    
                }
               
            }
            else{
                line+=".";
            }

            line+=" ";//for better spacing
        }
        cout<<line<<endl;
    }    
}

//for game logic
//good
bool Board::isCaseOccupied(vector<int> coordinates){
    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;    
    int row=coordinates[0];
    int column=coordinates[1];

    string nameCase=generateNameCase(coordinates);

    return piecesPositions.count(nameCase);
}


/*int main(){

    Board b;
    b.initiateBoard();
    cout<<"row :"<<b.getBoard().size()<<endl;
    cout<<"column : "<<b.getBoard()[0].size()<<endl;
    b.printBoard();

    Player p1("white");
    Player p2("black");

    p1.initiatePlayer(b.getPiecesPositions());
    p2.initiatePlayer(b.getPiecesPositions());

    vector<int> v(2);//case a6
    v[0]=4;
    v[1]=0;
    
    cout<<"is case occupied :"<<b.isCaseOccupied(v)<<endl;
    cout<<"case name :"<<b.getPiecesPositions().at("a7").getNamePiece()<<endl;
    b.getPiecesPositions().at("a7").setNamePiece("Yo");
    cout<<"new case name :"<<b.getPiecesPositions().at("a7").getNamePiece()<<endl;

}*/
    //initialisation "board"
    /*vector<int> v(2);//case a6
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
    cout<<"new name first captured piece : "<<pl.getCapturedPieces()[0].getNamePiece()<<endl;*/

//}

//to complete
//bool Board::isCaseUnderAttack
//bool Board::isKingUnderAttack
/*
int Board::gameLogic(Player player1,Player player2){
    int n=0;
    if(numberOfTurn==0){
        if(player1.getColorPlayer()=="white"){
            cout<<"You're the one to start player 1.\n"<<endl;
            //player1 play
            playerTurn(player1,player2);
        }

        //player2 play
        playerTurn(player2,player1);
        numberOfTurn++;

        while(n==0){
            n=playerExit();
        }
           
        return n;
    }

    playerTurn(player1);
    playerTurn(player2);
    numberOfTurn++;

    while(n==0){
        n=playerExit();
    }
    
    return n;

}

void Board::playerTurn(Player currentPlayer,Player adverser){
    int t=1;
    
    printBoard();

    if(currentPlayer.getColorPlayer()=="white"){

        cout<<"\nIt's your turn player 1\n"<<endl;
    }
    if(currentPlayer.getColorPlayer()=="black"){

        cout<<"\nIt's your turn player 2\n"<<endl;
    }

    while(t!=0){
       t=makeAMove(currentPlayer,adverser);
    }    
}

int Board::makeAMove(Player currentPlayer,Player adverser){

    //special move :castling :
    /*if(isCastlingPossible()){
        //ask if player want to do a castling
        if(yes){
            // function that gives the piece the player can use for the castling
            //ask where he wants to put the king
            //ask where he wants to move th tower

            //actualise  player and board position map with new coordinates
            currentPlayer.playedAMove();
            return 0;
        }
    }
    else the turn is a classic one;
    

    //choose piece to move
    string startPosition;
    cout<<"Enter the initial position of the piece you want to move :"<<endl;
    cin>>startPosition;

    //choose final position
    string endPosition;
    cout<<"Enter the final position of the piece you want to move :"<<endl;
    cin>>endPosition;

    vector<int> v(2);
    v=generateCaseCoordinates(endPosition);

    Piece p=piecesPositions.at(startPosition);

    if(p.getColorPiece()==currentPlayer.getColorPlayer()){
        if(p.isMoveLegal(v)){
            //if final case empty
            if(not piecesPositions.count(endPosition)){
                p.setCaseCoordinate(v);
                p.setCasePiece(endPosition);
                p.wasMoved();
                piecesPositions.insert(pair<string,Piece>(endPosition,p));
                currentPlayer.getPlayerPiecesPositions().insert(pair<string,Piece>(endPosition,p));
                piecesPositions.erase(startPosition);
                currentPlayer.getPlayerPiecesPositions().erase(startPosition);
                currentPlayer.playedAMove();

            }

            //if final case is occupied by one of player's piece
            if(isCaseOccupied(v) and piecesPositions.at(endPosition).getColorPiece()==currentPlayer.getColorPlayer()){

                cout<<"Error : Moving "<<piecesPositions.at(startPosition).getNamePiece()<<"from "<<startPosition
                <<"to "<<endPosition<< " is impossible !"<<endl;
                return 1;
            }

            //if final case is occupied by one of the adverser's piece
            if(isCaseOccupied(v) and piecesPositions.at(endPosition).getColorPiece()==adverser.getColorPlayer()){
                p.setCaseCoordinate(v);
                p.setCasePiece(endPosition);
                p.wasMoved();

                Piece adverserP=piecesPositions.at(endPosition);
                adverserP.setIsCaptured(true);

                currentPlayer.getCapturedPieces().push_back(adverserP);
                
                piecesPositions.insert(pair<string,Piece>(endPosition,p));
                piecesPositions.erase(startPosition);
                adverser.getPlayerPiecesPositions().erase(endPosition);
                currentPlayer.playedAMove();
            }    
        }

        //special case : pawn Capture: if final case is occupied by one of the adverser's piece and we are moving a pawn to make a capture
        if(isCaseOccupied(v) and piecesPositions.at(endPosition).getColorPiece()==adverser.getColorPlayer() and p.getNamePiece()=="pawn"){
            //if pawn can reach it to capture it
            if(p.pawnCapture(v)){

                p.setCaseCoordinate(v);
                p.setCasePiece(endPosition);

                Piece adverserP=piecesPositions.at(endPosition);
                adverserP.setIsCaptured(true);

                currentPlayer.getCapturedPieces().push_back(adverserP);
                
                piecesPositions.insert(pair<string,Piece>(endPosition,p));
                piecesPositions.erase(startPosition);
                adverser.getPlayerPiecesPositions().erase(endPosition);
                currentPlayer.playedAMove();

            }
        }     

        //special case : pawn promotion : if the piece we just moved is a pawn and it reached the adverser's camp
        if(currentPlayer.getPlayerPiecesPositions().at(endPosition).getNamePiece()=="pawn" ){
            int row=currentPlayer.getPlayerPiecesPositions().at(endPosition).getCaseCoordinate()[0];
            if(row==0 or row==7 ){
                currentPlayer.getPlayerPiecesPositions().at(endPosition).pawnPromotion();//promotes the pawn and update its name
                string newNamePiece=currentPlayer.getPlayerPiecesPositions().at(endPosition).getNamePiece();
                piecesPositions.at(endPosition).setNamePiece(newNamePiece);

                currentPlayer.getPlayerPiecesPositions().at(endPosition).wasMoved();
                piecesPositions.at(endPosition).wasMoved();
                currentPlayer.playedAMove();
            }
        }

        return 0;
    } 

    cout<<"Error : You can't move place belonging to the other play ."<<endl;
    return 1;
}

int Board::playerExit(){
    int x;
    cout<<"Choose an option :"<<endl;
    cout<<"1.Continue   2.Exit  3.Save and Exit:"<<endl;
    cin>>x;

    if(x<1 or x>3){
        return 0;
    }
    return x;
}*/
