#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* example of creating a hashtable with integers*/

// First create a hashtable of size xxx
// Then store numbers in the table, and if hash is same, add numbers in a linked list

#define NUM_BUCKETS 10
#define WORD_SIZE 45

typedef struct word{
    char name[WORD_SIZE];
    int age;
    struct word *next;
} word;


// prototypes
unsigned long hash(char *str);
void init_hashtable();
void print_hashtable();
bool insert(word *w);
word *find_hashtable(char *name);


// table of pointers
word *hashtable[NUM_BUCKETS];

int main()
{
    init_hashtable();

    word pierre = {.name = "Pierre", .age = 256};
    word alexandre = {.name = "Alexandre", .age = 25};
    word thomas = {.name = "Thomas", .age = 32};
    word mark = {.name = "Mark", .age = 32};
    word emily = {.name = "Emily", .age = 32};
    word jason = {.name = "Jason", .age = 32};
    word bernard = {.name = "Bernard", .age = 32};
    word james = {.name = "James", .age = 32};

    insert(&pierre);
    insert(&alexandre);
    insert(&thomas);
    insert(&mark);
    insert(&emily);
    insert(&jason);
    insert(&bernard);
    insert(&james);

    print_hashtable();

    word *tmp = find_hashtable("Pierre");
    if (tmp == NULL)
    {
        printf("Not found\n");
    }
    else
    {
        printf("Found\n");
    }

    tmp = find_hashtable("Baptiste");
    if (tmp == NULL)
    {
        printf("Not found\n");
    }
    else
    {
        printf("Found\n");
    }

}


unsigned long hash(char *str)
{
    unsigned long hash = 5381;
    int c;
    while ((c = *str++))
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    return hash % NUM_BUCKETS;
}

void init_hashtable()
{
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        hashtable[i] = NULL;
    }
}

void print_hashtable()
{
    for (int i = 0; i < NUM_BUCKETS; i++)
    {
        if (hashtable[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t", i);
            word *tmp = hashtable[i];
            while (tmp != NULL)
            {
                printf("%s - ", tmp->name);
                tmp = tmp -> next;
            }
            printf("\n");
        }

    }
}

bool insert(word *p)
{
    // if pointer not null, insert in linked list
    if (p == NULL)
    {
        return false;
    }
    unsigned long index = hash(p->name);
    p->next = hashtable[index]; // p becomes head of list
    hashtable[index] = p;
    return true;
}

word *find_hashtable(char *name)
{
    // find a word in the table
    // returns NULL if not found
    // returns pointer if found

    int index = hash(name);
    word *tmp = hashtable[index];
    while (tmp != NULL && strncmp(tmp->name, name, WORD_SIZE) != 0)
    {
        tmp = tmp->next;
    }
    return tmp;
}