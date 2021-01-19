#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

/* example of creating a hashtable with integers*/

// First create a hashtable of size xxx
// Then store numbers in the table, and if hash is same, add numbers in a linked list

#define NUM_BUCKETS 10
#define WORD_SIZE 50

typedef struct person{
    char name[WORD_SIZE];
    int age;
    struct person *next;
} person;


// prototypes
unsigned long hash(char *str);
void init_hashtable();
void print_hashtable();
bool insert(person *p);
person *find_hashtable(char *name);


// table of pointers
person *hashtable[50];



int main()
{
    // initializatoin of the table
    init_hashtable();

    // creation of memory nodes
    person pierre = {.name = "Pierre", .age = 256};
    person alexandre = {.name = "PIERRE", .age = 25};
    person thomas = {.name = "PIErre", .age = 32};
    person mark = {.name = "Mark", .age = 32};
    person emily = {.name = "Emily", .age = 32};
    person jason = {.name = "Jason", .age = 32};
    person bernard = {.name = "Bernard", .age = 32};
    person james = {.name = "James", .age = 32};

    // insert nodes
    insert(&pierre);
    insert(&alexandre);
    insert(&thomas);
    insert(&mark);
    insert(&emily);
    insert(&jason);
    insert(&bernard);
    insert(&james);

    // print table
    print_hashtable();

    person *tmp = find_hashtable("Pierre");
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
    // Count word length
    int word_length = 0;
    for(int i = 0; char[i] != '\0'; i++)
    {
        word_length +=1;
    }

    char word_lc[word_length];
    for(int i = 0; i < word_length; i++)
    {
        word_lc[i] = tolower(word[i]);
    }
    word_lc[wordlength]="\0";
    
    
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
            person *tmp = hashtable[i];
            while (tmp != NULL)
            {
                printf("%s - ", tmp->name);
                tmp = tmp -> next;
            }
            printf("\n");
        }

    }
}

bool insert(person *p)
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


person *find_hashtable(char *name)
{
    // find a person in the table
    // returns NULL if not found
    // returns pointer if found

    int index = hash(name);
    person *tmp = hashtable[index];
    while (tmp != NULL && strncmp(tmp->name, name, WORD_SIZE) != 0)
    {
        tmp = tmp->next;
    }
    return tmp;
}

/*bool delete_table()
{
    while (table != NULL)
    {
        node *tmp = list->next;
        free(list);
        list = tmp;
    }
}*/