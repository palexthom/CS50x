#include <stdio.h>
#include <cs50.h>
#include <math.h>

int checksum(long);
int firstDigit(long);
int first2Digits(long);
int nDigits(long);


int main(void)
{
    // USER INPUT
    long card;
    do
    {
        card = get_long("Number: ");
    }
    while (card < 0);

    // CALCULATE CARD LENGHTS AND FIRST DIGITS
    int nd = nDigits(card);
    int fd = firstDigit(card);
    int f2d = first2Digits(card);

    // INVALID CHECKSUM
    if ((checksum(card) % 10) != 0)
    {
        printf("INVALID\n");
    }
    // VISA CARDS
    else if ((fd == 4) && ((nd == 13) || (nd == 16)))
    {
        printf("VISA\n");
    }
    // AMEX CARDS
    else if ((f2d == 34) || (f2d == 37))
    {
        printf("AMEX\n");
    }
    // MASTERCARDS
    else if ((f2d >= 51) && (f2d <= 55))
    {
        printf("MASTERCARD\n");
    }
    // REST IS INVALID
    else
    {
        printf("INVALID\n");
    }
}

// Calculate length of card
int nDigits(long card)
{
    return floor(log10(card)) + 1;
}

// Calculate checksum
int checksum(long card)
{
    int length = nDigits(card);

    // Adding every other digit multiplied by 2
    int even = 0;
    int a = 0;
    for (long i = 10; i < pow(10, length); i *= 100)
    {
        a = 2 * ((int)((card / i) % 10));
        if (a < 10)
        {
            even = even + a;
        }
        else
        {
            even = even + 1 + (a % 10);
        }
    }
    //printf("%i\n", even);

    // Adding digits that weren't multiplied
    int odd = 0;
    for (long i = 1; i < pow(10, length); i *= 100)
    {
        odd = odd + ((int)((card / i) % 10));
    }
    //printf("%i\n", odd);

    // Calculating the checksum
    return even + odd;
    //printf("Checksum : %i\n"
}

// Remember : dividing int or long gives an integer
int firstDigit(long card)
{
    long b = pow(10, nDigits(card) - 1);
    return (card / b) % 10 ;
}


int first2Digits(long card)
{
    long b = pow(10, nDigits(card) - 2);
    return (card / b) % 100 ;
}