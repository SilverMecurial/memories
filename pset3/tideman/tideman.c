#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// Array of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
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
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        printf("Voter %i:\n", i + 1);

        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int x = 0; x < candidate_count; x++)
    {
        //if name matches candidates, the xth candidate is the rank-th preference of the voter
        if (strcmp(name, candidates[x]) == 0)
        {
            ranks[rank] = x;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    for (int i = 0; i < candidate_count; i++)
    {
        int j = 0;
        while (j < candidate_count)
        {
            if (i < j)
            {
                //if rank i is smaller than rank j ie i is preferred to j, preferences add 1
                preferences[ranks[i]][ranks[j]]++;
            }
            //checks for next rank
            j++;
        }
        //set j to i to save some steps, next j++ will satisfy j > i
        j = i;
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            //if more people prefer i to j than j to i, i wins j
            if (i != j && preferences[i][j] > preferences[j][i])
            {
                pairs[pair_count].winner = i;
                pairs[pair_count].loser = j;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int D[MAX];
    //creates array to store differences based on the pair's index
    int T[MAX];
    //creates temporary array to swap differences as well (will help later)
    pair s[MAX];
    //creates temporary variable for swapping

    for (int i = 0; i < pair_count; i++)
    {
        //gets strength of victory for each pair
        D[i] = preferences[pairs[i].winner][pairs[i].loser] - preferences[pairs[i].loser][pairs[i].winner];
    }

    for (int i = 0; i < pair_count; i++)
    {
        for (int j = i + 1; j < pair_count; j++)
        {
            if (D[i] < D[j])
            {
                s[i] = pairs[i];
                pairs[i] = pairs[j];
                pairs[j] = s[i];
                T[i] = D[i];
                D[i] = D[j];
                D[j] = T[i];
            }
        }
    }

    return;
}

bool cycle(int x);

bool cycle_helper(int x, bool source[])
{
    if (source[x] == true)
    {
        return true;
    }
    
    source[x] = true;
    
    for (int i = 0; i < candidate_count; i++)
    {
        if (locked[x][i] == true && cycle_helper(i, source) == true)
        {
            return true;
        }
    }
    
    for (int i = 0; i <= candidate_count; i++)
    {
        if (locked[x][i] == true && source[i] == true)
        {
            if (cycle(i) == true)
            {
                return true;
            }
        }
    }
    
    return false;
}


bool cycle(int i)
{
    bool source[candidate_count];
    //creates a bool array to check if any candidate is a source
    
    for (int x = 0; x < candidate_count; x++)
    {
        //ensures all candidates are not sources
        source[x] = false;
    }
    
    return cycle_helper(i, source);
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    for (int i = 0; i < pair_count; i++)
    {
        //locks all pairs by winner and loser
        locked[pairs[i].winner][pairs[i].loser] = true;
        
        if (cycle(pairs[i].winner) == true)
        {
            //undoes the last locking if a cycle is formed
            locked[pairs[i].winner][pairs[i].loser] = false;
        }
    }
    
    return;
}

bool is_winner(int i)
{
    for (int j = 0; j < candidate_count; j++)
    {
        if (locked[j][i] == true)
        {
            return false;
        }
    }
    
    return true;
}
// Print the winner of the election
void print_winner(void)
{
    for (int i = 0; i < candidate_count; i++)
    {
        if (is_winner(i) == true)
        {
            printf("%s\n", candidates[i]);
        }
    }
    return;
}

