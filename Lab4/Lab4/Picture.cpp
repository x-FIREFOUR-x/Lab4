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
    int8_t insignificant = 0;                               // не значемий байт що дописується для кратності 4
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
    
    int number_all_insignificant = (4 - (head.width * scale * 3 % 4)) * head.height;    // кількість всіх незначемих байтів
    head.biSizeImage = (head.width * head.height * 3) + number_all_insignificant;
    head.fileSize = head.biSizeImage + head.headerSize;
}

int interpolate(int x1, int y1, int x2, int y2, int z1, int z2, int z3, int z4, double x, double y)
{
    double res;
    res = (z1 / ((x2 - x1) * (y2 - y1))) * (x2 - x) * (y2 - y) + (z2 / ((x2 - x1) * (y2 - y1))) * (x2 - x) * (y - y1) + (z3 / ((x2 - x1) * (y2 - y1))) * (x - x1) * (y2 - y) + (z4 / ((x2 - x1) * (y2 - y1))) * (x - x1) * (y - y1);
    return round(res);
}