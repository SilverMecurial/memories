#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>
#include <stdint.h>
typedef uint8_t BYTE;

bool is_new_img(BYTE buffer[]);

int main(int argc, char *argv[])
{
    //ensures correct usage of command
    if (argc != 2)
    {
        printf("Usage: ./recover image.\n");
        
        return 1;
    }
    
    FILE *input = fopen(argv[1], "r");
    
    //checks if the file eists
    if (input == NULL)
    {
        printf("File not found.\n");
        
        return 1;
    }
    
    BYTE buffer[512];
    //creates buffer
    
    int fileno = 0;
    //sets number of files
    
    bool first_img = false;
    //check for where the first image is
    
    FILE *outfile;
    //creates an output file
    
    while (fread(buffer, 512, 1, input))
    {
        if (is_new_img(buffer))
        {
            if (first_img == false)
            {
                //if new image is found and first image is not found, new image is first image
                first_img = true;
            }
            else
            {
                //if it's not a new image, close outfile & end this
                fclose(outfile);
            }
        
            char filename[8];
            //creates a 8 char filename
            
            sprintf(filename, "%03i.jpg", fileno++);
            
            outfile = fopen(filename, "w");
            //writes into the new file
            if (outfile == NULL)
            {
                //if outfile doesn't exist, end program
                return 1;
            }
            fwrite(buffer, 512, 1, outfile);
        }
        else if (first_img == true)
        {
            //keep writing for the rest of the images
            fwrite(buffer, 512, 1, outfile);
        }
    }
    fclose(outfile);
    fclose(input);
    //closes all the files when all the jpgs are done being read
    
    return 0;
    
}


bool is_new_img(BYTE buffer[])
{
    //checks if file is jpg
    if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
    {
        return true;
    }
    
    return false;
}