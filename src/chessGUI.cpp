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

bool askOpponentType() {
    const int WIDTH = 600, HEIGHT = 400;
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Choose Opponent");

    sf::Font font;
    if (!font.loadFromFile("../resources/Font/Raleway-Light.ttf")) {
        cerr << "Failed to load font!" << endl;
        return false;
    }

    sf::Text title("Choose Your Opponent", font, 36);
    title.setPosition(100, 40);
    title.setFillColor(sf::Color::White);

    sf::RectangleShape humanBtn(sf::Vector2f(200, 60));
    humanBtn.setPosition(100, 150);
    humanBtn.setFillColor(sf::Color(100, 200, 100));

    sf::Text humanText("Play vs Human", font, 24);
    humanText.setPosition(120, 165);
    humanText.setFillColor(sf::Color::Black);

    sf::RectangleShape aiBtn(sf::Vector2f(200, 60));
    aiBtn.setPosition(100, 250);
    aiBtn.setFillColor(sf::Color(200, 100, 100));

    sf::Text aiText("Play vs AI", font, 24);
    aiText.setPosition(140, 265);
    aiText.setFillColor(sf::Color::Black);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed) {
                auto mouseX = event.mouseButton.x;
                auto mouseY = event.mouseButton.y;

                if (humanBtn.getGlobalBounds().contains(mouseX, mouseY)) {
                    window.close();
                    return false; // play vs human
                }
                if (aiBtn.getGlobalBounds().contains(mouseX, mouseY)) {
                    window.close();
                    return true; // play vs AI
                }
            }
        }

        window.clear(sf::Color(30, 30, 30));
        window.draw(title);
        window.draw(humanBtn);
        window.draw(humanText);
        window.draw(aiBtn);
        window.draw(aiText);
        window.display();
    }

    return false; // default
}

char promptPromotion(sf::RenderWindow& window, const map<string, sf::Sprite>& pieceSprites, const string& color) {
    sf::RectangleShape background(sf::Vector2f(WINDOW_WIDTH, WINDOW_HEIGHT));
    background.setFillColor(sf::Color(0, 0, 0, 150));  // semi-transparent dark overlay

    sf::Font font;
    font.loadFromFile("../resources/Font/Raleway-Light.ttf");

    sf::Text message("Choose a piece to promote to:", font, 28);
    message.setFillColor(sf::Color::White);
    message.setPosition(WINDOW_WIDTH / 2 - message.getLocalBounds().width / 2, 100);

    // Promotion options
    vector<char> pieces = {'q', 'r', 'b', 'n'};
    vector<sf::Sprite> options;

    float startX = WINDOW_WIDTH / 2 - (pieces.size() * TILE_SIZE) / 2;
    float y = 180;

    for (int i = 0; i < pieces.size(); ++i) {
        string name = color + pieces[i];
        sf::Sprite option = pieceSprites.at(name);
        option.setPosition(startX + i * TILE_SIZE + TILE_SIZE / 2, y + TILE_SIZE / 2);
        options.push_back(option);
    }

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return 'q'; // default
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                int x = event.mouseButton.x;
                int yClick = event.mouseButton.y;

                for (int i = 0; i < pieces.size(); ++i) {
                    sf::FloatRect bounds = options[i].getGlobalBounds();
                    if (bounds.contains(x, yClick)) {
                        return pieces[i]; // Return choice
                    }
                }
            }
        }

        window.clear();
        window.draw(background);
        window.draw(message);
        for (auto& s : options) window.draw(s);
        window.display();
    }

    return 'q'; // fallback
}

int displayChessBoard(Board& b, Player& p1, Player& p2, bool playAI){
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
        
    auto getBoardCoords = [](Board b,string pos) {
        vector<int> coords = b.generateCaseCoordinates(pos);
        return make_pair(coords[0],coords[1]);
    };

    
    string selectedSquare = "";
    bool isSelecting = false;
    string currentTurn = "white";  // white starts
    bool justPlayed=false;

    sf::Text title("Chess AI", font, 32);
    title.setFillColor(sf::Color::White);
    title.setPosition(WINDOW_SIZE / 2 - title.getLocalBounds().width / 2, 10);
        

    while (window.isOpen()) {
        board=stateBoard(b);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed){
                window.close();
                return 1; 
            } 

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (event.mouseButton.x >= LABEL_MARGIN && 
                    event.mouseButton.x < LABEL_MARGIN + TILE_SIZE * BOARD_SIZE &&
                    event.mouseButton.y >= TITLE_HEIGHT &&
                    event.mouseButton.y < TITLE_HEIGHT + TILE_SIZE * BOARD_SIZE){

                    int col = (event.mouseButton.x - LABEL_MARGIN) / TILE_SIZE;
                    int row = (event.mouseButton.y - TITLE_HEIGHT) / TILE_SIZE;
                
                    // process clicked square
                    string clickedSquare = b.generateNameCase({row, col});

                    if (!isSelecting) {
                        // First click: select
                        if (b.getPiecesPositions().count(clickedSquare) &&
                            b.getPiecesPositions().at(clickedSquare).getColorPiece() == currentTurn) {
                            selectedSquare = clickedSquare;
                            cout << "Clicked square: " << clickedSquare << " (" << row << "," << col << ")" << endl;
                            isSelecting = true;
                        }
                    } 
                    else {
                        // Second click: try move
                        string moveTo = clickedSquare;
                        cout << "Clicked square: " << clickedSquare << " (" << row << "," << col << ")" << endl;

                        isSelecting = false;
                        int r;
                        
                        if(currentTurn == "white"){
                            r=b.movePieceGUI(p1,p2,selectedSquare,moveTo);
                            if (r == 2) {
                                char choice = promptPromotion(window, pieceSprites, "w");
                                b.promotePawnGUI(p1, moveTo, choice);
                                board = stateBoard(b);
                            }
                        }

                        if(currentTurn == "black" && playAI==false){
                            r=b.movePieceGUI(p2,p1,selectedSquare,moveTo);
                            if (r == 2) {
                                char choice = promptPromotion(window, pieceSprites, "b");
                                b.promotePawnGUI(p2, moveTo, choice);
                                board = stateBoard(b);
                            }
                        }
                    
                        if(r!=0){
                            selectedSquare = "";
                            continue;
                        }

                        else{
                            // Move succeeded
                            board=stateBoard(b);
                            currentTurn = (currentTurn == "white") ? "black" : "white";
                            justPlayed=true;
                        }

                        selectedSquare = "";
                    }
                               
                }
            }
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
        
        // Highlight selected tile
    
        if (isSelecting && !selectedSquare.empty() && b.getPiecesPositions().count(selectedSquare)) {
            auto [row, col] = getBoardCoords(b, selectedSquare);
            sf::RectangleShape highlight(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            highlight.setPosition(LABEL_MARGIN + col * TILE_SIZE, TITLE_HEIGHT + row * TILE_SIZE);
            highlight.setFillColor(sf::Color(0, 255, 0, 100));  // semi-transparent green
            window.draw(highlight);
        }

        // Draw pieces
        for (const auto& entry : board ) {
            auto [row, col] = getBoardCoords(b,entry.first);
            std::string pieceName = entry.second;
            sf::Sprite& sprite = pieceSprites[pieceName];
            //sprite.setPosition(LABEL_MARGIN + col * TILE_SIZE, TITLE_HEIGHT + row * TILE_SIZE);
            sprite.setPosition(LABEL_MARGIN + col * TILE_SIZE + TILE_SIZE / 2.f,TITLE_HEIGHT + row * TILE_SIZE + TILE_SIZE / 2.f);

            window.draw(sprite);
        }
        
        window.display();

        // Handle AI move if needed
        if (playAI && currentTurn == "black" && justPlayed) {
           
            //std::this_thread::sleep_for(std::chrono::milliseconds(500)); // delay to simulate thinking
            int t=b.makeAMoveAI(p2,p1);
            if(t==1){
                cout<<"[ERROR]: AI internal error"<<endl;
                return 1;
            }
            board=stateBoard(b);
            p2.playedAMove();
            currentTurn = "white";
            justPlayed=false;
        }
    }

    return 0;

}

int main() {

    bool playAI = askOpponentType();  // Player chooses here

    /*Board b;
    b.initiateBoard();
    Player p1("white");
    Player p2("black");

    p1.initiatePlayer(b.getPiecesPositions());
    p2.initiatePlayer(b.getPiecesPositions());

    int a=displayChessBoard(b,p1,p2,playAI);*/

    Board b;
    b.initiateBoard();
    //cout<<"row :"<<b.getBoard().size()<<endl;
    //cout<<"column : "<<b.getBoard()[0].size()<<endl;
    
    Player p1("white");
    Player p2("black");

    p1.initiatePlayer(b.getPiecesPositions());
    p2.initiatePlayer(b.getPiecesPositions());
    
    int t=0;
    //b.printBoard();

    b.getPiecesPositions().erase("b8");
    p1.getPlayerPiecesPositions().erase("b8");
    
    //Piece captured;

    cout<<"name :"<<b.getPiecesPositions().at("b2").getNamePiece()<<endl;
    cout<<"name p1:"<<p1.getPlayerPiecesPositions().at("b2").getNamePiece()<<endl;

    // Perform a move
    Piece& p=b.getPiecesPositions()["b2"];  
    b.getPiecesPositions().erase("b8");
    b.getPiecesPositions().erase("b7");
    b.getPiecesPositions().erase("b2"); 

    //b.printBoard();

    b.getPiecesPositions()["b7"]=p;
    p1.getPlayerPiecesPositions()["b7"]=p;
    p.setCasePiece("b7");
    p.setCaseCoordinate({1, 1});

    b.getPiecesPositions()["b7"] = p;
    p1.getPlayerPiecesPositions()["b7"] = p;


    //b.printBoard();

    //cout<<"promotion ? :"<<b.getPiecesPositions().at("b8").canBePromoted()<<endl;
    //b.promotePawnGUI(p1,"b8",'q');

    int a=displayChessBoard(b,p1,p2,playAI);
    cout<<"new name :"<<b.getPiecesPositions().at("b8").getNamePiece()<<endl;
    cout<<"new name p1:"<<p1.getPlayerPiecesPositions().at("b8").getNamePiece()<<endl;

    cout<<"a :"<<a<<endl;
   
}
