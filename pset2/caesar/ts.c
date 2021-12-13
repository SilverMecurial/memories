#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
  if (argc !=2)
  {
      //checks if there is only one input
    printf("Error! Invalid input\n"); return 1;
  }
  
  int l = strlen(argv[1]);
  //gets length of string
  int k = atoi(argv[1]);
  //converts argv[1] into an int
  int x;
  
  printf("key: %i\n", k);
  //prints argv as int
  
  for (x = 0; x < strlen(argv[1]); x++)
  {
      //checks every character of argv[1] is a number
     if (isalpha(argv[1][x]) != 0)
    {
        printf("Usage: ./caesar key\n"); return 1;
    }
  }
  
  string s = get_string("plaintext: ");
  //gets input
  
  int a = strlen(s);
  
  for (x = 0; x < a; x++)
  {
    if (s[x] < 90)
    {
      s[x] = (((s[x] - 65) + k) % 26) + 65;
    }
    else if (s[x] < 122)
    {
      s[x] = (((s[x] - 97) + k) % 26) + 97;
    }
  }
  
  printf("ciphertext: %s\n", s);
  
}