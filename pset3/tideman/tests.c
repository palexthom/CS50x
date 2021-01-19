#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

#define MAX 4

int check(int win, int lose, int init_win);
bool locked[MAX][MAX];

int main (int argc, string argv[2])
{
    if (argc < 2)
    {
        printf("Usage : ./tests [testcase value]");
    }

    int x = atoi(argv[1]);

    // initialization to false
    for (int i = 0; i < MAX; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            locked[i][j] = false;
        }

    }
    // set a couple values True
    switch(x)
    {
        case 0:
            locked[0][1] = true;
            printf("Cas 0 : %i\n", check(0,1,0));
            break;
        case 1:
            locked[0][1] = true;
            locked[2][3] = true;
            printf("Cas 1 : %i\n", check(2,3,2));
            break;
        case 2:
            locked[0][1] = true;
            locked[2][3] = true;
            locked[0][2] = true;
            printf("Cas 2 : %i\n", check(0,2,0));
            break;
        case 3:
            locked[0][1] = true;
            locked[2][3] = true;
            locked[0][2] = true;
            locked[3][0] = true;
            printf("Cas 3 : %i\n", check(3,0,3));
        case 4:
            locked[0][2] = true;
            locked[2][3] = true;
            locked[3][0] = true;
            printf("Cas 4 : %i\n", check(3,0,3));
    }

}

int check(int win, int lose, int init_win)
{
    int res = -1;
    printf("Init win : %i\n", init_win);
    printf("win: %i ; lose: %i\n",win, lose);
    for (int i = 0; i < MAX; i++)
    {
        printf("line: %i ; col: %i ; locked : %i\n",lose, i, locked[lose][i]);
        if (locked[lose][i] == true)
        {
            printf("true\n");
            if (lose != init_win)
            {
                printf("Not looping\n");
                res = check(lose, i, init_win);
            }
            else
            {
                printf("Looping, time to stop");
                res = 0;
            }

        }
        else
        {
            printf("false\n");
        }
    }
    printf("Returning res %i\n",res);
    return res;
}