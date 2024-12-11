#include "buttonClass.hpp"   // button class
#include "colors.hpp"        // color class
#include "diceClass.hpp"     // calls class for the dice roll
#include "gridClass.hpp"     // class to utilize the grid for knucklebones
#include "logger.hpp"        // logger utility
#include <fstream>           // file I/O
#include <iostream>          // input/output
#include <locale.h>          // setting locales
#include <map>               // map data structure
#include <ncurses.h>         // Ncurses library
#include <string>            // string data structure
#include <vector>            // vector data structure
#include <ctime>             // rand and time operations
#include <unistd.h>          // usleep for animation

/*****************************************************************************
*
*  Author:           Jack Leary
*  Email:            jackleary645@gmail.com
*  Label:            Ncurses Knucklebones (work in progress)
*  Course:           2143 OOP
*  Semester:         Fall 2024
*
*  Description:
*        This program simulates a dice roll using the Ncurses library. It animates
*        a dice and shows the image on the screen. It is the start of a Knucklebones
*        simulation I was attempting to work on which is why many classes and files
*        went unused.
*
*  Usage:
*        - Compile the program with `g++ -o knucklebones main.cpp buttonClass.cpp colors.cpp diceClass.cpp gridClass.cpp logger.cpp -lncurses`
*        - Run the game with `./knucklebones`
*        - Players can roll a dice and it will appear on screen.
*
*  Files:             main.cpp    : driver program for the Knucklebones game
*                     buttonClass.hpp  : class for button functionality (if used)
*                     colors.hpp        : class for color handling
*                     diceClass.hpp     : dice handling class
*                     gridClass.hpp     : class for grid management
*                     logger.hpp        : utility for logging events
*****************************************************************************/

/**
 * show_image
 *
 * Description:
 *      Simulates displaying an image in the game interface.
 *      This function is used for animations, like the dice roll.
 *
 * Params:
 *      std::string : image_path - Path to the image file to be displayed.
 *
 * Returns:
 *      void
 */
void show_image(const std::string& image_path) {
    printw("Displaying image: %s\n", image_path.c_str());
    refresh();
}

/**
 * animate_dice
 *
 * Description:
 *      Animates the dice rolling by displaying a sequence of images.
 *      This simulates a rolling effect for the player.
 *
 * Params:
 *      void
 *
 * Returns:
 *      void
 */
void animate_dice() {
    for (int i = 1; i <= 24; i++) {
        // Construct the filename for the animation frame
        std::string frame = (i < 10) ? "00" + std::to_string(i) + ".png" : "0" + std::to_string(i) + ".png";
        
        // Clear the screen and display the current frame
        clear();
        show_image(frame);
        
        // Wait for a brief moment to simulate animation (e.g., 50ms per frame)
        usleep(50000);  // 50 milliseconds
    }
}

/**
 * Dice
 *
 * Description:
 *      This class represents a dice that can be rolled with a configurable number
 *      of sides. The dice is used by players in the Knucklebones game to generate
 *      random values during their turn.
 *
 * Public Methods:
 *      - Dice(int sides = 6) : Constructor that initializes the dice with a given number of sides.
 *      - int roll()          : Rolls the dice and returns the result.
 *      - int get_value()     : Returns the last rolled value.
 *
 * Private Methods:
 *      - None
 *
 * Usage:
 *      Dice dice;              // Create a dice with 6 sides
 *      int roll_value = dice.roll();  // Roll the dice and store the value
 *      int value = dice.get_value();  // Get the value of the last roll
 */
class Dice {
public:
  Dice(int sides = 6) : sides(sides), current_value(1) {}

  int roll() {
    current_value = rand() % sides + 1;
    return current_value;
  }

  int get_value() const { return current_value; }

private:
  int sides;         // Number of sides on the die
  int current_value; // Last rolled value
};

/**
 * Player
 *
 * Description:
 *      This class represents a player in the Knucklebones game. Each player
 *      has a name, a score, and a 3x3 grid where dice values can be placed.
 *      Players take turns rolling dice, placing them on their grid, and removing
 *      opponent's dice if necessary.
 *
 * Public Methods:
 *      - Player(const std::string &name)   : Constructor to initialize the player with a name.
 *      - int roll_dice()                   : Rolls the dice and returns the result.
 *      - void place_die(int column, int value) : Places the rolled die value in the specified column.
 *      - int get_score()                   : Returns the player's score.
 *      - void remove_opponent_die(int column, int value) : Removes an opponent's die from the grid.
 *      - bool check_full_grid()            : Checks if the player's grid is full.
 *
 * Private Methods:
 *      - void update_score()               : Updates the player's score based on their grid.
 *
 * Usage:
 *      Player p1("Player1");            // Create player 1
 *      int roll = p1.roll_dice();        // Roll the dice
 *      p1.place_die(0, roll);            // Place the rolled value in column 0
 *      int score = p1.get_score();       // Get player's score
 */
class Player {
public:
  Player(const std::string &name)
      : name(name), score(0), grid(3, std::vector<int>(3, 0)) {}

  int roll_dice() {
    animate_dice();  // Show dice animation before rolling
    return dice.roll();
  }

  void place_die(int column, int value) {
    for (int row = 0; row < 3; ++row) {
      if (grid[column][row] == 0) {
        grid[column][row] = value;
        break;
      }
    }
    update_score();
  }

  int get_score() const { return score; }

  void remove_opponent_die(int column, int value) {
    for (int row = 0; row < 3; ++row) {
      if (grid[column][row] == value) {
        grid[column][row] = 0;
        break;
      }
    }
  }

  bool check_full_grid() const {
    for (const auto &column : grid) {
      for (int cell : column) {
        if (cell == 0)
          return false;
      }
    }
    return true;
  }

private:
  std::string name;                   // Player's name
  int score;                          // Player's score
  Dice dice;                          // Player's dice
  std::vector<std::vector<int>> grid; // Player's 3x3 grid

  void update_score() {
    score = 0;
    for (int col = 0; col < 3; ++col) {
      int col_score = 0;
      std::vector<int> counts(7, 0); // counts for dice values 1-6
      for (int row = 0; row < 3; ++row) {
        int value = grid[col][row];
        if (value > 0) {
          counts[value]++;
          col_score += value;
        }
      }
      for (int value = 1; value <= 6; ++value) {
        if (counts[value] > 1) {
          col_score += (counts[value] - 1) * value * counts[value];
        }
      }
      score += col_score;
    }
  }
};

/**
 * KnucklebonesGame
 *
 * Description:
 *      This class manages the entire Knucklebones game. It initializes the players,
 *      starts the game loop, and handles player turns, including rolling dice, 
 *      placing dice on the grid, and removing opponent's dice. It checks for the 
 *      game's end conditions and displays the final scores.
 *
 * Public Methods:
 *      - KnucklebonesGame(const std::string &player1_name, const std::string &player2_name) : 
 *        Constructor to initialize the game with two players.
 *      - void start_game() : Starts the game and runs the game loop.
 *      - void end_game() : Ends the game and displays the final scores.
 *
 * Private Methods:
 *      - bool check_full_game() : Checks if the game is over (e.g., when both players' grids are full).
 *      - void handle_die_removal(int player_idx, int column, int value) : Handles the logic for removing opponent's die.
 *
 * Usage:
 *      KnucklebonesGame game("Player1", "Player2");  // Create a game with two players
 *      game.start_game();                            // Start the game
 */
class KnucklebonesGame {
public:
  KnucklebonesGame(const std::string &player1_name, const std::string &player2_name)
      : player1(player1_name), player2(player2_name), current_player_idx(0) {}

  void start_game() {
    while (!check_full_game()) {
      Player &current_player = (current_player_idx == 0) ? player1 : player2;
      // Roll dice and take player actions
      int roll = current_player.roll_dice();
      int column = 0;  // Get user input for column (this is simplified for now)
      current_player.place_die(column, roll);
      current_player_idx = (current_player_idx == 0) ? 1 : 0;
    }
    end_game();
  }

  void end_game() {
    clear();
    if (player1.get_score() > player2.get_score()) {
      printw("Player 1 wins with a score of %d!\n", player1.get_score());
    } else if (player2.get_score() > player1.get_score()) {
      printw("Player 2 wins with a score of %d!\n", player2.get_score());
    } else {
      printw("It's a tie with a score of %d!\n", player1.get_score());
    }
    refresh();
  }

private:
  Player player1;     // First player
  Player player2;     // Second player
  int current_player_idx; // Index of the current player (0 for player1, 1 for player2)

  bool check_full_game() {
    return player1.check_full_grid() && player2.check_full_grid();
  }

  void handle_die_removal(int player_idx, int column, int value) {
    Player &opponent = (player_idx == 0) ? player2 : player1;
    opponent.remove_opponent_die(column, value);
  }
};

/**
 * Main Function
 *
 * Description:
 *      This is the entry point for the program. It initializes the Ncurses 
 *      library, sets the locale, and starts the Knucklebones game.
 *
 * Params:
 *      int argc : The number of command-line arguments.
 *      char **argv : The command-line arguments.
 *
 * Returns:
 *      0 if the program runs successfully.
 */
int main(int argc, char **argv) {
  setlocale(LC_ALL, "");  // Set locale for Ncurses

  initscr();  // Initialize the screen
  cbreak();   // Disable line buffering
  noecho();   // Disable automatic echoing of input
  curs_set(0);  // Hide the cursor

  KnucklebonesGame game("Player1", "Player2");
  game.start_game();

  endwin();  // End Ncurses mode
  return 0;
}
