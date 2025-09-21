#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../include/player.hpp"
#include "../include/piece.hpp"

using namespace std;

// Piece default constructor 
TEST_CASE("Piece default constructor", "[piece]") {
    Piece p;

    REQUIRE(p.getNamePiece() == "");
    REQUIRE(p.getColorPiece() == "");
    REQUIRE(p.getCasePiece() == "");
    REQUIRE(p.getCaseCoordinate()==vector<int>{0,0});
    REQUIRE(p.getNumberOfMove() == 0);
    REQUIRE(p.getIsCaptured() == false);
    REQUIRE(p.getIsPromoted() == false);
    REQUIRE(p.getLastMove() == "");
}

//Piece setters
TEST_CASE("Piece name setter", "[piece]") {
    Piece p;

    REQUIRE(p.getNamePiece() == "");
    p.setNamePiece("rook");
    REQUIRE_FALSE(p.getNamePiece() == "");
    REQUIRE(p.getNamePiece() == "rook");
}

TEST_CASE("Piece color setter", "[piece]") {
    Piece p;

    REQUIRE(p.getColorPiece() == "");
    p.setColorPiece("white");
    REQUIRE_FALSE(p.getColorPiece() == "");
    REQUIRE(p.getColorPiece() == "white");
}

TEST_CASE("Piece case name setter", "[piece]") {
    Piece p;

    REQUIRE(p.getCasePiece() == "");
    p.setCasePiece("a1");
    REQUIRE(p.getCasePiece() == "a1");
}

TEST_CASE("Piece case coordinates", "[piece]") {
    Piece p;
    vector<int> coord = {1,1};

    REQUIRE(p.getCaseCoordinate().empty());
    p.setCaseCoordinate(coord);
    REQUIRE_FALSE(p.getCaseCoordinate().empty());
    REQUIRE(p.getCaseCoordinate() == coord);

}

//Move update
TEST_CASE("Piece move updates state", "[piece]") {
    Piece p;
    
    std::vector<int> coords = {4, 4};
    p.setCasePiece("e4");
    p.setCaseCoordinate(coords);
    p.setLastMove("e2");
    p.wasMoved();

    REQUIRE(p.getCasePiece() == "e4");
    REQUIRE(p.getCaseCoordinate() == coords);
    REQUIRE(p.getLastMove() == "e2");
    REQUIRE(p.getNumberOfMove() == 1);
    p.setNumberOfMove(5);
    REQUIRE(p.getNumberOfMove() == 5);
}

//Capture Flag
TEST_CASE("Piece captured flag", "[piece]") {
    Piece p;
    REQUIRE(p.getIsCaptured() == false);
    p.setIsCaptured(true);
    REQUIRE(p.getIsCaptured() == true);
}

//Promotion Flag
TEST_CASE("Piece promotion flag", "[piece]") {
    Piece p;
    REQUIRE(p.getIsPromoted() == false);
    p.setIsPromoted(true);
    REQUIRE(p.getIsPromoted() == true);
}

//Black pieces initialisation
TEST_CASE("Black pieces initialisation", "[piece]") {
    Piece p,a;
    vector<int> coordinates={0,0};
    vector<int> coord={1,0};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);

    REQUIRE(p.getColorPiece() == "black");
    REQUIRE(p.getCaseCoordinate()==coordinates);

    REQUIRE(a.getColorPiece() == "black");
    REQUIRE(a.getCaseCoordinate()==coord);

}

//White pieces initialisation
TEST_CASE("White pieces initialisation", "[piece]") {
    Piece p,a;
    vector<int> coordinates={6,0};
    vector<int> coord={7,0};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);

    REQUIRE(p.getColorPiece() == "white");
    REQUIRE(p.getCaseCoordinate()==coordinates);

    REQUIRE(a.getColorPiece() == "white");
    REQUIRE(a.getCaseCoordinate()==coord);

}

//Pawn
TEST_CASE("Pawn initialisation", "[piece]") {
    Piece p,a;
    vector<int> coordinates={1,0};
    vector<int> coord={6,0};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);

    REQUIRE(p.getNamePiece() == "pawn");
    REQUIRE(a.getNamePiece() == "pawn");

}

//Rook
TEST_CASE("Rook initialisation", "[piece]") {
    Piece p,a,b,c;
    vector<int> coordinates={0,0};
    vector<int> coord={0,7};
    vector<int> coo={7,0};
    vector<int> crd={7,7};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);
    b.initiatePiece(coo);
    c.initiatePiece(crd);

    REQUIRE(p.getNamePiece() == "rook");
    REQUIRE(a.getNamePiece() == "rook");
    REQUIRE(b.getNamePiece() == "rook");
    REQUIRE(c.getNamePiece() == "rook");

}

//Knight
TEST_CASE("Knight initialisation", "[piece]") {
    Piece p,a,b,c;
    vector<int> coordinates={0,1};
    vector<int> coord={0,6};
    vector<int> coo={7,1};
    vector<int> crd={7,6};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);
    b.initiatePiece(coo);
    c.initiatePiece(crd);

    REQUIRE(p.getNamePiece() == "knight");
    REQUIRE(a.getNamePiece() == "knight");
    REQUIRE(b.getNamePiece() == "knight");
    REQUIRE(c.getNamePiece() == "knight");

}

//Bishop
TEST_CASE("Bishop initialisation", "[piece]") {
    Piece p,a,b,c;
    vector<int> coordinates={0,2};
    vector<int> coord={0,5};
    vector<int> coo={7,2};
    vector<int> crd={7,5};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);
    b.initiatePiece(coo);
    c.initiatePiece(crd);

    REQUIRE(p.getNamePiece() == "bishop");
    REQUIRE(a.getNamePiece() == "bishop");
    REQUIRE(b.getNamePiece() == "bishop");
    REQUIRE(c.getNamePiece() == "bishop");

}

//Queen
TEST_CASE("Queen initialisation", "[piece]") {
    Piece p,a;
    vector<int> coordinates={0,3};
    vector<int> coord={7,3};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);

    REQUIRE(p.getNamePiece() == "queen");
    REQUIRE(a.getNamePiece() == "queen");

}

//King
TEST_CASE("King initialisation", "[piece]") {
    Piece p,a;
    vector<int> coordinates={0,4};
    vector<int> coord={7,4};

    p.initiatePiece(coordinates);    
    a.initiatePiece(coord);

    REQUIRE(p.getNamePiece() == "king");
    REQUIRE(a.getNamePiece() == "king");

}

