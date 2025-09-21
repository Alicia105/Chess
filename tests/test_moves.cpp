#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../include/player.hpp"
#include "../include/piece.hpp"

using namespace std;
//coordinates in C++: coordinates[0]=row,coordinates[1]column;

//Pawn logic
TEST_CASE("Pawn move", "[piece]") {
    Piece p;

    p.initiatePiece({1,0});
    REQUIRE_FALSE(p.pawnMove({0,0}));
    REQUIRE_FALSE(p.pawnMove({-1,-1}));
    REQUIRE_FALSE(p.pawnMove({1,0}));

    REQUIRE(p.pawnMove({2,0}));
    REQUIRE(p.pawnMove({3,0}));
    REQUIRE_FALSE(p.pawnMove({2,1}));

    p.setCaseCoordinate({0,7});
    REQUIRE_FALSE(p.pawnMove({0,9}));

    p.initiatePiece({6,0});
    REQUIRE_FALSE(p.pawnMove({7,0}));
    REQUIRE_FALSE(p.pawnMove({8,-1}));
    REQUIRE_FALSE(p.pawnMove({6,0}));

    REQUIRE(p.pawnMove({5,0}));
    REQUIRE(p.pawnMove({4,0}));
    REQUIRE_FALSE(p.pawnMove({5,1}));

    p.setCaseCoordinate({7,7});
    REQUIRE_FALSE(p.pawnMove({7,9}));
}

//Rook logic
TEST_CASE("Rook move", "[piece]") {
    Piece p;

    p.initiatePiece({0,0});
    REQUIRE_FALSE(p.rookMove({3,3}));
    REQUIRE_FALSE(p.rookMove({-1,0}));
    REQUIRE_FALSE(p.rookMove({0,-1}));
    REQUIRE_FALSE(p.rookMove({0,9}));
    REQUIRE_FALSE(p.rookMove({9,0}));
    REQUIRE_FALSE(p.rookMove({0,0}));

    REQUIRE(p.rookMove({0,7}));
    REQUIRE(p.rookMove({7,0}));    

}

//Knight logic
TEST_CASE("Knight move", "[piece]") {
    Piece p;

    p.initiatePiece({0,1});
    REQUIRE_FALSE(p.knightMove({-2,0}));
    REQUIRE_FALSE(p.knightMove({-2,2}));

    p.setCaseCoordinate({3,3});

    REQUIRE(p.knightMove({1,2}));
    REQUIRE(p.knightMove({1,4}));

    REQUIRE(p.knightMove({5,2}));
    REQUIRE(p.knightMove({5,4}));
    
    REQUIRE(p.knightMove({2,1}));
    REQUIRE(p.knightMove({2,5}));

    REQUIRE(p.knightMove({4,1}));
    REQUIRE(p.knightMove({4,5})); 

    p.setCaseCoordinate({7,3});
    REQUIRE_FALSE(p.knightMove({9,4}));
    REQUIRE_FALSE(p.knightMove({9,2}));
}

//Bishop logic
TEST_CASE("Bishop move", "[piece]") {
    Piece p;

    p.initiatePiece({0,2});

    REQUIRE_FALSE(p.bishopMove({-1,1}));
    REQUIRE_FALSE(p.bishopMove({6,8}));

    p.setCaseCoordinate({3,3});

    REQUIRE_FALSE(p.bishopMove({0,3}));
    REQUIRE_FALSE(p.bishopMove({3,7}));

    REQUIRE(p.bishopMove({7,7}));
    REQUIRE(p.bishopMove({0,6}));
    REQUIRE(p.bishopMove({0,0}));
    REQUIRE(p.bishopMove({6,0}));

}

//Queen logic
TEST_CASE("Queen move", "[piece]") {
    Piece p;
   
    p.initiatePiece({0,3});
    REQUIRE_FALSE(p.queenMove({-1,3}));
    REQUIRE_FALSE(p.queenMove({8,3}));
    REQUIRE_FALSE(p.queenMove({0,-1}));
    REQUIRE_FALSE(p.queenMove({5,8}));

    p.setCaseCoordinate({3,3});

    REQUIRE(p.queenMove({0,3}));
    REQUIRE(p.queenMove({7,3}));
    REQUIRE(p.queenMove({3,0}));
    REQUIRE(p.queenMove({3,7}));

    REQUIRE(p.queenMove({7,7}));
    REQUIRE(p.queenMove({0,6}));
    REQUIRE(p.queenMove({0,0}));
    REQUIRE(p.queenMove({6,0}));


}

//King logic
TEST_CASE("King move", "[piece]") {
    Piece p;

    p.initiatePiece({0,4});
    p.setCaseCoordinate({0,0});
    REQUIRE_FALSE(p.kingMove({-1,0}));
    REQUIRE_FALSE(p.kingMove({0,-1}));

    p.setCaseCoordinate({7,7});
    REQUIRE_FALSE(p.kingMove({7,8}));
    REQUIRE_FALSE(p.kingMove({8,7}));

    p.setCaseCoordinate({3,3});

    REQUIRE_FALSE(p.kingMove({0,3}));
    REQUIRE_FALSE(p.kingMove({7,7}));

    REQUIRE(p.kingMove({2,3}));
    REQUIRE(p.kingMove({4,3}));
    REQUIRE(p.kingMove({3,2}));
    REQUIRE(p.kingMove({3,4}));

    REQUIRE(p.kingMove({2,2}));
    REQUIRE(p.kingMove({2,4}));
    REQUIRE(p.kingMove({4,2}));
    REQUIRE(p.kingMove({4,4}));

}

