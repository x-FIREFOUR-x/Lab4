#include <iostream>
#include <fstream>
#include "BMPstruct.h"

using namespace std;
int main()
{
    BMP_head a;
    ifstream f;
    if (f)
    f.open("bmp.bmp" , ios::binary);
    if (f.is_open())
    {
        cout << true << endl;
        f.read((char*)&a, sizeof(BMP_head));

        cout << sizeof(BMP_head) << endl;
        cout << a.id[0] << " " << a.id[1] << " " << a.fileSize << " " << a.reserved[0] << " " << a.reserved[1] << " ";
        cout << a.headerSize << " " << a.infoSize << " " << a.width << " " << a.height << " " << a.biplanes << " " << a.bitsPixel << " ";
        cout << a.biCompression << " " << a.biSizeImage << " " << a.biXPelsPerMeter << " " << a.biYPelsPerMeter << " " << a.biClrUsed << " " << a.biClrImportant << endl;

        f.close();
    }

    

    return 0;
}


