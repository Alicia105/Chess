#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../include/player.hpp"

using namespace std;

//Default Player constructor
TEST_CASE("Player default constructor", "[player]") {
    Player p;

    REQUIRE(p.getColorPlayer() == "");
    REQUIRE(p.getCapturedPieces().empty());
    REQUIRE(p.getPlayerPiecesPositions().empty());
    REQUIRE(p.getNumberOfMove() == 0);
}

//Player constructor with color parameter
TEST_CASE("Player constructor with color parameter", "[player]") {
    Player p("black");

    REQUIRE(p.getColorPlayer() != "");
    REQUIRE(p.getColorPlayer() == "black");
    REQUIRE(p.getCapturedPieces().empty());
    REQUIRE(p.getPlayerPiecesPositions().empty());
    REQUIRE(p.getNumberOfMove() == 0);
}


// Player setters
TEST_CASE("Player color setter", "[player]") {
    Player p;

    REQUIRE(p.getColorPlayer() == "");
    p.setColorPlayer("black");
    REQUIRE(p.getColorPlayer() == "black");
    p.setColorPlayer("w");
    REQUIRE(p.getColorPlayer() == "w");
}

TEST_CASE("Player's captured pieces setter", "[player]") {
    Player p;
    Piece a;

    REQUIRE(p.getCapturedPieces().empty());
    p.setCapturedPiece(a);
    REQUIRE_FALSE(p.getCapturedPieces().empty());
    REQUIRE(p.getCapturedPieces().size()==1);

}

TEST_CASE("Player's number of move setter", "[player]") {
    Player p;
    
    REQUIRE(p.getNumberOfMove() == 0);
    p.playedAMove();
    REQUIRE_FALSE(p.getNumberOfMove() == 0);
    REQUIRE(p.getNumberOfMove() == 1);
    p.setNumberOfMove(5);
    REQUIRE(p.getNumberOfMove() == 5);
}

//test initiatePlayer

//test getCapturedPieces

//test getPlayerPiecesPositions