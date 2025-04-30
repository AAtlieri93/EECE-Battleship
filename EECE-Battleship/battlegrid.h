/*This is the header filer, this defins the structure for the Battlegrid as well as any function prototypes for what exists in Battlegrid.c
more can be added here if they relate to grid mechanics just to keep things neat*/
#ifndef BATTLEGRID_H
#define BATTLEGRID_H

// Defining maximum grid dimensions NOTE---> these have to be changed if we want bigger grids
#define MAX_GAME_ROWS 7  // Maximum playable grid size for rows (0-6 indexing)
#define MAX_GAME_COLS 7  // Maximum playable grid size for columns
#define MAX_VIS_ROWS 8   // Visual grid includes headers, so it's 1 row larger than the game grid
#define MAX_VIS_COLS 8   // Visual grid includes headers, so it's 1 column larger than the game grid

// Structure for managing the game grid
typedef struct {
    int referenceGrid[MAX_GAME_ROWS][MAX_GAME_COLS]; // Core grid: tracks ship locations, hits, and misses
    char visualGrid[MAX_VIS_ROWS][MAX_VIS_COLS];     // Display grid: includes fog of war (~), hits (O), and misses (X)
    int gameRows;    // Number of playable rows (set dynamically, e.g., 5 for a 5x5 grid)
    int gameCols;    // Number of playable columns (set dynamically, e.g., 5 for a 5x5 grid)
    int visRows;     // Number of rows in the visual grid (gameRows + 1 for headers)
    int visCols;     // Number of columns in the visual grid (gameCols + 1 for headers)
    int remainingShips; // Tracks the number of ships left to sink
    int maxTurns;       // Maximum number of turns allowed before the game ends
} BattleGrid; // name of structure

// Function prototypes (declared here for use in other files)
void setupGrid(BattleGrid* bg, int testGrid[MAX_GAME_ROWS][MAX_GAME_COLS]); // Copies a predefined test grid into the reference grid
void buildVisualGrid(BattleGrid* bg); // Creates the fog-of-war display grid
void updateVisualGrid(BattleGrid* bg, int rowGuess, int colGuess, int* remainingTurns); // Updates the grid based on the player's guess
void printGrid(BattleGrid* bg); // Prints the visual grid 
#endif
