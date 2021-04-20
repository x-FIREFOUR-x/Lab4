#include "Picture.h"

void  Picture::read_picture(string file_name)
{
    ifstream fin;
    fin.open(file_name, ios::binary);
    fin.read((char*)& head, sizeof(BMP_head));
    
    pixels = new Pixel_triplet* [head.height];
    for (int i = 0; i < head.height; i++)
        pixels[i] = new Pixel_triplet [head.width];

    int number_insignificant = 4 - (head.width * 3 % 4);    // кількість байт що дописані для кратності 4 
    int8_t insignificant;                                   // не значемий байт дописаний для кратності 4
    if (number_insignificant == 4)
        number_insignificant = 0;

    for (int i = 0; i < head.height; i++)
    {
        for (int j = 0; j < head.width; j++)
        {
            fin.read((char*)&pixels[i][j], sizeof(Pixel_triplet));
        }

        for (int k = 0; k < number_insignificant; k++)
        {
            fin.read((char*)&insignificant, sizeof(int8_t));
        }
    }


    fin.close();
}

void  Picture:: write_picture(string file_name)
{
    ofstream fout;
    fout.open(file_name, ios::binary);
    fout.write((char*)&head, sizeof(BMP_head));

    int number_insignificant = 4 - (head.width * 3 % 4);    // кількість байт що потрібно дописати для кратності 4 
    if (number_insignificant == 4)
        number_insignificant = 0;

    uint8_t insignificant = 0;                               // не значемий байт що дописується для кратності 4
    for (int i = 0; i < head.height; i++)
    {
        for (int j = 0; j < head.width; j++)
        {
            fout.write((char*)&pixels[i][j], sizeof(Pixel_triplet));
        }
        
        for (int k = 0; k < number_insignificant; k++)
        {
            fout.write((char*)&insignificant, sizeof(int8_t));
        }
    }
    
    fout.close();
}

void Picture::enlarge_picture(int scale)
{
    Pixel_triplet** new_pixels = new Pixel_triplet* [head.height * scale];
    for (int i = 0; i < head.height*scale; i++)
        new_pixels[i] = new Pixel_triplet[head.width * scale];

    

    for (int i = 0; i < head.height*scale; i++)
    {
        for (int j = 0; j < head.width*scale; j++)
        {
            new_pixels[i][j] = pixels[i / scale][j / scale];
        }
    }
    
    for (int i = 0; i < head.height; i++)
        delete[] pixels[i];
    delete[] pixels;
    
    pixels = new_pixels;
    new_pixels = nullptr;

    head.width = head.width * scale;
    head.height = head.height * scale;
    
    int number_all_insignificant = (4 - (head.width * 3 % 4)) * head.height;    // кількість всіх незначемих байтів
    if (number_all_insignificant % 4 == 0)
        number_all_insignificant = 0;

    head.biSizeImage = (head.width * head.height * 3) + number_all_insignificant;
    head.fileSize = head.biSizeImage + head.headerSize;
}

void Picture::enlarge_picture(double scale)
{
    int newHeight = head.height * scale;
    int newWidth = head.width * scale;
    Pixel_triplet** new_pixels = new Pixel_triplet * [newHeight];

    for (int i = 0; i < newHeight; i++)
        new_pixels[i] = new Pixel_triplet[newWidth];

    double koefx = (double)(head.width - 1) / (newWidth - 1);
    double koefy = (double)(head.height - 1) / (newHeight - 1);

    for (int i = 0; i < newHeight - 1; i++)
    {
        for (int j = 0; j < newHeight - 1; j++)
        {
            int x1, y1, x2, y2, z1, z2, z3, z4;
            double x, y;
            x1 = (int)(j * koefx);
            y1 = (int)(i * koefy);
            x2 = (int)(j * koefx) + 1;
            y2 = (int)(i * koefy) + 1;
            x = j * koefx;
            y = i * koefy;
            new_pixels[i][j].blueComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].blueComponent, pixels[y2][x1].blueComponent, pixels[y1][x2].blueComponent, pixels[y2][x2].blueComponent, x, y);
            new_pixels[i][j].redComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].redComponent, pixels[y2][x1].redComponent, pixels[y1][x2].redComponent, pixels[y2][x2].redComponent, x, y);
            new_pixels[i][j].greenComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].greenComponent, pixels[y2][x1].greenComponent, pixels[y1][x2].greenComponent, pixels[y2][x2].greenComponent, x, y);

        }
    }
    for (int i = 0; i < head.height; i++)
        delete[] pixels[i];
    delete[] pixels;

    pixels = new_pixels;
    new_pixels = nullptr;

    head.width = newWidth;
    head.height = newHeight;

    int number_all_insignificant = (4 - ((head.width  * 3) % 4)) * head.height;    // кількість всіх незначемих байтів

    if (((number_all_insignificant / head.height) % 4) == 0)
        number_all_insignificant = 0;

    head.biSizeImage = (head.width * head.height * 3) + number_all_insignificant;
    head.fileSize = head.biSizeImage + head.headerSize;
}

uint8_t Picture::interpolate(double x1, double y1, double x2, double y2, double z11, double z12, double z21, double z22, double x, double y)
{
    double res;
    res = (z11 / ((x2 - x1) * (y2 - y1))) * (x2 - x) * (y2 - y) + (z12 / ((x2 - x1) * (y2 - y1))) * (x2 - x) * (y - y1) + (z21 / ((x2 - x1) * (y2 - y1))) * (x - x1) * (y2 - y) + (z22 / ((x2 - x1) * (y2 - y1))) * (x - x1) * (y - y1);
    return (uint8_t)res;
}