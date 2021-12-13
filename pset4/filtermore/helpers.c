#include "helpers.h"
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //finds the average RGB value using float 3.0 to prevent losing decimals
            //rounds up to next whole number
            int k = round((image[i][j].rgbtBlue + image[i][j].rgbtRed + image[i][j].rgbtGreen) / 3.0);

            //sets all RGB value to same ie k to get grey pixel
            image[i][j].rgbtBlue = image[i][j].rgbtRed = image[i][j].rgbtGreen = k;
        }
    }
    return;
}

int overflow(int input)
{
    //checks that the pixel can still be printed ie is within 255
    if (input > 255)
    {
        //if pixel is more than 255, its set AT 255
        input = 255;
    }

    return input;
}
// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int originalRed = image[i][j].rgbtRed;
            int originalBlue = image[i][j].rgbtBlue;
            int originalGreen = image[i][j].rgbtGreen;

            //formulas provided by pset to change
            int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
            int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
            int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

            //checks if the RGB value is over 255
            image[i][j].rgbtRed = overflow(sepiaRed);
            image[i][j].rgbtBlue = overflow(sepiaBlue);
            image[i][j].rgbtGreen = overflow(sepiaGreen);

        }
    }

    return;
}

void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    //swaps the addresses of a and b using temp variable
    RGBTRIPLE temp = *a;
    *a = *b;
    *b = temp;

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            //swaps the address of the jth pixel from the left & right in the ith row
            swap(&image[i][j], &image[i][width - (j + 1)]);
        }
    }

    return;
}

bool exists(int a, int b, int height, int width)
{
    if (a >= 0 && a < height && b >= 0 && b < width)
    {
        //the pixel exists if it is within the height & width of the image
        return true;
    }

    return false;
}

RGBTRIPLE blur_pixel(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    //declare a and b as ints for the new i and j values
    int a;
    int b;

    //these are floats to prevent losing of decimal places during division
    float totalR = 0.0;
    float totalB = 0.0;
    float totalG = 0.0;
    float n = 0.0;

    //create temporary new pixel to store new values
    RGBTRIPLE newpixel;

    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            //new i and j
            a = i + y;
            b = j + x;

            if (exists(a, b, height, width) == true)
            {
                //RGB values are added only if they exist
                totalR += image[a][b].rgbtRed;
                totalG += image[a][b].rgbtGreen;
                totalB += image[a][b].rgbtBlue;
                //number of pixels that exist
                n++;
            }
        }
    }

    //new RGB values are returned to the function
    newpixel.rgbtRed = round(totalR / n);
    newpixel.rgbtGreen = round(totalG / n);
    newpixel.rgbtBlue = round(totalB / n);


    return newpixel;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //creates temporary variable to store blurred image
    RGBTRIPLE final_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //keep blurred image in a separate variable so the original image can be used for other pixels
            final_image[i][j] = blur_pixel(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //replaces original image with blurred image
            image[i][j] = final_image[i][j];
        }
    }

    return;
}

RGBTRIPLE edged(int i, int j, int height, int width, RGBTRIPLE image[height][width])
{
    float redX = 0, greenX = 0, blueX = 0, redY = 0, greenY = 0, blueY = 0;
    //creates the sobel table
    int Gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            if (exists(i + y, j + x, height, width))
            {
                //sobelX is the "multiplier" of each pixel
                int sobelX = Gx[x + 1][y + 1];
                redX += sobelX * image[i + y][j + x].rgbtRed;
                greenX += sobelX * image[i + y][j + x].rgbtGreen;
                blueX += sobelX * image[i + y][j + x].rgbtBlue;
                
                //sobelY works with Gx table because flipping the x & y axes creates the Gy table
                int sobelY = Gx[y + 1][x + 1];
                redY += sobelY * image[i + y][j + x].rgbtRed;
                greenY += sobelY * image[i + y][j + x].rgbtGreen;
                blueY += sobelY * image[i + y][j + x].rgbtBlue;
                
            }
        }
    }
    
    RGBTRIPLE newpixel;
    newpixel.rgbtRed = overflow(round(sqrt(redX * redX + redY * redY)));
    newpixel.rgbtGreen = overflow(round(sqrt(greenX * greenX + greenY * greenY)));
    newpixel.rgbtBlue = overflow(round(sqrt(blueX * blueX + blueY * blueY)));
    
    return newpixel;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //creates temporary storage array (again)
    RGBTRIPLE new_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            new_image[i][j] = edged(i, j, height, width, image);
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = new_image[i][j];
        }
    }

    return;
}
