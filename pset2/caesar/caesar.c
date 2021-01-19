#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int shift(char letter, int lettercase, int key);

int main(int argc, string argv[2])
{
    // checking number of arg
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //printf("Arg 0 : %s\n",argv[0]);
    //printf("Arg 1 : %s\n",argv[1]);

    // Check if non decimal digit in argv[1]
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (isdigit(argv[1][i]) == 0)
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }
    }

    // Cast argv[1) into an int
    int k = 0;
    k = atoi(argv[1]);
    if (k == 0)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    //printf("Key : %i\n",k);
    k = k % 26;

    // Get plaintext
    string pt = get_string("plaintext:\t");
    string ct = pt; // ciphertext, initialized to it has the right length

    // Iterate through text
    for (int i = 0; pt[i] != '\0'; i++)
    {
        // printf("Current character: %c\n", pt[i]);
        if (isalpha(pt[i]) == 0)
        {
            ct[i] = pt[i];
        }
        else if (islower(pt[i]) != 0)
        {
            ct[i] = shift(pt[i], 0, k);
        }
        else if (isupper(pt[i]) != 0)
        {
            ct[i] = shift(pt[i], 1, k);
        }
    }

    printf("ciphertext:\t%s\n", ct);
}

int shift(char letter, int lc, int key)
{
    //lc : 0 is lowercase, 1 is uppercase

    int sl = letter + key; // shifted letter

    if (lc == 0 && sl > 122)
    {
        return sl - 26;
    }
    else if (lc == 1 && sl > 90)
    {
        return sl - 26;
    }

    return sl;
}