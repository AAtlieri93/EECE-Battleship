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

    /*printf("Welcome to Battleship! Please enter a number for your random Battleship map: \n"); // Asks player to enter a number for RNG
    scanf("%d", &seedVal); // Random seed value from player input
    srand(seedVal); // Generated psuedo-random values for RNG factors in the game production

    // Difficulty loop to make sure the player inputs a correct diffculty choice
    /*while (validDiff == 0) {
        printf("Choose your difficulty: Easy | Normal | Hard\n");
        scanf("%s", difficulty);

        if (strcmp(difficulty, "Easy") == 0 || strcmp(difficulty, "easy") == 0) { // Easy difficulty
            printf("Easy difficulty chosen!\n"); // Tells player that they have succesfully chosen the easy difficulty
            remainingTurns = 7; // 7 turns for easy mode
            gameGrid.gameRows = 3; // 3 rows in the game grid
            gameGrid.gameCols = 3; // 3 columns in the game grid
            diffSize = 3; // Size 3
            shipAmount = 2; // 2 Ships
            validDiff = 1; // Breaks out of "choose difficulty" loop
        }
        else if (strcmp(difficulty, "Normal") == 0 || strcmp(difficulty, "normal") == 0) { // Normal difficulty
            printf("Normal difficulty chosen!\n"); // Tells player that they have succesfully chosen the normal difficulty
            remainingTurns = 13; // 13 turns for normal mode
            gameGrid.gameRows = 5; // 5 rows in the game grid
            gameGrid.gameCols = 5; // 5 columns in the game grid
            diffSize = 5; // Size 5
            shipAmount = 3; // 3 Ships
            validDiff = 1; // Breaks out of "choose difficulty" loop
        }
        else if (strcmp(difficulty, "Hard") == 0 || strcmp(difficulty, "hard") == 0) { // Hard difficulty
            printf("Hard difficulty chosen!\n"); // Tells player that they have succesfully chosen the hard difficulty
            remainingTurns = 17; // 17 turns for hard mode
            gameGrid.gameRows = 7; // 7 rows in the game grid
            gameGrid.gameCols = 7; // 7 columns in the game grid
            diffSize = 7; // Size 7
            shipAmount = 5; // 5 Ships
            validDiff = 1; // Breaks out of "choose difficulty" loop
        }
        else
            printf("Invalid input, please try again.\n"); // Tells player that they did not input a valid difficulty and asks them to retry
     }
     */

     /* Define 5x5 test grid for gameplay(1 = ship, 2 = hit, 3 = miss, 0 = empty) NOTE--->haven't tested with a larger or smaller grid
     * BIG NOTE===> COMMENT THIS OUT DON'T ERASE.  this can be use for debugging, place random gen code above it  */
    int testGrid[MAX_GAME_ROWS][MAX_GAME_COLS] = {
        {0, 0, 0, 0, 0}, // place values here to change test grid 
        {0, 0, 0, 0, 0}, // ships will always remain hidden ( hopefully) until end of game
        {0, 0, 0, 0, 0}, // misses and hits will show right away if placed here
        {0, 0, 0, 0, 0}, // 
        {0, 0, 0, 0, 0}  // 
    };

    /*int hor; // Defines if a ship is placed horizontally or verically
    int valid = 0; // Used to see if a ship can be correctly placed
    int shipHead, shipTail; // Parts of the ship being generated
    int i, k;

    /*for (k = 0; k < shipAmount; ++k) { // Will reiterate until all ships have been placed
        while (valid == 0) {
            hor = rand() % 2; // Basically a coin flip for horizontal or verical

            shipHead = rand() % diffSize; // Randomized head position
            shipTail = rand() % diffSize; // Randomized tail position

            valid = 1; // Will validate a ship placement
            for (i = 0; i < 2; ++i) { // For ship sizes of 2
                if (hor == 0) { // If ship placement is horizontal
                    if (shipTail + 1 == diffSize) { // If the tail of the ship is out of bounds of the map size, it will invalidate the ship placement and try again
                        valid = 0;
                        break;
                    }
                }
                else { // If ship placement is vertical
                    if (shipHead + 1 == diffSize) { // If the head of the ship is out of bounds of the map size, it will invalidate the ship placement and try again
                        valid = 0;
                        break;
                    }
                }
            }
            if (valid == 1) { // Will only place full ships if previous ship positions are valid
                for (i = 0; i < 2; ++i) { // Ships of size 2
                    if (hor == 0) // If ship placement is horizontal
                        testGrid[shipHead][shipTail + i] = 1; // Places a horizontal ship
                    else // If ship placement is vertical
                        testGrid[shipHead + i][shipTail] = 1; // Places a verical ship
                }
            }
        }
        valid = 0; // Resets valid ship placement for the next ship
    }

    */


    // Initialize the grid dimensions based on the test grid size
    //gameGrid.visRows = gameGrid.gameRows + 1; // Include 1 header row
    //gameGrid.visCols = gameGrid.gameCols + 1; // Include 1 header column

    // Call to the readGrid fuction using the test grid NOTE---> replace test grid with generated grid
    readGrid(&gameGrid, testGrid);
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
        printf("Enter row and column (e.g., A 1): tries left: %d\n", gameGrid.maxTurns);
        printf("ship count %d\n", gameGrid.remainingShips);
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
        updateVisualGrid(&gameGrid, rowGuess, colGuess, &gameGrid.maxTurns);

        // Call to the function display the updated grid after the guess
        printGrid(&gameGrid);
    }

    return 0;
}
