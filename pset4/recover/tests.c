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

    char *sourcefile = malloc(strlen(argv[1]));
    for (int i = 0, n = strlen(argv[1]); i < n + 1; i++)
    {
        sourcefile[i] = argv[1][i];
    }

    printf("sourcefile : %s\n", sourcefile);

    int foo = 257895;
    unsigned char* p = (unsigned char*)&foo;
    printf("first byte : %0x\n", *p); // outputs the first byte of `foo`
    printf("Second byte : %x\n", p[1]); // outputs the second byte of `foo`

    // s i sa box pointing to a unnammed box containing the first char of my string
    // the box named s contains an hex value that is the address where that first char is stored
    char *s = "Chaine de caract";
    printf("Print first char : %c\n", *s);
    printf("Print string : %s\n", s);
    printf("Print pointer : %p\n", s);




}