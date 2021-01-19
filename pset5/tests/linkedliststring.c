#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

/* creating a single-listed list that stores strings*/

// defining the single listed list node structure
typedef struct sllnode
{
    char *val[50];
    struct sllnode* next;
}
sllnode;

// Prototypes
sllnode* create(char *val); // create list
sllnode* insert(sllnode *head, char *val); // insert a node
bool find(sllnode head, char *val); // search through list


// HAP : do we create a "list" pointer that xould be the head of a list ?
// or is the 1st element already a node ?
// node *list = NULL; then list = n; to point at first element ?

int main()
{
    // Create a linked list using the function create
    char *prenom = "Pierre";
    sllnode *list = create(prenom); // list is a pointer, destination is a node 6/NULL

    // Insert nodes in the list
    prenom = "Alexandre";
    list = insert(list, prenom);
    prenom = "Thomas";
    list = insert(list, prenom);

    // Print list
    printf("Printing list :\n");
    for (sllnode *tmp = list; tmp != NULL; tmp = tmp->next)
    {
        // Within the node, we'll just print the number stored:
        printf("- %s\n", tmp->val[0]);
    }


    // Search
    char *searched = "Baptiste";
    printf("Cherche %s\n", searched);
    bool exists = find(*list, searched);
    printf("Trouvé ? -› %i\n", exists);

    searched = "Alexandre";
    printf("Cherche %s\n", searched);
    exists = find(*list, searched);
    printf("Trouvé ? -› %i\n", exists);

    // Delete an element / the entire list

}

// create a list
sllnode* create(char *val)
{
    // takes an argument, returns a pointer

    // allocate space for a new node
    sllnode *n = malloc(sizeof(sllnode));
    // check we do not run out of memory
    if (n != NULL)
    {
        // initialize val
        n->val[0] = &val[0];
        // initialize next
        n->next = NULL;
    }
    // return pointer
    return n;
}

// search through a linked list to find an element
bool find(sllnode head, char *val)
{
    // takes as parameter head of list and value searched
    // create a traversal pointer (just a pointer, no need to malloc)
    //sllnode *trav = &head;

    for (sllnode *trav = &head; trav != NULL; trav = trav->next)
    {
        printf("Testé : %s\n", trav->val[0]);
        //printf("Next : %i\n", trav->next->val);
        if (trav->val[0] == val)
        {
            return true;
        }
    }
    return false;
}

sllnode* insert(sllnode* head, char *val)
{
    // insert val in head list, returns pointer

    // allocate memory
    sllnode *n = malloc(sizeof(sllnode));

    // check we do not run out of memory
    if (n != NULL)
    {
        // Setting val
        n->val[0] = &val[0];
        // Setting next
        n->next = head;
    }
    // return pointer
    return n;
}