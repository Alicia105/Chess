#include <iostream>
#include "../include/board.hpp"
#include "../include/menu.hpp"

using namespace std;

void printWelcome(){
    cout<<"===========================CHESS===========================\n"<<endl;
    cout<<"Welcome to our chess game !"<<endl;
    return;
} 

void printRules(){
    cout<<"You are going to play a 2D Chess game."<<endl;
    cout<<"You can exit at the end of each turn."<<endl;
    cout<<"Each piece is represented by the first letter of its name (except for knights that are indicated by n)."<<endl;
    cout<<"Their position is named by a letter from a to h for the column and a number from 8 to 1 for the row (e.g a6)"<<endl;
    cout<<""<<endl;
    //cout<<"You can also choose to save the current board to resume later."<<endl;
    cout<<"May the best win !"<<endl;

    return;
}

void printBye(){
    cout<<"Thank you for playing our chess game !"<<endl;
    cout<<"=========================== BYE ===========================\n"<<endl;
    return;
} 

int main(){

    //initiate basic components for game
    Board b;
    b.initiateBoard();

    Player p1("white");
    Player p2("black");

    p1.initiatePlayer(b.getPiecesPositions());
    p2.initiatePlayer(b.getPiecesPositions());

    //start game
    printWelcome();
    printRules();

    int t=1;

    while(t==1){
        t=b.gameLogic(p1,p2);
    }

    if(t==3){
        cout<<"Your was successfully saved !"<<endl;
    }

    printBye();
    return 0;
}



