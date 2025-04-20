#include <iostream>
#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include "../include/board.hpp"
#include "../include/piece.hpp" 

const int TILE_SIZE = 100;
const int BOARD_SIZE = 8;
const int WINDOW_SIZE = TILE_SIZE * BOARD_SIZE;

const int LABEL_MARGIN = 40;

const int TITLE_HEIGHT = 60;
const int WINDOW_WIDTH = TILE_SIZE * BOARD_SIZE + 2 * LABEL_MARGIN;
const int WINDOW_HEIGHT = TILE_SIZE * BOARD_SIZE + TITLE_HEIGHT + LABEL_MARGIN;


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
    //const int WINDOW_HEIGHT = TILE_SIZE * BOARD_SIZE + 100; // extra room
    sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Chess GUI with SFML");

    window.setFramerateLimit(60);

    sf::Color lightSquare(240, 217, 181);
    sf::Color darkSquare(181, 136, 99);

    map<string, sf::Texture> pieceTextures;
    map<string, sf::Sprite> pieceSprites;
    
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

        // Center origin
        sprite.setTexture(pieceTextures[name]);
        sf::FloatRect bounds = sprite.getLocalBounds();
        sprite.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
    
        // Scale to TILE_SIZE (e.g., 70% of tile)
        float scaleX = (TILE_SIZE * 0.7f) / bounds.width;
        float scaleY = (TILE_SIZE * 0.7f) / bounds.height;
        sprite.setScale(scaleX, scaleY);
    
        pieceSprites[name]=sprite;

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

        // Background frame
        sf::RectangleShape boardFrame(sf::Vector2f(BOARD_SIZE * TILE_SIZE + 2, BOARD_SIZE * TILE_SIZE + 2));
        boardFrame.setPosition(LABEL_MARGIN - 1, TITLE_HEIGHT);
        boardFrame.setFillColor(sf::Color(50, 50, 50));  // Border dark gray
        boardFrame.setOutlineColor(sf::Color::White);
        boardFrame.setOutlineThickness(2);
        window.draw(boardFrame);

        // Draw board with labels
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                sf::RectangleShape tile(sf::Vector2f(TILE_SIZE, TILE_SIZE));
                tile.setPosition(LABEL_MARGIN + col * TILE_SIZE, TITLE_HEIGHT + row * TILE_SIZE);
                tile.setFillColor((row + col) % 2 == 0 ? lightSquare : darkSquare);
                window.draw(tile);
            }
        }
        
        // Draw labels
        for (int i = 0; i < BOARD_SIZE; ++i) {
            // Column label (a–h) below
            sf::Text colLabel;
            colLabel.setFont(font);
            colLabel.setCharacterSize(24);
            colLabel.setFillColor(sf::Color::White);
            colLabel.setStyle(sf::Text::Bold);
            colLabel.setString(static_cast<char>('a' + i));
            colLabel.setPosition(LABEL_MARGIN + i * TILE_SIZE + TILE_SIZE / 2 - 8, TITLE_HEIGHT + TILE_SIZE * BOARD_SIZE + 5);
            window.draw(colLabel);
        
            // Row label (8–1) on left
            sf::Text rowLabel;
            rowLabel.setFont(font);
            rowLabel.setCharacterSize(24);
            rowLabel.setFillColor(sf::Color::White);
            rowLabel.setStyle(sf::Text::Bold);
            rowLabel.setString(std::to_string(8 - i));
            rowLabel.setPosition(10, TITLE_HEIGHT + i * TILE_SIZE + TILE_SIZE / 2 - 15);
            window.draw(rowLabel);
        }
        
        // Draw pieces
        for (const auto& entry : board ) {
            auto [row, col] = getBoardCoords(entry.first);
            std::string pieceName = entry.second;
            sf::Sprite& sprite = pieceSprites[pieceName];
            //sprite.setPosition(LABEL_MARGIN + col * TILE_SIZE, TITLE_HEIGHT + row * TILE_SIZE);
            sprite.setPosition(LABEL_MARGIN + col * TILE_SIZE + TILE_SIZE / 2.f,TITLE_HEIGHT + row * TILE_SIZE + TILE_SIZE / 2.f);

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
