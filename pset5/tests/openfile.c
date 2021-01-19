#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>


int main()
{
   // Open and read dictionary file
    char str[45];
    char* filename = "../speller/dictionaries/medium";
    FILE *file = fopen(filename, "r");
    if (file == NULL)
    {
        printf("Could not open file %s",filename);
        return 1;
    }

    // Read each line/word with fgets and print it
    /*while (fgets(str, 50, file) != NULL)
        printf("%s", str);
    fclose(file);*/

    // Read each line/word with fscand anf print it
    char word[45];
    while (fscanf(file, "%s", word) != EOF)
        printf("%s\n", word);
    fclose(file);
}