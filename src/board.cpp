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

void Board::updateScore(Player p){
    if(p.getColorPlayer()=="white"){
        scorePlayer1+=1;
    }
    if(p.getColorPlayer()=="black"){
        scorePlayer2+=1;
    }
}

void Board::movePiece(string from, string to) {
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

//isKingInCheck
bool Board::isKingUnderAttack(Player p,string kingPosition){

    string kingColor=p.getColorPlayer();

    if (kingPosition.empty()) {
        cout << "Error: King not found!" << endl;
        return false;
    }

    // Check if any opponent piece can attack the king
    for (auto piece : piecesPositions) {
        if (piece.second.getColorPiece() != kingColor) {
            vector<int> endCoord = generateCaseCoordinates(kingPosition);
            if (piece.second.isMoveLegal(endCoord) &&
                (piece.second.getNamePiece() == "knight" || isPathClear(piece.first, kingPosition))) {
                return true; // King is under attack
            }
        }
    }
    return false;
}

//CheckMate
bool Board::isCheckMate(Player p){

    // Find the king's position
    string kingPosition=getKingPosition(p);

    //Should never happen
    if (kingPosition.empty()){
        cout << "Error: King not found!" << endl;
        return false;
    }
    
    if (!isKingUnderAttack(p)) {
        return false; // Not in check, so not checkmate
    }

    string kingColor=p.getColorPlayer();

    // Define possible king moves
    vector<pair<int, int>> moves = {
        {-1,0}, {1,0}, {0,-1}, {0,1},
        {-1,-1}, {-1,1}, {1,-1}, {1,1}
    };

    vector<int> kingCoord=generateCaseCoordinates(kingPosition);
    vector<string> attackers=findKingAttackers(p);

    //Check if the king has an escape move
    // Iterate through possible moves
    for (auto move : moves) {
        int newX = kingCoord[0] + move.first;
        int newY = kingCoord[1] + move.second;
        vector<int> endCoord={newX,newY};

        if (endCoord[0] >= 0 && endCoord[0] < 8 && endCoord[1] >= 0 && endCoord[1] < 8) { // Check board limits
            string newPosition = generateNameCase(endCoord);

            // If the square is not occupied by the same color and doesn't put king in check, it's a valid escape
            if ((!piecesPositions.count(newPosition) || piecesPositions.at(newPosition).getColorPiece() != kingColor) &&
                !isKingUnderAttack(kingColor)) {
                return false; // King has an escape move, so it's not checkmate
            }
        }
    }

    //Can Attacker be aptured or blocked
    for(auto attackerPosition: attackers){
        for (auto pc : piecesPositions) {
            if (pc.second.getColorPiece() == kingColor) { // Friendly piece
                vector<int> attackCoord = generateCaseCoordinates(attackerPosition);
                // Get the path from attacker to king (for blocking)
                vector<vector<int>> pathToKing = getPath(attackCoord, kingCoord);

                if (pc.second.isMoveLegal(attackCoord) && isPathClear(pc.second.getCasePiece(), attackerPosition)){
                    return false; // A piece can capture the attacker -> No checkmate
                }

                for (auto square : pathToKing) {
                    if (pc.second.isMoveLegal(square) && isPathClear(pc.second.getCasePiece(), generateNameCase(square))) {
                        return false; // A piece can block the attack -> No checkmate
                    }
                }
            }
        }
    }

    // If no escape, block, or capture is possible, it's checkmate
    return true;
}

//CheckMate
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

            // If the square is not occupied by the same color and doesn't put king in check, it's a valid escape
            if (!piecesPositions.count(newPosition) || piecesPositions.at(newPosition).getColorPiece() != kingColor){
                // Simulate the move to see if it puts the king in check
                Board tempBoard = *this;
                tempBoard.movePiece(kingPosition, newPosition);
                if (!tempBoard.isKingUnderAttack(p,newPosition)) {
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

            // Generate all possible moves for this piece
            for (int i = 0; i <grid.size(); i++) {
                for (int j = 0; j < grid[0].size(); j++) {
                    vector<int> testCoord = {i, j};
                    string testPosition = generateNameCase(testCoord);

                    // Check if the move is legal
                    if (piece.second.isMoveLegal(testCoord) && 
                        (piece.second.getNamePiece() == "knight" || isPathClear(piecePosition, testPosition))) {
                        
                        // Simulate the move to check if it avoids check
                        Board tempBoard = *this;
                        tempBoard.movePiece(piecePosition, testPosition);
                        if (!tempBoard.isKingUnderAttack(p,getKingPosition(p))) {
                            return false; // A piece has a legal move, no stalemate
                        }
                    }
                }
            }
        }
    }

    // If no legal moves exist, it's a stalemate
    return true;
}

//bool Board::isKingUnderAttack

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
        cout<<"\nNumber of Turn : "<<getNumberOfTurn()<<endl;
        if(t==4){
            return t;
        }

        //to fix
        while(n==0){
            n=playerExit();
            cout<<"Please enter a valid option"<<endl;
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

    //to fix
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

//good
int Board::makeAMove(Player currentPlayer,Player adverser){

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

    if(x==1){
        return 5;
    }

    if(x==2){
        return 6;
    }

    if(x==3){
        return 7;
    }
   
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

