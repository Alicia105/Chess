#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "../include/board.hpp"
#include "../include/piece.hpp" 

const int TILE_SIZE = 100;
const int BOARD_SIZE = 8;
const int WINDOW_SIZE = TILE_SIZE * BOARD_SIZE;

sf::Vector2f getTilePosition(int row, int col) {
    return sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE);
}

std::map<std::string, std::string> stateBoard(Board b){
    
    for(int i=0; i<b.getBoard().size();i++){
        for(int j=0; j<b.getBoard()[0].size();j++){
            std::string position=b.getBoard()[i][j];
            if(!b.getPiecesPositions().count(position)) continue;
            std::string n=b.getPiecesPositions().at(position).getNamePiece();
            std::string c=b.getPiecesPositions().at(position).getColorPiece();
            if(n=="knight"){
                std::string id=c.substr(0,1)+"n";
                board[position]=id;
            }
            else{
                std::string id=c.substr(0,1)+n.substr(0,1);
                board[position]=id;
            }
        }
    }

}

int displayChessBoard(Board b, Player p1, Player p2){
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_SIZE), "Chess GUI with SFML");
    window.setFramerateLimit(60);

    sf::Color lightSquare(240, 217, 181);
    sf::Color darkSquare(181, 136, 99);

    std::map<std::string, sf::Texture> pieceTextures;
    std::map<std::string, sf::Sprite> pieceSprites;

    std::string pieces[] = {
        "wp", "wr", "wn", "wb", "wq", "wk",
        "bp", "br", "bn", "bb", "bq", "bk"
    };

    for (const auto& name : pieces) {
        sf::Texture texture;
        if (!texture.loadFromFile("../images/chessIcons/" + name + ".png")) {
            std::cerr << "Failed to load " << name << ".png" << std::endl;
            continue;
        }
        pieceTextures[name] = texture;
        pieceSprites[name].setTexture(pieceTextures[name]);
    }

    // Initial positions
    std::map<std::string, std::string> board=stateBoard(b);
        
    auto getBoardCoords = [](const std::string& pos) {
        int col = pos[0] - 'a';
        int row = 8 - (pos[1] - '0');
        //std::vector<int> coords = b.generateCaseCoordinates(pos);
        return std::make_pair(row, col);
    };

    
    std::string selectedSquare = "";
    bool isSelecting = false;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
                return 1; 
            } 

            /*if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    int x = event.mouseButton.x;
                    int y = event.mouseButton.y;
    
                    int col = x / squareSize;
                    int row = y / squareSize;
    
                    // Flip Y-axis if needed
                    std::string clickedSquare = b.generateNameCase({row, col});
    
                    if (!isSelecting) {
                        selectedSquare = clickedSquare;
                        isSelecting = true;
                        std::cout << "Selected from: " << selectedSquare << std::endl;
                    } else {
                        std::string moveTo = clickedSquare;
                        isSelecting = false;
                        std::cout << "Trying move: " << selectedSquare << " -> " << moveTo << std::endl;
    
                        // Call your move logic here
                        if (b.makeMove(selectedSquare, moveTo)) {
                            std::cout << "Move made!" << std::endl;
                            //update board for drawing
                            board=stateBoard(b);
                        } else {
                            std::cout << "Illegal move!" << std::endl;
                        }
                    }
                }
            }*/
        }
        

        window.clear();

        // Draw board
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(getTilePosition(row, col));
                tile.setFillColor((row + col) % 2 == 0 ? lightSquare : darkSquare);
                window.draw(tile);
            }
        }

        // Draw pieces
        for (const auto& entry : board ) {
            auto [row, col] = getBoardCoords(entry.first);
            std::string pieceName = entry.second;
            sf::Sprite& sprite = pieceSprites[pieceName];
            sprite.setPosition(getTilePosition(row, col));
            window.draw(sprite);
        }
        
        window.display();
    }

    return 0;

}

int main() {
    int a=displayChessBoard(b,p1,p2);
    cout<<"a :"<<a<<endl;
   
}
