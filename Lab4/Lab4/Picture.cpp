#include "Picture.h"

void  Picture::read_picture(string file_name)
{
    ifstream fin;
    fin.open(file_name, ios::binary);
    fin.read((char*)& head, sizeof(BMP_head));
    
    pixels = new Pixel_triplet* [head.height];
    for (int i = 0; i < head.height; i++)
        pixels[i] = new Pixel_triplet [head.width];

    int number_insignificant = 4 - (head.width * 3 % 4);    // ????????? ???? ?? ???????? ??? ????????? 4 
    int8_t insignificant;                                   // ?? ???????? ???? ????????? ??? ????????? 4
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

    int number_insignificant = 4 - (head.width * 3 % 4);    // ????????? ???? ?? ???????? ???????? ??? ????????? 4 
    if (number_insignificant == 4)
        number_insignificant = 0;

    uint8_t insignificant = 0;                               // ?? ???????? ???? ?? ??????????? ??? ????????? 4
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
    
    int number_all_insignificant = (4 - (head.width * 3 % 4)) * head.height;    // ????????? ???? ?????????? ??????
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
    for (int i = 0; i < newWidth - 1; i++)
    {
        int x1, y1, x2, y2, z1, z2, z3, z4;
        double x, y;
        x1 = (int)(i * koefx);
        y1 = (int)((newHeight - 1) * koefy) - 1;
        x2 = (int)(i * koefx) + 1;
        y2 = (int)((newHeight - 1) * koefy);
        x = i * koefx;
        y = (newHeight - 1) * koefy - 1;
        new_pixels[(newHeight - 1)][i].blueComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].blueComponent, pixels[y2][x1].blueComponent, pixels[y1][x2].blueComponent, pixels[y2][x2].blueComponent, x, y);
        new_pixels[(newHeight - 1)][i].redComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].redComponent, pixels[y2][x1].redComponent, pixels[y1][x2].redComponent, pixels[y2][x2].redComponent, x, y);
        new_pixels[(newHeight - 1)][i].greenComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].greenComponent, pixels[y2][x1].greenComponent, pixels[y1][x2].greenComponent, pixels[y2][x2].greenComponent, x, y);
    }
    for (int i = 0; i < newHeight - 1; i++)
    {
        int x1, y1, x2, y2, z1, z2, z3, z4;
        double x, y;
        x1 = (int)((newWidth - 1) * koefx) - 1;
        y1 = (int)(i * koefy);
        x2 = (int)((newWidth - 1) * koefx);
        y2 = (int)(i * koefy) + 1;
        x = (newWidth - 1) * koefx;
        y = i * koefy;
        new_pixels[i][(newWidth - 1)].blueComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].blueComponent, pixels[y2][x1].blueComponent, pixels[y1][x2].blueComponent, pixels[y2][x2].blueComponent, x, y);
        new_pixels[i][(newWidth - 1)].redComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].redComponent, pixels[y2][x1].redComponent, pixels[y1][x2].redComponent, pixels[y2][x2].redComponent, x, y);
        new_pixels[i][(newWidth - 1)].greenComponent = interpolate(x1, y1, x2, y2, pixels[y1][x1].greenComponent, pixels[y2][x1].greenComponent, pixels[y1][x2].greenComponent, pixels[y2][x2].greenComponent, x, y);
    }
    for (int i = 0; i < head.height; i++)
        delete[] pixels[i];
    delete[] pixels;

    pixels = new_pixels;
    new_pixels = nullptr;

    head.width = newWidth;
    head.height = newHeight;

    int number_all_insignificant = (4 - ((head.width  * 3) % 4)) * head.height;    // ????????? ???? ?????????? ??????

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
void Picture::reflection(int orientation)
{
    switch (orientation)
    {
    case 0: break;
    case 1: 
        reflection_horizontal(); 
        break;
    case 2: 
        reflectionVertical();
        break;
    case 3: 
        reflection_horizontal(); 
        reflectionVertical(); 
        break;
    default: 
        break;
    }
}
void Picture::reflectionVertical()
{
    Pixel_triplet** new_pixels = new Pixel_triplet * [head.height];
    for (int i = 0; i < head.height; i++)
        new_pixels[i] = new Pixel_triplet[head.width];
    for (int i = 0; i < head.height; i++)
    {
        new_pixels[i] = pixels[head.height - i - 1];
    }

    pixels = new_pixels;
    new_pixels = nullptr;
}
void Picture::reflection_horizontal()
{
    Pixel_triplet** new_pixels = new Pixel_triplet* [head.height];
    for (int i = 0; i < head.height; i++)
        new_pixels[i] = new Pixel_triplet[head.width];

    for (int i = 0; i < head.height ; i++)
    {
        for (int j = 0; j < head.width; j++)
        {
            new_pixels[i][j] = pixels[i][head.width - j - 1];
        }
    }

    for (int i = 0; i < head.height; i++)
        delete[] pixels[i];
    delete[] pixels;

    pixels = new_pixels;
    new_pixels = nullptr;
}