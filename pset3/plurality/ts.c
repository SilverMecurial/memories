#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name;
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");
        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}


// Update vote totals given a new vote
bool vote(string name)
{
    for (int i = 0; i < candidate_count; i++)
    {
        //when i is the index of the candidate, this will return true and add 1 to the vote
        if (strcmp(name, candidates[i].name) == 0)
        {
            candidates[i].votes++;
            printf("%i\n", candidates[i].votes);
            return true;
        }

    }    
    //if it doesn't match any candidate name, it returns false
    return false;
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    // TODO
    int k = 0;
    
    for (int x = 0; x < candidate_count; x++)
    {
        if (candidates[x].votes > k)
        {
            //sets k to the highest number of votes
            k = candidates[x].votes;
        }
    }
    
    for (int x = 0; x < candidate_count; x++)
    {
        if (candidates[x].votes == k)
        {
            printf("%s\n", candidates[x].name);
        }
    }
    return;
}