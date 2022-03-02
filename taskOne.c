// Import relevant libraries
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Define a main method with a header such that two parameters are accepted.
int main (int argc, char *argv[])
{
    // Define all variables used throughout the program.
    double taxPercent, taxAmount, tipPercent, tipAmount, totalBill;
    int mealNumber;
    char *mealNames[4] = {"Salad", "Soup", "Sandwich", "Pizza"};
    double mealPrices[4] = {9.95, 4.55, 13.25, 22.35}; 

    // Validate that the correct number and types of command line arguments
    // have been passed into main. Terminate with an error if user input is bad.
    if(argc != 3)
    {
       printf("ERROR: Invalid number of parameters. Please enter the tax as a"
       " percentage, followed by the tip as a percentage.");
       goto terminate_program;
    }
    taxPercent = atof(argv[1]);
    tipPercent = atof(argv[2]);
    if(taxPercent <= 0 || tipPercent <= 0)
    {
        printf("ERROR: Bad parameter values. Please enter the tax as a"
         " percentage, followed by the tip as a percentage. Both values"
         " must be greater than 0.");
        goto terminate_program;
    }

    // Generate a random integer in [0, 3] to determine meal choice. Seeds the 
    // random number generator using system time.
    time_t currentTime;
    time(&currentTime);
    srand((unsigned) currentTime);
    mealNumber = rand() % 4;

    // Calculate the tax amount, tip amount, and total bill.
    taxAmount = roundf(taxPercent / 100 * mealPrices[mealNumber] * 100) / 100;
    tipAmount = roundf(tipPercent / 100 * mealPrices[mealNumber] * 100) / 100;
    totalBill = taxAmount + tipAmount + mealPrices[mealNumber];

    // Output all information to the terminal.
    printf("Food Bill: \n-----\n");
    printf("%s - $%.2f\n", mealNames[mealNumber], mealPrices[mealNumber]);
    printf("Tax        - $%.2f\n", taxAmount);
    printf("Tip        - $%.2f\n-----\n", tipAmount);
    printf("Total Bill - $%.2f\n", totalBill);

    // Terminate program.
    terminate_program:
    return 0;
}