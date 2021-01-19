#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

bool valid_triangle (float a, float b, float c);

int main(int argc, string argv[3])
{
    printf("%i", valid_triangle(strtof(argv[1], NULL), strtof(argv[2], NULL), strtof(argv[3], NULL)));
}

bool valid_triangle (float a, float b, float c)
{
    // Make sure they are all positive
    if (a <= 0 || b <= 0 || c <= 0)
    {
        return false;
    }

    if (a <= b + c && b <= a + c && c <= a + b)
    {
        return true;
    }
    else
    {
        return false;
    }
}