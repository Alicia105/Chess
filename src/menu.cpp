#include <iostream>
#include "board.hpp"

void printWelcome(){
    cout<<"===========================CHESS===========================\n"<<endl;
    cout<<"Welcome to our chess game !"<<endl;
    return;
} 

int main(){

    //initiate basic components for game
    Board b;
    b.initiateBoard();

    Player p1("white");
    Player p2("black");

    p1.initiatePlayer(b.getPiecesPostions());
    p2.initiatePlayer(b.getPiecesPostions());

    //start game
    printWelcome();

}



