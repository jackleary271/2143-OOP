/*****************************************************************************
 *
 *  Author:           Jack Leary
 *  Email:            jackleary645@gmail.com
 *  Title:            Knucklebones Ncurses
 *  Course:           CMPS 2143
 *  Semester:         Fall 2024
 *
 *  Description:
 *        This program implements a basic version of the Knucklebones game
 *        using Ncurses. It allows two players to roll dice, place dice into
 *        columns on their respective grids, and calculate scores based on
 *        unique scoring rules. The game ends when both players' grids are
 *        full, and the winner is determined by the highest score.
 *
 *  Usage:
 *        - Compile and run the program.
 *        - Players take turns rolling dice and placing them into columns.
 *        - The program keeps track of scores and ends the game when grids are
 *full.
 *
 *  Files:
 *       main.cpp        : driver program
 *****************************************************************************/

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

/**
 * Dice
 *
 * Description:
 *      This class simulates a die with a specified number of sides.
 *      It allows rolling the die to generate a random value.
 *
 * Public Methods:
 *      - Dice(int sides = 6)
 *      - int roll()
 *      - int get_value() const
 *
 * Private Methods:
 *      None
 *
 * Usage:
 *      Dice d(6);           // Create a 6-sided die
 *      int result = d.roll(); // Roll the die
 */
class Dice {
public:
  Dice(int sides = 6) : sides(sides), current_value(1) {}

  /**
   * Public : roll
   *
   * Description:
   *      Rolls the die to generate a random value between 1 and the number of
   * sides.
   *
   * Params:
   *      None
   *
   * Returns:
   *      int : The rolled value
   */
  int roll() {
    current_value = rand() % sides + 1;
    return current_value;
  }

  /**
   * Public : get_value
   *
   * Description:
   *      Returns the last rolled value of the die.
   *
   * Params:
   *      None
   *
   * Returns:
   *      int : The current die value
   */
  int get_value() const { return current_value; }

private:
  int sides;         // Number of sides on the die
  int current_value; // Last rolled value
};

/**
 * Player
 *
 * Description:
 *      This class represents a player in the Knucklebones game.
 *      It manages the player's dice rolls, grid, and score calculations.
 *
 * Public Methods:
 *      - Player(const std::string& name)
 *      - int roll_dice()
 *      - void place_die(int column, int value)
 *      - int get_score() const
 *      - void remove_opponent_die(int column, int value)
 *      - bool check_full_grid() const
 *
 * Private Methods:
 *      - void update_score()
 *
 * Usage:
 *      Player p("Player 1");   // Create a player
 *      int roll = p.roll_dice(); // Roll the player's die
 *      p.place_die(0, roll);    // Place the rolled value in column 0
 */
class Player {
public:
  Player(const std::string &name)
      : name(name), score(0), grid(3, std::vector<int>(3, 0)) {}

  int roll_dice() { return dice.roll(); }

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

  /**
   * Private : update_score
   *
   * Description:
   *      Calculates and updates the player's score based on the current grid
   * state.
   *
   * Params:
   *      None
   *
   * Returns:
   *      None
   */
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
 *      This class manages the Knucklebones game logic, including player turns,
 *      dice rolls, and score calculations.
 *
 * Public Methods:
 *      - KnucklebonesGame(const std::string& player1_name, const std::string&
 * player2_name)
 *      - void start_game()
 *      - void end_game()
 *
 * Private Methods:
 *      - void handle_die_removal(int player_index, int column, int value)
 *      - bool check_full_game() const
 *
 * Usage:
 *      KnucklebonesGame game("Player 1", "Player 2");
 *      game.start_game();
 */
class KnucklebonesGame {
public:
  KnucklebonesGame(const std::string &player1_name,
                   const std::string &player2_name)
      : players{Player(player1_name), Player(player2_name)}, current_round(0) {
    srand(static_cast<unsigned>(time(0)));
  }

  void start_game() {
    initscr(); // Initialize Ncurses
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    while (!check_full_game()) {
      for (int i = 0; i < 2; ++i) {
        int roll = players[i].roll_dice();
        mvprintw(0, 0,
                 "Player %d rolled a %d. Choose a column (0, 1, or 2): ", i + 1,
                 roll);
        refresh();

        int column = getch() - '0';
        while (column < 0 || column > 2 ||
               players[i].check_full_column(column)) {
          mvprintw(1, 0, "Invalid column! Try again: ");
          refresh();
          column = getch() - '0';
        }

        players[i].place_die(column, roll);
        handle_die_removal(i, column, roll);
      }
      ++current_round;
    }
    end_game();
    endwin(); // End Ncurses
  }

  void end_game() {
    int score1 = players[0].get_score();
    int score2 = players[1].get_score();
    std::cout << "Game Over! Final Scores:\n";
    std::cout << "Player 1: " << score1 << std::endl;
    std::cout << "Player 2: " << score2 << std::endl;
    std::cout << "Winner: " << (score1 > score2 ? "Player 1" : "Player 2")
              << "\n";
  }

private:
  std::vector<Player> players; // List of players
  int current_round;           // Current round number

  void handle_die_removal(int player_index, int column, int value) {
    int opponent_index = (player_index + 1) % 2;
    players[opponent_index].remove_opponent_die(column, value);
  }

  bool check_full_game() const {
    return players[0].check_full_grid() && players[1].check_full_grid();
  }
};

int main() {
  KnucklebonesGame game("Player 1", "Player 2");
  game.start_game();
  return 0;
}