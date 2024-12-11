#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

// Dice class to handle the dice roll
class Dice {
public:
    Dice(int frameDelayMs = 50) : frameDelay(frameDelayMs), frameIndex(0), isRolling(false), score(0) {}

    // Load the frames for the rolling animation
    void loadFrames(const std::string& baseFilename, int start, int end) {
        frames.clear();
        for (int i = start; i <= end; ++i) {
            sf::Texture texture;
            std::string prefix = (i < 10) ? "00" : "0"; // Properly format filenames like 001.png, 002.png
            std::string filename = "images/" + prefix + std::to_string(i) + ".png";

            if (!texture.loadFromFile(filename)) {
                std::cerr << "Error loading " << filename << std::endl;
                continue;
            }
            frames.push_back(texture);
        }
    }

    // Start the dice roll animation
    void roll() {
        isRolling = true;
        frameIndex = 0;
        clock.restart();
    }

    // Update the dice animation
    void update(sf::Sprite& sprite) {
        if (!isRolling) return;

        if (clock.getElapsedTime().asMilliseconds() > frameDelay) {
            frameIndex++;
            if (frameIndex < frames.size()) {
                sprite.setTexture(frames[frameIndex]);
                sprite.setScale(0.5f, 0.5f); // Scaling the dice during the animation
                clock.restart();
            }
            else {
                // Generate a random dice face (1 to 6)
                std::mt19937 rng(static_cast<unsigned>(std::chrono::system_clock::now().time_since_epoch().count()));
                std::uniform_int_distribution<int> dist(1, 6);
                int finalDiceFace = dist(rng);
                std::string finalFilename = "images/" + std::to_string(finalDiceFace) + ".png";

                if (!texture.loadFromFile(finalFilename)) {
                    std::cerr << "Error loading final dice texture: " << finalFilename << std::endl;
                    return;
                }

                sprite.setTexture(texture);
                sprite.setScale(0.5f, 0.5f); // Scaling the final dice result

                score += finalDiceFace; // Add the value of the dice face to the score
                isRolling = false;
            }
        }
    }

    bool isDiceRolling() const { return isRolling; }

    int getScore() const { return score; } // Getter for the score

private:
    std::vector<sf::Texture> frames;  // Store frames for animation
    sf::Texture texture;              // Texture for the final dice face
    int frameIndex;                   // Current frame index
    int frameDelay;                   // Delay between frames
    bool isRolling;                   // Is the dice animation playing?
    sf::Clock clock;                  // Clock to track frame timing
    int score;                        // Score that increments based on dice face value
};

// Player class to represent a player in the game
class Player {
public:
    // Constructor to initialize player with name and initial score
    Player(const std::string& playerName, const sf::Font& playerFont)
        : name(playerName), score(0) {
        label.setFont(playerFont); // Initialize the label font
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::White);
        label.setString(name + ": " + std::to_string(score));
    }

    // Set position of the player's label on the screen
    void setLabelPosition(float x, float y) {
        label.setPosition(x, y);
    }

    // Draw the player's label on the window
    void drawLabel(sf::RenderWindow& window) const {
        window.draw(label);
    }

    // Add a Dice object to the player's dice set
    void addDice(Dice dice) {
        dice_set.push_back(dice);
    }

    // Roll all dice in the player's dice set
    void rollDice() {
        for (auto& dice : dice_set) {
            dice.roll();  // Start rolling each dice
        }
    }

    // Get the current score of the player
    int getScore() const {
        return score;
    }

    // Update the score by adding the given points
    void updateScore(int points) {
        score += points;
        label.setString(name + ": " + std::to_string(score)); // Update the label
    }

    // Get the player's name
    std::string getName() const {
        return name;
    }

    // Display the player's stats for debugging purposes
    void displayStats() const {
        std::cout << "Player: " << name << ", Score: " << score << std::endl;
    }

private:
    std::string name;           // Player's name
    int score;                  // Player's score
    std::vector<Dice> dice_set; // Player's set of dice
    sf::Text label;             // Text object for displaying player info
};

// Grid class to represent the game grid
class Grid {
public:
    // Constructor to initialize the grid with rows, columns, and cell sizes
    Grid(int rows, int cols, float cellSize, float cellSpacing, float startX, float startY);

    // Draw the grid on the window
    void draw(sf::RenderWindow& window);

    // Place a dice in a specific grid cell
    bool place_dice(int row, int col, int value);

    // Get the value in a specific cell
    int get_cell_value(int row, int col) const;

    // Get the graphical representation of a cell
    sf::RectangleShape get_cell(int row, int col) const;

    // Get the dice sprite for a specific cell
    sf::Sprite get_dice_sprite(int row, int col) const;

    // Access the dice animations in the grid
    Dice& get_dice_animation(int row, int col);

private:
    int rows, cols;                          // Grid dimensions
    float cellSize, cellSpacing;             // Size and spacing of cells
    std::vector<sf::RectangleShape> cells;    // Cell shapes
    std::vector<std::vector<int>> gridValues; // Values stored in the grid
    std::vector<std::vector<sf::Sprite>> diceSprites; // Dice sprites
    std::vector<std::vector<Dice>> diceAnimations;    // Dice animations
    float startX, startY;                    // Starting position for the grid
};

// Grid constructor implementation
Grid::Grid(int rows, int cols, float cellSize, float cellSpacing, float startX, float startY)
    : rows(rows), cols(cols), cellSize(cellSize), cellSpacing(cellSpacing), startX(startX), startY(startY) {

    // Initialize the grid values
    gridValues.resize(rows, std::vector<int>(cols, 0)); // 0 means no dice placed

    // Initialize dice sprites and animations
    diceSprites.resize(rows, std::vector<sf::Sprite>(cols));
    diceAnimations.resize(rows, std::vector<Dice>(cols, Dice(cellSize)));

    // Initialize grid cells
    cells.reserve(rows * cols);
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            // Set up the cell shape
            sf::RectangleShape cell(sf::Vector2f(cellSize, cellSize));
            cell.setFillColor(sf::Color::White);
            cell.setOutlineColor(sf::Color::Black);
            cell.setOutlineThickness(2.f);

            // Position the cell
            float x = startX + col * (cellSize + cellSpacing);
            float y = startY + row * (cellSize + cellSpacing);
            cell.setPosition(x, y);
            cells.push_back(cell);

            // Initialize dice sprite position
            diceSprites[row][col].setPosition(x, y);

            // Initialize dice animation frames (optional)
            diceAnimations[row][col].loadFrames("images", 1, 24); // Example frames setup
        }
    }
}

// Draw grid cells on the window
void Grid::draw(sf::RenderWindow& window) {
    for (auto& cell : cells) {
        window.draw(cell);
    }
    // Optionally, draw dice sprites
    for (int row = 0; row < rows; ++row) {
        for (int col = 0; col < cols; ++col) {
            window.draw(diceSprites[row][col]);
        }
    }
}

// Place a dice in a specific cell and update grid value
bool Grid::place_dice(int row, int col, int value) {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false; // Invalid cell
    }
    gridValues[row][col] = value;
    return true;
}

// Get the value in a specific cell
int Grid::get_cell_value(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return -1; // Invalid cell
    }
    return gridValues[row][col];
}

// Get the graphical representation of a specific cell
sf::RectangleShape Grid::get_cell(int row, int col) const {
    return cells[row * cols + col];
}

// Get the dice sprite for a specific cell
sf::Sprite Grid::get_dice_sprite(int row, int col) const {
    return diceSprites[row][col];
}

// Access the dice animation object for a specific cell
Dice& Grid::get_dice_animation(int row, int col) {
    return diceAnimations[row][col];
}

// Main function to run the game
int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "Dice Rolling Game");

    // Load font for player labels
    sf::Font font;
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Error loading font" << std::endl;
        return -1;
    }

    // Create two players
    Player player1("Player 1", font);
    player1.setLabelPosition(10, 10);
    Player player2("Player 2", font);
    player2.setLabelPosition(10, 40);

    // Create a grid
    Grid grid(5, 5, 60.f, 10.f, 200.f, 100.f); // 5x5 grid, starting at (200, 100)

    // Add dice to players
    Dice dice1;
    player1.addDice(dice1);
    Dice dice2;
    player2.addDice(dice2);

    // Game loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Update dice animations for both players
        for (int row = 0; row < 5; ++row) {
            for (int col = 0; col < 5; ++col) {
                Dice& diceAnimation = grid.get_dice_animation(row, col);
            }
        }

        // Clear screen
        window.clear();

        // Draw grid and players
        grid.draw(window);
        player1.drawLabel(window);
        player2.drawLabel(window);

        // Display everything
        window.display();
    }

    return 0;
}
