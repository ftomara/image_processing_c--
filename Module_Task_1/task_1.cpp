#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "/Users/fatmaomara/Desktop/image_processing_c++/stb_image.h"
#include "/Users/fatmaomara/Desktop/image_processing_c++/stb_image_write.h"
using namespace std;
void manipulatePixels(vector<vector<int>> &v)
{
    int height = v.size(), width = v.front().size();
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int avg = 0;
            for (int x = i - 1; x <= i + 1; x++)
            {
                for (int y = j - 1; y <= j + 1; y++)
                {
                    if (x >= 0 && x < height && y >= 0 && y < width && !(x == i && y == j))
                    {
                        avg += v[x][y];
                    }
                }
            }
            v[i][j] = avg / 8;
        }
    }
}
int main()
{
    int width, height, channels;
    unsigned char *img = stbi_load("shifo.bmp", &width, &height, &channels, 0);
    if (img == NULL)
    {
        cout << "Error loading image" << endl;
        return 1;
    }
    cout << "Image loaded successfully: " << width << "x" << height << ", " << channels << " channels" << endl;
    vector<vector<int>> red(height, vector<int>(width));
    vector<vector<int>> green(height, vector<int>(width));
    vector<vector<int>> blue(height, vector<int>(width));
    vector<vector<int>> alpha(height, vector<int>(width));

    // getting red channel pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = (width * i + j) * channels;
            red[i][j] = (int)img[index];
            green[i][j] = (int)img[index + 1];
            blue[i][j] = (int)img[index + 2];
            alpha[i][j] = (int)img[index + 3];
        }
    }
    manipulatePixels(red);
    manipulatePixels(green);
    manipulatePixels(blue);
    manipulatePixels(alpha);
    // manipulate pixels to there neighbours avg

    // image writing
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int index = (width * i + j) * channels;
            img[index] = (char)red[i][j];
            img[index + 1] = (char)green[i][j];
            img[index + 2] = (char)blue[i][j];
            img[index + 3] = (char)alpha[i][j];
        }
    }
    if (!stbi_write_bmp("shifo_out.bmp", width, height, channels, img))
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
