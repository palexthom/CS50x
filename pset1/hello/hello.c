#include <stdio.h>
#include <cs50.h> //neded to use get_string

int main(void)
{
    //asking the user's name
    string name = get_string("What is your name?\n");
    //printing hello + input name
    printf("Hello, %s!\n", name);
}