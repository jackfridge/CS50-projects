#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Get a positive integer from the user for the starting population value
    int n;
    do
    {
        n = get_int("Start size: ");
    }
    while (n < 9);

    //Get a positive integer that is larger than the starting for the ending population value
    int m;
    do
    {
        m = get_int("End size: ");
    }
    while (m < n);

    //Determine number of years to attain target ending population
    int year = 0;

    //If end size is identical to starting size, indicate 0 years
    if (m == n)
    {
        printf("Years: 0\n");
    }
    else
    {
        do
        {
            //Calculate the number of births and deaths
            int birth = n / 3;
            int death = n / 4;

            //Add births and substract deaths for 1 year
            n += birth;
            n -= death;

            //Add 1 year to the counter each time you add births and substract deaths
            year++;
        }
        //Repeat as long as population has not reached target ending population
        while (n < m);

        //Display the number of years it took to get to ending population
        printf("Years: %i\n", year);
    }
}