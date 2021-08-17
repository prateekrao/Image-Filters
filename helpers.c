#include "helpers.h"
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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE swap;
    if (width % 2 != 0)
    {
        for (int i = 0; i < height; i++)
        {
            // printf("[i][0]Before: %i\n[i][width]Before: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            swap = image[i][0];
            image[i][0] = image[i][width - 1];
            image[i][width - 1] = swap;
            // printf("[i][0]After: %i\n[i][width]After: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            for (int j = 1; j < ((width / 2)  + 0.5); j++)
            {
                swap = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = swap;
            }
        }
    }
    else
    {
        for (int i = 0; i < height; i++)
        {
            // printf("[i][0]Before: %i\n[i][width]Before: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            swap = image[i][0];
            image[i][0] = image[i][width - 1];
            image[i][width - 1] = swap;
            // printf("[i][0]After: %i\n[i][width]After: %i\n", image[i][0].rgbtRed, image[i][width - 1].rgbtRed);
            for (int j = 1; j < (width / 2); j++)
            {
                swap = image[i][j];
                image[i][j] = image[i][(width - 1) - j];
                image[i][(width - 1) - j] = swap;
            }
        }
    }

    return;

}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    typedef struct
    {
        int Red;
        int Blue;
        int Green;
    }
    temp;
    temp image2[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float averageR = image[i][j].rgbtRed;
            float averageG = image[i][j].rgbtGreen;
            float averageB = image[i][j].rgbtBlue;
            int counter = 1;

            // 7
            if (i != 0)
            {
                averageR += image[i - 1][j].rgbtRed;
                averageB += image[i - 1][j].rgbtBlue;
                averageG += image[i - 1][j].rgbtGreen;
                counter++;
            }
            //4
            if (j != 0)
            {
                averageR += image[i][j - 1].rgbtRed;
                averageB += image[i][j - 1].rgbtBlue;
                averageG += image[i][j - 1].rgbtGreen;
                counter++;
            }
            //2
            if (i != (height - 1))
            {
                averageR += image[i + 1][j].rgbtRed;
                averageB += image[i + 1][j].rgbtBlue;
                averageG += image[i + 1][j].rgbtGreen;
                counter++;
            }
            //5
            if (j != (width - 1))
            {
                averageR += image[i][j + 1].rgbtRed;
                averageB += image[i][j + 1].rgbtBlue;
                averageG += image[i][j + 1].rgbtGreen;
                counter++;
            }
            //1
            if ((i != 0) && (j != 0))
            {
                averageR += image[i - 1][j - 1].rgbtRed;
                averageB += image[i - 1][j - 1].rgbtBlue;
                averageG += image[i - 1][j - 1].rgbtGreen;
                counter++;
            }
            //3
            if ((i != 0) && (j != (width - 1)))
            {
                averageR += image[i - 1][j + 1].rgbtRed;
                averageB += image[i - 1][j + 1].rgbtBlue;
                averageG += image[i - 1][j + 1].rgbtGreen;
                counter++;
            }
            //6
            if ((i != (height - 1)) && (j != 0))
            {
                averageR += image[i + 1][j - 1].rgbtRed;
                averageB += image[i + 1][j - 1].rgbtBlue;
                averageG += image[i + 1][j - 1].rgbtGreen;
                counter++;
            }
            //8
            if ((i != (height - 1)) && (j != (width - 1)))
            {
                averageR += image[i + 1][j + 1].rgbtRed;
                averageB += image[i + 1][j + 1].rgbtBlue;
                averageG += image[i + 1][j + 1].rgbtGreen;
                counter++;
            }

            averageR = averageR / counter;
            averageB = averageB / counter;
            averageG = averageG / counter;
            image2[i][j].Red = roundf(averageR);
            image2[i][j].Blue = roundf(averageB);
            image2[i][j].Green = roundf(averageG);
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = image2[i][j].Red;
            image[i][j].rgbtBlue = image2[i][j].Blue;
            image[i][j].rgbtGreen = image2[i][j].Green;
        }
    }


    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Create temp array
    RGBTRIPLE temp[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            temp[i][j] = image[i][j];
        }
    }
    // Initialise Sobel arrays
    int Gx[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int Gy[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // Loop through columns
        for (int j = 0; j < width; j++)
        {
            // Initialise ints
            float Gx_red;
            float Gx_blue;
            float Gx_green;
            float Gy_red;
            float Gy_blue;
            float Gy_green;
            Gx_red = Gx_blue = Gx_green = Gy_red = Gy_blue = Gy_green = 0;
            // For each pixel, loop vertical and horizontal
            for (int k = -1; k < 2; k++)
            {
                for (int l = -1; l < 2; l++)
                {
                    // Check if pixel is outside rows
                    if (i + k < 0 || i + k >= height)
                    {
                        continue;
                    }
                    // Check if pixel is outside columns
                    if (j + l < 0 || j + l >= width)
                    {
                        continue;
                    }
                    // Otherwise add to sums
                    Gx_red += temp[i + k][j + l].rgbtRed * Gx[k + 1][l + 1];
                    Gx_green += temp[i + k][j + l].rgbtGreen * Gx[k + 1][l + 1];
                    Gx_blue += temp[i + k][j + l].rgbtBlue * Gx[k + 1][l + 1];
                    Gy_red += temp[i + k][j + l].rgbtRed * Gy[k + 1][l + 1];
                    Gy_green += temp[i + k][j + l].rgbtGreen * Gy[k + 1][l + 1];
                    Gy_blue += temp[i + k][j + l].rgbtBlue * Gy[k + 1][l + 1];
                }
            }
             // Calculate Sobel operator
            int red = round(sqrt(Gx_red * Gx_red + Gy_red * Gy_red));
            int green = round(sqrt(Gx_green * Gx_green + Gy_green * Gy_green));
            int blue = round(sqrt(Gx_blue * Gx_blue + Gy_blue * Gy_blue));
            // Cap at 255
            if (red > 255)
            {
                red = 255;
            }
            if (green > 255)
            {
                green = 255;
            }
            if (blue > 255)
            {
                blue = 255;
            }
            // Assign new values to pixels
            image[i][j].rgbtRed = red;
            image[i][j].rgbtGreen = green;
            image[i][j].rgbtBlue = blue;
        }
    }
    return;
}