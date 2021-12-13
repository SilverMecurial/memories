#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {
        printf("Voter %i\n", i + 1);
        //so I know which voter I'm on
        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");
    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }
    }

    // Eliminate last-place candidates
    int min = find_min();
    bool tie = is_tie(min);

    // If tie, everyone wins
    if (tie)
    {
        for (int i = 0; i < candidate_count; i++)
        {
            if (!candidates[i].eliminated)
            {
                printf("%s\n", candidates[i].name);
            }
            break;
        }
    }

    // Eliminate anyone with minimum number of votes
    eliminate(min);

    // Reset vote counts back to zero
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].votes = 0;
    }

    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int x = 0; x < candidate_count; x++)
    {
        if (strcmp(name, candidates[x].name) == 0)
        {
            preferences[voter][rank] = x;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    int a = 0;
    // TODO
    for (int i = 0; i < voter_count; i++)
    {
        while (candidates[preferences[i][a]].eliminated == true)
        {
            //if the ath choice is eliminated, increase a to get the next candidate
            a++;
        }
        
        if (candidates[preferences[i][a]].eliminated == false)
        {
            //if the candidate isn't eliminated they get 1 more vote
            candidates[preferences[i][a]].votes++;
        }
        //resets a to check for the next voter's ath vote
        a = 0;
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes > round(voter_count / 2))
        //if candidate votes are more than half (rounded up)
        {
            printf("%s\n", candidates[i].name);
            //they won so print name
            return true;
        }
    }
    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    int min = 999;
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes <= min && candidates[i].eliminated == false)
        {
            min = candidates[i].votes;
        }
    }
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int m = 0;
    int n = 0;
    
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].eliminated == false)
        {
            //number of candidates remaining
            n++;
        }
        
        if (candidates[i].votes == min)
        {
            //number of candidates with the minimum number of votes
            m++;
        }
    }
    
    if (m == n)
    //if all candidates have the same ie minimum number of votes, it's a tie
    {
        return true;
    }
    
    return false;
}

// Eliminate the candidate (or candidiates) in last place
void eliminate(int min)
{
    // TODO
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            //removes the candidates with the least number of votes
            candidates[i].eliminated = true;
        }
    }
    return;
}
