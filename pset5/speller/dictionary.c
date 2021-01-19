// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <ctype.h>

#include "dictionary.h"



// Number of buckets in hash table
const unsigned int N = 1000;

// Hash table
node *table[N];

unsigned long dict_size;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // Convert to lowercase before hashing
    int word_length = 0;
    for(int i = 0; word[i] != '\0'; i++)
    {
        word_length +=1;
    }
    // printf("Longueur = %i\n",word_length);
    char ss[word_length+1];
    for(int i = 0; i < word_length; i++)
    {
        ss[i] = tolower(word[i]);
    }
    ss[word_length]= '\0';

    unsigned long index = hash(ss);
    node *tmp = table[index];
    while (tmp->next !=NULL)
    {
        // printf("Mot dans la liste-> %s\n",tmp->word);
        if (strcasecmp(tmp->word,word) == 0)
        {
            return true;
        }
        else
        tmp = tmp->next;
    }
    // last case
    if (strcasecmp(tmp->word,word) == 0)
    {
        return true;
    }
    return false;
}

// Hashes word to a number
unsigned long hash(const char *word)
{
    unsigned int hash = 5381;
    int c;
    while ((c = *word++))
    {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    //printf("Resultat HASH -> %i\n", hash % N);
    return hash % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open dictionary file and check if NULL
    char str[45];
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not open file %s",dictionary);
        return false;
    }

    // Read strings one at a time
    char mot[LENGTH];
    while (fscanf(file, "%s", mot) != EOF)
        {
            // Create temp pointer and allocate heap
            node *tmp = malloc(sizeof(node));
            // Copy value to the node
            strcpy(tmp->word, mot);
            // Insert in hashtable
            insert (tmp);
            dict_size+=1;
        }
    // Close dictionary file
    fclose(file);

    // print_table();

    // Return True when done
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dict_size;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *tmp = table[i];
        while (tmp != NULL)
        {
            node *tmpp = tmp->next;
            free(tmp);
            tmp = tmpp;
        }
    }
    return true;
}


bool insert(node *n)
{
    // if pointer not null, insert in linked list
    if (n == NULL)
    {
        return false;
    }

    unsigned long index = hash(n->word);
    n->next = table[index]; // p becomes head of list
    table[index] = n;
    return true;
}

    // Print table, just to check if its ok
void print_table()
{
    /*for (int i = 0; i < N; i++)
    {
        if (table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t", i);
            node *tmp = table[i];
            while (tmp != NULL)
            {
                printf("%s - ", tmp->word);
                tmp = tmp -> next;
            }
            printf("\n");
        }

    }*/

    int i = 890;
    printf("\t%i\t", i);
        node *tmp = table[i];
        while (tmp != NULL)
        {
            printf("%s - ", tmp->word);
            tmp = tmp -> next;
        }
        printf("\n");
}