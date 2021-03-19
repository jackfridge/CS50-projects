#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    float cash;
    //Ask positive amount of money
    do
    {
        cash = get_float("Change owed: ");
    }
    while (cash < 0);

    //Convert amount to cents, rounded
    int cents = round(cash * 100);

    //Substract 25 cents until less than 25 cents remain
    int i;
    int coins = 0;
    for (i = 0; cents > 24; i++)
    {
        cents -= 25;

        //Each for loop adds 1 coin to the total amount
        coins++;
    }

    //Substract 10 cents until less than 10 cents remain
    int j;
    for (j = 0; cents > 9; j++)
    {
        cents -= 10;
        coins++;
    }

    //Substract 5 cents until less than 5 cents remain
    int k;
    for (k = 0; cents > 4; k++)
    {
        cents -= 5;
        coins++;
    }

    //Substract 1 cent until less than 1 cent remains
    int l;
    for (l = 0; cents > 0; l++)
    {
        cents -= 1;
        coins++;
    }

    //Display total amount of coins counted
    printf("%i\n", coins);
}
