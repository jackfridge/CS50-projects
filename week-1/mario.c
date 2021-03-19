#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int block = 0;
    do
    {
        //Obtain desired height
        block = get_int("Height: ");
    }

    //Limit input to values 1-8
    while (block < 1 || block > 8);

    int i;
    for (i = 0; i < block; i++)
    {
        //Print spaces before blocks on the left side
        int h;
        for (h = 1; h < block - i; h++)
        {
            printf(" ");
        }

        //Prints blocks on the left side
        int j;
        for (j = 0; j < i + 1; j++)
        {
            printf("#");
        }

        //Add space between left and right sides of pyramid
        printf("  ");

        //Prints blocks on the right side
        int k;
        for (k = 0; k < i + 1; k++)
        {
            printf("#");
        }

        //Add a new line before repeating initial loop to add on the next lower floor of blocks
        printf("\n");
    }
}