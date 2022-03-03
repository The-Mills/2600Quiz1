// Import relevant libraries
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Define global variables if necessary.
int maxPossibleValue = 1000000, maxPossibleValueDigits = 7, 
    maxValue = 10, minValue = 1, gamesPlayed = 0;
int guessesPerGame[9999]; // 10000 games before buffer overflow

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
    gamesPlayed++;

    // Define all relevant local variables
    char currentCharInput;
    char userNumberInput[maxPossibleValueDigits];
    int numberGuesses = 0, currentNumDigits = 0, value = 0,
    correctNumber = rand() % (maxValue - minValue + 1) + minValue;

    // Place the game into a second infinite loop.
    while(1)
    {
        // Ask the user to input a number
        game_promptInput:
        printf("\nPlease enter a number between %d and %d," 
            " inclusive or 'q' to quit: ", minValue, maxValue);
        
        // Reset variables used in the user input loop
        currentNumDigits = 0;
        value = 0;
        // Collect and validate user input
        currentCharInput = getchar();
        if(currentCharInput == '\n' || currentCharInput == EOF) // Case 1 - Only enters newline
            goto game_badInput;
        else if(currentCharInput == 'q' || currentCharInput == 'Q') // Case 2 - Player quits
        {
            if(flushBuffer() > 0)
                goto game_badInput;
            else
                // The player's Q input has been fully verified as legal. Continue to
                // next part of the program.
                goto game_quitInput;
        }
        else if (currentCharInput >= '0' && currentCharInput <= '9') // Case 3 - Enters number
        {
            userNumberInput[currentNumDigits++] = currentCharInput;

            for(currentNumDigits; currentNumDigits < maxPossibleValueDigits; currentNumDigits++)
            {
                currentCharInput = getchar();
                if(currentCharInput < '0' || currentCharInput > '9')
                {
                    if(currentCharInput != '\n' && currentCharInput != EOF)
                    {
                        flushBuffer();
                        goto game_badInput;
                    }
                    else
                        goto game_numberInput_smallBuffer;
                }
                userNumberInput[currentNumDigits] = currentCharInput;
            }
            if(flushBuffer() > 0) // More than maxPossibleValueDigits input
                goto game_badInput;
            game_numberInput_smallBuffer:

            // Convert to integer from char array.
            for(int i = 0; currentNumDigits > 0; currentNumDigits--, i++)
                value += (int)pow(10, i) * (userNumberInput[currentNumDigits -1] - '0');
            
            // Verify input is between the current maximum and minimum values.
            if(value < minValue || value > maxValue)
                goto game_badInput;
            
            // Integer input has now been fully verified as legal. Continue to next
            // part of the program.
            goto game_goodIntegerInput;
        }
        else // Case 4 - All other bad inputs
        {
            flushBuffer();
            goto game_badInput;
        }

        game_badInput:
        printf("ERROR: Bad value entered. Please try again.\n");
        goto game_promptInput;


        // If the input value is a number, compare it with the correct number
        game_goodIntegerInput:
        numberGuesses++;
        // If the guess is correct, store the game's data, congratulate
        // the player, then return.
        if(value == correctNumber)
        {
            printf("You guessed correctly after %d guesses!" 
                " Congratulations!\n----------\n", numberGuesses);
            guessesPerGame[gamesPlayed] = numberGuesses;
            return;
        }
        // If the game is a loss, inform the user and prompt for another guess.
        else
        {
            if(value < correctNumber)
                printf("You guessed too low! Try again!");
            else
                printf("You guessed too high! Try again!");
            goto game_promptInput;
        }

        // If the input value is 'q' --> mark the game as a loss and return
        game_quitInput:
        printf("You forfetied the game after %d guesses!"
            " The correct value was %d\n----------\n", numberGuesses, correctNumber);
        guessesPerGame[gamesPlayed] = -1;
        return;
    }
    
}

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
    if(flushBuffer() > 0) // More than maxPossibleValueDigits input
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
    // Seed random number generator
    time_t currentTime;
    time(&currentTime);
    srand((unsigned) currentTime);
    
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
        if (userCharInput == '\n' || userCharInput == EOF || flushBuffer() > 0 
        || (userCharInput != '1' && userCharInput != '2' && userCharInput != '3'))
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
    for(int i = 1; i <= gamesPlayed; i++)
    {
        if(guessesPerGame[i] == -1)
            printf("Game #%d - You forfeited and lost this game!\n", i);
        else
            printf("Game #%d - You won after %d guesses!\n", i, guessesPerGame[i]);
    }
    return 0;
}