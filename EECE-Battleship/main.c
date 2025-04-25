/* This is the skeleton code I made for main.c it's was only for testing my fuctions but caould be repurposed for the actual framework for the finished code. I do recommend leaving parts not used 
commented out if not used  until we are sure everything works.  Please note is may be buggy I did note test alot of differnet cases using this code and... forgot to put something in incase a lowercase letter is entered 
for a target guess.
Variables in use below 
variable ---> description
gameGrid  ---> structure creation
remainingTurns ---> int for number of rounds (temporary until set by difficulty or user)
testGrid ---> array for testing
rowChar  ---> player input for row charater 
colGuess ---> player input for column 
rowGuess ---> The variable used to hold the converted rowChar variable
*/



#define _CRT_SECURE_NO_WARNINGS // Do not remove, it makes my life easy :3
#include <stdio.h> 
#include "battlegrid.h" // Include the header for grid stucture and function prototypes

int main() {
    BattleGrid gameGrid; // Create an instance of the BattleGrid structure to manage the game state
    int remainingTurns = 10; // Start with 10 turns for the player

    /* Define 5x5 test grid for gameplay(1 = ship, 2 = hit, 3 = miss, 0 = empty) NOTE--->haven't tested with a larger or smaller grid
    * BIG NOTE===> COMMENT THIS OUT DON'T ERASE.  this can be use for debugging, place random gen code above it  */
    int testGrid[MAX_GAME_ROWS][MAX_GAME_COLS] = {
        {1, 0, 0, 0, 0}, // place values here to change test grid 
        {0, 1, 0, 3, 0}, // ships will always remain hidden ( hopefully) until end of game
        {0, 0, 1, 0, 0}, // misses and hits will show right away if placed here
        {3, 0, 0, 1, 0}, // 
        {0, 2, 0, 0, 1}  // 
    };

    // Initialize the grid dimensions based on the test grid size
    gameGrid.gameRows = 5; // 5 rows in the game grid
    gameGrid.gameCols = 5; // 5 columns in the game grid
    gameGrid.visRows = gameGrid.gameRows + 1; // Include 1 header row
    gameGrid.visCols = gameGrid.gameCols + 1; // Include 1 header column

    // Call to the readGrid fuction using the test grid NOTE---> replace test grid with generated grid
    readGrid(&gameGrid, testGrid);

    // Calling Function to build the visual grid with fog-of-war (~)
    buildVisualGrid(&gameGrid);

    // Calling function to display the initial grid to the player
    printGrid(&gameGrid);

    // Main game loop test: continues until turns run out or all ships are sunk
    while (remainingTurns > 0 && gameGrid.remainingShips > 0) {
        char rowChar; // Player's input for the row (e.g., 'A', 'B', 'C')
        int colGuess; // Player's input for the column (e.g., 1, 2, 3)

        // Prompt the player for input
        printf("Enter row and column (e.g., A 1): ");
        scanf(" %c %d", &rowChar, &colGuess); // Read the row letter and column number

        // Convert the row letter (e.g., 'A') to a numeric index
        int rowGuess = rowChar - 'A' + 1; // 'A' maps to 1, 'B' maps to 2, etc. ( playing with the integer values for ASCII charater )
        /*NOTE--->An example on how this works: For 'A' the ASCII int value is 65 for 'B' the int value is 66 
        * So if rowChar = 'B' then what us happening is 'B' - 'A' + 1 = 2 which is  66 - 65 + 1 = 2*/  

        // Validate the player's input
        if (rowGuess < 1 || rowGuess > gameGrid.gameRows || colGuess < 1 || colGuess > gameGrid.gameCols) {
            printf("Invalid coordinates! Try again.\n");
            while (getchar() != '\n'); // Clear the input buffer
            continue; // Restart the loop to ask for input again
        }

        // Call to the function to update the grid based on the player's guess
        updateVisualGrid(&gameGrid, rowGuess, colGuess, &remainingTurns);

        // Call to the function display the updated grid after the guess
        printGrid(&gameGrid);
    }

    return 0; 
}
