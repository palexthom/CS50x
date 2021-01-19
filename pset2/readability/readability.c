#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

int count_letters(int length, string text);
int count_words(int length, string text);
int count_sentences(int length, string text);

int main(void)
{
    string text = get_string("Text: ");
    //printf("%s\n", text);*

    // Length of the string
    int length = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        length += 1;
    }
    //printf("Longueur : %i\n", length);

    // Count Letters (a to z, A to Z)
    int letters = count_letters(length, text);
    //printf("Letters : %i\n", letters);

    // Count Words (sequence of char separated by spaces)
    int words = count_words(length, text);
    //printf("Words : %i\n", words);

    // Count sentences (any occurence of ".", "!" or "?")
    int sentences = count_sentences(length, text);
    //printf("Sentences : %i\n", sentences);

    // Calculate index
    float L = ((float) letters / words) * 100;
    float S = ((float) sentences / words) * 100;
    int index = round(0.0588 * L - 0.296 * S - 15.8);

    // Print grade
    // Note to self : wanted to set a msg and print it in the end
    string msg = "";

    if (index <= 1)
    {
        msg = "Before Grade 1\n";
        printf("%s", msg);
    }

    else if (index > 16)
    {
        msg = "Grade 16+\n";
        printf("%s", msg);
    }

    else
        // Note to self : didnt manage to concatenate str and int to make a msg to print
    {
        printf("Grade %i\n", index);
    }
    // printf("%s", msg);
}

int count_letters(int length, string text)
{
    int letters = 0;

    if (length <= 0)
    {
        return 0;
    }

    for (int i = 0; i < length; i++)
    {
        if isalnum(text[i])
        {
            letters += 1;
        }
    }

    return letters;
}

int count_words(int length, string text)
{
    int words = 0;
    if (length <= 0)
    {
        return 0;
    }
    for (int i = 0; i < length; i++)
    {
        if isblank(text[i])
        {
            words += 1;
        }
    }
    return words + 1;
}

int count_sentences(int length, string text)
{
    if (length <= 0)
    {
        return 0;
    }

    int sentences = 0;
    for (int i = 0; i < length; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences += 1;
        }
    }
    return sentences;
}