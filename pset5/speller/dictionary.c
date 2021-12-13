// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

int wordNumber = 0;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    // TODO
    int check = hash(word);
    
    node *checker = table[check];
    
    while (checker != NULL)
    {
        if (strcasecmp(checker->word, word) == 0)
        {
            return true;
        }
        
        checker = checker->next;
    }
    
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO
    int x = 0;
    
    for (int i = 0; word[i] != '\0'; i++)
    {
        x += tolower(word[i]);
    }
    
    return x % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // TODO
    FILE *input = fopen(dictionary, "r");

    if (input == NULL)
    {
        return false;
    }
    
    //ensures the whole table is NULL before starting
    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }
    
    //creates an array to put the word into
    char tmpword[LENGTH + 1];
    
    //reads each word
    while (fscanf(input, "%s\n", tmpword) != EOF)
    {
        node *tmp = malloc(sizeof(node));
        //creates temp node for word
        if (tmp == NULL)
        {
            return false;
        }
        
        //adds word into temp node
        strcpy(tmp->word, tmpword);
        
        //hashes the word
        int index = hash(tmpword);
        
        if (table[index] == NULL)
        {
            //if table[index] is empty, it's the first word in that hash table
            table[index] = tmp;
        }
        else
        {
            //adds the word to the top of the hash table
            tmp->next = table[index];
            table[index] = tmp;
        }
        
        //counts the number of words
        wordNumber++;
    }
    
    //closes the file
    fclose(input);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return wordNumber;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        while (table[i] != NULL)
        {
            node *clear = table[i];
            table[i] = table[i]->next;
            free(clear);
        }
        
        table[i] = NULL;
    }
    return true;
}
