#include <iostream>
#include <vector>
#include <map>
#include "board.hpp"
#include "piece.hpp"

using namespace std;

Board::Board(){
    grid=vector<vector<string>>(8,vector<string>(8));
    piecesPostions=map<string,Piece>();
}

Board::~Board(){}

//getters
vector<vector<string>> Board::getBoard(){
    return grid;
}

vector<int>Board::getCase(string nameCase){

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

map<string,Piece> getPiecesPostions(){
    return piecesPostions;
}

//setters

string Board::setCase(vector<int> coordinates,string nameCase){

    //coordinates in C++: coordinates[0]=row,coordinates[1]=column;
    int row=coordinates[0];
    int column=coordinates[1];   

    grid[row][column]=nameCase;
}

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
    
    string nameCase=column+to_string(numRow);

    return nameCase;
}

void Board::initiateBoard(){

    //coordinates in C++: coordinates[0]=row,coordinates[1]column;

    for(int i=0;i<grid.size();i++){
        for(int j=0;j<grid[i].size();j++){
            
            vector<int> coord(2);
            coord[0]=i;
            coord[1]=j;
            string s=generateNameCase(coord);

            //Piece
            Piece p;
            p.initiatePiece(coord);
            p.setCasePiece(s);

            //Board
            grid[i][j]=s;
            piecesPostions.insert(pair<string,Piece>(s,p));                  

        }
    }
}