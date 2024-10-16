## 1. Dice Class
### Data:
- sides: Integer (number of sides, typically 6 for this game).
- current_value: Integer (value of the rolled die, ranging from 1 to 6).
### Actions:
- roll(): Rolls the die and updates current_value with a random number between 1 and 6.
- get_value(): Returns the current rolled value of the die.
### Relationships:
- Composition: A Player HAS-A Dice. Dice will be used by the Player to roll during the game. 
 
## 2. Player Class
### Data:
- name: String (player’s name).
- userid: String (player's username/handle).
- score: Integer (the player's current score).
- board: 2D array (3x3 grid to hold the dice values).
- dice_set: Array of Dice objects (representing dice used by the player).
- player_stats: List of Stats (can store information like total wins, losses, etc.).
- streak: Integer (tells the user what their winstreak is) (possibly inherits from winner?).
### Actions:
- roll_dice(): Rolls a die and returns the rolled value.
- place_die(column, value): Places the rolled die value in the specified column of the player's grid.
- get_score(): Calculates and returns the player's current score based on dice values and multiplication bonuses.
- remove_opponent_die(column, value): Removes the opponent's dice in the same column with matching value.
- update_score(points): Updates the player’s score after placing a die or modifying the grid.
- check_full_grid(): Checks if the player's grid is fully populated.
### Relationships:
- Composition: A Player HAS-A Dice.
- A Player participates in the game and interacts with the grid (which represents their board).

## 3. Game Class
### Data:
- players: List of Player objects.
- current_round: Integer (tracks the current round of play).
### Actions:
- start_game(): Initializes the game.
- end_game(): Ends the game.
- get_winner(): Compares the scores of the players and returns the winner.
### Relationships:
- A Game has players and manages them.

## 4. Knucklebones Game Class (inherits from Game)
### Data:
- players: List of Player objects (2 players in this game).
- current_round: Integer (keeps track of the number of rounds).
- rules: Rulebook (the rules for the game).
### Actions:
- start_game(): Initiates a new game with both players.
- end_game(): Ends the game, compares scores, and declares a winner.
- start_round(): Handles each round, where players take turns rolling dice and placing them on the grid.
- get_winner(): Determines the winner based on the final scores.
- apply_scoring_rules(): Applies the specific scoring rules, including the multiplication bonus for matching dice in the same column.
- handle_die_removal(player, column, value): Handles the removal of the opponent’s dice when a player places a die in the same column and with the same value.
- check_full_game(): Checks if both players' grids are fully populated, signaling the end of the game.
- update_game_state(): Updates the game state after each round, including scores and board status.
### Relationships:
- Inheritance: Knucklebones IS-A Game.
- Composition: Knucklebones HAS-A Player and Board.

## Keywords:
- chat (wishful)
- coins (wishful)
- first name (necessary, but could be combined in a name class)
- last name (necessary, but could be combined in a name class)
- high score (possible)
- leaderboard (wishful)
- levels (wishful)
- messaging (wishful)
- player stats (necessary)
- score (necessary)
- streak (possible)
- team stats (wishful)
- teams (wishful)
- userid (necessary)
- winner (necessary)
