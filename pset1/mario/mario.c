#include <stdio.h>
#include <cs50.h> //neded to use get_string

int main(void)
{
    // User input
    int n;
    do
    {
        n = get_int("Height: ");
    }
    while (n < 1 | n > 8);
    //printf("Stored: %i\n", n);

    // simple Pyramid
    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }*/

    // complex Pyramid
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            printf(" ");
        }
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("  ");
        for (int j = 0; j <= i; j++)
        {
            printf("#");
        }
        printf("\n");
    }
}