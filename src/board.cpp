#include <iostream>
#include <vector>
#include <map>
#include <cstring>
#include <string>
#include <algorithm>
#include <cctype>
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

//good
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

//good
map<string,Piece>& Board::getPiecesPositions(){
    return piecesPositions;
}

//good
int Board::getNumberOfTurn(){
    return numberOfTurn;
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

//good
bool Board::isPathClear(string startPosition, string endPosition){
    vector<int> startCoord = generateCaseCoordinates(startPosition);
    vector<int> endCoord = generateCaseCoordinates(endPosition);

    int startRow = startCoord[0];
    int startCol = startCoord[1];

    int endRow = endCoord[0];
    int endCol = endCoord[1];

    int rowStep, colStep;

    // Determine row direction
    if (endRow > startRow) {
        rowStep = 1;
    } else if (endRow < startRow) {
        rowStep = -1;
    } else {
        rowStep = 0;
    }

    // Determine column direction
    if (endCol > startCol) {
        colStep = 1;
    } else if (endCol < startCol) {
        colStep = -1;
    } else {
        colStep = 0;
    }

    int currentRow = startRow + rowStep;
    int currentCol = startCol + colStep;

    while (currentRow != endRow || currentCol != endCol) {

        vector<int> coordinates={currentRow, currentCol};
        string position = generateNameCase(coordinates);

        if (piecesPositions.count(position) > 0) {
            return false; // Path is blocked
        }

        currentRow += rowStep;
        currentCol += colStep;
    }

    return true; // Path is clear  
}

//to complete
//bool Board::isCaseUnderAttack
//bool Board::isKingUnderAttack

//good
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
        cout<<"\nNumber of Turn : "<<getNumberOfTurn()<<endl;

        //to fix
        while(n==0){
            n=playerExit();
        }
           
        return n;
    }

    playerTurn(player1,player2);
    playerTurn(player2,player1);    
    numberOfTurn++;
    cout<<"\nNumber of Turn : "<<getNumberOfTurn()<<endl;

    //to fix
    while(n==0){
        n=playerExit();
    }
    
    return n;

}

//good
void Board::playerTurn(Player currentPlayer,Player adverser){
    int t=1;
    
    printBoard();

    if(currentPlayer.getColorPlayer()=="white"){

        cout<<"\nIt's your turn player 1\n"<<endl;
    }
    if(currentPlayer.getColorPlayer()=="black"){

        cout<<"\nIt's your turn player 2\n"<<endl;
    }

    while(t==1){
       t=makeAMove(currentPlayer,adverser);
       if(t==1){
        cout<<"Uncorrect move. Redo your turn."<<endl;
       }
       
    }    
}

//good
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
    else the turn is a classic one;*/
    
    //choose piece to move
    string startPosition;
    cout<<"Enter the initial position of the piece you want to move :"<<endl;
    //cin>>startPosition;
    
    getline(cin,startPosition);

    startPosition=processMoveInput(startPosition); 

    cout<<startPosition<<endl;

    if(checkIfCorrectMoveInput(startPosition)==0){
        cout << "Error: Enter a position in the correct format (e.g. a7)"<< endl;
        return 1;
    }

    // Validate there's a piece at the starting position
    if (piecesPositions.count(startPosition)== 0) {
        cout << "Error: No piece found at " << startPosition << "." << endl;
        return 1;
    }
    // Validate there's a piece at the starting position and it belongs to the player
    if (piecesPositions.count(startPosition)==1 && piecesPositions.at(startPosition).getColorPiece() != currentPlayer.getColorPlayer()) {
        cout << "Error: This piece belongs to the other player." << endl;
        return 1;
    }
    
    //choose final position
    string endPosition;
    cout<<"Enter the final position of the piece you want to move :"<<endl;
    //cin>>endPosition;
    
    getline(cin,endPosition);

    endPosition=processMoveInput(endPosition);

    cout<<endPosition<<endl;

    vector<int> endCoordinates=generateCaseCoordinates(endPosition);

    Piece& p=piecesPositions.at(startPosition);

    if(!p.isMoveLegal(endCoordinates)){
        cout << "Error: The move is not legal for this piece." << endl;
        return 1;
    }
    
    if(p.getNamePiece()!="knight" && !isPathClear(startPosition,endPosition)){
        cout << "Error: The path is blocked." << endl;
        return 1;
    }

    // If the final case is empty, just move the piece
    if (!piecesPositions.count(endPosition)) {
        p.setCaseCoordinate(endCoordinates);
        p.setCasePiece(endPosition);
        p.wasMoved();
        
        piecesPositions[endPosition] = p;
        currentPlayer.getPlayerPiecesPositions()[endPosition] = p;

        piecesPositions.erase(startPosition);
        currentPlayer.getPlayerPiecesPositions().erase(startPosition);

        currentPlayer.playedAMove();
    }
    else{
        // If final position is occupied by one of the adverser's pieces and handle the capture
        if (piecesPositions.at(endPosition).getColorPiece() == adverser.getColorPlayer()) {
            // Capture the piece
            Piece adverserPiece = piecesPositions.at(endPosition);
            adverserPiece.setIsCaptured(true);
            currentPlayer.getCapturedPieces().push_back(adverserPiece);

            p.setCaseCoordinate(endCoordinates);
            p.setCasePiece(endPosition);
            p.wasMoved();

            piecesPositions[endPosition] = p;
            piecesPositions.erase(startPosition);

            adverser.getPlayerPiecesPositions().erase(endPosition);
            currentPlayer.playedAMove();
        } 
        // If final position is occupied by the player's own piece
        else if (piecesPositions.at(endPosition).getColorPiece() == currentPlayer.getColorPlayer()) {
            cout << "Error: You can't move a piece to a square occupied by your own piece." << endl;
            return 1;
        }
    }

    // Special case: Pawn Capture (diagonal capture) and move check
    if (p.getNamePiece() == "pawn" && isCaseOccupied(endCoordinates) && piecesPositions.at(endPosition).getColorPiece() == adverser.getColorPlayer()) {
        if (p.pawnCapture(endCoordinates)) {
            // Capture logic as explained above
            Piece adverserPiece = piecesPositions.at(endPosition);
            adverserPiece.setIsCaptured(true);
            currentPlayer.getCapturedPieces().push_back(adverserPiece);

            p.setCaseCoordinate(endCoordinates);
            p.setCasePiece(endPosition);
            p.wasMoved();

            piecesPositions[endPosition] = p;
            piecesPositions.erase(startPosition);
            adverser.getPlayerPiecesPositions().erase(endPosition);

            currentPlayer.playedAMove();
        }
    }

    // Special case: Pawn Promotion (if the pawn reaches the enemy's back row)
    if (p.getNamePiece() == "pawn") {
        int row = p.getCaseCoordinate()[0];
        if (row == 0 || row == 7) {
            currentPlayer.getPlayerPiecesPositions().at(endPosition).pawnPromotion(); // Promote the pawn

            string newPieceName = currentPlayer.getPlayerPiecesPositions().at(endPosition).getNamePiece();
            piecesPositions.at(endPosition).setNamePiece(newPieceName);

            piecesPositions.at(endPosition).wasMoved();
            currentPlayer.getPlayerPiecesPositions().at(endPosition).wasMoved();

            currentPlayer.playedAMove();
        }
    }

    return 0;
}

int Board::playerExit(){
    int x;
    cout<<"Choose an option :"<<endl;
    cout<<"1.Continue   2.Exit  3.Save and Exit:"<<endl;
    cin>>x;
    cin.ignore();

    if(x<1 || x>3){
        return 0;
    }
    return x;
}

//good
bool Board::checkIfCorrectMoveInput(string moveInput) {
    if (moveInput.length() != 2) {
        return false; // Input must be exactly two characters
    }

    char col = moveInput[0]; // First character should be a-h
    char row = moveInput[1]; // Second character should be 1-8

    vector<char> colName = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h'}; // Columns should be letters
    vector<char> rowName = {'1', '2', '3', '4', '5', '6', '7', '8'}; // Rows should be numbers

    bool isColCorrect = false, isRowCorrect = false;

    for (char c : colName) {
        if (c == col) {
            isColCorrect = true;
            break;
        }
    }

    for (char r : rowName) {
        if (r == row) {
            isRowCorrect = true;
            break;
        }
    }

    return isRowCorrect && isColCorrect;
}

//good
string Board::processMoveInput(string moveInput){

    moveInput.erase(remove_if(moveInput.begin(), moveInput.end(), ::isspace), moveInput.end());
    transform(moveInput.begin(), moveInput.end(), moveInput.begin(), ::tolower);

    return moveInput;
}

/*int main(){

    Board b;
    b.initiateBoard();
    cout<<"row :"<<b.getBoard().size()<<endl;
    cout<<"column : "<<b.getBoard()[0].size()<<endl;

    Player p1("white");
    Player p2("black");

    p1.initiatePlayer(b.getPiecesPositions());
    p2.initiatePlayer(b.getPiecesPositions());

    int t=1;

    while(t==1){
        t=b.gameLogic(p1,p2);
        cout<<"\nnumber of Turn : "<<b.getNumberOfTurn()<<endl;
    }
}*/
 