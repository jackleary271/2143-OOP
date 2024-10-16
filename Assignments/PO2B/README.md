## 1. Dice Class
### Data:
- sides: Integer (number of sides, typically 6 for this game).
- current_value: Integer (value of the rolled die, ranging from 1 to 6).
### Actions:
- roll(): Rolls the die and updates current_value with a random number between 1 and 6.
- get_value(): Returns the current rolled value of the die.
### Relationships:
- Composition: A Player HAS-A Dice to use during the game.
 
## 2. Player Class
### Data:
- name: String (player’s name).
- score: Integer (the player's current score).
- grid: 2D array (3x3 grid to hold the dice values).
- dice_set: Array of Dice objects (representing dice used by the player).
- player_stats: Dictionary (can store additional information like total wins, losses, etc.).
### Actions:
- roll_dice(): Rolls a die and returns the rolled value.
- place_die(column, value): Places the rolled die value in the specified column of the player's grid.
- get_score(): Calculates and returns the player's current score based on dice values and multiplication bonuses.
- remove_opponent_die(column, value): Removes the opponent's dice in the same column with matching value.
- update_score(points): Updates the player’s score after placing a die or modifying the grid.
- check_full_grid(): Checks if the player's grid is fully populated.
### Relationships:
- Composition: A Player HAS-A Dice.
- A Player participates in the game.

## 3. Board Class
### Data:
- grid: 2D array (3x3 grid for each player).
- players: List of Player objects.
### Actions:
- update_board(): Updates the player's grid with a new die.
- display_board(): Displays the current board state for both players.
- check_full_board(): Checks if both players' grids are full, signaling the end of the game.
### Relationships:
- Composition: A Board HAS-A Player, as each player interacts with the board.

## 4. Knucklebones Game Class (inherits from Game)
### Data:
- players: List of Player objects (2 players in this game).
- board: Board object that manages the grid for both players.
- current_round: Integer (keeps track of the number of rounds).
- rules: Dictionary (the rules for the game).
### Actions:
- start_game(): Initiates a new game with both players.
- end_game(): Ends the game, compares scores, and declares a winner.
- start_round(): Handles each round, where players take turns rolling dice and placing them on the board.
- get_winner(): Determines the winner based on the final scores.
- apply_scoring_rules(): Applies the specific scoring rules, including the multiplication bonus for matching dice in the same column.
- handle_die_removal(): Removes opponent's matching die when placed in the same column.
### Relationships:
- Inheritance: Knucklebones IS-A Game.
- Composition: Knucklebones HAS-A Player and Board.

## 5. Game Class
### Data:
- players: List of Player objects.
- current_round: Integer (tracks the current round of play).
### Actions:
- start_game(): Initializes the game.
- end_game(): Ends the game.
- get_winner(): Compares the scores of the players and returns the winner.
### Relationships:
- A Game has players and manages them.
