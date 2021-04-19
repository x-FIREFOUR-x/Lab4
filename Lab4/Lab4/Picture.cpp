#include "Picture.h"

void  Picture::read_picture(string file_name)
{
    ifstream fin;
    fin.open(file_name, ios::binary);
    fin.read((char*)& head, sizeof(BMP_head));

    /*
    cout << sizeof(BMP_head) << endl;
    cout << head.id[0] << " " << head.id[1] << " " << head.fileSize << " " << head.reserved[0] << " " << head.reserved[1] << " ";
    cout << head.headerSize << " " << head.infoSize << " " << head.width << " " << head.height << " " << head.biplanes << " " << head.bitsPixel << " ";
    cout << head.biCompression << " " << head.biSizeImage << " " << head.biXPelsPerMeter << " " << head.biYPelsPerMeter << " " << head.biClrUsed << " " << head.biClrImportant << endl;
    */
    
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
