#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string key[]){

    //validating key
    if (argc != 2) {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    int keyLength = strlen(key[1]);
    //65 is ascii for 'A'
    int x = 65;

    for (int i = 0; i <= keyLength; i++) {
        char KEY = toupper(key[1][i]);

        if (i == keyLength) {
            printf("Each character must be unique\n");
            return 1;
        }

        if ((int)KEY == x) {
            i = -1;
            x++;
        }

        if (x == 91){
            break;
        }
    }
    
    if (keyLength != 26){
        printf("Key must contain 26 characters\n");
        return 1;
    }

    //Getting input string
    string pText = get_string("plaintext: ");

    //Enchiphering and printing
    
    for (int l = 0; l < strlen(pText); l++) {
        //checking for non-alpha and printing
        if (isalpha(pText[l] == 0)) {
            printf("ptext:%c\n", pText[l]);
        }
        //only letters are passed through here
        else {
            char chgText = pText[l];
            printf("chgtext:%c\n", chgText);
            char upperText = toupper(chgText);
            printf("upptext:%c\n", upperText);
            char encText = key[1][(int)upperText - 65];
            printf("enctext:%c\n", encText);
            if (islower(pText[l]) == 1){
                
            }
        }
    }

printf("\n");
return 0;
}