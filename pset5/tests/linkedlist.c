#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* example of creating a single-listed list*/

// defining the single listed list node structure
typedef struct sllnode
{
    int val;
    struct sllnode* next;
}
sllnode;

// Prototypes
sllnode* create(int val); // create list
sllnode* insert(sllnode *head, int val); // insert a node
bool find(sllnode head, int val); // search through list


// HAP : do we create a "list" pointer that xould be the head of a list ?
// or is the 1st element already a node ?
// node *list = NULL; then list = n; to point at first element ?

int main()
{
    // Create a linked list using the function create
    sllnode *list = create(6); // list is a pointer, destination is a node 6/NULL

    // Insert nodes in the list
    list = insert(list, 8);
    list = insert(list, 13);
    list = insert(list, 14);
    list = insert(list, 15);


    // Print list
    printf("Printing list :\n");
    for (sllnode *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        // Within the node, we'll just print the number stored:
        printf("- %i\n", tmp->val);
    }


    // Search
    int searched = 5;
    printf("Cherche %i\n", searched);
    bool exists = find(*list, searched);
    printf("Trouvé ? -› %i\n", exists);

    searched = 8;
    printf("Cherche %i\n", searched);
    exists = find(*list, searched);
    printf("Trouvé ? -› %i\n", exists);

    // Delete an element / the entire list

}

// create a list
sllnode* create(int val)
{
    // takes an argument, returns a pointer

    // allocate space for a new node
    sllnode *n = malloc(sizeof(sllnode));
    // check we do not run out of memory
    if (n != NULL)
    {
        // initialize val
        n->val = val;
        // initialize next
        n->next = NULL;
    }
    // return pointer
    return n;
}

// search through a linked list to find an element
bool find(sllnode head, int val)
{
    // takes as parameter head of list and value searched
    // create a traversal pointer (just a pointer, no need to malloc)
    //sllnode *trav = &head;

    for (sllnode *trav = &head; trav != NULL; trav = trav->next)
    {
        printf("Testé : %i\n", trav->val);
        //printf("Next : %i\n", trav->next->val);
        if (trav->val == val)
        {
            return true;
        }
    }
    return false;
}

sllnode* insert(sllnode* head, int val)
{
    // insert val in head list, returns pointer

    // allocate memory
    sllnode *n = malloc(sizeof(sllnode));

    // check we do not run out of memory
    if (n != NULL)
    {
        // Setting val
        n->val = val;
        // Setting next
        n->next = head;
    }
    // return pointer
    return n;
}