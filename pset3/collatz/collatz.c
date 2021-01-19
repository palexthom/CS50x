#include <math.h>
#include <cs50.h>
#include <stdio.h>

int collatz_func(int n);
int steps = 0;

int main(void)
{
    int argn = get_int("Input :\n");
    int result = collatz_func(argn);
    printf("%i", result);

}

// Solution from the video :
// Return 1 + collatz_func and no need for "steps"

int collatz_func(int n)
{
	// Best case
	if(n == 1)
	{
		return 0;
	}
	// Even recursive case
	else if (n % 2 == 0)
	{
		collatz_func(n / 2);
		steps += 1;
	}
	// Odd recursive case
	else
	{
		collatz_func( 3 * n + 1);
		steps +=1;
	}
	return steps;
}