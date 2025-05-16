#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "/Users/fatmaomara/Desktop/image_processing_c++/stb_image.h"
#include "/Users/fatmaomara/Desktop/image_processing_c++/stb_image_write.h"
using namespace std;
int main()
{
    int width, height, channels;
    unsigned char *img = stbi_load("small-2.bmp", &width, &height, &channels, 0);
    if (img == NULL)
    {
        cout << "Error loading image" << endl;
        return 1;
    }
    cout << "Image loaded successfully: " << width << "x" << height << ", " << channels << " channels" << endl;
    vector<vector<int>> v(height, vector<int>(width));

    // getting red channel pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = (width * i + j) * channels;
            v[i][j] = (int)img[index];
        }
    }

    // manipulate pixels to there neighbours avg
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg;
            if (j == 0 && (i != 0 && i != height - 1))
            {
                avg = v[i - 1][j] + v[i - 1][j + 1] + v[i][j + 1] + v[i + 1][j] + v[i + 1][j + 1];
            }
            else if (j == width - 1 && (i != 0 && i != height - 1))
            {
                avg = v[i - 1][j - 1] + v[i - 1][j] + v[i][j - 1] + v[i + 1][j - 1] + v[i + 1][j];
            }
            else if (i == 0 && (j != 0 && j != width - 1))
            {
                avg = v[i][j - 1] + v[i][j + 1] + v[i + 1][j - 1] + v[i + 1][j] + v[i + 1][j + 1];
            }
            else if (i == height - 1 && (j != 0 && j != width - 1))
            {
                avg = v[i - 1][j - 1] + v[i - 1][j] + v[i - 1][j + 1] + v[i][j - 1] + v[i][j + 1];
            }
            else if (j == 0 && i == 0)
            {
                avg = v[i][j + 1] + v[i + 1][j] + v[i + 1][j + 1];
            }
            else if (j == 0 && i == height - 1)
            {
                // j-1 , i+1
                avg = v[i - 1][j] + v[i - 1][j + 1] + v[i][j + 1];
            }
            else if (j == width - 1 && i == 0)
            {
                // j+1 , i-1
                avg = v[i][j - 1] + v[i + 1][j - 1] + v[i + 1][j];
            }
            else if (j == width - 1 && i == height - 1)
            {
                // j+1 ,i+1
                avg = v[i - 1][j - 1] + v[i - 1][j] + v[i][j - 1];
            }
            else
            {
                avg = v[i - 1][j - 1] + v[i - 1][j] + v[i - 1][j + 1] + v[i][j - 1] + v[i][j + 1] + v[i + 1][j - 1] + v[i + 1][j] + v[i + 1][j + 1];
            }
            v[i][j] = avg / 8;
        }
    }

    // image writing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = (width * i + j) * channels;
            img[index] = (char)v[i][j];
        }
    }
    if (!stbi_write_bmp("output.bmp", width, height, channels, img))
    {
        cout << "Error writing image" << endl;
    }
    else
    {
        cout << "image written sccessfully\n";
    }

    // for (auto line : v)
    // {
    //     for (auto l : line)
    //     {
    //         cout << l << " ";
    //     }
    //     cout << endl;
    // }

    stbi_image_free(img);
    return 0;
}
