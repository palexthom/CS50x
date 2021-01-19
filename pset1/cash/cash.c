#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    // User input
    float change;
    do
    {
        change = get_float("Changed owed: ");
    }
    while (change < 0);
    printf("%.2f\n", change);

    // Conversion to cents
    int cents = (int) round(100 * change);
    //printf("Conversion to cents : %i\n", cents);

    // Calculation of coins
    int coins;
    // How many quarters
    coins = cents / 25;
    cents = cents % 25;
    // Wow many dimes
    coins = coins + cents / 10;
    cents = cents % 10;
    // How many nickels
    coins = coins + cents / 5;
    cents = cents % 5;
    // How many pennies
    coins = coins + cents;

    //Printing result
    printf("%i\n", coins);

}

