#include <iostream>
#include <SFML/Graphics.hpp>

#define WIDTH 512
#define HEIGHT 512
#define TILE 64  

int board[8][8] = {
    {2, 3, 4, 5, 6, 4, 3, 2 }, 
    {1, 1, 1, 1, 1, 1, 1, 1 }, 
    {0, 0, 0, 0, 0, 0, 0, 0 }, 
    {0, 0, 0, 0, 0, 0, 0, 0 }, 
    {0, 0, 0, 0, 0, 0, 0, 0 }, 
    {0, 0, 0, 0, 0, 0, 0, 0 }, 
    {-1,-1,-1,-1,-1,-1,-1,-1}, 
    {-2,-3,-4,-5,-6,-4,-3,-2} 
};

void isMoveLegal() {

}
void drawBoard(sf::RenderWindow& window) {
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            sf::RectangleShape tileShape(sf::Vector2f(TILE, TILE));
            tileShape.setPosition(col * TILE, row * TILE);

            if ((row + col) % 2 == 0)
                tileShape.setFillColor(sf::Color(238, 238, 210));  // Light square color
            else
                tileShape.setFillColor(sf::Color(118, 150, 86));   // Dark square color

            window.draw(tileShape);

            if (board[row][col] != 0) {
                sf::CircleShape pieceShape(TILE / 2 - 4);
                pieceShape.setPosition(col * TILE + 4, row * TILE + 4);
                if (board[row][col] > 0)  // White pawn
                    pieceShape.setFillColor(sf::Color::White);
                else  // Black pawn (-1)
                    pieceShape.setFillColor(sf::Color::Black);
                window.draw(pieceShape);
            }
        }
    }
}

sf::Vector2i getTileUnderMouse(sf::RenderWindow& window) {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    return {mousePos.x / TILE, mousePos.y / TILE};  // Convert mouse position to board tile
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "Chess Game in SFML");
    sf::Vector2i selectedTile(-1, -1);  
    sf::Sprite peices();

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                sf::Vector2i clickedTile = getTileUnderMouse(window);

                if (selectedTile.x == -1 && selectedTile.y == -1) {
                    if (board[clickedTile.y][clickedTile.x] != 0) {
                        selectedTile = clickedTile;
                    }
                } else {
                    board[clickedTile.y][clickedTile.x] = board[selectedTile.y][selectedTile.x];
                    board[selectedTile.y][selectedTile.x] = 0;  // Remove piece from the original spot
                    selectedTile = {-1, -1};  // Deselect the tile
                }
            }
        }

        window.clear();
        drawBoard(window); 
        window.display();
    }

    return 0;
}
