#include <stdio.h>
#include <cs50.h>
#include <ctype.h>

int main(void)
{
    // with cs50 :
    //string s = "EMMA";
    //printf("%s\n", s);

    // without CS50 :
    char *s = "EMMA";

    // Printing the whole string
    printf("Printing string : %s\n", s);

    // Printing the pointer
    printf("Printing pointer : %p\n", s);

    // Printing the first character
    printf("Printing 1st char : %c\n", s[0]);

    // Printing the address of the 1st character
    printf("Printing address of 1st char : %p\n", &s[0]);

    // Fixed length char :
    char *string[50];
    *string = "Longue chaine de moins de 50 caract";
    printf("Printing long string : %s\n", *string);

    // Changing name
    s = "PIERRE";
    printf("Printing new string : %s\n", s);

    // ToLowercase
    s = "PIERRE";
    int word_length = 0;
    for(int i = 0; s[i] != '\0'; i++)
    {
        word_length +=1;
    }
    printf("Longueur = %i\n",word_length);
    char ss[word_length];
    for(int i = 0; i < word_length; i++)
    {
        ss[i] = tolower(s[i]);
    }
    printf("%s\n",ss);

}

