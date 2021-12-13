#include <stdio.h>
#include <cs50.h>
#include <math.h>
#include <string.h>

int main(void)
{
    
    int i, words = 1, letters = 0, punctuations = 0, comma = 0;
    float al, as, index;
    
    string t = get_string("Text: ");
    //requests for text
    int l = strlen(t);
    //gets length of string
    for (i = 0; i < l; i++)
    {
        if (t[i] == ' '){
            //there is a space after each word except the last, so this counts the number of words.
            words++;}
        else if (t[i] == '.' || t[i] == '!' || t[i] == '?'){
            //there is a punctuation after each sentence, so this counts the number of sentences.
            punctuations++;}
        else if (t[i] == ',' || t[i] == ';' || t[i] == ':' || t[i] == '-' || (int) t[i] == 34 || (int) t[i] == 39){
            //this just omits the extra punctuations.
            comma++;}
        else{
            //this counts letters ie everything else.
            letters++;}
    }
    printf("w = %i, p = %i, l = %i", words, punctuations, letters);
    al = (float) letters / words * 100;
    //gets average letters per hundred words
    as = (float) punctuations / words * 100;
    //gets average sentences per hundred words
    index = 0.0588 * al - 0.296 * as - 15.8;
    //index formula
    if (index < 1){
        //for things below grade 1
        printf("Before Grade 1\n");
        return 0;}
    else if (index > 16){
        //for complex texes above grade 16
        printf("Grade 16+\n");
        return 0;}
    if (1 <= index || index <= 16){
        //for anything in between
        index = round(index);
        printf("Grade %i\n", (int) index);}
}