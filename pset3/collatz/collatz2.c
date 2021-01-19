#include <math.h>
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

int collatz(int n);

int main(int argc, string argv[])
{
    printf("%i\n", collatz(atoi(argv[1])));
}


int collatz(int n)
{
    // Best case
    if (n == 1)
    {
        return 0;
    }
    // Even recursive case
    else if (n % 2 == 0)
    {
        return 1 + collatz(n / 2);
    }
    // Odd recursive case
    else
    {
        return 1 + collatz(3 * n + 1);
    }
}