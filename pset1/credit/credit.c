#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    long input;
    long n;
    long a;
    long b;
    int c;
    int d = 0;
    int final;
    int check;
    int valid = 0;
    int invalid = 1;
do
{
    //this gets the credit card number
    //loop so that negative numbers are removed
    n = get_long("Number: ");
}
while (n < 0);

    input = n;
    
    if (log10(n) + 1 <= 12)
    {
        printf("INVALID\n");
        
        return 0;
    }

    a = n / 10;
//divide by 10 to remove the first digit
    b = a % 10;
//remainder gets you the first digit to multiply
    c = b * 2;
    if (c >= 10)
    //breaks the first digit up into its parts
    {
        d = c % 10;
        c = c / 10;
        c += d;
    }
    final = c;
//starts the check number
    while(log10(a) > 0)
    //as long as there are any digits left,
    {
        a = a/100;
        //removes 2 numbers
        b = a % 10;
        //gets the next number
        c = b * 2;
        //multiplies the digit by 2
        if (c >= 10)
        {
            d = c % 10;
            //gets the first digit of c
            c = c / 10;
            // gets the second digit of c
            c += d;
            //makes c c again
        }
        final += c;
        //makes the check
    }
    while (log10(n) > 0)
    {
        a = n % 10;
        n = n / 100;
        final += a;
    }

    if (final % 10 == 0)
    {
        valid = 1;
    }
    else
    {
        printf("INVALID\n");
        
        return 0;
    }
    
    while (input >= 100)
    {
        input = input / 10;
    }
    
    if (valid == 1 && input < 50 && input > 39)
    {
        printf("VISA\n");
    }
    
    else if (valid == 1 && input <= 55 && input > 49 )
    {
        printf("MASTERCARD\n");
    }
    
    else if (valid == 1 && (input == 34 || input == 37))
    {
        printf("AMEX\n");
    }
    else 
    {
        printf("INVALID\n");
        
        return 0;
    }
}

