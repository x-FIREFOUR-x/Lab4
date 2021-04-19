#include "Picture.h"

void  Picture::read_picture(string file_name)
{
    ifstream fin;
    fin.open(file_name, ios::binary);
    fin.read((char*)& head, sizeof(BMP_head));

    
    cout << sizeof(BMP_head) << endl;
    cout << head.id[0] << " " << head.id[1] << " " << head.fileSize << " " << head.reserved[0] << " " << head.reserved[1] << " ";
    cout << head.headerSize << " " << head.infoSize << " " << head.width << " " << head.height << " " << head.biplanes << " " << head.bitsPixel << " ";
    cout << head.biCompression << " " << head.biSizeImage << " " << head.biXPelsPerMeter << " " << head.biYPelsPerMeter << " " << head.biClrUsed << " " << head.biClrImportant << endl;
    
    
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
