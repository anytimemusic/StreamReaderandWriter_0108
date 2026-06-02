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
            //kondisi jika baris hanyab berisi huruf q
            if (baris == "q") break;
            //menulius n memasukkan nilai dari baris ke dalam file
            outfile << baris  << endl;
        }

    //menutup file apabila telah selesai ditulis
    outfile.close();

    //membuka file dalam mode membaca
    ifstream infile;

    //menunjuk ke sebuah nama file dgn ekstensi .txt
    infile.open(NamaFile + ".txt", ios::in);

    cout << endl << ">= Membaca dan membuka file" << endl;
    //kondisi jika file ada
    if (infile.is_open())
    {
        //perulangan untuk menampilkan setiap baris
        while (getline(infile, baris))
        {
            cout << baris << endl;
        }
        //menutup file jika telah selesai di loop
        infile.close();
    }
    //kondisi jika file tidak ada
    elese cout << "unable to open file";
    return 0;
}