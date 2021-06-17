#include "util.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            
            float average = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            average = average / 3;
            int rounded = rintf(average);
            image[i][j].rgbtBlue = roundf(rounded);
            image[i][j].rgbtGreen = roundf(rounded);
            image[i][j].rgbtRed = roundf(rounded);
        }

    }

    return;
}

