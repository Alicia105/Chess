#include <iostream>
#include "../include/board.hpp"
#include "../include/chessGUI.hpp"
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
    //cout<<"You can also choose to save the current board to resume later."<<endl;
    cout<<"May the best win !"<<endl;

    return;
}

int chooseOpponent(){
    int x;
    cout<<"Do you want to play against a human or AI ?"<<endl;
    cout<<"1.Human 2.AI"<<endl;
    cin>>x;
   
    while(x!=1 && x!=2){
        cout<<"Please enter a valid option (1 or 2):"<<endl;
        cin>>x;
    }
    cin.ignore();
    return x;
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

    int a=displayChessBoard(b,p1,p2);

    if(a==1){
        
    }

    //start game
    printWelcome();
    printRules();
    int c=chooseOpponent();

    if(c==1){
        int t=5;
        cout<<"You chose to play againt a human.\n"<<endl;
        while(t==5){
            t=b.gameLogic(p1,p2);
            /*if(b.isGameOver(p1,p2)){
                b.printScore();
            }*/           
        }

        if(t==7){
            cout<<"Your game was successfully saved !"<<endl;
        }

        if(t==4){
            cout<<"Error: Unexpected internal error"<<endl;
        }

        printBye();
        return 0;

    }
    if(c==2){
        cout<<"You chose to play againt AI.\n"<<endl;
        int t=5;

        while(t==5){
            t=b.gameLogicAI(p1,p2);
            if(b.isGameOver(p2)){
                b.printScore();
            }
        }

        if(t==7){
            cout<<"Your game was successfully saved !"<<endl;
        }

        if(t==4){
            cout<<"Error: Unexpected internal error"<<endl;
        }

        printBye();
        return 0;
    }

    return 0;
    
}



