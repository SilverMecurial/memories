#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        //checks if there is only one input
        printf("Usage: ./substitution key\n");
        return 1;
    }
  
    int l = strlen(argv[1]);
    //gets length of argv
    int x, y;
    
    if (l != 26)
    {
        //ensures that key is 26 characters
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    
    string key = argv[1];
    string test = argv[1];
    //creates a bunch of strings to use later -- not sure if needed but 
    for (x = 0; x < l; x++)
    {
        key[x] = toupper(test[x]);
        //checks that every character of key is unique
        
        for (y = 0; y < l; y++)
        {
            if (key[x] == key[y] && y != x)
            {
                printf("Each character must be unique.\n");
                return 1;
            }
        }
    
        if (isalpha(argv[1][x]) == 0)
        {
            //checks that every character of key is a letter
            printf("Only letters are accepted.\n");
            return 1;
        }
    }
    
    string s = get_string("plaintext: ");
    //gets string to encrypt
    int sl = strlen(s);
    //finds length of string
    
    for (x = 0; x < sl; x++)
    {
        if (s[x] >= 65 && s[x] <= 90)
        {
            //since my key is already all upper, it just takes the ASCII code of s and finds the right key for it
            s[x] = key[s[x] - 65];
        }
        else if (s[x] >= 97 && s[x] <= 122)
        {
            //for lowercase s, it uses the same principle but tolower changes it back to lowercase
            s[x] = key[s[x] - 97];
            s[x] = tolower(s[x]);
        }
        else
        {
            //for non letter chars eg spaces, punctuations and numbers
            s[x] = s[x];
        }
        
    }
    //prints out result
    printf("ciphertext: %s\n", s);
}