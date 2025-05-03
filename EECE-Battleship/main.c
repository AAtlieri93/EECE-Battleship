/*  main.c  


Variables in use below
variable ---> description
gameGrid  ---> structure creation
remainingTurns ---> int for number of rounds (temporary until set by difficulty or user)
arrayGrid ---> array for testing
rowChar  ---> player input for row charater
colGuess ---> player input for column
rowGuess ---> The variable used to hold the converted rowChar variable
*/



#define _CRT_SECURE_NO_WARNINGS // Do not remove, it makes my life easy :3
#include <stdio.h> 
#include <stdlib.h> // Used for random ship generation
#include <string.h> // To read difficulty input
#include "battlegrid.h" // Include the header for grid stucture and function prototypes

BattleGrid gameGrid = { 0 }; // Initializes structure members to zero  

int main() {
    BattleGrid gameGrid = { 0 }; // Create an instance of the BattleGrid structure to manage the game state
    int maxTurns ; // Start with 10 turns for the player
    char difficulty[8]; // Difficulty choice from player
    int validDiff = 0; // Used to check if player input a valid difficulty
    int seedVal; // Player input seed value
    int diffSize; // Size of the array depending on the difficulty chosen
    int shipAmount; // Amount of ships depending on the difficulty chosen
    int RemainingTurns = gameGrid.maxTurns;
    int hintUsed = 0; // Keeps track of hints
    char input[50]; // Buffer for user input

    
     /* Define 5x5 test grid for gameplay(1 = ship, 2 = hit, 3 = miss, 0 = empty) NOTE--->haven't tested with a larger or smaller grid
     * BIG NOTE===> COMMENT THIS OUT DON'T ERASE.  this can be use for debugging, place random gen code above it  */
    int arrayGrid[MAX_GAME_ROWS][MAX_GAME_COLS] = {
        {0, 0, 0, 0, 0}, // place values here to change test grid 
        {0, 0, 0, 0, 0}, // ships will always remain hidden ( hopefully) until end of game
        {0, 0, 0, 0, 0}, // misses and hits will show right away if placed here
        {0, 0, 0, 0, 0}, // 
        {0, 0, 0, 0, 0}  // 
    };

    // Call to the setupGrid fuction using the test grid NOTE---> replace test grid with generated grid
    setupGrid(&gameGrid, arrayGrid);
    gameGrid.visRows = gameGrid.gameRows + 1; // NEW  moved to after the read grid fuction
    gameGrid.visCols = gameGrid.gameCols + 1;


    // Calling Function to build the visual grid with fog-of-war (~)
    buildVisualGrid(&gameGrid);

    // Calling function to display the initial grid to the player
    printGrid(&gameGrid);

    // Main game loop test: continues until turns run out or all ships are sunk
    while (gameGrid.maxTurns > 0 && gameGrid.remainingShips > 0) {
        char rowChar; // Player's input for the row (e.g., 'A', 'B', 'C')
        int colGuess; // Player's input for the column (e.g., 1, 2, 3)

        // Prompt the player for input
        printf("Enter row and column (e.g., A 1) or type 'Get hint': tries left: %d\n", gameGrid.maxTurns);
        //printf("ship count %d\n", gameGrid.remainingShips);
        //(" %c %d", &rowChar, &colGuess); // Read the row letter and column number
        fgets(input, sizeof(input), stdin); // Read full input line (supports 'Get hint')

        input[strcspn(input, "\n")] = 0; // Removes new lines

        if (strcmp(input, "Get hint") == 0 || strcmp(input, "get hint") == 0) {
            if (hintUsed == 0) {
                giveHint(&gameGrid); // Call hint function
                hintUsed = 1; // Set flag to prevent further use
            } else {
                printf("Hint already used! You only get one!\n");
            }
            continue; // Skip turn cost if player uses hint
        }

        
        // Parse input as coordinate guess
        if (sscanf(input, " %c %d", &rowChar, &colGuess) != 2) { // Input format validation
            printf("Invalid input format! Please enter like 'A 1' or 'Get hint'.\n");
            continue; // Restart loop for a valid input
        }

        // Handle lowercase letters
        if (rowChar >= 'a' && rowChar <= 'z') {
            rowChar -= 32; // Convert to uppercase by subtracting 32 from ASCII value
        }

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
        updateVisualGrid(&gameGrid, rowGuess, colGuess, &gameGrid.maxTurns);

        // Call to the function display the updated grid after the guess
        printGrid(&gameGrid);
    }

    return 0;
}
