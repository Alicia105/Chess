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
    scorePlayer1=0;
    scorePlayer2=0;
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

//good
string Board::getKingPosition(Player pl){

    string kingColor=pl.getColorPlayer();
    string kingPosition = "";

    for (auto piece : piecesPositions) {
        if (piece.second.getNamePiece() == "king" && piece.second.getColorPiece() == kingColor) {
            kingPosition = piece.first;
            return kingPosition;
        }
    }
    return kingPosition;//If king not found 
}

//good
vector<vector<int>> Board::getPath(vector<int> startCoordinates, vector<int> endCoordinates) {
    vector<vector<int>> path;

    // Determine the step for row and column movement
    int rowStep = 0;
    if (endCoordinates[0] > startCoordinates[0]) {
        rowStep = 1;
    } else if (endCoordinates[0] < startCoordinates[0]) {
        rowStep = -1;
    }

    int colStep = 0;
    if (endCoordinates[1] > startCoordinates[1]) {
        colStep = 1;
    } else if (endCoordinates[1] < startCoordinates[1]) {
        colStep = -1;
    }

    // Calculate the path from start to end
    int currentRow = startCoordinates[0] + rowStep;
    int currentCol = startCoordinates[1] + colStep;

    while (currentRow != endCoordinates[0] || currentCol != endCoordinates[1]) {
        path.push_back({currentRow, currentCol});
        currentRow += rowStep;
        currentCol += colStep;
    }

    return path;
}

//setters
//good
void Board::clearBoard(){
    piecesPositions.clear();
}

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
                p.setLastMove("");
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



//for game logic-----------------------------------------------------------------------------------------------------------------------------------------------
//good
void Board::updateScore(Player p){
    if(p.getColorPlayer()=="white"){
        scorePlayer1+=1;
    }
    if(p.getColorPlayer()=="black"){
        scorePlayer2+=1;
    }
}

void Board::printScore(){
    cout<<"Final score : Player 1 : "<<scorePlayer1<<" - "<<"Player 2 : "<<scorePlayer2<<endl;
}

//good
bool Board::isKingsideCastlingPossible(Player currentPlayer) {

    string kingPosition = getKingPosition(currentPlayer);
    string kingColor = currentPlayer.getColorPlayer();

    if (kingPosition.empty()){
        return false; // King not found
    }

    if(kingColor=="white"){
        // Ensure the king and rook squares are occupied
        if (!piecesPositions.count("e1") || !piecesPositions.count("h1")){
            return false;
        }
        // Ensure the king and rook haven't moved
        if (piecesPositions.at("e1").getNumberOfMove()!=0 || piecesPositions.at("h1").getNumberOfMove()!=0){
            return false;
        }
        // Ensure the squares between the king and rook are empty
        if(!isPathClear("e1","h1")){
            return false;
        }
        // Ensure the king is not in check and does not pass through a check
        if(isKingUnderAttack(currentPlayer,"e1") || isKingUnderAttack(currentPlayer,"f1") || isKingUnderAttack(currentPlayer,"g1")){
            return false;
        }
        return true;
    }
    if(kingColor=="black"){
        // Ensure the king and rook squares are occupied
        if (!piecesPositions.count("e8") || !piecesPositions.count("h8")){
            return false;
        }
        // Ensure the king and rook haven't moved
        if (piecesPositions.at("e8").getNumberOfMove()!=0 || piecesPositions.at("h8").getNumberOfMove()!=0){
            return false;
        }
        // Ensure the squares between the king and rook are empty
        if(!isPathClear("e8","h8")){
            return false;
        }
        // Ensure the king is not in check and does not pass through a check
        if(isKingUnderAttack(currentPlayer,"e8") || isKingUnderAttack(currentPlayer,"f8") || isKingUnderAttack(currentPlayer,"g8")){
            return false;
        }
        return true;
    }

    return false; //should never happen
}

//good
bool Board::isQueensideCastlingPossible(Player currentPlayer) {

    string kingPosition = getKingPosition(currentPlayer);
    string kingColor = currentPlayer.getColorPlayer();

    if (kingPosition.empty()){
        return false; // King not found
    }

    if(kingColor=="white"){
        // Ensure the king and rook squares are occupied
        if (!piecesPositions.count("e1") || !piecesPositions.count("a1")){
            return false;
        }
        // Ensure the king and rook haven't moved
        if (piecesPositions.at("e1").getNumberOfMove()!=0 || piecesPositions.at("a1").getNumberOfMove()!=0){
            return false;
        }
        // Ensure the squares between the king and rook are empty
        if(!isPathClear("e1","a1")){
            return false;
        }
        // Ensure the king is not in check and does not pass through a check
        if(isKingUnderAttack(currentPlayer,"e1") || isKingUnderAttack(currentPlayer,"d1") || isKingUnderAttack(currentPlayer,"c1") || isKingUnderAttack(currentPlayer,"b1")){
            return false;
        }
        return true;
    }
    if(kingColor=="black"){
        // Ensure the king and rook squares are occupied
        if (!piecesPositions.count("e8") || !piecesPositions.count("a8")){
            return false;
        }
        // Ensure the king and rook haven't moved
        if (piecesPositions.at("e8").getNumberOfMove()!=0 || piecesPositions.at("a8").getNumberOfMove()!=0){
            return false;
        }
        // Ensure the squares between the king and rook are empty
        if(!isPathClear("e8","a8")){
            return false;
        }
        // Ensure the king is not in check and does not pass through a check
        if(isKingUnderAttack(currentPlayer,"e8") || isKingUnderAttack(currentPlayer,"d8") || isKingUnderAttack(currentPlayer,"c8") || isKingUnderAttack(currentPlayer,"b8")){
            return false;
        }
        return true;
    }
    return false; //should never happen
}

//good
bool Board::isCastlingPossible(Player p){
    return isQueensideCastlingPossible(p) || isKingsideCastlingPossible(p);
}

//good
void Board::chooseCastling(Player p){
    int x;
    cout<<"You can do a castling ! Do you want to do one ?"<<endl;
    cout<<"1.Yes 2.No"<<endl;
    cin>>x;

    if(x==1){
        if(isKingsideCastlingPossible(p) && isQueensideCastlingPossible(p)){
            int y;
            cout<<"On what side do you want to do a castling ?"<<endl;
            cout<<"1.Kingside 2.Queenside 3.None"<<endl;
            cin>>y;
            if(y==1){
                cout<<"You chose to do a Kingside castling"<<endl;
                doKingsideCastling(p);
                return;
            }
            if(y==2){
                cout<<"You chose to do a Queenside castling"<<endl;
                doQueensideCastling(p);
                return;
            }
            else{
                return;
            }      
        }
        if(isKingsideCastlingPossible(p)){
            int a;
            cout<<"Do you want to do a Kingside castling ?"<<endl;
            cout<<"1.Yes 2.No"<<endl;
            cin>>a;
            if(a==1){
                doKingsideCastling(p);
                return;
            }
            if(a==2){
                return;
            }
            else{
                cout<<"Error : Incorrect input"<<endl;
                return;
            }
        }

        if(isQueensideCastlingPossible(p)){
            int b;
            cout<<"Do you want to do a Queenside castling ?"<<endl;
            cout<<"1.Yes 2.No"<<endl;
            cin>>b;
            if(b==1){
                doQueensideCastling(p);
                return;
            }
            if(b==2){
                return;
            }
            else{
                cout<<"Error : Incorrect input"<<endl;
                return;
            }
        }
    }
    if(x==2){
        return;
    }
    cout<<"Error : Incorrect input"<<endl;
    return;

}

//good
void Board::doQueensideCastling(Player p){
    string colorPlayer=p.getColorPlayer();

    if(colorPlayer=="white"){
        string kingPosition="e1";
        string rookPosition="a1";

        string kingEndPosition="c1";
        string rookEndPosition="d1";

        Piece& king = piecesPositions.at(kingPosition);
        Piece& rook = piecesPositions.at(rookPosition);

        // for the king
        vector<int> kingEndCoord = generateCaseCoordinates(kingEndPosition);
        king.setCaseCoordinate(kingEndCoord);
        king.setCasePiece(kingEndPosition);
        king.setLastMove(kingPosition);
        king.wasMoved();
        
        piecesPositions[kingEndPosition] = king;
        p.getPlayerPiecesPositions()[kingEndPosition] = king;

        piecesPositions.erase(kingPosition);
        p.getPlayerPiecesPositions().erase(kingPosition);

        // for the rook
        vector<int> rookEndCoord = generateCaseCoordinates(rookEndPosition);
        rook.setCaseCoordinate(rookEndCoord);
        rook.setCasePiece(rookEndPosition);
        rook.setLastMove(rookPosition);
        rook.wasMoved();
        
        piecesPositions[rookEndPosition] = rook;
        p.getPlayerPiecesPositions()[rookEndPosition] = rook;

        piecesPositions.erase(rookPosition);
        p.getPlayerPiecesPositions().erase(rookPosition);

        p.playedAMove();
        
    }
    if(colorPlayer=="black"){
        string kingPosition="e8";
        string rookPosition="a8";

        string kingEndPosition="c8";
        string rookEndPosition="d8";

        Piece& king = piecesPositions.at(kingPosition);
        Piece& rook = piecesPositions.at(rookPosition);

        // for the king
        vector<int> kingEndCoord = generateCaseCoordinates(kingEndPosition);
        king.setCaseCoordinate(kingEndCoord);
        king.setCasePiece(kingEndPosition);
        king.setLastMove(kingPosition);
        king.wasMoved();
        
        piecesPositions[kingEndPosition] = king;
        p.getPlayerPiecesPositions()[kingEndPosition] = king;

        piecesPositions.erase(kingPosition);
        p.getPlayerPiecesPositions().erase(kingPosition);

        // for the rook
        vector<int> rookEndCoord = generateCaseCoordinates(rookEndPosition);
        rook.setCaseCoordinate(rookEndCoord);
        rook.setCasePiece(rookEndPosition);
        rook.setLastMove(rookPosition);
        rook.wasMoved();
        
        piecesPositions[rookEndPosition] = rook;
        p.getPlayerPiecesPositions()[rookEndPosition] = rook;

        piecesPositions.erase(rookPosition);
        p.getPlayerPiecesPositions().erase(rookPosition);

        p.playedAMove();
    }


}

//good
void Board::doKingsideCastling(Player p){
    string colorPlayer=p.getColorPlayer();

    if(colorPlayer=="white"){
        string kingPosition="e1";
        string rookPosition="h1";

        string kingEndPosition="g1";
        string rookEndPosition="f1";

        Piece& king = piecesPositions.at(kingPosition);
        Piece& rook = piecesPositions.at(rookPosition);

        // for the king
        vector<int> kingEndCoord = generateCaseCoordinates(kingEndPosition);
        king.setCaseCoordinate(kingEndCoord);
        king.setCasePiece(kingEndPosition);
        king.setLastMove(kingPosition);
        king.wasMoved();
        
        piecesPositions[kingEndPosition] = king;
        p.getPlayerPiecesPositions()[kingEndPosition] = king;

        piecesPositions.erase(kingPosition);
        p.getPlayerPiecesPositions().erase(kingPosition);

        // for the rook
        vector<int> rookEndCoord = generateCaseCoordinates(rookEndPosition);
        rook.setCaseCoordinate(rookEndCoord);
        rook.setCasePiece(rookEndPosition);
        rook.setLastMove(rookPosition);
        rook.wasMoved();
        
        piecesPositions[rookEndPosition] = rook;
        p.getPlayerPiecesPositions()[rookEndPosition] = rook;

        piecesPositions.erase(rookPosition);
        p.getPlayerPiecesPositions().erase(rookPosition);

        p.playedAMove();
        
    }
    if(colorPlayer=="black"){
        string kingPosition="e8";
        string rookPosition="h8";

        string kingEndPosition="g8";
        string rookEndPosition="f8";

        Piece& king = piecesPositions.at(kingPosition);
        Piece& rook = piecesPositions.at(rookPosition);

        // for the king
        vector<int> kingEndCoord = generateCaseCoordinates(kingEndPosition);
        king.setCaseCoordinate(kingEndCoord);
        king.setCasePiece(kingEndPosition);
        king.setLastMove(kingPosition);
        king.wasMoved();
        
        piecesPositions[kingEndPosition] = king;
        p.getPlayerPiecesPositions()[kingEndPosition] = king;

        piecesPositions.erase(kingPosition);
        p.getPlayerPiecesPositions().erase(kingPosition);

        // for the rook
        vector<int> rookEndCoord = generateCaseCoordinates(rookEndPosition);
        rook.setCaseCoordinate(rookEndCoord);
        rook.setCasePiece(rookEndPosition);
        rook.setLastMove(rookPosition);
        rook.wasMoved();
        
        piecesPositions[rookEndPosition] = rook;
        p.getPlayerPiecesPositions()[rookEndPosition] = rook;

        piecesPositions.erase(rookPosition);
        p.getPlayerPiecesPositions().erase(rookPosition);

        p.playedAMove();
    }

}

//good
vector<string> Board::findKingAttackers(Player pl){

    string kingPosition=getKingPosition(pl);
    string kingColor=pl.getColorPlayer();

    vector<string> attackers;
    
    for (auto p : piecesPositions) {
        if (p.second.getColorPiece() != kingColor) { // Opponent piece
            vector<int> targetCoordinates = generateCaseCoordinates(kingPosition);
            
            if (p.second.isMoveLegal(targetCoordinates) && isPathClear(p.second.getCasePiece(), kingPosition)) {
                attackers.push_back(p.second.getCasePiece()); // Attacker found
            }
        }
    }
    return attackers;
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

//good
bool Board::isCaseOccupied(vector<int> coordinates){
    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;    
    int row=coordinates[0];
    int column=coordinates[1];

    string nameCase=generateNameCase(coordinates);

    return piecesPositions.count(nameCase);
}

//isKingInCheck
//good
bool Board::isKingUnderAttack(Player p,string kingPosition){

    string kingColor=p.getColorPlayer();

    if (kingPosition.empty()) {
        cout << "Error: King not found!" << endl;
        return false;
    }

    vector<int> endCoord = generateCaseCoordinates(kingPosition);

    // Check if any opponent piece can attack the king
    for (auto piece : piecesPositions) {
        if (piece.second.getColorPiece() != kingColor) {
            string start =piece.first;
            if (!piece.second.isMoveLegal(endCoord)) continue;
            
            if (piece.second.getNamePiece() == "knight"){
                return true; // King is under attack
            }

            if (isPathClear(start, kingPosition)){
                return true; // King is under attack
            }
        }
    }
    return false;
}

//CheckMate
//good
bool Board::isCheckMate(Player p){

    // Find the king's position
    string kingPosition=getKingPosition(p);
    cout<<"kingPo : "<<kingPosition<<endl;

    //Should never happen
    if (kingPosition.empty()){
        cout << "Error: King not found!" << endl;
        return false;
    }
    cout<<"yahoo"<<endl;

    if (!isKingUnderAttack(p,kingPosition)) {
        cout<<"hello"<<endl;
        return false; // Not in check, so not checkmate
    }
    cout<<"belbe"<<endl;
    //cout<<"is in check"<<endl;

    string kingColor=p.getColorPlayer();
    cout<<kingColor<<endl;

    // Define possible king moves
    vector<pair<int, int>> moves = {
        {-1,0}, {1,0}, {0,-1}, {0,1},
        {-1,-1}, {-1,1}, {1,-1}, {1,1}
    };

    vector<int> kingCoord=generateCaseCoordinates(kingPosition);
    vector<string> attackers=findKingAttackers(p);

    cout<<"colombe"<<endl;

    //Check if the king has an escape move
    // Iterate through possible moves
    for (auto move : moves) {
        int i=0;
        int newX = kingCoord[0] + move.first;
        int newY = kingCoord[1] + move.second;
        vector<int> endCoord={newX,newY};
        //cout<<"new king coord to try: {"<<newX<<","<<newY<<"}"<<endl;

        if (endCoord[0] >= 0 && endCoord[0] < 8 && endCoord[1] >= 0 && endCoord[1] < 8) { // Check board limits
            string newPosition = generateNameCase(endCoord);
            cout<<"new position :"<<newPosition<<endl;

            // If the square is not occupied by the same color and doesn't put king in check, it's a valid escape
            if (!piecesPositions.count(newPosition) || piecesPositions.at(newPosition).getColorPiece() != kingColor){
                // Simulate king move on a copy of the board
                Board tempBoard = *this;
                tempBoard.movePiece(kingPosition, newPosition);

                if (!tempBoard.isKingUnderAttack(p, newPosition)) {
                    cout<<"ds:" <<i<<endl;
                    return false; // King has an escape move, so it's not checkmate
                }
            }
        }
    }

    //Can Attacker be captured or blocked
    // Try capturing or blocking the attacker
    for (auto attackerPosition : attackers) {
        vector<int> attackCoord = generateCaseCoordinates(attackerPosition);
        vector<vector<int>> pathToKing = getPath(attackCoord, kingCoord);

        for (auto pc : piecesPositions) {
            if (pc.second.getColorPiece() == kingColor && pc.second.getNamePiece() != "king") {
                string piecePosition = pc.first;

                // Attempt to capture the attacker
                if (pc.second.isMoveLegal(attackCoord) && 
                    (pc.second.getNamePiece() == "knight" || isPathClear(piecePosition, attackerPosition))) {
                    // Simulate the capture
                    Board tempBoard = *this;
                    tempBoard.movePiece(piecePosition, attackerPosition);
                    if (!tempBoard.isKingUnderAttack(p, kingPosition)) {
                        return false; // Attacker can be captured => no checkmate
                    }
                }

                // Attempt to block the attacker (not applicable for knights)
                for (auto square : pathToKing) {
                    string blockSquare = generateNameCase(square);
                    if (pc.second.isMoveLegal(square) && isPathClear(piecePosition, blockSquare)) {
                        Board tempBoard = *this;
                        tempBoard.movePiece(piecePosition, blockSquare);
                        if (!tempBoard.isKingUnderAttack(p, kingPosition)) {
                            return false; // Attack can be blocked => no checkmate
                        }
                    }
                }
            }
        }
    }


    // If no escape, block, or capture is possible, it's checkmate
    return true;
}

//StaleMate
//good
bool Board::isStaleMate(Player p){

    // Find the king's position
    string kingPosition=getKingPosition(p);

    //Should never happen
    if (kingPosition.empty()){
        cout << "Error: King not found!" << endl;
        return false;
    }

    if (isKingUnderAttack(p,kingPosition)) {
        return false; // If the king is in check, it can't be stalemate
    }

    string kingColor=p.getColorPlayer();

    // Define possible king moves
    vector<pair<int, int>> moves = {
        {-1,0}, {1,0}, {0,-1}, {0,1},
        {-1,-1}, {-1,1}, {1,-1}, {1,1}
    };

    vector<int> kingCoord=generateCaseCoordinates(kingPosition);
  
    //// Check if the king has a legal move
    // Iterate through possible moves
    for (auto move : moves) {
        int newX = kingCoord[0] + move.first;
        int newY = kingCoord[1] + move.second;
        vector<int> endCoord={newX,newY};

        if (endCoord[0] >= 0 && endCoord[0] < 8 && endCoord[1] >= 0 && endCoord[1] < 8) { // Check board limits
            string newPosition = generateNameCase(endCoord);
            //cout << "here" << endl;

            // If the square is not occupied by the same color and doesn't put king in check, it's a valid escape
            if (!piecesPositions.count(newPosition) || piecesPositions.at(newPosition).getColorPiece() != kingColor){
                // Simulate the move to see if it puts the king in check
                Board tempBoard = *this;
                tempBoard.movePiece(kingPosition, newPosition);
                //cout << "See" << endl;

                if (!tempBoard.isKingUnderAttack(p,newPosition)) {
                    //cout << "we out here" << endl;
                    return false; // The king has a safe move, no stalemate
                }
            }   
        }
    }

    // Check if any other piece of the player has a legal move
    for (auto piece : piecesPositions){
        if (piece.second.getColorPiece() == kingColor) { // If the piece belongs to the current player
            string piecePosition = piece.first;
            vector<int> pieceCoord = generateCaseCoordinates(piecePosition);
            //cout << "over here" << endl;

            // Generate all possible moves for this piece
            for (int i = 0; i <grid.size(); i++) {
                for (int j = 0; j < grid[0].size(); j++) {
                    vector<int> testCoord = {i, j};
                    string testPosition = generateNameCase(testCoord);

                    // Check if the move is legal
                    if (piece.second.isMoveLegal(testCoord) && 
                        (piece.second.getNamePiece() == "knight" || isPathClear(piecePosition, testPosition))) {
                            //cout << "in grid" << endl;
                        
                        // Simulate the move to check if it avoids check
                        Board tempBoard = *this;
                        tempBoard.movePiece(piecePosition, testPosition);
                        if (!tempBoard.isKingUnderAttack(p,testPosition)) {
                            //cout << "yo" << endl;
                            return false; // A piece has a legal move, no stalemate

                        }
                    }
                }
            }
        }
    }

    // If no legal moves exist, it's a stalemate
    //cout << "hello" << endl;
    return true;
}

//isEnPassant possible

bool Board::isEnPassant(Player currentPlayer,Player adverser,string startPosition,string endPosition){

    // Check possible pawn neighbours
    vector<pair<int, int>> moves = {{0,-1}, {0,1}};

    //Get player colors
    string playerColor=currentPlayer.getColorPlayer();
    string adverserColor=adverser.getColorPlayer();

    //cout<<"here"<<endl;

    //the startPosition square is empty--> no piece to move 
    if(!piecesPositions.count(startPosition)){
        return false;
    }

    //cout<<"and here"<<endl;

    //check the current piece belongs to the player and is a pawn
    if(piecesPositions.at(startPosition).getColorPiece()==playerColor && piecesPositions.at(startPosition).getNamePiece()=="pawn"){
        //cout<<"1"<<endl;
        for(auto move : moves){
            //cout<<"2"<<endl;
            //check only neighbours on board 
            int c = piecesPositions.at(startPosition).getCaseCoordinate()[1];
            //cout<<"c:"<<c<<endl;
            if(c+move.second>=0 && c+move.second<8){
                //cout<<"3"<<endl;
                //check if a potential adverser pawn is next to current player pawn
                int row=piecesPositions.at(startPosition).getCaseCoordinate()[0]+move.first;
                int col=piecesPositions.at(startPosition).getCaseCoordinate()[1]+move.second;

                vector<int> adverserPawnCoord={row,col};
                string adverserPawnPosition=generateNameCase(adverserPawnCoord);
                vector<int> endCoord=generateCaseCoordinates(endPosition);
    
                //if the neighbour case is not empty and belongs to an adverser piece
                if(piecesPositions.count(adverserPawnPosition) && piecesPositions.at(adverserPawnPosition).getColorPiece()!=playerColor){
                    //cout<<"4"<<endl;
                    //if this case is a pawn and only made one move
                    if(piecesPositions.at(adverserPawnPosition).getNamePiece()=="pawn" && piecesPositions.at(adverserPawnPosition).getNumberOfMove()==1){
                        //cout<<"5"<<endl;
                        //Get the last position of the adverser pawn
                        string lastAdverserPawnPosition=piecesPositions.at(adverserPawnPosition).getLastMove();
                        vector<int> lastAdverserPawnCoord=generateCaseCoordinates(lastAdverserPawnPosition);

                        if(lastAdverserPawnCoord[0]==6 && adverserColor=="white"){
                            //cout<<"6"<<endl;
                            
                            //cout<<"endCoord x : "<<endCoord[0]<<endl;
                            //cout<<"endCoord y : "<<endCoord[1]<<endl;
                            //cout<<"adverserPawnCoord x : "<<adverserPawnCoord[0]<<endl;
                            //cout<<"adverserPawnCoord y : "<<adverserPawnCoord[1]<<endl;

                            if(endCoord[0]==adverserPawnCoord[0]+1 && endCoord[1]==adverserPawnCoord[1]){
                                //cout<<"7"<<endl;
                                return true;
                            }
                            
                            
                        }
                        if(lastAdverserPawnCoord[0]==1 && adverserColor=="black"){
                            //cout<<"8"<<endl;
                            
                            //cout<<"endCoord x : "<<endCoord[0]<<endl;
                            //cout<<"endCoord y : "<<endCoord[1]<<endl;
                            //cout<<"adverserPawnCoord x : "<<adverserPawnCoord[0]<<endl;
                            //cout<<"adverserPawnCoord y : "<<adverserPawnCoord[1]<<endl;

                            if(endCoord[0]==adverserPawnCoord[0]-1 && endCoord[1]==adverserPawnCoord[1]){
                                //cout<<"9"<<endl;
                                return true;
                            }
                        }            
                    }
                }

            }
           
        }
    }

    return false;
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

//good
int Board::makeAMove(Player currentPlayer,Player adverser){
    //good
    string kingPosition=getKingPosition(currentPlayer);

    //Should never happen
    if (kingPosition.empty()){
        cout << "Error: King not found!" << endl;
        return 4;
    }

    if(isStaleMate(currentPlayer)){
        cout<<"GAME OVER : Stalemate : That's a draw !"<<endl;
        return 3;
    }


    if(isCheckMate(currentPlayer)){
        cout<<"GAME OVER : You are checkmate !"<<endl;
        updateScore(adverser);
        return 2;
    }
   
    if(isKingUnderAttack(currentPlayer,kingPosition)){
        cout<<"Beware : Your king is in check !"<<endl;
    }

    //special move :castling :
    if(isCastlingPossible(currentPlayer)){
        chooseCastling(currentPlayer);
        return 0;
    }
    
    
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
    if (piecesPositions.count(startPosition)==1 && piecesPositions.at(startPosition).getColorPiece() != currentPlayer.getColorPlayer()){
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

    if(piecesPositions.count(endPosition) && piecesPositions.at(endPosition).getNamePiece()=="king" && piecesPositions.at(endPosition).getColorPiece()==adverser.getColorPlayer()){
        cout << "Error: You can't directly capture the king." << endl;
        return 1;
    }

    if(isEnPassant(currentPlayer,adverser,startPosition,endPosition)){
        int direction;
        string playerColor = currentPlayer.getColorPlayer();
    
        if (playerColor == "white") {
            direction = 1;
        } else if (playerColor == "black") {
            direction = -1;
        } else {
            cout << "Error: Unknown player color for en passant." << endl;
            return 1;
        }
    
        // Determine the position of the captured pawn (not on the destination square)
        vector<int> capturedPawnCoord = {endCoordinates[0] + direction, endCoordinates[1]};
        string capturedPawnPos = generateNameCase(capturedPawnCoord);
    
        if (piecesPositions.count(capturedPawnPos)) {
            Piece& capturedPawn = piecesPositions.at(capturedPawnPos);
            capturedPawn.setIsCaptured(true);
            currentPlayer.getCapturedPieces().push_back(capturedPawn);
            
            piecesPositions.erase(capturedPawnPos);
            adverser.getPlayerPiecesPositions().erase(capturedPawnPos);
            p.setLastMove(startPosition);

            // Move the current player's pawn
            piecesPositions[endPosition] = p;
            currentPlayer.getPlayerPiecesPositions()[endPosition] = p;

            piecesPositions.erase(startPosition);
            currentPlayer.getPlayerPiecesPositions().erase(startPosition);
                        
            p.wasMoved();    
            currentPlayer.playedAMove();
    
            return 0;
        }

        cout << "Error: The pawn to caputre wasn't found." << endl; //should never happen
        return 1;
    }


    if(!p.isMoveLegal(endCoordinates) && !(p.pawnCapture(endCoordinates) && p.getColorPiece()==currentPlayer.getColorPlayer())){
        cout << "Error: The move is not legal for this piece." << endl;
        return 1;
        
    }
    
    if(p.getNamePiece()!="knight" && !isPathClear(startPosition,endPosition)){
        cout << "Error: The path is blocked." << endl;
        return 1;
    }

    // If the final case is empty, just move the piece
    if (!piecesPositions.count(endPosition)){
        p.setCaseCoordinate(endCoordinates);
        p.setCasePiece(endPosition);
        p.setLastMove(startPosition);
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
            Piece& adverserPiece = piecesPositions.at(endPosition);
            adverserPiece.setIsCaptured(true);
            currentPlayer.getCapturedPieces().push_back(adverserPiece);

            /*if(adverserPiece.getNamePiece()=="king" && adverserPiece.getIsCaptured()){
                if(isCheckMate(adverser)){
                    cout<<"GAME OVER : You won !"<<endl;
                    updateScore(currentPlayer);
                    return 2;
                }
            }*/

            p.setCaseCoordinate(endCoordinates);
            p.setCasePiece(endPosition);
            p.setLastMove(startPosition);
            p.wasMoved();

            piecesPositions[endPosition] = p;
            piecesPositions.erase(startPosition);

            currentPlayer.getPlayerPiecesPositions()[endPosition] = p;
            currentPlayer.getPlayerPiecesPositions().erase(startPosition);

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
    if(p.getNamePiece() == "pawn" && isCaseOccupied(endCoordinates) && piecesPositions.count(endPosition) && piecesPositions.at(endPosition).getColorPiece()==adverser.getColorPlayer()) {
        if (p.pawnCapture(endCoordinates)) {
            // Capture logic as explained above
            Piece& adverserPiece = piecesPositions.at(endPosition);
            adverserPiece.setIsCaptured(true);
            currentPlayer.getCapturedPieces().push_back(adverserPiece);

            /*if(adverserPiece.getNamePiece()=="king" && adverserPiece.getIsCaptured()){
                if(isCheckMate(adverser)){
                    cout<<"GAME OVER : You won !"<<endl;
                    updateScore(currentPlayer);
                    return 2;
                }
            }*/

            p.setCaseCoordinate(endCoordinates);
            p.setCasePiece(endPosition);
            p.setLastMove(startPosition);
            p.wasMoved();

            piecesPositions[endPosition] = p;
            piecesPositions.erase(startPosition);

            currentPlayer.getPlayerPiecesPositions()[endPosition] = p;
            currentPlayer.getPlayerPiecesPositions().erase(startPosition);
            
           
            adverser.getPlayerPiecesPositions().erase(endPosition);

            currentPlayer.playedAMove();
        }
    }

    // Special case: Pawn Promotion (if the pawn reaches the enemy's back row)
    if (p.getNamePiece() == "pawn" && p.getColorPiece() == currentPlayer.getColorPlayer()) {
        int row=piecesPositions.at(endPosition).getCaseCoordinate()[0];
        if (row == 0 || row == 7) {
            if (currentPlayer.getPlayerPiecesPositions().count(endPosition)){
                Piece& promotedPiece = currentPlayer.getPlayerPiecesPositions().at(endPosition);
                promotedPiece.pawnPromotion(); // Promote the pawn
                promotedPiece.setIsPromoted(true);
                string newPieceName = promotedPiece.getNamePiece();
                piecesPositions.at(endPosition).setNamePiece(newPieceName);
            }
        }
    }

    return 0;
    //good--end
}

//good
int Board::playerExit(){
    int x;
    cout<<"Choose an option :"<<endl;
    cout<<"1.Continue   2.Exit  3.Save and Exit:"<<endl;
    cin>>x;
    cin.ignore();

    if(x<1 || x>3){
        return 0;
    }

    if(x==1){
        return 5;
    }

    if(x==2){
        return 6;
    }

    if(x==3){
        return 7;
    }

    return 0;
}

void Board::movePiece(string from, string to){
    // If there is a piece at the "to" position, temporarily remove it
    bool captured = piecesPositions.count(to);
    Piece capturedPiece;
    if (captured) {
        capturedPiece = piecesPositions.at(to);
        piecesPositions.erase(to);
    }

    // Move the piece
    piecesPositions[to] = piecesPositions[from];
    piecesPositions[to].setCasePiece(to);
    piecesPositions.erase(from);

    // If this was a simulation, you could restore the captured piece
}

//good
int Board::gameLogic(Player player1,Player player2){
    int n=0;
    int t=0;
    if(numberOfTurn==0){
        if(player1.getColorPlayer()=="white"){
            cout<<"You're the one to start player 1.\n"<<endl;
            //player1 play
            t=playerTurn(player1,player2);
            if(t==4){
                return t;
            }
        }

        //player2 play
        t=playerTurn(player2,player1);
        numberOfTurn++;
        cout<<"\nNumber of Turn : "<<getNumberOfTurn()<<"\n"<<endl;
        if(t==4){
            return t;
        }

       
        while(n==0){
            n=playerExit();
            if(n==0){
                cout<<"Please enter a valid option"<<endl;
            }
        }
           
        return n;
    }

    t=playerTurn(player1,player2);

    //player1 is checkmate or we have a stalemate
    if(t==2 || t==3){
        return t;
    }

    if(t==4){
        return t;
    }

    t=playerTurn(player2,player1);    
    numberOfTurn++;
    cout<<"\nNumber of Turn : "<<getNumberOfTurn()<<endl;

    //player2 is checkmate or we have a stalemate
    if(t==2 || t==3){
        return t;
    }

    if(t==4){
        return t;
    }

    
    while(n==0){
        n=playerExit();
        cout<<"Please enter a valid option"<<endl;
    }
    
    return n;
}

//good
int Board::playerTurn(Player currentPlayer,Player adverser){
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
    
    if(t==2){
        cout<<"Final score : Player 1 : "<<scorePlayer1<<" - "<<"Player 2 : "<<scorePlayer2<<endl;
    }

    if(t==3){
        cout<<"Final score : Player 1 : "<<scorePlayer1<<" - "<<"Player 2 : "<<scorePlayer2<<endl;
    }

    return t;
}

//for ai game logic--------------------------------------------------------------------------------------------------------------------------------------------------------------

bool Board::isGameOver(Player aiPlayer){
    return isCheckMate(aiPlayer)|| isStaleMate(aiPlayer);
}

int Board::evaluate(Player& aiPlayer, Player& opponent){
    int score = 0;

    // Piece value map
    map<string, int> pieceValue = {
        {"pawn", 100},
        {"knight", 320},
        {"bishop", 330},
        {"rook", 500},
        {"queen", 900},
        {"king", 20000}
    };

    for (auto p : piecesPositions) {
        Piece& piece = p.second;
        string color = piece.getColorPiece();
        string name = piece.getNamePiece();

        int value = pieceValue[name];

        if (color == aiPlayer.getColorPlayer()) {
            score += value;
        } else {
            score -= value;
        }
    }

    return score;
}

void Board::movePieceMini(string from, string to, Piece* capturedPiece) {
    cout << "[DEBUG] movePieceMini: trying to move from " << from << " to " << to << endl;

    // Prevent moving to the same square
    if (from == to) {
        cout << "[ERROR] Invalid move: source and destination are the same (" << from << ")" << endl;
        return;
    }

    // Check if there's a piece at the source
    if (!piecesPositions.count(from)) {
        cout << "[ERROR] No piece at source square " << from << endl;
        return;
    }

    // Handle capture
    if (piecesPositions.count(to) && capturedPiece != nullptr) {
        *capturedPiece = piecesPositions.at(to);
        capturedPiece->setLastMove(to);
        capturedPiece->setIsCaptured(true);
    } else if (capturedPiece != nullptr) {
        *capturedPiece = Piece(); // default empty piece
    }

    // Move piece
    piecesPositions[to] = piecesPositions.at(from);
    piecesPositions[to].setCasePiece(to);
    piecesPositions[to].setCaseCoordinate(generateCaseCoordinates(to));
    piecesPositions[to].setLastMove(from);

    // Remove from original square
    piecesPositions.erase(from);
}

void Board::undoMovePieceMini(string from, string to, Piece& capturedPiece) {
    cout << "[DEBUG] undoMovePieceMini: undoing move from " << from << " to " << to << endl;

    // Restore the moved piece back to its original position
    if (!piecesPositions.count(to)) {
        cout << "[ERROR] Cannot undo: no piece at destination " << to << endl;
        return;
    }

    piecesPositions[from] = piecesPositions[to];
    piecesPositions[from].setCasePiece(from);
    piecesPositions[from].setCaseCoordinate(generateCaseCoordinates(from));
    piecesPositions[from].setLastMove(to);

    // Restore captured piece if there was one
    if (capturedPiece.getNamePiece() != "") {
        capturedPiece.setLastMove(to);
        capturedPiece.setIsCaptured(false);
        piecesPositions[to] = capturedPiece;
    } else {
        piecesPositions.erase(to);
    }
}

int Board::minimax(Player aiPlayer, Player opponent, int depth, bool isMaximizingPlayer, int alpha, int beta){
//int Board::minimax(Player aiPlayer, Player opponent, int depth, bool isMaximizingPlayer) {
    cout<<"DEPTH : "<<depth<<endl;
    cout<<"debut"<<endl;
    string colorAIPlayer = aiPlayer.getColorPlayer();
    string colorHumanPlayer = opponent.getColorPlayer();
    cout<<"nous"<<endl;

    //cout << "Depth: " << depth << ", Game over: " << isGameOver(aiPlayer, opponent) << endl;

    if (depth == 0||isGameOver(aiPlayer)) {
        int eval= evaluate(aiPlayer, opponent);
        cout << "Base case reached with evaluation: " << eval << endl;
        return eval;
    }
    /*if (depth == 0||isGameOver(aiPlayer, opponent)) {
        int eval= evaluate(aiPlayer, opponent);
        cout << "Base case reached with evaluation: " << eval << endl;
        return eval;
    }*///->pb with isGameOver
    cout<<"Allons"<<endl;

    if (isMaximizingPlayer) {
        int maxEval = INT_MIN;
        vector<vector<string>> moves = getAllLegalMoves(aiPlayer, opponent);
        cout<<"marchons"<<endl;
        
        if (moves.empty()) {
            return evaluate(aiPlayer, opponent);  // No moves => evaluate the current state
        }
     
        for (auto m : moves){
            cout<<"{ "<<m[0]<<", "<<m[1]<<" }\n";
        }

        cout<<"num of moves (max) :"<<moves.size()<<endl;


        for (auto move : moves) {
            Board temp = *this;
            Piece capturedPiece;
            Piece capturedPiece1;
           

            if (move.size() == 4) {
                //temp.movePiece(move[0], move[1]);
                //temp.movePiece(move[2], move[3]);
                temp.movePieceMini(move[0], move[1], &capturedPiece);
                temp.movePieceMini(move[2], move[3], &capturedPiece1);
                cout<<"1"<<endl;
               


                //int eval = temp.minimax(aiPlayer, opponent, depth - 1, false);
                int eval = temp.minimax(aiPlayer, opponent, depth - 1, false, alpha, beta);
                cout<<"2"<<endl;

                //temp.movePiece(move[1], move[0]);
                //temp.movePiece(move[3], move[2]);

                temp.undoMovePieceMini(move[0],move[1], capturedPiece);
                temp.undoMovePieceMini(move[2],move[3], capturedPiece1);

                cout<<"3"<<endl;

                maxEval = max(maxEval, eval);
                alpha = max(alpha, eval);
                if (beta <= alpha){
                    break;  // beta cut-off
                }
                    
            } else {
                cout<<"4"<<endl;
                cout << "Trying move from " << move[0] << " to " << move[1] << endl;
                temp.movePieceMini(move[0], move[1], &capturedPiece);
                cout<<"5"<<endl;
                //for debugging
                if(!temp.getPiecesPositions().count(move[1])){
                    cout<<"help"<<endl;
                }

                string name = temp.getPiecesPositions().at(move[1]).getNamePiece();
                string color = temp.getPiecesPositions().at(move[1]).getColorPiece();
                int row = temp.getPiecesPositions().at(move[1]).getCaseCoordinate()[0];
                cout<<"la"<<endl;

                if (name == "pawn" && color == colorAIPlayer && ((color == "white" && row == 0) || (color == "black" && row == 7))) {
                    temp.getPiecesPositions().at(move[1]).setIsPromoted(true);
                    int eval;
                    for (int i = 0; i < 4; i++) {
                        switch (i) {
                            case 0: temp.getPiecesPositions().at(move[1]).setNamePiece("queen"); break;
                            case 1: temp.getPiecesPositions().at(move[1]).setNamePiece("bishop"); break;
                            case 2: temp.getPiecesPositions().at(move[1]).setNamePiece("rook"); break;
                            case 3: temp.getPiecesPositions().at(move[1]).setNamePiece("knight"); break;
                        }
                        //eval = temp.minimax(aiPlayer, opponent, depth - 1, false);
                        eval = temp.minimax(aiPlayer, opponent, depth - 1, false, alpha, beta);
                        cout<<"6"<<endl;
                        maxEval = max(maxEval, eval);
                        alpha = max(alpha, eval);
                        if (beta <= alpha){
                            break;  // beta cut-off
                        }
                        
                    }
                    temp.getPiecesPositions().at(move[1]).setNamePiece("pawn");
                    temp.getPiecesPositions().at(move[1]).setIsPromoted(false);
                    cout<<"7"<<endl;
                    temp.undoMovePieceMini(move[0],move[1],capturedPiece);
                    cout<<"8"<<endl;
                } else {
                    //int eval = temp.minimax(aiPlayer, opponent, depth - 1, false);
                    int eval = temp.minimax(aiPlayer, opponent, depth - 1, false, alpha, beta);
                    cout<<"9"<<endl;
                    temp.undoMovePieceMini(move[0],move[1], capturedPiece);
                    cout<<"10"<<endl;
                    maxEval = max(maxEval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha){
                        break;  // beta cut-off
                    }
                }
            }
        }
        return maxEval;
    } else {
        int minEval = INT_MAX;
        vector<vector<string>> moves = getAllLegalMoves(opponent, aiPlayer);
        cout<<"enfants"<<endl;

        if (moves.empty()) {
            return evaluate(aiPlayer, opponent);  // No moves => evaluate the current state
        }
        cout<<"num of moves (min) :"<<moves.size()<<endl;
        for (auto m : moves){
            cout<<"{ "<<m[0]<<", "<<m[1]<<" }\n";
        }

       

        for (auto move : moves) {
            Board temp = *this;
            Piece capturedPiece;
            Piece capturedPiece1;

            if (move.size() == 4) {
                //temp.movePiece(move[0], move[1]);
                //temp.movePiece(move[2], move[3]);
                temp.movePieceMini(move[0], move[1], &capturedPiece);
                temp.movePieceMini(move[2], move[3], &capturedPiece1);
                cout<<"11"<<endl;

                //int eval = temp.minimax(aiPlayer, opponent, depth - 1, true);
                int eval = temp.minimax(aiPlayer, opponent, depth - 1, true, alpha, beta);
                cout<<"12"<<endl;

                //temp.movePiece(move[1], move[0]);
                //temp.movePiece(move[3], move[2]);

                temp.undoMovePieceMini(move[0],move[1], capturedPiece);
                temp.undoMovePieceMini(move[2], move[3], capturedPiece1);

                minEval = min(minEval, eval);
                beta = min(beta, eval);
                if (beta <= alpha){
                    break;  // alpha cut-off
                }
        
            } else {
                cout<<"13"<<endl;
                temp.movePieceMini(move[0], move[1], &capturedPiece);
                cout<<"14"<<endl;

                string name = temp.getPiecesPositions().at(move[1]).getNamePiece();
                string color = temp.getPiecesPositions().at(move[1]).getColorPiece();
                int row = temp.getPiecesPositions().at(move[1]).getCaseCoordinate()[0];

                if (name == "pawn" && color == colorHumanPlayer && ((color == "white" && row == 0) || (color == "black" && row == 7))) {
                    temp.getPiecesPositions().at(move[1]).setIsPromoted(true);
                    cout<<"15"<<endl;
                    int eval;
                    for (int i = 0; i < 4; i++) {
                        switch (i) {
                            case 0: temp.getPiecesPositions().at(move[1]).setNamePiece("queen"); break;
                            case 1: temp.getPiecesPositions().at(move[1]).setNamePiece("bishop"); break;
                            case 2: temp.getPiecesPositions().at(move[1]).setNamePiece("rook"); break;
                            case 3: temp.getPiecesPositions().at(move[1]).setNamePiece("knight"); break;
                        }
                        cout<<"16"<<endl;
                        //eval = temp.minimax(aiPlayer, opponent, depth - 1, true);
                        eval = temp.minimax(aiPlayer, opponent, depth - 1, true, alpha, beta);
                        cout<<"17"<<endl;
                        minEval = min(minEval, eval);
                        beta = min(beta, eval);
                        if (beta <= alpha){
                            break;  // alpha cut-off
                        }
                    }
                    temp.getPiecesPositions().at(move[1]).setNamePiece("pawn");
                    temp.getPiecesPositions().at(move[1]).setIsPromoted(false);
                    cout<<"18"<<endl;
                    temp.undoMovePieceMini(move[0], move[1], capturedPiece);
                    cout<<"19"<<endl;
                } else {
                    cout<<"20"<<endl;
                    //int eval = temp.minimax(aiPlayer, opponent, depth - 1, true);
                    int eval = temp.minimax(aiPlayer, opponent, depth - 1, true, alpha, beta);
                    cout<<"21"<<endl;
                    temp.undoMovePieceMini(move[0],move[1], capturedPiece);
                    cout<<"22"<<endl;
                    minEval = min(minEval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha){
                        break;  // alpha cut-off
                    }
                }
            }
        }
        return minEval;
    }
}

vector<string> Board::findBestMove(Player aiPlayer, Player opponent, int depth,int alpha, int beta){
//vector<string> Board::findBestMove(Player aiPlayer, Player opponent, int depth) {
    int bestScore = INT_MIN;
    vector<string> bestMove;
    cout<<"here"<<endl;
    vector<vector<string>> moves = getAllLegalMoves(aiPlayer, opponent);
    for (auto m : moves){
        cout<<"{ "<<m[0]<<", "<<m[1]<<" }\n";
    }
    cout<<"1"<<endl;
    string colorAIPlayer = aiPlayer.getColorPlayer();

    for (auto move : moves) {
        if (move.size() >= 2 && move[0] == move[1]) continue; // Ignore invalid move
        Board temp = *this;
        

        // Handle castling (4-part move)
        if (move.size() == 4) {
            Piece capturedPiece1;
            Piece capturedPiece2;
            //temp.movePiece(move[0], move[1]);
            //temp.movePiece(move[2], move[3]);
            temp.movePieceMini(move[0],move[1],&capturedPiece1);
            temp.movePieceMini(move[0],move[1],&capturedPiece2); 
        } else {
            Piece capturedPiece;
            //temp.movePiece(move[0], move[1]);
            temp.movePieceMini(move[0],move[1],&capturedPiece);

            // Check if promotion is possible
            auto& piece = temp.getPiecesPositions().at(move[1]);
            cout<<"yolo"<<endl;
            if (piece.getNamePiece() == "pawn" && piece.getColorPiece() == colorAIPlayer) {
                int row = piece.getCaseCoordinate()[0];

                bool isPromotion = (row == 0 && colorAIPlayer == "white") || 
                                   (row == 7 && colorAIPlayer == "black");

                if (isPromotion) {
                    piece.setIsPromoted(true);
                    vector<string> promotionPieces = {"queen", "bishop", "rook", "knight"};

                    for (const string& promo : promotionPieces) {
                        piece.setNamePiece(promo);
                        //int score = temp.minimax(aiPlayer, opponent, depth - 1, false);
                        int score = temp.minimax(aiPlayer, opponent, depth - 1, false,alpha,beta);

                        if (score > bestScore) {
                            bestScore = score;
                            vector<string> promotedMove = move;
                            promotedMove.push_back(promo);
                            bestMove = promotedMove;
                        }
                        // Alpha-Beta Pruning
                        alpha = max(alpha, bestScore);
                        if (beta <= alpha) {
                            break;  // Cut-off if beta is smaller or equal to alpha
                        }
                    }

                    // Skip regular minimax call after promotion
                    continue;
                }
            }
        }

        // Regular move evaluation
        cout<<"onestone"<<endl;
        //int score = temp.minimax(aiPlayer, opponent, depth - 1, false);
        int score = temp.minimax(aiPlayer, opponent, depth - 1, false, alpha, beta);
        cout<<"more"<<endl;
        if (score > bestScore) {
            bestScore = score;
            bestMove = move;
        }

        // Alpha-Beta Pruning
        alpha = max(alpha, bestScore);
        if (beta <= alpha) {
            break;  // Cut-off if beta is smaller or equal to alpha
        }
    }

    return bestMove;
}

vector<vector<string>> Board::getAllLegalMoves(Player& currentPlayer, Player& adverser) {
    string colorPlayer = currentPlayer.getColorPlayer();
    vector<vector<string>> allMoves;

    for (auto p : piecesPositions) {
        Piece& piece = p.second;
        string start = piece.getCasePiece();
        string color = piece.getColorPiece();
        string name = piece.getNamePiece();

        if (color != colorPlayer) continue;

        for (int i = 0; i < grid.size(); i++) {
            for (int j = 0; j < grid[0].size(); j++) {
                vector<int> coord = {i, j};
                string end = generateNameCase(coord);

                // Make sure we don't generate moves to the same square
                if (start == end) continue;

                // Make sure we don't generate moves to a square belonging to us
                if (piecesPositions.count(end) && piecesPositions.at(end).getColorPiece() == color) continue;

                if (name == "pawn") {
                    if (!piecesPositions.count(end)) {
                        // Normal forward move
                        if (piece.pawnMove(coord)) {
                            allMoves.push_back({start, end});
                        }
                    } else {
                        // Diagonal capture
                        if (piece.pawnCapture(coord) && piecesPositions.at(end).getColorPiece() != color) {
                            allMoves.push_back({start, end});
                        }
                    }
                
                    // En passant
                    if (isEnPassant(currentPlayer, adverser, start, end)) {
                        allMoves.push_back({start, end});
                    }
                }
                else{

                    // Check move legality and path clearance (except for knight)
                    if (piece.isMoveLegal(coord) && (name == "knight" || isPathClear(start, end))) {

                        // Defensive check: ensure the source is still valid
                        if (piecesPositions.count(start)) {
                            allMoves.push_back({start, end});
                        }
                    }

                }
                
            }
        }

        // Handle castling
        if (name == "king") {
            if (isKingsideCastlingPossible(currentPlayer)) {
                if (colorPlayer == "white") {
                    allMoves.push_back({"e1", "g1", "h1", "f1"});
                } else if (colorPlayer == "black") {
                    allMoves.push_back({"e8", "g8", "h8", "f8"});
                }
            }
            if (isQueensideCastlingPossible(currentPlayer)) {
                if (colorPlayer == "white") {
                    allMoves.push_back({"e1", "c1", "a1", "d1"});
                } else if (colorPlayer == "black") {
                    allMoves.push_back({"e8", "c8", "a8", "d8"});
                }
            }
        }
    }

    return allMoves;
}

int Board::playerTurnAI(Player aiPlayer,Player adverser){
    int t;
    cout<<"\nAI's turn....\n"<<endl;//until here
    t=makeAMoveAI(aiPlayer,adverser);
    return t;
}

int Board::gameLogicAI(Player humanPlayer,Player aiPlayer){
    int n=0;
    int t=0;
    if(numberOfTurn==0){
        if(humanPlayer.getColorPlayer()=="white"){
            cout<<"You're the one to start player 1.\n"<<endl;
            //player1 play
            t=playerTurn(humanPlayer,aiPlayer);
            if(t==4){
                return t;
            }
        }

        //AI play
        t=playerTurnAI(aiPlayer,humanPlayer);

        //AI internal mistake
        if(t==1){
            return t=4;
        }
       
        numberOfTurn++;
        cout<<"\nNumber of Turn : "<<getNumberOfTurn()<<"\n"<<endl;
       
       
        while(n==0){
            n=playerExit();
            if(n==0){
                cout<<"Please enter a valid option"<<endl;
            }
        }
           
        return n;
    }

    t=playerTurn(humanPlayer,aiPlayer);

    //player1 is checkmate or we have a stalemate
    if(t==2 || t==3){
        return t;
    }

    if(t==4){
        return t;
    }

    //AI play
    t=playerTurnAI(aiPlayer,humanPlayer);
    numberOfTurn++;
    cout<<"\nNumber of Turn : "<<getNumberOfTurn()<<endl;

    //AI internal mistake
   
    if(t==1){
        return t=4;
    }
    
    while(n==0){
        n=playerExit();
        cout<<"Please enter a valid option"<<endl;
    }
    
    return n;
}

int Board::makeAMoveAI(Player aiPlayer,Player adverser){
    cout<<"cou"<<endl;
    //vector<string> move = findBestMove(aiPlayer,adverser,3);
    vector<string> move = findBestMove(aiPlayer,adverser,3,INT_MIN, INT_MAX);//pb here
    cout<<"coucou"<<endl;
    string playerColor=aiPlayer.getColorPlayer();   

    if(move.size()==2){//simple move, with capture or en passant (pawn)
        Piece& p=piecesPositions.at(move[0]);
        int t=0;

        if(piecesPositions.count(move[1]) && piecesPositions.at(move[1]).getColorPiece()==adverser.getColorPlayer()){
            Piece& captured=piecesPositions.at(move[1]);
            captured.setIsCaptured(true);
            aiPlayer.getCapturedPieces().push_back(captured);
    
            piecesPositions.erase(move[1]);
            adverser.getPlayerPiecesPositions().erase(move[1]);
            t=1;
        }

        if(isEnPassant(aiPlayer,adverser,move[0],move[1]) && t!=1){
            vector<int> endCapture=generateCaseCoordinates(move[1]);
            int row=endCapture[0];
            int col=endCapture[1];

            if(playerColor=="white"){
                vector<int> coordCapture={row+1,col};
                string capturePosition=generateNameCase(coordCapture);

                Piece& captured=piecesPositions.at(capturePosition);
                captured.setIsCaptured(true);
                aiPlayer.getCapturedPieces().push_back(captured);
        
                piecesPositions.erase(capturePosition);
                adverser.getPlayerPiecesPositions().erase(capturePosition);

            }
            if(playerColor=="black"){
                vector<int> coordCapture={row-1,col};
                string capturePosition=generateNameCase(coordCapture);

                Piece& captured=piecesPositions.at(capturePosition);
                captured.setIsCaptured(true);
                aiPlayer.getCapturedPieces().push_back(captured);
        
                piecesPositions.erase(capturePosition);
                adverser.getPlayerPiecesPositions().erase(capturePosition);
            }         
        }

        p.setLastMove(move[0]);
        p.setCasePiece(move[1]);
       
        p.setCaseCoordinate(generateCaseCoordinates(move[1]));
        p.wasMoved();
        
        // Move the pieces
        piecesPositions[move[1]]=p;
        aiPlayer.getPlayerPiecesPositions()[move[1]]=p;
      
        piecesPositions.erase(move[0]);
        aiPlayer.getPlayerPiecesPositions().erase(move[0]);
        aiPlayer.playedAMove();
        return 0;
    }

    if(move.size()==3){//promotion & capture
        Piece& p=piecesPositions.at(move[0]);

        p.setLastMove(move[0]);
        p.setCasePiece(move[1]);
        p.setNamePiece(move[2]);
        p.setCaseCoordinate(generateCaseCoordinates(move[1]));
        p.wasMoved();

        if(piecesPositions.count(move[1]) && piecesPositions.at(move[1]).getColorPiece()==adverser.getColorPlayer()){
            Piece& captured=piecesPositions.at(move[1]);
            captured.setIsCaptured(true);
            aiPlayer.getCapturedPieces().push_back(captured);
    
            piecesPositions.erase(move[1]);
            adverser.getPlayerPiecesPositions().erase(move[1]);

        }

        // Move the pieces
        piecesPositions[move[1]]=p;
        aiPlayer.getPlayerPiecesPositions()[move[1]]=p;
      
        piecesPositions.erase(move[0]);
        aiPlayer.getPlayerPiecesPositions().erase(move[0]);
        aiPlayer.playedAMove();
        return 0;
        
    }

    if(move.size()==4){//castling 
        Piece& k=piecesPositions.at(move[0]);
        Piece& r=piecesPositions.at(move[2]);

        k.setLastMove(move[0]);
        k.setCasePiece(move[1]);
        k.setCaseCoordinate(generateCaseCoordinates(move[1]));
        k.wasMoved();

        r.setLastMove(move[2]);
        r.setCasePiece(move[3]);
        r.setCaseCoordinate(generateCaseCoordinates(move[3]));
        r.wasMoved();


        // Move the pieces
        piecesPositions[move[1]]=k;
        piecesPositions[move[3]]=r;

        aiPlayer.getPlayerPiecesPositions()[move[1]]=k;
        aiPlayer.getPlayerPiecesPositions()[move[3]]=r;     

        piecesPositions.erase(move[0]);
        piecesPositions.erase(move[2]);

        aiPlayer.getPlayerPiecesPositions().erase(move[0]);
        aiPlayer.getPlayerPiecesPositions().erase(move[2]);
        aiPlayer.playedAMove();
        return 0;
        
    }
    return 1;
}

void Board::displayPiecesMap() const {
    for (auto entry : piecesPositions) {
        cout << entry.first << ": " << entry.second.getNamePiece() << endl;
    }
}

//for GUI
int Board::movePieceGUI(Player& currentPlayer, Player& adverser,string selectedSquare, string moveTo){
    cout<<"1"<<endl;

    string colorPlayer=currentPlayer.getColorPlayer();
    cout<<"2"<<endl;
    vector<vector<string>> moves =getAllLegalMoves(currentPlayer, adverser);
    for(auto m:moves){
        cout<<"start :"<<m[0]<<" , "<<"end : "<<m[1]<<endl;
    }
    cout<<"3"<<endl;


    // Prevent moving to the same square
    if (selectedSquare == moveTo){
        cout<<"4"<<endl;
        cout << "[ERROR] Invalid move: source and destination are the same (" << selectedSquare << ")" << endl;
        return 1;
    }

    // Check if there's a piece at the source
    if (!piecesPositions.count(selectedSquare)) {
        cout<<"5"<<endl;
        cout << "[ERROR] No piece at source square " << selectedSquare << endl;
        return 1;
    }

    // Move opponent's piece 
    if (piecesPositions.count(selectedSquare) && piecesPositions.at(selectedSquare).getColorPiece()!=colorPlayer){
        cout<<"6"<<endl;
        cout << "[ERROR] Opponent's piece : you can't move it"<< endl;
        return 1;              
    }

    // Move to a piece occupied by player's piece 
    if (piecesPositions.count(moveTo) && piecesPositions.at(moveTo).getColorPiece()==colorPlayer){
        cout<<"7"<<endl;
        cout << "[ERROR] Square occupied by your piece : you can't move your square to your piece"<< endl;
        return 1;              
    }

    cout<<"8"<<endl;
    if(isCastlingPossible(currentPlayer)){
        bool isWhite = (colorPlayer == "white");
        bool isKingSideCastle = selectedSquare == (isWhite ? "e1" : "e8") && moveTo == (isWhite ? "g1" : "g8");
        bool isQueenSideCastle = selectedSquare == (isWhite ? "e1" : "e8") && moveTo == (isWhite ? "c1" : "c8");
        if(isKingSideCastle){
            doKingsideCastling(currentPlayer);
            currentPlayer.playedAMove();
            return 0;
        }
        if(isQueenSideCastle){
            doQueensideCastling(currentPlayer);
            currentPlayer.playedAMove();
            return 0;
        }
    }

    for(auto m: moves){
        cout<<"9"<<endl;
        if(m.size()==2){
            cout<<"10"<<endl;
            if(m[0]==selectedSquare && m[1]==moveTo){
                cout<<"11"<<endl;

                Piece& p=piecesPositions.at(selectedSquare);
                vector<int> endCoord=generateCaseCoordinates(moveTo);

                if(isEnPassant(currentPlayer,adverser,selectedSquare,moveTo)){
                    cout<<"12"<<endl;
                    int dir = (colorPlayer == "white") ? 1 : -1;
                    vector<int>pawnCoord = {endCoord[0]+dir, endCoord[1]};
                    string endPos = generateNameCase(pawnCoord);
                
                    // Capture the piece
                    if (piecesPositions.count(endPos)) {
                        Piece& adverserPiece = piecesPositions.at(endPos);
                        adverserPiece.setIsCaptured(true);
                        adverserPiece.setLastMove(endPos);
                        currentPlayer.getCapturedPieces().push_back(adverserPiece);
                        adverser.getPlayerPiecesPositions().erase(endPos);
                        piecesPositions.erase(endPos);  // <<== don't forget this!
                    }
                }

                if (piecesPositions.count(moveTo) && piecesPositions.at(moveTo).getColorPiece() == adverser.getColorPlayer()) {
                    cout<<"13"<<endl;
                    // Capture the piece
                    Piece& adverserPiece = piecesPositions.at(moveTo);
                    adverserPiece.setIsCaptured(true);
                    adverserPiece.setLastMove(moveTo);
                    currentPlayer.getCapturedPieces().push_back(adverserPiece);
                    adverser.getPlayerPiecesPositions().erase(moveTo);
            
                }
                cout<<"14"<<endl;            
                           
                p.setCaseCoordinate(endCoord);
                p.setCasePiece(moveTo);
                p.setLastMove(selectedSquare);
                p.wasMoved();
            
                piecesPositions[moveTo] = p;
                piecesPositions.erase(selectedSquare);
            
                currentPlayer.getPlayerPiecesPositions()[moveTo] = p;
                currentPlayer.getPlayerPiecesPositions().erase(selectedSquare);
                
                currentPlayer.playedAMove();

                
                cout<<"promotion ? :"<<currentPlayer.getPlayerPiecesPositions().at(moveTo).canBePromoted()<<endl;
                cout<<"promotion in board ? :"<<piecesPositions.at(moveTo).canBePromoted()<<endl;
                if(currentPlayer.getPlayerPiecesPositions().at(moveTo).canBePromoted()){
                    cout<<"15"<<endl;                    
                    return 2;
                }
                if(isCheckMate(currentPlayer)){
                    return 3;
                }
                
                if (isStaleMate(currentPlayer)) {
                    return 4;       
                }
                return 0;
            }

        }
    }

    return 1;

}

void Board::promotePawnGUI(Player& p, string position, char type){
    string name;

    switch(type){
        case 'r':
            name="rook";
            break;
        case 'n':
            name="knight";
            break;
        case 'b':
            name="bishop";
            break;
        case 'q':
            name="queen";
            break;
        default :
            name="queen";
            break;
    }

    if(piecesPositions.count(position) && p.getPlayerPiecesPositions().count(position)){
        Piece & pi= piecesPositions.at(position);
        pi.setNamePiece(name);
        piecesPositions[position]=pi;

        Piece & pl= p.getPlayerPiecesPositions().at(position);
        pl.setNamePiece(name);
        p.getPlayerPiecesPositions()[position]=pl;
    }
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
    
    int t=0;
    b.printBoard();

    b.getPiecesPositions().erase("b8");
    p1.getPlayerPiecesPositions().erase("b8");
    
    //Piece captured;

    cout<<"name :"<<b.getPiecesPositions().at("b2").getNamePiece()<<endl;
    cout<<"name p1:"<<p1.getPlayerPiecesPositions().at("b2").getNamePiece()<<endl;

    // Perform a move
    Piece& p=b.getPiecesPositions()["b2"];  
    b.getPiecesPositions().erase("b8");
    b.getPiecesPositions().erase("b2"); 

    b.printBoard();

    b.getPiecesPositions()["b8"]=p;
    p1.getPlayerPiecesPositions()["b8"]=p;

    b.printBoard();

    cout<<"promotion ? :"<<b.getPiecesPositions().at("b8").canBePromoted()<<endl;
    b.promotePawnGUI(p1,"b8",'q');
    cout<<"new name :"<<b.getPiecesPositions().at("b8").getNamePiece()<<endl;
    cout<<"new name p1:"<<p1.getPlayerPiecesPositions().at("b8").getNamePiece()<<endl;
    return t;    
}
*/
/*int main() {
    Board b;
    b.initiateBoard();

    cout << "Initial Board:" << endl;
    b.printBoard();

    Piece captured;

    // Perform a move
    b.movePieceMini("b2", "b4", &captured);

    cout << "\nAfter b2 to b4:" << endl;
    b.printBoard();

    cout << "\nAfter doing b2 to b4:" << endl;
    b.printBoard();

    // Try another move
    b.movePieceMini("a7", "a5", &captured);

    cout << "\nAfter a7 to a5:" << endl;
    b.printBoard();
    cout<<b.getPiecesPositions().at("a5").getNamePiece()<<endl;

    b.movePieceMini("b4", "a5", &captured);
    cout<<captured.getNamePiece()<<endl;

    cout << "\nAfter b4 to a5:" << endl;
    b.printBoard();

    // Undo the move
    b.undoMovePieceMini("b4", "a5", captured);
    cout << "\nAfter a5 to b4:" << endl;
    cout<<captured.getNamePiece()<<endl;
    cout<<b.getPiecesPositions().at("a5").getNamePiece()<<endl;
    b.printBoard();

    return 0;
}*/

  

