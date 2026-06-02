#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{

    //deklarasi variabel baris dan namafile
    string baris, NamaFile;

    //membuat input untuk menangkap nama file
    cout << "Masukkan nama file : ";
    cin >> NamaFile;

    //membuat file dalam mode menulis
    ofstream outfile;
    //menunjuk ke sebuah nama file dgn ekstensi .txt
    outfile.open(NamaFile + ".txt", ios::out);

    cout << ">= Menulis file, \'q\' untuk keluar" << endl;

    //looping untuk menulis isi file
    while (true)
    {
        
        cout << "- ";
        //mendapatkan setiap karakter dalam satu baris
        getline(cin, baris);
        
}