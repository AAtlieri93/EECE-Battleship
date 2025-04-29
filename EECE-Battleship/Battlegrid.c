/* this contains all the function definitions for the grid system, if more fuctions are added here make sure to place the prototype in battlegrid.h or things may break.
the header file is important here. there is alot of pointer use here to move data in and out of the functions to main.c 
NOTE---> Variable are initialized in the fuctions not in the beginning of the file, variables and pointes in use are listed below for reference
variable ---> description
bg       ---> pointer
i        --->  integer for row indexing
j        --->   integer for column indexing
testgrid ---> for testing the read fuction
MAX_GAME_ROWS---> defined in header
MAX_GAME_COLS---> defined in header
rowLabels --->  characters for row headers
colLabels --->  characters for column headers
MAX_VIS_ROWS ---> defined in header
MAX_VIS_COLs ---> defined in header
actualRow ---> The variable used to shift index placement between the reference grid and visual grid 
actualCol ---> Same as above but just for columns (sorry in advance if these are confusing names because of the rowGuess and colGuess within main.c)
*/


#define _CRT_SECURE_NO_WARNINGS // Do not remove, it makes my life easy :3
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "battlegrid.h" // Include the header file for battlegrid structure and function prototypes


void readGrid(BattleGrid* bg, int testGrid[MAX_GAME_ROWS][MAX_GAME_COLS]) {// Initializing the core function to read generated grids (ships, hits, misses) currently using test grid in main.c
    bg->remainingShips = 0;  // Start by setting the number of ships to 0
    bg->maxTurns = 10;       // Set the maximum number of turns allowed ------> this can be changed or pulled from main instead, placed here for testing 
    char difficulty[8]; // Difficulty choice from player
    int validDiff = 0; // Used to check if player input a valid difficulty
    int seedVal; // Player input seed value
    int diffSize; // Size of the array depending on the difficulty chosen
    int shipAmount; // Amount of ships depending on the difficulty chosen

    printf("Welcome to Battleship! Please enter a number for your random Battleship map: \n"); // Asks player to enter a number for RNG
    scanf("%d", &seedVal); // Random seed value from player input
    srand(seedVal); // Generated psuedo-random values for RNG factors in the game production
    
    // Difficulty loop to make sure the player inputs a correct diffculty choice
    while (validDiff == 0) {
        printf("Choose your difficulty: Easy | Normal | Hard\n");
        scanf("%s", difficulty);

        if (strcmp(difficulty, "Easy") == 0 || strcmp(difficulty, "easy") == 0) { // Easy difficulty
            printf("Easy difficulty chosen!\n"); // Tells player that they have succesfully chosen the easy difficulty
            bg->maxTurns = 7; // 7 turns for easy mode
            bg->gameRows = 3; // 3 rows in the game grid
            bg->gameCols = 3; // 3 columns in the game grid
            diffSize = 3; // Size 3
            shipAmount = 2; // 2 Ships
            validDiff = 1; // Breaks out of "choose difficulty" loop
        }
        else if (strcmp(difficulty, "Normal") == 0 || strcmp(difficulty, "normal") == 0) { // Normal difficulty
            printf("Normal difficulty chosen!\n"); // Tells player that they have succesfully chosen the normal difficulty
            bg->maxTurns = 13; // 13 turns for normal mode
            bg->gameRows = 5; // 5 rows in the game grid
            bg->gameCols = 5; // 5 columns in the game grid
            diffSize = 5; // Size 5
            shipAmount = 3; // 3 Ships
            validDiff = 1; // Breaks out of "choose difficulty" loop
        }
        else if (strcmp(difficulty, "Hard") == 0 || strcmp(difficulty, "hard") == 0) { // Hard difficulty
            printf("Hard difficulty chosen!\n"); // Tells player that they have succesfully chosen the hard difficulty
            bg->maxTurns = 17; // 17 turns for hard mode
            bg->gameRows = 7; // 7 rows in the game grid
            bg->gameCols = 7; // 7 columns in the game grid
            diffSize = 7; // Size 7
            shipAmount = 5; // 5 Ships
            validDiff = 1; // Breaks out of "choose difficulty" loop
        }
        else
            printf("Invalid input, please try again.\n"); // Tells player that they did not input a valid difficulty and asks them to retry
     }
    int hor; // Defines if a ship is placed horizontally or verically
    int valid = 0; // Used to see if a ship can be correctly placed
    int shipHead, shipTail; // Parts of the ship being generated
    int i, k;

    for (k = 0; k < shipAmount; ++k) { // Will reiterate until all ships have been placed
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
    /* Essentially how this piece of code works is that it checks if the ship placement will be horizontal or vertical, and then will see
    if the second part of the ship exceeds the grid size or if it collides with an existing ship. If so, the code will fail and will be
    forced to retry another ship position, constantly retying until it can place a valid ship that does not collide with the grid limits and
    existing ships, and it will continue to do this until all ships are placed.
    */
    int checkShip = 1; // Will be used to check for correct ship placement
    // Copying the test grid into the reference grid and count ships
    for (i = 0; i < bg->gameRows; i++) { // Loop through the game rows
        for (int j = 0; j < bg->gameCols; j++) { // Loop through the game columns
            bg->referenceGrid[i][j] = testGrid[i][j]; // Copy each cell value from testGrid
            if ((testGrid[i][j] == 1 && testGrid[i][j - 1]) || (testGrid[i][j] == 1 && testGrid[i - 1][j])) { // Check if the cell before or above has a ship position
                checkShip = 0; // Will invalidate this position as the start of a new ship
            }
            if (checkShip == 1) { // Will only run if this is a new ship
              if (testGrid[i][j] == 1 && testGrid[i][j+1] == 1) { // Checks if it's a vertical ship
                bg -> remainingships++; // Increments ship count by 1
              }
              else if (testGrid[i][j] == 1 && testGrid[i+1][j] == 1) { // Checks if it's a horizontal ship
                bg -> remainingships++; // Increments ship count by 1
              }
            }
        checkShip = 1; // Resets valid ship position for next ship count iteration
        }
    }
    /* Function: The code will go through row by row, column by column, and if it finds a ship position, it will first check if a ship has already been counted
    from that spot, since all secondary parts of the ships are generated either leftwards (if horizontal) or downwards (if vertical). So if a "1" is detected above
    or to the left of that ship, the code will say that particular ship position has already been accounted for and the code should not increment the ship count.
    If there are no "1" to the top or left of that position, the code will first check if it's a vertical ship. If so, increment the ship count by 1. If not, then
    the code will check if it's a horizontal ship instead, and if so, increment ship count by 1.
    */
    /* Purpose: Sets up the game logic grid with ships, hits, and misses from test grid.This should be able to be modified to work with the proper grid generation
    * NOTE---> Still have to figure out ship size, as is every instance of 1 in the grid read counts as it's own ship, Maybe we could use this as a very hard mode with a large grid?
    * The grid should scale based on size entered, I have not fully tested */
}

/* Function to build the visual grid(includes headers, hides ships with in fog of war) 
Note--->I have not figured out colors yet but if there is time and when the rest of the game works I may add it in*/
void buildVisualGrid(BattleGrid* bg) {
    // Defining labels for rows ('A'-'G') and columns ('1'-'7') If we go bigger then 7x7 this will have to be changed
    char rowLabels[MAX_VIS_ROWS] = { ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G' }; // Row headers
    char colLabels[MAX_VIS_COLS] = { ' ', '1', '2', '3', '4', '5', '6', '7' }; // Column headers

    // Loop through the visual grid to assign headers and fog of war
    for (int i = 0; i < bg->visRows; i++) { // Loop through visual grid rows
        for (int j = 0; j < bg->visCols; j++) { // Loop through visual grid columns
            if (i == 0) {
                bg->visualGrid[i][j] = colLabels[j]; // First row contains column headers
            }
            else if (j == 0) {
                bg->visualGrid[i][j] = rowLabels[i]; // First column contains row headers
            }
            else {
                // Map each cell of the generated grid to the ASCII symbol, NOTE I believe color probably goes here, I just want it working 
                switch (bg->referenceGrid[i - 1][j - 1]) { // Adjusting for headers since the 2D visual grid is one power larger, stops Headers from being over written and also going out of range
                case 0: bg->visualGrid[i][j] = '~'; break; // Empty cell, fog of war
                case 1: bg->visualGrid[i][j] = '~'; break; // Hidden ship, fog of war
                case 2: bg->visualGrid[i][j] = 'O'; break; // Hit
                case 3: bg->visualGrid[i][j] = 'X'; break; // Miss
                }
            }
        }
    }
    /* Purpose: Builds a visual battlegrid with headers and initial fog - of - war(~). This will hide ships but will show hits and misses if present in the referenced array 
    regardless if it's freshly generated
    Note---> this array will always be 1 size bigger to make room for the header, we will have to change quite a few sections of code if we want to games bigger than 7x7
    It's possible to add more characters to display here if we do power ups or other extra features
    I do want to figure out if colors are possible still*/
}

// function to update the grid based on player guesses 
void updateVisualGrid(BattleGrid* bg, int rowGuess, int colGuess, int* remainingTurns) {
    // Validate input coordinates (guesses starting at 1)
    if (rowGuess < 1 || rowGuess > bg->gameRows || colGuess < 1 || colGuess > bg->gameCols) {
        printf("Invalid coordinates! Please enter a valid row and column.\n");
        return; // Exit the function if input is invalid maybe a good idea to have the this loop instead of exit, will fix later 
    }

    // Convert player input to battle grid coordinates (starting at 0)
    int actualRow = rowGuess - 1; // Adjust row index
    int actualCol = colGuess - 1; // Adjust column index

    // Check the cell in the grid
    if (bg->referenceGrid[actualRow][actualCol] == 1) { // If there's a ship
        printf("Hit!\n");
        bg->visualGrid[actualRow + 1][actualCol + 1] = 'O'; // Mark hit in the visual grid Note---> due to the header we have to shift the charater change over
        bg->referenceGrid[actualRow][actualCol] = 2; // Update the battle grid to reflect the hit
        bg->remainingShips--; // Reduce the ship count
    }
    else { // If no ship is present
        printf("Miss!\n");
        bg->visualGrid[actualRow + 1][actualCol + 1] = 'X'; // Mark miss in the visual grid Note---> due to the header we have to shift the charater change over
        bg->referenceGrid[actualRow][actualCol] = 3; // Update the battle grid to reflect the miss
    }

    // Decrement remaining turns
    (*remainingTurns)--;

    // End the game and reveal all ships when turns run out
    if (*remainingTurns == 0) {
        printf("Game over! Revealing all remaining ships...\n");
        for (int i = 0; i < bg->gameRows; i++) { // Loop through game rows
            for (int j = 0; j < bg->gameCols; j++) { // Loop through game columns
                if (bg->referenceGrid[i][j] == 1) { // If there's still a ship
                    bg->visualGrid[i + 1][j + 1] = 'S'; // Reveal ship on the visual grid, + 1 to change the correct charater 
                }
            }
        }
    }
    /* Purpose: Updates the visual and game grids based on the player's guess. 
    Note---> this feels messy and I may of over complicated things by shifting grid sizes between the test case and visual grid but it seems to work, I do feel if thigs break this is where it may happen
    if we go over grids larger than 7x7*/
}

// Function to Print the visual battle grid
void printGrid(BattleGrid* bg) {
    for (int i = 0; i < bg->visRows; i++) { // Loop through visual grid rows
        for (int j = 0; j < bg->visCols; j++) { // Loop through visual grid columns
            printf("%c ", bg->visualGrid[i][j]); // Print each cell
        }
        printf("\n"); // Move to the next row
    }
    /* Purpose: Prints the visual grid to the console, showing fog - of - war, hits, misses, and headers.
    * Note---> May be the simplest function*/
}
