#include "helpers.h"
#include <math.h>

int clamp(int value, int min, int max);
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;
            float average = ((float)blue + (float)green + (float)red) / 3;
            int average_rounded = (int)round(average);
            image[i][j].rgbtBlue = average_rounded;
            image[i][j].rgbtGreen = average_rounded;
            image[i][j].rgbtRed = average_rounded;
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
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;
            int red = image[i][j].rgbtRed;

            float sepia_blue = (.272 * red + .534 * green + .131 * blue);
            image[i][j].rgbtBlue = sepia_blue > 255 ? 255 : (int)round(sepia_blue);
            float sepia_green = (.349 * red + .686 * green + .168 * blue);
            image[i][j].rgbtGreen = sepia_green > 255 ? 255 : (int)round(sepia_green);
            float sepia_red = (.393 * red + .769 * green + .189 * blue);
            image[i][j].rgbtRed = sepia_red > 255 ? 255 : (int)round(sepia_red);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < (int)(width / 2); j++)
        {
            RGBTRIPLE swap = image[i][j];
            image[i][j] = image[i][width - 1 - j];
            image[i][width - 1 - j] = swap;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    // for (int i = 0; i < height; i++)
    // {
    //     for (int j = 0; j < width; j++)
    //     {

    //         // int check_bounds_i = clamp(i, 0, width);
    //         // int check_bounds_j = clamp(j, 0, width);
    //         int check_bounds_i = i;
    //         int check_bounds_j = j;

    //         int summ_color_top_b = copy[check_bounds_i - 1][check_bounds_j - 1].rgbtBlue +
    //                                copy[check_bounds_i - 1][check_bounds_j].rgbtBlue +
    //                                copy[check_bounds_i - 1][check_bounds_j + 1].rgbtBlue;
    //         int summ_color_top_g = copy[check_bounds_i - 1][check_bounds_j - 1].rgbtGreen +
    //                                copy[check_bounds_i - 1][check_bounds_j].rgbtGreen +
    //                                copy[check_bounds_i - 1][check_bounds_j + 1].rgbtGreen;
    //         int summ_color_top_r = copy[check_bounds_i - 1][check_bounds_j - 1].rgbtRed +
    //                                copy[check_bounds_i - 1][check_bounds_j].rgbtRed +
    //                                copy[check_bounds_i - 1][check_bounds_j + 1].rgbtRed;

    //         int summ_color_main_b = copy[check_bounds_i][check_bounds_j - 1].rgbtBlue +
    //                                 copy[check_bounds_i][check_bounds_j].rgbtBlue +
    //                                 copy[check_bounds_i][check_bounds_j + 1].rgbtBlue;
    //         int summ_color_main_g = copy[check_bounds_i][check_bounds_j - 1].rgbtGreen +
    //                                 copy[check_bounds_i][check_bounds_j].rgbtGreen +
    //                                 copy[check_bounds_i][check_bounds_j + 1].rgbtGreen;
    //         int summ_color_main_r = copy[check_bounds_i][check_bounds_j - 1].rgbtRed +
    //                                 copy[check_bounds_i][check_bounds_j].rgbtRed +
    //                                 copy[check_bounds_i][check_bounds_j + 1].rgbtRed;

    //         int summ_color_low_b = copy[check_bounds_i + 1][check_bounds_j - 1].rgbtBlue +
    //                                copy[check_bounds_i + 1][check_bounds_j].rgbtBlue +
    //                                copy[check_bounds_i + 1][check_bounds_j + 1].rgbtBlue;
    //         int summ_color_low_g = copy[check_bounds_i + 1][check_bounds_j - 1].rgbtGreen +
    //                                copy[check_bounds_i + 1][check_bounds_j].rgbtGreen +
    //                                copy[check_bounds_i + 1][check_bounds_j + 1].rgbtGreen;
    //         int summ_color_low_r = copy[check_bounds_i + 1][check_bounds_j - 1].rgbtRed +
    //                                copy[check_bounds_i + 1][check_bounds_j].rgbtRed +
    //                                copy[check_bounds_i + 1][check_bounds_j + 1].rgbtRed;

    //         int aver_color_g = (int)roundf((summ_color_top_g + summ_color_main_g + summ_color_low_g) / 9);
    //         int aver_color_b = (int)roundf((summ_color_top_b + summ_color_main_b + summ_color_low_b) / 9);
    //         int aver_color_r = (int)roundf((summ_color_top_r + summ_color_main_r + summ_color_low_r) / 9);

    //         image[i][j].rgbtBlue = aver_color_b;
    //         image[i][j].rgbtGreen = aver_color_g;
    //         image[i][j].rgbtRed = aver_color_r;
    //     }
    // }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int summ_b = 0;
            int summ_g = 0;
            int summ_r = 0;
            int count_existed_pixels = 0;

            // inner box 3x3
            for (int box_i = -1; box_i <= 1; box_i++)
            {
                for (int box_j = -1; box_j <= 1; box_j++)
                {
                    // neighbor row
                    int ni = i + box_i;
                    // neighbor column
                    int nj = j + box_j;

                    // out of bounds check
                    // if not out of bounds
                    // add color HEX to summ_rgb
                    if (ni >= 0 && ni < height && nj >= 0 && nj < width)
                    {
                        summ_b += copy[ni][nj].rgbtBlue;
                        summ_g += copy[ni][nj].rgbtGreen;
                        summ_r += copy[ni][nj].rgbtRed;
                        count_existed_pixels++;
                    }
                }
            }

            image[i][j].rgbtBlue = roundf((float)summ_b / count_existed_pixels);
            image[i][j].rgbtGreen = roundf((float)summ_g / count_existed_pixels);
            image[i][j].rgbtRed = roundf((float)summ_r / count_existed_pixels);
        }
    }
    return;
}

// int clamp(int value, int min, int max)
// {
//     if (value < min)
//         return value;
//     if (value >= max)
//         return value;
//     return value;
// }

// int out_bounds_b(int i, int j, int height, int width, RGBTRIPLE img[i][j])
// {
//     if (i < 0 || j < 0)
//         return 0;
//     if (i >= height || j >= width)
//         return 0;
//     return img[i][j].rgbtBlue + img[i][j].rgbtBlue + img[i][j].rgbtBlue;
// }

// int out_bounds_g(int i, int j, int height, int width, RGBTRIPLE img[i][j])
// {
//     if (i < 0 || j < 0)
//         return 0;
//     if (i >= height || j >= width)
//         return 0;
//     return img[i][j].rgbtGreen + img[i][j].rgbtGreen + img[i][j].rgbtGreen;
// }

// int out_bounds_r(int i, int j, int height, int width, RGBTRIPLE img[i][j])
// {
//     if (i < 0 || j < 0)
//         return 0;
//     if (i >= height || j >= width)
//         return 0;
//     return img[i][j].rgbtRed + img[i][j].rgbtRed + img[i][j].rgbtRed;
// }