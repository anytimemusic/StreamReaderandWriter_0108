#include <iostream>
using namespace std;

int main()
{
    //membuat isi dari try untuk pengujian error
    try
    {
        cout << "Selamat datang di prodi TI UMY" << endl;
        //trhow 0.5; //melemparkan sebuah integer maka
        cout << "pernyataan tidak akan ditampilkan" << endl;
    }
    //kondisi jika trhow yg bertipe data integer
    catch (int a)
    {
        cout << "pengecualian akan di eksekusi" << endl;
    }
    //kondisi jika trhow bertipe data selain integer
    catch (...)
    {
        cout << "default pengecualian dieksekusi" << endl;
    }
    return 0;
}