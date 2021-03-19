#include <stdio.h>
#include <cs50.h>

int main(void)
{
    //Ask for credit card number
    long credit = get_long("Number: ");

    //Count the number of digits
    int digits = 0;
    long digit_check = credit;
    while (digit_check > 0)
    {
        digit_check /= 10;
        digits++;
    }

    //Verify if 15 digit corresponds to correct AMEX digits
    if (digits == 15)
    {
        //Obtain first 2 digits
        long n15_check = credit;
        for (int i = 0; i < 13; i++)
        {
            n15_check /= 10;
        }

        //Match first digits to known AMEX digits
        if (n15_check == 34 || n15_check == 37)
        {
            long checksum = credit * 10;
            int sum_1 = 0;
            int sum_2 = 0;

            //Obtain and add every 2 digits 8 times, until all 15 digits are covered
            for (int i = 0; i < 8; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;
                temp *= 2;

                //If a sum is 10 or over, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_1 += temp;
                }
                else
                {
                    sum_1 += temp;
                }
            }

            //Add every 2 digits, not covered by previous for loop
            checksum = credit * 100;
            for (int i = 0; i < 8; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;

                //If a sum is 10 or over, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_2 += temp;
                }
                else
                {
                    sum_2 += temp;
                }
            }

            int tot_sum = sum_1 + sum_2;

            //Verify if last digit is 0 to validate checksum
            tot_sum %= 10;
            if (tot_sum == 0)
            {
                printf("AMEX\n");
            }

            else
            {
                printf("INVALID\n");
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }

    //Verify if number corresponds to MasterCard or one of the VISA digits
    else if (digits == 16)
    {
        //Obtain the first two digits
        long n16_check = credit;
        for (int i = 0; i < 14; i++)
        {
            n16_check /= 10;
        }

        //Match first digits to known MASTERCARD digits
        if (n16_check == 51 || n16_check == 52 || n16_check == 53 || n16_check == 54 || n16_check == 55)
        {
            long checksum = credit * 10;
            int sum_1 = 0;
            int sum_2 = 0;

            //Obtain every 2 digits 8 times, to cover all 16 digits
            for (int i = 0; i < 8; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;
                temp *= 2;

                //If a sum is 10 or over, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_1 += temp;
                }
                else
                {
                    sum_1 += temp;
                }
            }

            checksum = credit * 100;

            //Obtain every 2 digits 8 times, unused by previous for loop
            for (int i = 0; i < 8; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;

                //If a sum is 10 or over, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_2 += temp;
                }
                else
                {
                    sum_2 += temp;
                }
            }

            int tot_sum = sum_1 + sum_2;

            //Verify if last digit is 0 to validate checksum
            tot_sum %= 10;
            if (tot_sum == 0)
            {
                printf("MASTERCARD\n");
            }

            else
            {
                printf("INVALID\n");
            }
        }

        //Obtain first digit of number (to verify VISA)
        else if (n16_check / 10 == 4)
        {
            long checksum = credit * 10;
            int sum_1 = 0;
            int sum_2 = 0;

            //Obtain every 2 digits 8 times, until all 16 digits are passed
            for (int i = 0; i < 8; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;
                temp *= 2;

                //If a sum is 10 or over, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_1 += temp;
                }
                else
                {
                    sum_1 += temp;
                }
            }

            //Obtain every 2 digits 8 times, unused by previous for loop
            checksum = credit * 100;
            for (int i = 0; i < 8; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;

                //If a sum is 10 or over, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_2 += temp;
                }
                else
                {
                    sum_2 += temp;
                }
            }

            int tot_sum = sum_1 + sum_2;

            //Verify if last digit is 0 to validate checksum
            tot_sum %= 10;
            if (tot_sum == 0)
            {
                printf("VISA\n");
            }

            else
            {
                printf("INVALID\n");
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }

    //Verify the second possibility for VISA digits
    else if (digits == 13)
    {
        //Obtain first 2 digits
        long n13_check = credit;
        for (int i = 0; i < 12; i++)
        {
            n13_check /= 10;
        }

        //Match first digits to known VISA digits
        if (n13_check == 4)
        {
            long checksum = credit * 10;
            int sum_1 = 0;
            int sum_2 = 0;

            //Obtain every 2 digits 6 times, until 13 digits are passed
            for (int i = 0; i < 6; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;
                temp *= 2;

                //If a sum is 10 or more, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_1 += temp;
                }
                else
                {
                    sum_1 += temp;
                }
            }

            //Obtain every 2 digits 7 times, unused by previous for loop
            checksum = credit * 100;
            for (int i = 0; i < 7; i++)
            {
                checksum /= 100;
                int temp = checksum % 10;

                //If a sum is 10 or more, add the 2 separate digits
                if (temp > 9)
                {
                    int temp1 = temp / 10;
                    int temp2 = temp % 10;
                    temp = temp1 + temp2;

                    sum_2 += temp;
                }
                else
                {
                    sum_2 += temp;
                }
            }

            int tot_sum = sum_1 + sum_2;

            //Verify if last digit is 0 to validate checksum
            tot_sum %= 10;
            if (tot_sum == 0)
            {
                printf("VISA\n");
            }

            else
            {
                printf("INVALID\n");
            }
        }

        else
        {
            printf("INVALID\n");
        }
    }

    else
    {
        printf("INVALID\n");
    }
}