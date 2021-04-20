﻿#include <iostream>
#include <fstream>
#include <string>
#include "Picture.h"

using namespace std;
int main(int argc, char* argv[])
{
    if (argc != 4)
    {
        cout << "error!" << endl;
        return -1;
    }
   
    string fin = argv[1];
    string fout = argv[2];
    double scale = stod(argv[3]);

    Picture pict;
    pict.read_picture(fin);
    pict.enlarge_picture(scale);
    pict.write_picture(fout);

    cout << "Enlarging image " << scale << " times... Done." << endl;
    cout << "Written result to " << fout << endl;

    system("pause");
    return 0;
}


