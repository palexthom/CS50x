#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int index_letter(char letter);
int case_letter(char letter);
int shift(char letter, int lc, int key);

int main(int argc, string argv[2])
{
    // checking number of arg
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    // checking if non alpha caracter in argv[1]
    int length_key = 0;
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        length_key += 1;
        if (isalpha(argv[1][i]) == 0)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }
    // checking length of key
    if (length_key != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    // transforming key into indexes
    char base_key[26];
    char shift_keys[26];
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        base_key[i] = index_letter(argv[1][i]);
    }
    // looking for duplicate characters
    // actually making sure I have each caracter once
    for (int i = 0; i < 26; i++)
    {
        bool found = false;
        for (int j = 0; j < 26; j++)
        {
            if (i + 1 == base_key[j])
            {
                found = true;
            }
        }
        if (!found)
        {
            printf("Usage: ./substitution key\n");
            return 1;
        }
    }

    // Transforming key into shift indexes
    for (int i = 0; i < 26; i++)
    {
        shift_keys[i] = base_key[i] - (i + 1);
        if (shift_keys[i] < 0)
        {
            shift_keys[i] = shift_keys[i] + 26;
        }
        // printf("%i\t%i\t%i\n",argv[1][i],base_key[i], shift_keys[i]);
    }

    // Get plaintext
    string pt = get_string("plaintext:\t");
    string ct = pt; // ciphertext, initialized to it has the right length

    // transforming plaintext to ciphertext
    for (int i = 0; pt[i] != '\0'; i++)
    {
        ct[i] = shift(pt[i], case_letter(pt[i]), shift_keys[index_letter(pt[i]) - 1]);
    }
    printf("ciphertext:\t%s\n", ct);
}


int index_letter(char letter)
{
    int cl = case_letter(letter);
    if (cl == 0)
    {
        return (letter - 64 - 32);
    }
    else if (cl == 1)
    {
        return (letter - 64);
    }
    return -1;
}

int case_letter(char letter)
{
    if (islower(letter) != 0)
    {
        return 0;
    }
    else if (isupper(letter) != 0)
    {
        return 1;
    }
    return -1;
}

int shift(char letter, int lc, int key)
{
    //lc : 0 is lowercase, 1 is uppercase

    int sl = letter + key; // shifted letter

    if (lc == 0 && sl > 122)
    {
        return (sl - 26);
    }
    else if (lc == 1 && sl > 90)
    {
        return (sl - 26);
    }

    return sl;
}