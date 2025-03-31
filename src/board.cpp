#include <iostream>
#include <vector>
#include "board.hpp"
#include "piece.hpp"

using namespace std;

Board::Board(){}
Board::~Board(){}

//geters
vector<vector<string>> Board::getBoard(){
    return grid;
}

vector<int>Board::getCase(string nameCase){
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

map<string,Piece> getPiecesPostions(){
    return piecesPostions;
}

//setters
vector<vector<string>> Board::setBoard(){}

string Board::setCase(vector<int> coordinates){

    char column=nameCase.at(0);
    char row=nameCase.at(1);

    //Convert row into int 
    int numRow = row - '0';

    for (int i=0; i<grid.size(); i++){
        for(string s:v){
           
        }

    }

}
string Board::generateNameCase(){}