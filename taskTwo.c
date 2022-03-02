// Import relevant libraries
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define global variables if necessary.
int maxPossibleValue = 1000000, maxPossibleValueDigits = 7, 
    maxValue = 10, minValue = 1;
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

// Define a playGame() function
void playGame()
{
    // Define all relevant local variables
}


// Ask the user to input a number

// Collect and validate user input

// Execute different instructions based on the input value

// If the input value is 'q' --> mark the game as a loss and return

// If the input value is a number, compare it with the correct number

// If the guess is correct, store the game's data, congratulate
// the player, then return.

// If the game is a loss, inform the user and prompt for another guess.



// Define a changeMaxValue() function
void changeMaxValue()
{
    char userNumberInput[maxPossibleValueDigits];
    char currentChar;
    int currentNumDigits = 0, value = 0;

    collect_maxValue_input:
    // Tell the user what the largest value possible is.
    printf("\nPlease input an integer between %d and %d\n", minValue, maxPossibleValue);

    // Collect and validate user input.
    for(currentNumDigits = 0; currentNumDigits < maxPossibleValueDigits; currentNumDigits++)
    {
        currentChar = getchar();
        if(currentChar < '0' || currentChar > '9')
        {
            if(currentChar != '\n' && currentChar != EOF)
            {
                flushBuffer();
                goto maxValue_badInput;
            }
            else if(currentNumDigits == 0) // User enters newline and nothing else
                goto maxValue_badInput;
            else // User enters < 7 digits
                goto maxValue_smallBuffer;
        }
        userNumberInput[currentNumDigits] = currentChar;
    }
    if(flushBuffer() > 0) // More than maxNumberCharacters input
        goto maxValue_badInput;
    maxValue_smallBuffer:

    // Convert from char array to integer
    value = 0;
    for(int i = 0; currentNumDigits > 0; currentNumDigits--, i++)
        value += (int)pow(10, i) * (userNumberInput[currentNumDigits -1] - '0');
    
    // If the number is valid, replace the max value with the user's input.
    if(value < minValue || value > maxPossibleValue)
        goto maxValue_badInput;
    maxValue = value;
    return;

    maxValue_badInput:
    printf("ERROR: Bad value entered. Please try again.\n----------");
    goto collect_maxValue_input;
}

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
        scanf("%c", &userCharInput);
        if (userCharInput == '\n' || flushBuffer() > 0 || (userCharInput != '1' && userCharInput != '2' && userCharInput != '3'))
        {
            printf("ERROR: Please enter exactly 1, 2, or 3.\n"
                    "----------\n");
            goto display_menu;
        }

        // Execute different instructions based on
        // the input value.
        switch(userCharInput)
        {
            // Input value '1' --> execute playGame() function
            case '1':
                playGame();
                goto display_menu;
            // Input value '2' --> execute changeMaxValue() function
            case '2':
                changeMaxValue();
                goto display_menu;
            // Input value '3' --> break from the main game loop and run termination code
            case '3':
                goto terminate_program;
        }  
    }

    // Terminate program
    terminate_program:
    printf("\n\nThank you for playing!\n");
    printf("%s", gameLog);

    return 0;
}