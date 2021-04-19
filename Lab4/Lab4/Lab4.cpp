#include <iostream>
#include <fstream>
#include "Picture.h"

using namespace std;
int main()
{
    string fin, fout;
    cout << "input mane file read: ";
    cin >> fin;
    cout << "input mane file write: ";
    cin >> fout;
    cout << fin << " " << fout << endl;
    int scale;
    cout << "input scale: ";
    cin >> scale;
    Picture a;
    a.read_picture(fin);
    a.enlarge_picture(scale);
    a.write_picture(fout);


    return 0;
}


