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
            float red = image[i][j].rgbtRed;
            float green = image[i][j].rgbtGreen;
            float blue = image[i][j].rgbtBlue;

            float grey_value = round((red + blue + green) / 3);

            image[i][j].rgbtRed = (int) grey_value;
            image[i][j].rgbtGreen = (int) grey_value;
            image[i][j].rgbtBlue = (int) grey_value;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
        {
            for (int j = 0; j < width; j++)
            {
                int originalRed = (int) image[i][j].rgbtRed;
                int originalGreen = (int) image[i][j].rgbtGreen;
                int originalBlue = (int) image[i][j].rgbtBlue;

                int sepiaRed = round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue);
                int sepiaGreen = round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue);
                int sepiaBlue = round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue);

                if (sepiaRed > 255)
                {
                    sepiaRed = 255;
                }

                if (sepiaBlue > 255)
                {
                    sepiaBlue = 255;
                }

                if (sepiaGreen > 255)
                {
                    sepiaGreen = 255;
                }

                image[i][j].rgbtRed = sepiaRed;
                image[i][j].rgbtGreen = sepiaGreen;
                image[i][j].rgbtBlue = sepiaBlue;
            }
        }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int MAX = floor(width / 2);
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < MAX; j++)
        {
            RGBTRIPLE tempTriple = image[i][j];
            image[i][j] = image[i][width -1 - j];
            image[i][width - 1 - j] = tempTriple;
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE blur_image[height][width];
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float newRed = 0;
            float newGreen = 0;
            float newBlue = 0;
            int cpt = 0;
            for (int k = (i - 1); k <= (i + 1); k++)
            {
                for (int l = (j - 1); l <= (j + 1); l++)
                {
                    if ((k >= 0 && k < height) && (l >=0 && l < width))
                    {
                        newRed += image[k][l].rgbtRed;
                        newGreen += image[k][l].rgbtGreen;
                        newBlue += image[k][l].rgbtBlue;
                        cpt += 1;
                    }
                }
            }
            if (cpt != 0)
            {
                blur_image[i][j].rgbtRed = (int) round(newRed / cpt);
                blur_image[i][j].rgbtGreen = (int) round(newGreen / cpt);
                blur_image[i][j].rgbtBlue = (int) round(newBlue / cpt);
            }
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j] = blur_image[i][j];
        }
    }

    return;
}

