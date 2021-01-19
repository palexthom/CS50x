// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>

// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Prototypes
bool check(const char *word);
unsigned long hash(const char *word);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
bool insert(node *p);
void print_table();

#endif // DICTIONARY_H
