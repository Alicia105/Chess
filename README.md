# Chess AI Game ♟️🤖

## **Description**  
A C++ implementation of a chess game with an AI opponent. This project allows users to play chess against a computer using the minimax algorithm with alpha-beta pruning for an optimal AI player.The player has the choice between a human or AI opponent.

## **Table of Contents**  
- [Features](#features)  
- [Requirements](#requirements)  
- [Installation](#installation)
- [How to run](#How-to-run)
- [How to use](#How-to-use)

## **Features ✨**  
- Possibility to **play against AI 🤖 or human opponent**.  
- **Choice between Graphic User Interface (GUI) or Command Line Interface (CLI) game**.  
- **Move generation for all pieces** (King 👑, Queen 👸, Rook 🏰, Knight 🏇, Bishop ♗, Pawn ♙).
- Basic **AI using the Minimax algorithm with alpha-beta pruning 🧠**.
- **Castling, en passant, and pawn promotion support 🔄**.
- **Stalemate, Check and Checkmate detection 🏁**.

## **Requirements ⚙️**  
- **C++ 11 or higher**
- **SFML 2.6.2** 
- **A C++ compiler (GCC, Clang, etc.)** 


## **Installation 🛠️**  
- Clone or download the repository
<pre> git clone https://github.com/Alicia105/Chess.git</pre>
- Navigate to the project directory
<pre> cd Chess </pre>

## 🚀**How to run** 
1. Navigate to the project directory
<pre> cd Chess </pre>

2. Create a build directory
<pre> mkdir build
 cd build </pre>

3. Run the CMake
<pre> cmake ..</pre>

4. Build the project with make
<pre> make </pre>

5. Run the executable file
<pre> ./Chess.exe </pre>


## **How to use** 
1. The app is pretty straightforward to use. The GUI window opens and ask you to choose your opponent.

![Chessboard GUI Oppnent Choice](images/OpponentMenu.jpg)

2. Once the opponent is chosen you can play by clicking on the piece you want to move and the end square destination. The white piece always start. When the AI opponent is chosen it's always playing with the black pieces. The selected square is highlighted in green.

![Chessboard GUI Window](images/ChessboardGUI.jpg)

3. Once you close the window you'll be asked if you want to play using CLI.

4. If you choose yes you'll see the following message. You just have to follow along the indications on the terminal to play  
![Main menu](images/homeMenu.jpg)