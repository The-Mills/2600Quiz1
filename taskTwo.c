// Import relevant libraries
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define global variables if necessary.
unsigned int maxValue = 10;
int userNumberInput;
char gameLog[] = "Game Log:\n";

// A helper function that consumes all extra input characters from stdin.
// Returns a value > 0 if there were extra characters in the buffer, else 0.
int flushBuffer()
{
    int currentChar, numberDuplicates = 0;
    while ((currentChar = getchar()) != '\n' && currentChar != EOF)
        ++numberDuplicates;
    return numberDuplicates;
}

// Define a changeMaxValue() function

// Tell the user what the largest value possible is.

// Collect and validate user input.

// If the number is valid, replace the max value with the user's input.


// Define a main function
int main()
{
    // Define all variables that will be used throughout the program.
    char userCharInput;

    // Place the game in an infinite loop
    while (1)
    { 
        // Display menu
        display_menu:
        printf("Press 1 to play a game\n"
               "Press 2 to change the max number\n"
               "Press 3 to quit\n");

        // Collect and validate user input, flushing buffer after the first character.
        scanf(" %c", &userCharInput);
        if (flushBuffer() > 0 || (userCharInput != '1' && userCharInput != '2' && userCharInput != '3'))
        {
            printf("ERROR: Please enter exactly 1, 2, or 3.\n"
                    "----------\n");
            goto display_menu;
        }

        // Execute different instructions based on
        // the input value.
        switch(userCharInput)
        {
            case '1': case '2':
                break;
            case '3':
                goto terminate_program;
        }

        // Input value '1' --> execute playGame() function
        // Input value '2' --> execute changeMaxValue() function
        // Input value '3' --> break from the main game loop and run termination code
    }

    // Terminate program
    terminate_program:
    printf("\n\nThank you for playing!\n");
    printf("%s", gameLog);

    return 0;
}

// Define a playGame() function

// Define all relevant local variables

// Ask the user to input a number

// Collect and validate user input

// Execute different instructions based on the input value

// If the input value is 'q' --> mark the game as a loss and return

// If the input value is a number, compare it with the correct number

// If the guess is correct, store the game's data, congratulate
// the player, then return.

// If the game is a loss, inform the user and prompt for another guess.


