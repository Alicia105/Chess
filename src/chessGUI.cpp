#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "../include/board.hpp"
#include "../include/piece.hpp" 

const int TILE_SIZE = 100;
const int BOARD_SIZE = 8;
const int WINDOW_SIZE = TILE_SIZE * BOARD_SIZE;

using namespace std;

sf::Vector2f getTilePosition(int row, int col) {
    return sf::Vector2f(col * TILE_SIZE, row * TILE_SIZE);
}

map<string, string> stateBoard(Board b){
    
    map<string, string> board;
    for(int i=0; i<b.getBoard().size();i++){
        for(int j=0; j<b.getBoard()[0].size();j++){
            string position=b.getBoard()[i][j];
            if(!b.getPiecesPositions().count(position)) continue;
            string n=b.getPiecesPositions().at(position).getNamePiece();
            string c=b.getPiecesPositions().at(position).getColorPiece();
            if(n=="knight"){
                string id=c.substr(0,1)+"n";
                board[position]=id;
            }
            else{
                string id=c.substr(0,1)+n.substr(0,1);
                board[position]=id;
            }
        }
    }
    return board;
}

int displayChessBoard(Board b, Player p1, Player p2){
    const int WINDOW_HEIGHT = TILE_SIZE * BOARD_SIZE + 100; // extra room
    sf::RenderWindow window(sf::VideoMode(WINDOW_SIZE, WINDOW_HEIGHT), "Chess GUI with SFML");
    //sf::RenderWindow window(sf::VideoMode({WINDOW_SIZE, WINDOW_SIZE}), "Chess GUI with SFML");
    window.setFramerateLimit(60);

    sf::Color lightSquare(240, 217, 181);
    sf::Color darkSquare(181, 136, 99);

    map<string, sf::Texture> pieceTextures;
    map<string, sf::Sprite> pieceSprites;
    // Sprite storage with unique_ptr
    //map<string, unique_ptr<sf::Sprite>> pieceSprites;

    string pieces[] = {
        "wp", "wr", "wn", "wb", "wq", "wk",
        "bp", "br", "bn", "bb", "bq", "bk"
    };

    for (const auto& name : pieces) {
        sf::Texture texture;
        sf::Sprite sprite;
        
        if (!texture.loadFromFile("../resources/images/chessIcons/" + name + ".png")) {
            cerr << "Failed to load " << name << ".png" << endl;
            continue;
        }
        pieceTextures[name] = texture;
        //sf::Sprite sprite(texture);
        //pieceSprites[name]=sprite;
        pieceSprites[name].setTexture(pieceTextures[name]);

        // Create sprite and store in map
        //auto sprite = make_unique<sf::Sprite>(pieceTextures[name]);
        //pieceSprites[name] = std::move(sprite);
    }

    // Initial positions
    map<string, string> board=stateBoard(b);

    sf::Font font;
    if (!font.loadFromFile("../resources/Font/Raleway-Light.ttf")) {
        cerr << "Failed to load font!" << endl;
        return -1;
    }
        
    auto getBoardCoords = [](const string& pos) {
        int col = pos[0] - 'a';
        int row = 8 - (pos[1] - '0');
        //vector<int> coords = b.generateCaseCoordinates(pos);
        return make_pair(row, col);
    };

    
    string selectedSquare = "";
    bool isSelecting = false;

    sf::Text title("Chess AI", font, 32);
    title.setFillColor(sf::Color::White);
    title.setPosition(WINDOW_SIZE / 2 - title.getLocalBounds().width / 2, 10);
        

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
                    string clickedSquare = b.generateNameCase({row, col});
    
                    if (!isSelecting) {
                        selectedSquare = clickedSquare;
                        isSelecting = true;
                        cout << "Selected from: " << selectedSquare << endl;
                    } else {
                        string moveTo = clickedSquare;
                        isSelecting = false;
                        cout << "Trying move: " << selectedSquare << " -> " << moveTo << endl;
    
                        // Call your move logic here
                        if (b.makeMove(selectedSquare, moveTo)) {
                            cout << "Move made!" << endl;
                            //update board for drawing
                            board=stateBoard(b);
                        } else {
                            cout << "Illegal move!" << endl;
                        }
                    }
                }
            }*/
        }
        

        window.clear();

        // Draw title
        window.draw(title);

        // Offset board down to leave room for title
        int boardOffsetY = 50;  // Space for title

        // Draw board with labels
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(col * TILE_SIZE, boardOffsetY + row * TILE_SIZE);
                tile.setFillColor((row + col) % 2 == 0 ? lightSquare : darkSquare);
                window.draw(tile);
            }
        }

        // Draw board
        /*for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(getTilePosition(row, col));
                tile.setFillColor((row + col) % 2 == 0 ? lightSquare : darkSquare);
                window.draw(tile);
            }
        }*/

        // Draw labels
        for (int i = 0; i < BOARD_SIZE; ++i) {
            // Column labels (a–h)
            sf::Text colLabel;
            colLabel.setFont(font);
            colLabel.setCharacterSize(18);
            colLabel.setFillColor(sf::Color::Black);
            colLabel.setString(static_cast<char>('a' + i));
            colLabel.setPosition(i * TILE_SIZE + TILE_SIZE / 2 - 5, boardOffsetY + BOARD_SIZE * TILE_SIZE + 5);
            window.draw(colLabel);

            // Row labels (8–1)
            sf::Text rowLabel;
            rowLabel.setFont(font);
            rowLabel.setCharacterSize(18);
            rowLabel.setFillColor(sf::Color::Black);
            rowLabel.setString(std::to_string(8 - i));
            rowLabel.setPosition(5, boardOffsetY + i * TILE_SIZE + TILE_SIZE / 2 - 10);
            window.draw(rowLabel);
        }

        // Draw pieces
        /*for (const auto& entry : board ) {
            auto [row, col] = getBoardCoords(entry.first);
            string pieceName = entry.second;
            sf::Sprite& sprite = pieceSprites[pieceName];
            sprite.setPosition(getTilePosition(row, col));
            window.draw(sprite);
        }*/

        // Draw pieces
        for (const auto& entry : board ) {
            auto [row, col] = getBoardCoords(entry.first);
            std::string pieceName = entry.second;
            sf::Sprite& sprite = pieceSprites[pieceName];
            //sprite.setPosition(getTilePosition(row, col));
            sprite.setPosition(col * TILE_SIZE, boardOffsetY + row * TILE_SIZE);
            window.draw(sprite);
        }
        
        window.display();
    }

    return 0;

}

int main() {
    Board b;
    b.initiateBoard();
    Player p1("white");
    Player p2("black");

    p1.initiatePlayer(b.getPiecesPositions());
    p2.initiatePlayer(b.getPiecesPositions());

    int a=displayChessBoard(b,p1,p2);

    cout<<"a :"<<a<<endl;
   
}
