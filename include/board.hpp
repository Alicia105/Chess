#ifndef DEF_BOARD
#define DEF_BOARD

#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cctype>
#include "piece.hpp"
#include "player.hpp"

class Board{

    private:
    std::vector<std::vector<std::string>> grid;//chess grid of 8x8, eac case contains a string representing the name of the case in traditional chess nomenclature
    std::map<std::string,Piece> piecesPositions;
    int numberOfTurn;
    int scorePlayer1;
    int scorePlayer2;

    public :
    Board();
    ~Board();

    //geters
    std::vector<std::vector<std::string>> getBoard();//good
    std::vector<int> getCase(std::string nameCaseInChess);//nameCaseInChess:name of the case in chess nomenclature 
    std::map<std::string,Piece>& getPiecesPositions();//good
    int getNumberOfTurn();//good
    std::string getKingPosition(Player pl);//good
    std::vector<std::vector<int>> getPath(std::vector<int> startCoordinates, std::vector<int> endCoordinates);//good

    //setters

    void clearBoard();//good
    //coordinates in C++: coordinates[0]=row,coordinates[1]column;
    void setCase(std::vector<int> coordinates,std::string nameCaseInChess);//good ->coordinates in C++,nameCaseInChess:name of the case in chess nomenclature-->name the case with nameInChess
    std::string generateNameCase(std::vector<int> coordinates);//good ->coordinates in C++, return nameCaseInChess
    std::vector<int> generateCaseCoordinates(std::string nameCaseInChess);//good
    void initiateBoard();//good
    
    //visualization
    void printBoard();//good

    //for game logic
    void printScore();
    void updateScore(Player p);//good
    bool isKingsideCastlingPossible(Player currentPlayer);//good
    bool isQueensideCastlingPossible(Player currentPlayer);//good
    bool isCastlingPossible(Player p);//good
    void chooseCastling(Player p);//good
    void doQueensideCastling(Player p);//good
    void doKingsideCastling(Player p);//good

    void movePiece(std::string from, std::string to);//good
    bool isCaseOccupied(std::vector<int> coordinates);//good
    bool isPathClear(std::string startPosition,std::string endPosition);//good
    std::vector<std::string> findKingAttackers(Player pl);//good
    bool isKingUnderAttack(Player p,std::string kingPosition);//good
    bool isCheckMate(Player p);//good
    bool isStaleMate(Player p);//good
    bool isEnPassant(Player currentPlayer,Player adverser,std::string startPosition,std::string endPosition);//good
    
    int gameLogic(Player player1,Player player2);//good
    int playerTurn(Player player1,Player player2);//good
    int makeAMove(Player currentPlayer,Player adverser);//good
    int playerExit();//good
    bool checkIfCorrectMoveInput(std::string moveInput);//good
    std::string processMoveInput(std::string moveInput);//good

    //for ai
    bool isGameOver(Player aiPlayer);
    int evaluate(Player& aiPlayer, Player& humanPlayer);
    void movePieceMini(std::string from, std::string to,Piece* capturedPiece = nullptr);
    void undoMovePieceMini(std::string from, std::string to,Piece& capturedPiece);
    //int minimax(Player aiPlayer, Player humanPlayer, int depth, bool isMaximizing);
    int minimax(Player aiPlayer, Player humanPlayer, int depth, bool isMaximizing, int alpha, int beta);
    std::vector<std::vector<std::string>> getAllLegalMoves(Player& currentPlayer,Player& adverser);
    //std::vector<std::string> findBestMove(Player aiPlayer, Player opponent, int depth);
    std::vector<std::string> findBestMove(Player aiPlayer, Player opponent, int depth,int alpha, int beta);
    int playerTurnAI(Player humanPlayer,Player aiPlayer);
    int gameLogicAI(Player humanPlayer,Player aiPlayer);
    int makeAMoveAI(Player aiPlayer,Player adverser);
    void displayPiecesMap() const;

    //for GUI
    int movePieceGUI(Player& currentPlayer, Player& adverser,std::string selectedSquare, std::string moveTo);
    void promotePawnGUI(Player& p, std::string position, char type);
    
    
};

#endif