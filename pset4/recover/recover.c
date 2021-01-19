#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char *argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: ./recover [filename]\n");
        return 1;
    }

    // Read the filename
    // *sourcefile : a box containing a link to a box containing a char
    // malloc makes sure we have room in the heap for the length of the input file
    char *sourcefile = malloc(strlen(argv[1]));
    for (int i = 0, n = strlen(argv[1]); i < n + 1; i++)
    {
        sourcefile[i] = argv[1][i];
    }
    // printf("sourcefile : %s\n", sourcefile);

    // Create pointer to a file
    // "File" is a box, containing the address where file is
    FILE *file = fopen(sourcefile, "r");

    // If file not found, inform  user
    if (file == NULL)
    {
        printf("Usage: ./recover [filename]\n");
        return 1;
    }

    // Create a JPEG file


    // Read file in a buffer
    unsigned char buffer[512]; // buffer we'll use, stores 512 bytes
    int count = -1;
    char *filename = malloc(8);
    FILE *img = NULL;

    while (fread(buffer, sizeof(char) * 8, 64, file))
    {
        // printf("%0x\n", buffer[0]);
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            count += 1; // counts files
            // first file : create and write
            if (count == 0)
            {
                sprintf(filename, "%03i.jpg", count); // creates name
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(char) * 8, 64, img);
            }

            //Other files : close / open / write
            else
            {
                fclose(img);
                sprintf(filename, "%03i.jpg", count); // creates name
                img = fopen(filename, "w");
                fwrite(buffer, sizeof(char) * 8, 64, img);
            }
        }
        else if (count != -1)
        {
            // keep writing in same file

            fwrite(buffer, sizeof(char) * 8, 64, img);
            //printf("Perdu\n");
        }
    }

    // printf("Number of pics : %i\n", count);
    free(sourcefile);

}

// TODO : check for memory leaks