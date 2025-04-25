/* this contains all the function definitions for the grid system, if more fuctions are added here make sureto place the prototype in battlegrid.h or things may break.
the header file is important here. there is alot of pointer use here to move data in and out of the functions to main.c 
NOTE---> Variable are initilized in the fuctions not in the beginning of the file, variables and pointes in use are listed below for reference
variable ---> description
bg       ---> pointer
i        --->  integer for row indexing
j        --->   integer for column indexing
testgrid ---> for testing the read fuction
MAX_GAME_ROWS---> defined in header
MAX_GAME_COLS---> defined in header
rowLabels --->  characters for row headers
colLabels --->  charaters for column headers
MAX_VIS_ROWS ---> defined in header
MAX_VIS_COLs ---> defined in header
actualRow ---> The variable used to shift index placement between the reference grid and visual grid 
actualCol ---> Same as above but just for columns (sorry in advance if these are confusing names because of the rowGuess and colGuess within main.c)
*/


#define _CRT_SECURE_NO_WARNINGS // Do not remove, it makes my life easy :3
#include <stdio.h> 
#include "battlegrid.h" // Include the header file for battlegrid structure and function prototypes


void readGrid(BattleGrid* bg, int testGrid[MAX_GAME_ROWS][MAX_GAME_COLS]) {// Initializing the core function to read generated grids (ships, hits, misses) currently using test grid in main.c
    bg->remainingShips = 0;  // Start by setting the number of ships to 0
    bg->maxTurns = 10;       // Set the maximum number of turns allowed ------> this can be changed or pulled from main instead, placed here for testing 

    // Copying the test grid into the reference grid and count ships
    for (int i = 0; i < bg->gameRows; i++) { // Loop through the game rows
        for (int j = 0; j < bg->gameCols; j++) { // Loop through the game columns
            bg->referenceGrid[i][j] = testGrid[i][j]; // Copy each cell value from testGrid
            if (testGrid[i][j] == 1) { // Check if the cell contains a ship (value 1)
                bg->remainingShips++;  // adding to ship value--->  this will have to be adjusted, right now the fuction sees every 1 as a ship, not that every ship has a size
            }
        }
    }
    /* Purpose: Sets up the game logic grid with ships, hits, and misses from test grid.This should be able to be modified to work with the proper grid generation
    * NOTE---> Still have to figure out ship size, as is every instace of 1 in the grid read counts as it's own ship, Maybe we could use this as a very hard mode with a large grid?
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
    Note---> this array will alway be 1 size bigger to make room for the header, we will have to change quite a few sections of code if we want to gammes bigger than 7x7
    It's possible to add more charaters to display here if we do power ups or other extra features
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
    Note---> this feels messy and I may of over complicated things by shifing grid sizes between the test case and visual grid but it seems to work, I do feel if thigs break this is where it may happen
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