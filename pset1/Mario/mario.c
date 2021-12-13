#include <stdio.h>
#include <cs50.h>

int main(void)
{
    
int h;
int i;
int j;
int k;

do
{
//prompts user for height
h = get_int("Height:");
}

while (h<1 || h>8);

for (i = 0; i < h; i++)
//main loop
{
    for (k = i - h; k < -1; k++)
    {
        //space loop
        printf(" ");
    }
    for (j = 0; j <= i; j++)
    {
        //hash loop
        printf("#");
    }
    printf("\n");
    
}

}
