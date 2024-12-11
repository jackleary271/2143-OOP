/*****************************************************************************
*
*  Author:           Jack Leary
*  Email:            jackleary645@gmail.com
*  Label:            KnuckleBones SFML
*  Course:           2143 OOP
*  Semester:         Fall 2024
*
*  Description:
*        This program simulates a dice-rolling game with animation. Players can
*        roll a dice to generate a random face (1 to 6), and the face value is
*        added to their score. The program uses SFML for graphics and animation.
*
*  Usage:
*        - Compile and run the program.
*        - Follow on-screen instructions to interact with the dice-rolling
*          animation and track player scores.
*
*  Files:
*        main.cpp         : Driver program
*        images/          : Directory containing dice images for animation
*****************************************************************************/

// Includes SFML graphics library and standard utilities
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <random>
#include <chrono>

// Dice class to handle the dice roll
/**
 * Dice
 *
 * Description:
 *      Handles the dice rolling animation and score management.
 *      Loads textures for animation, manages animation frames, and calculates
 *      the final dice face and score.
 *
 * Public Methods:
 *      - Dice(int frameDelayMs = 50)
 *      - void loadFrames(const std::string& baseFilename, int start, int end)
 *      - void roll()
 *      - void update(sf::Sprite& sprite)
 *      - bool isDiceRolling() const
 *      - int getScore() const
 *
 * Private Methods:
 *      - N/A
 *
 * Usage:
 *      Dice dice;                               // Create a Dice object
 *      dice.loadFrames("images/", 1, 6);        // Load dice images for animation
 *      dice.roll();                             // Start the dice animation
 *      dice.update(sprite);                     // Update the dice animation
 *      int totalScore = dice.getScore();        // Get the total score
 */
class Dice {
public:
    /**
     * Constructor: Dice
     *
     * Description:
     *      Initializes the Dice object with a specified frame delay and other
     *      required parameters.
     *
     * Params:
     *      int frameDelayMs - Delay between animation frames in milliseconds
     */
    Dice(int frameDelayMs = 50) : frameDelay(frameDelayMs), frameIndex(0), isRolling(false), score(0) {}

    /**
     * Public : loadFrames
     *
     * Description:
     *      Loads image frames for the dice rolling animation.
     *
     * Params:
     *      const std::string& baseFilename - Base directory for image files
     *      int start                       - Starting image index
     *      int end                         - Ending image index
     *
     * Returns:
     *      void
     */
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

    /**
     * Public : roll
     *
     * Description:
     *      Starts the dice rolling animation.
     *
     * Params:
     *      None
     *
     * Returns:
     *      void
     */
    void roll() {
        isRolling = true;
        frameIndex = 0;
        clock.restart();
    }

    /**
     * Public : update
     *
     * Description:
     *      Updates the dice animation and sets the final dice face when
     *      animation ends.
     *
     * Params:
     *      sf::Sprite& sprite - Sprite object to display the dice texture
     *
     * Returns:
     *      void
     */
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

    /**
     * Public : isDiceRolling
     *
     * Description:
     *      Checks if the dice animation is still rolling.
     *
     * Params:
     *      None
     *
     * Returns:
     *      bool - True if rolling, false otherwise
     */
    bool isDiceRolling() const { return isRolling; }

    /**
     * Public : getScore
     *
     * Description:
     *      Returns the total score from the dice rolls.
     *
     * Params:
     *      None
     *
     * Returns:
     *      int - The current score
     */
    int getScore() const { return score; }

private:
    std::vector<sf::Texture> frames;  // Store frames for animation
    sf::Texture texture;              // Texture for the final dice face
    int frameIndex;                   // Current frame index
    int frameDelay;                   // Delay between frames
    bool isRolling;                   // Is the dice animation playing?
    sf::Clock clock;                  // Clock to track frame timing
    int score;                        // Score that increments based on dice face value
};

/**
 * Player
 *
 * Description:
 *      This class represents a player in the game, managing the player's name, score, and dice. It provides functionality to update and display the player's score, roll dice, and display their information.
 *
 * Public Methods:
 *      - Player(const std::string& playerName, const sf::Font& playerFont) - Constructor to initialize the player's name and score.
 *      - void setLabelPosition(float x, float y) - Sets the position of the player's label on the screen.
 *      - void drawLabel(sf::RenderWindow& window) const - Draws the player's label on the window.
 *      - void addDice(Dice dice) - Adds a dice to the player's dice set.
 *      - void rollDice() - Rolls all dice in the player's dice set.
 *      - int getScore() const - Returns the player's current score.
 *      - void updateScore(int points) - Updates the player's score.
 *      - std::string getName() const - Returns the player's name.
 *      - void displayStats() const - Displays the player's name and score for debugging purposes.
 *
 * Private Methods:
 *      - None.
 *
 * Usage:
 *      - Player player("Player 1", font);
 *      - player.setLabelPosition(150.f, 450.f);
 *      - player.addDice(dice);
 *      - player.rollDice();
 */
class Player {
public:
    /**
     * Public : Player
     *
     * Description:
     *      Constructor to initialize player with a name and initial score, 
     *      also initializes the label for displaying the player's name and score.
     *
     * Params:
     *      - playerName: const std::string& 
     *          - The name of the player.
     *      - playerFont: const sf::Font&
     *          - The font used to display the player's label.
     *
     * Returns:
     *      - None
     */
    Player(const std::string& playerName, const sf::Font& playerFont)
        : name(playerName), score(0) {
        label.setFont(playerFont); // Initialize the label font
        label.setCharacterSize(20);
        label.setFillColor(sf::Color::White);
        label.setString(name + ": " + std::to_string(score));
    }

    /**
     * Public : setLabelPosition
     *
     * Description:
     *      Sets the position of the player's label on the screen.
     *
     * Params:
     *      - x: float
     *          - The x-coordinate for the label's position.
     *      - y: float
     *          - The y-coordinate for the label's position.
     *
     * Returns:
     *      - None
     */
    void setLabelPosition(float x, float y) {
        label.setPosition(x, y);
    }

    /**
     * Public : drawLabel
     *
     * Description:
     *      Draws the player's label (name and score) onto the window.
     *
     * Params:
     *      - window: sf::RenderWindow&
     *          - The window where the player's label will be drawn.
     *
     * Returns:
     *      - None
     */
    void drawLabel(sf::RenderWindow& window) const {
        window.draw(label);
    }

    /**
     * Public : addDice
     *
     * Description:
     *      Adds a Dice object to the player's set of dice.
     *
     * Params:
     *      - dice: Dice
     *          - The Dice object to be added to the player's dice set.
     *
     * Returns:
     *      - None
     */ 
    void addDice(Dice dice) {
        dice_set.push_back(dice);
    }

    /**
     * Public : rollDice
     *
     * Description:
     *      Rolls all dice in the player's dice set, triggering the roll on each one.
     *
     * Params:
     *      - None
     *
     * Returns:
     *      - None
     */
    void rollDice() {
        for (auto& dice : dice_set) {
            dice.roll();  // Start rolling each dice
        }
    }

    /**
     * Public : getScore
     *
     * Description:
     *      Returns the current score of the player.
     *
     * Params:
     *      - None
     *
     * Returns:
     *      - int
     *          - The player's current score.
     */
    int getScore() const {
        return score;
    }

    /**
     * Public : updateScore
     *
     * Description:
     *      Updates the player's score by adding the given points and updates the label accordingly.
     *
     * Params:
     *      - points: int
     *          - The number of points to be added to the player's score.
     *
     * Returns:
     *      - None
     */
    void updateScore(int points) {
        score += points;
        label.setString(name + ": " + std::to_string(score)); // Update the label
    }

    /**
     * Public : getName
     *
     * Description:
     *      Returns the player's name.
     *
     * Params:
     *      - None
     *
     * Returns:
     *      - std::string
     *          - The player's name.
     */
    std::string getName() const {
        return name;
    }

    /**
     * Public : displayStats
     *
     * Description:
     *      Displays the player's name and score to the console for debugging purposes.
     *
     * Params:
     *      - None
     *
     * Returns:
     *      - None
     */
    void displayStats() const {
        std::cout << "Player: " << name << ", Score: " << score << std::endl;
    }

private:
    std::string name;               // Player's name
    int score;                      // Player's score
    std::vector<Dice> dice_set;     // Player's set of dice
    sf::Text label;                 // Text object for displaying player info
};

/**
 * Grid
 *
 * Description:
 *      This class represents the game grid, which consists of cells where dice can be placed. It provides functionality to draw the grid, manage dice placements, and animate dice within the grid cells.
 *
 * Public Methods:
 *      - Grid(int rows, int cols, float cellSize, float cellSpacing, float startX, float startY) - Constructor to initialize the grid with the specified number of rows, columns, and cell sizes.
 *      - void draw(sf::RenderWindow& window) - Draws the grid on the window.
 *      - bool place_dice(int row, int col, int value) - Places a dice in a specific grid cell.
 *      - int get_cell_value(int row, int col) const - Returns the value in a specific grid cell.
 *      - sf::RectangleShape get_cell(int row, int col) const - Returns the graphical representation of a grid cell.
 *      - sf::Sprite get_dice_sprite(int row, int col) const - Returns the sprite of the dice placed in a specific cell.
 *      - Dice& get_dice_animation(int row, int col) - Returns the dice animation object for a specific grid cell.
 *
 * Private Methods:
 *      - None.
 *
 * Usage:
 *      - Grid grid(rows, cols, cellSize, cellSpacing, startX, startY);
 *      - grid.draw(window);
 *      - grid.place_dice(row, col, value);
 *      - grid.get_cell_value(row, col);
 */

class Grid {
public:
    /**
     * Public : Grid
     *
     * Description:
     *      Constructor to initialize the grid with rows, columns, and cell sizes
     *
     * Params:
     *      - int rows: The number of rows in the grid
     *      - int cols: The number of columns in the grid
     *      - float cellSize: The size of each cell in the grid
     *      - float cellSpacing: The space between each cell in the grid
     *      - float startX: The starting X coordinate for the grid
     *      - float startY: The starting Y coordinate for the grid
     *
     * Returns:
     *      - None
     */
    Grid(int rows, int cols, float cellSize, float cellSpacing, float startX, float startY);

    /**
     * Public : draw
     *
     * Description:
     *      Draw the grid on the window
     *
     * Params:
     *      - sf::RenderWindow& window: The window to draw the grid on
     *
     * Returns:
     *      - None
     */
    void draw(sf::RenderWindow& window);

    /**
     * Public : place_dice
     *
     * Description:
     *      Place a dice in a specific grid cell
     *
     * Params:
     *      - int row: The row of the cell where the dice should be placed
     *      - int col: The column of the cell where the dice should be placed
     *      - int value: The value of the dice to place in the cell
     *
     * Returns:
     *      - bool: True if the dice was placed successfully, false otherwise
     */
    bool place_dice(int row, int col, int value);

    /**
     * Public : get_cell_value
     *
     * Description:
     *      Get the value stored in a specific grid cell
     *
     * Params:
     *      - int row: The row of the cell to retrieve the value from
     *      - int col: The column of the cell to retrieve the value from
     *
     * Returns:
     *      - int: The value stored in the cell, or -1 if the position is invalid
     */
    int get_cell_value(int row, int col) const;

    /**
     * Public : get_cell
     *
     * Description:
     *      Get the graphical representation of a grid cell
     *
     * Params:
     *      - int row: The row of the cell to retrieve the graphical representation from
     *      - int col: The column of the cell to retrieve the graphical representation from
     *
     * Returns:
     *      - sf::RectangleShape: The graphical representation of the specified cell
     */
    sf::RectangleShape get_cell(int row, int col) const;

    /**
     * Public : get_dice_sprite
     *
     * Description:
     *      Get the dice sprite for a specific cell
     *
     * Params:
     *      - int row: The row of the cell to retrieve the dice sprite from
     *      - int col: The column of the cell to retrieve the dice sprite from
     *
     * Returns:
     *      - sf::Sprite: The dice sprite for the specified cell
     */
    sf::Sprite get_dice_sprite(int row, int col) const;

    /**
     * Public : get_dice_animation
     *
     * Description:
     *      Access the dice animations in the grid
     *
     * Params:
     *      - int row: The row of the cell to retrieve the dice animation from
     *      - int col: The column of the cell to retrieve the dice animation from
     *
     * Returns:
     *      - Dice&: A reference to the dice animation object for the specified cell
     */
    Dice& get_dice_animation(int row, int col);

private:
    int rows, cols;                                       // Grid dimensions
    float cellSize, cellSpacing;                          // Size and spacing of cells
    std::vector<sf::RectangleShape> cells;                // Cell shapes
    std::vector<std::vector<int>> gridValues;             // Values stored in the grid
    std::vector<std::vector<sf::Sprite>> diceSprites;     // Dice sprites
    std::vector<std::vector<Dice>> diceAnimations;        // Dice animations
    float startX, startY;                                 // Starting position for the grid
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
    // Optionally, draw dice sprites here
}

// Accessor for dice sprite
sf::Sprite Grid::get_dice_sprite(int row, int col) const {
    return diceSprites[row][col];
}

// Accessor for dice animation
Dice& Grid::get_dice_animation(int row, int col) {
    return diceAnimations[row][col];
}

// Place a dice in a specific grid cell
bool Grid::place_dice(int row, int col, int value) {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        gridValues[row][col] = value;
        return true;
    }
    return false;
}

// Get the value stored in a specific grid cell
int Grid::get_cell_value(int row, int col) const {
    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        return gridValues[row][col];
    }
    return -1;  // Invalid position
}

// Get the graphical representation of a grid cell
sf::RectangleShape Grid::get_cell(int row, int col) const {
    int index = row * cols + col;
    return cells[index];
}

/**
 * Public: Game
 *
 * Description:
 *      Initializes and runs the game window where two players roll dice on two separate grids.
 *      Handles user input, dice animation, and the rendering of game elements including grids and player labels.
 *
 * Params:
 *      - window: sf::RenderWindow&
 *          - The window to render the game onto.
 *
 * Returns:
 *      - void: This function does not return any value.
 */
void Game(sf::RenderWindow& window) {
    Dice diceAnimation(50);
    diceAnimation.loadFrames("images", 1, 24);

    const int rows = 3;
    const int cols = 3;
    const float cellSize = 100.f;
    const float cellSpacing = 10.f;
    const float gridStartX1 = 100.f;
    const float gridStartY = 100.f;
    const float gridStartX2 = gridStartX1 + (cols * (cellSize + cellSpacing)) + 100.f;

    Grid grid1(rows, cols, cellSize, cellSpacing, gridStartX1, gridStartY);
    Grid grid2(rows, cols, cellSize, cellSpacing, gridStartX2, gridStartY);

    std::vector<std::vector<sf::Sprite>> diceSprites1(rows, std::vector<sf::Sprite>(cols));
    std::vector<std::vector<sf::Sprite>> diceSprites2(rows, std::vector<sf::Sprite>(cols));
    std::vector<std::vector<Dice>> diceAnimations1(rows, std::vector<Dice>(cols));
    std::vector<std::vector<Dice>> diceAnimations2(rows, std::vector<Dice>(cols));

    // Load font
    sf::Font font;
    if (!font.loadFromFile("resources/arial.ttf")) {
        std::cerr << "Error loading font!" << std::endl;
        return;
    }

    Player player1("Player 1", font);
    player1.setLabelPosition(150.f, 450.f); // Position below grid 1

    Player player2("Player 2", font);
    player2.setLabelPosition(750.f, 450.f); // Position below grid 2

    bool cellSelected = false;
    sf::Vector2i selectedCell(-1, -1);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
                if (!diceAnimation.isDiceRolling()) {
                    for (int row = 0; row < rows; ++row) {
                        for (int col = 0; col < cols; ++col) {
                            sf::RectangleShape cell1 = grid1.get_cell(row, col);
                            sf::RectangleShape cell2 = grid2.get_cell(row, col);

                            if (cell1.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                selectedCell = sf::Vector2i(col, row);
                                cellSelected = true;

                                diceSprites1[selectedCell.y][selectedCell.x] = sf::Sprite();
                                diceAnimations1[selectedCell.y][selectedCell.x] = Dice(50);
                                diceAnimations1[selectedCell.y][selectedCell.x].loadFrames("images", 1, 24);
                                diceAnimations1[selectedCell.y][selectedCell.x].roll();
                            }

                            if (cell2.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                                selectedCell = sf::Vector2i(col, row);
                                cellSelected = true;

                                diceSprites2[selectedCell.y][selectedCell.x] = sf::Sprite();
                                diceAnimations2[selectedCell.y][selectedCell.x] = Dice(50);
                                diceAnimations2[selectedCell.y][selectedCell.x].loadFrames("images", 1, 24);
                                diceAnimations2[selectedCell.y][selectedCell.x].roll();
                            }
                        }
                    }
                }
            }
        }

        // Update dice animation for grid 1 and 2
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (diceAnimations1[row][col].isDiceRolling()) {
                    diceAnimations1[row][col].update(diceSprites1[row][col]);
                }
                if (diceAnimations2[row][col].isDiceRolling()) {
                    diceAnimations2[row][col].update(diceSprites2[row][col]);
                }
            }
        }

        // Update the position of dice sprites
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                if (diceSprites1[row][col].getTexture() && diceSprites1[row][col].getTextureRect().width) {
                    sf::RectangleShape cell1 = grid1.get_cell(row, col);
                    diceSprites1[row][col].setPosition(cell1.getPosition().x + (cellSize - diceSprites1[row][col].getGlobalBounds().width) / 2,
                        cell1.getPosition().y + (cellSize - diceSprites1[row][col].getGlobalBounds().height) / 2);
                }

                if (diceSprites2[row][col].getTexture() && diceSprites2[row][col].getTextureRect().width) {
                    sf::RectangleShape cell2 = grid2.get_cell(row, col);
                    diceSprites2[row][col].setPosition(cell2.getPosition().x + (cellSize - diceSprites2[row][col].getGlobalBounds().width) / 2,
                        cell2.getPosition().y + (cellSize - diceSprites2[row][col].getGlobalBounds().height) / 2);
                }
            }
        }

        window.clear();

        grid1.draw(window);
        grid2.draw(window);

        // Draw dice sprites for both grids
        for (int row = 0; row < rows; ++row) {
            for (int col = 0; col < cols; ++col) {
                window.draw(diceSprites1[row][col]);
                window.draw(diceSprites2[row][col]);
            }
        }

        // Draw player labels
        player1.drawLabel(window);
        player2.drawLabel(window);

        window.display();
    }
}

/**
* Public : main
*
* Description:
*      This is the entry point of the program. It initializes a window for the game,
*      sets the framerate limit, and starts the Game function to handle the game logic.
*
* Params:
*      - None
*
* Returns:
*      - int : Returns 0 to indicate successful execution
*/

int main() {
    sf::RenderWindow window(sf::VideoMode(1500, 800), "Dice Roll Animation on Grid");
    window.setFramerateLimit(60);

    Game(window);  // Call the Game function

    return 0;
}
