#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
int score_match(int pair_index);
int sum_line(int index);
int sum_column(int index);
int check(int win, int lose, int init_win);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i], name) == 0)
        {
            ranks[rank] = i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
// Update preference[][] table
// Reçoit en argument un tableau avec les indices des candidats dans l'ordre de vote
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            preferences[ranks[i]][ranks[j]] += 1;
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = i + 1; j < candidate_count; j++)
        {
            if (preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count += 1;
            }
            else if (preferences[i][j] < preferences[j][i])
            {
                pairs[pair_count].winner = j;
                pairs[pair_count].loser = i;
                pair_count += 1;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // Max pair # = MAX (MAX-1) / 2 = 36
    // Sort algo doesn't matter much, chosing selection sort

    for (int i = 0; i < pair_count; i++)
    {
        int strength = 0;
        int index_max = 0;
        pair current_match = pairs[i];

        for (int j = i; j < pair_count; j++)
        {
            int score = score_match(j);
            if (score > strength)
            {
                strength = score;
                index_max = j;
            }
        }
        //swap
        pairs[i] = pairs[index_max];
        pairs[index_max] = current_match;
    }

    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
// not creating circles = can't have true in i's line and i's column
{
    for (int i = 0; i < pair_count; i++)
    {
        locked[pairs[i].winner][pairs[i].loser] = true;

        if (check(pairs[i].winner, pairs[i].loser, pairs[i].winner) == 0)
        {
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    return;
}

// Print the winner of the election
void print_winner(void)
// Winner doesn't have any arrow pointing at them : column without ones
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (sum_column(i) == 0)
        {
            printf("%s\n", candidates[i]);
            return;
        }
    }
}


// HELPER FUNCTIONS

int score_match(int pair_index)
{
    int score_win = preferences[pairs[pair_index].winner][pairs[pair_index].loser];
    int score_lose = preferences[pairs[pair_index].loser][pairs[pair_index].winner];
    return score_win - score_lose;
}


int sum_line(int index)
{
    int sum = 0;
    for (int i = 0; i < MAX; i++)
    {
        sum = sum + locked[index][i];
    }
    return sum;
}

int sum_column(int index)
{
    int sum = 0;
    for (int i = 0; i < MAX; i++)
    {
        sum = sum + locked[i][index];
    }
    return sum;
}

int check(int win, int lose, int init_win)
{
    int res = -1;
    //printf("Init win : %i\n", init_win);
    //printf("win: %i ; lose: %i\n",win, lose);
    for (int i = 0; i < MAX; i++)
    {
        //printf("line: %i ; col: %i ; locked : %i\n",lose, i, locked[lose][i]);
        if (locked[lose][i] == true)
        {
            //printf("true\n");
            if (lose != init_win)
            {
                //printf("Not looping\n");
                res = check(lose, i, init_win);
            }
            else
            {
                //printf("Looping, time to stop");
                res = 0;
            }

        }
        else
        {
            //printf("false\n");
        }
    }
    //printf("Returning res %i\n",res);
    return res;
}