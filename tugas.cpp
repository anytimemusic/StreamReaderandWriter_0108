#include <iostream>
#include <fstream>
#include <string>
#include <array>
#include <stdexcept>
#include <vector>

using namespace std;

// ==========================================
// 1. STRUKTUR KELAS TOKO ELEKTRONIK (OOP)
// ==========================================
class TokoElektronik {
private:
    // Enkapsulasi: Array berkapasitas 3 elemen untuk barang di etalase
    array<string, 3> etalase;

public:
    // Constructor: Mengisi data awal etalase secara otomatis
    TokoElektronik() {
        etalase[0] = "Laptop Acer Nitro";
        etalase[1] = "Smartphone Google Pixel";
        etalase[2] = "Keyboard Mechanical Ajazz";
    }

    // Method Public dengan Exception Handling kustom
    string ambilProdukEtalase(size_t nomorRak) {
        try {
            // Menggunakan .at() untuk memicu out_of_range jika indeks tidak valid
            return etalase.at(nomorRak);
        }
        catch (const out_of_range& e) {
            // Melemparkan kembali (throw) pesan error kustom sesuai ketentuan
            throw runtime_error("Gagal Mengambil Barang : Rak nomor " + to_string(nomorRak) + " kosong atau tidak tersedia!");
        }
    }
};

// ==========================================
// FUNGSI PEMBANTU UNTUK CRUD GUDANG (FILE I/O)
// ==========================================

// Fungsi Helper untuk membaca semua data dari file ke dalam vector
vector<string> bacaSemuaBarang() {
    vector<string> daftarBarang;
    ifstream fileInput("gudang.txt");
    string namaBarang;
    
    if (fileInput.is_open()) {
        while (getline(fileInput, namaBarang)) {
            if (!namaBarang.empty()) {
                daftarBarang.push_back(namaBarang);
            }
        }
        fileInput.close();
    }
    return daftarBarang;
}

// Fungsi Helper untuk menulis ulang vector data kembali ke file
void tulisSemuaBarang(const vector<string>& daftarBarang) {
    ofstream fileOutput("gudang.txt", ios::trunc); // Overwrite file lama
    if (fileOutput.is_open()) {
        for (const auto& barang : daftarBarang) {
            fileOutput << barang << "\n";
        }
        fileOutput.close();
    }
}

// [READ] Menampilkan daftar barang dari file .txt
void tampilkanGudang() {
    vector<string> daftarBarang = bacaSemuaBarang();
    cout << "\n=== DAFTAR BARANG DI GUDANG (gudang.txt) ===\n";
    if (daftarBarang.empty()) {
        cout << "[ Gudang Masih Kosong ]\n";
    } else {
        for (size_t i = 0; i < daftarBarang.size(); ++i) {
            cout << i + 1 << ". " << daftarBarang[i] << "\n";
        }
    }
    cout << "============================================\n";
}

// [CREATE] Menambahkan data barang baru
void tambahBarang() {
    cin.ignore();
    string barangBaru;
    cout << "Masukkan nama barang baru: ";
    getline(cin, barangBaru);

    if (!barangBaru.empty()) {
        ofstream fileOutput("gudang.txt", ios::app); // Append mode
        if (fileOutput.is_open()) {
            fileOutput << barangBaru << "\n";
            fileOutput.close();
            cout << "Sukses: Barang \"" << barangBaru << "\" berhasil ditambahkan ke gudang.\n";
        } else {
            cout << "Error: Gagal membuka file gudang.txt!\n";
        }
    }
}

// [UPDATE] Memperbarui data barang berdasarkan nomor urut
void updateBarang() {
    tampilkanGudang();
    vector<string> daftarBarang = bacaSemuaBarang();
    if (daftarBarang.empty()) return;

    size_t nomor;
    cout << "Pilih nomor barang yang ingin diubah: ";
    cin >> nomor;

    if (nomor > 0 && nomor <= daftarBarang.size()) {
        cin.ignore();
        string namaBaru;
        cout << "Masukkan nama baru untuk \"" << daftarBarang[nomor - 1] << "\": ";
        getline(cin, namaBaru);
        
        daftarBarang[nomor - 1] = namaBaru;
        tulisSemuaBarang(daftarBarang);
        cout << "Sukses: Data barang berhasil diperbarui.\n";
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

// [DELETE] Menghapus data barang berdasarkan nomor urut
void hapusBarang() {
    tampilkanGudang();
    vector<string> daftarBarang = bacaSemuaBarang();
    if (daftarBarang.empty()) return;

    size_t nomor;
    cout << "Pilih nomor barang yang ingin dihapus: ";
    cin >> nomor;

    if (nomor > 0 && nomor <= daftarBarang.size()) {
        string barangDihapus = daftarBarang[nomor - 1];
        daftarBarang.erase(daftarBarang.begin() + (nomor - 1));
        tulisSemuaBarang(daftarBarang);
        cout << "Sukses: Barang \"" << barangDihapus << "\" berhasil dihapus dari gudang.\n";
    } else {
        cout << "Pilihan tidak valid!\n";
    }
}

// ==========================================
// SIMULASI PENANGANAN ERROR ETALASE
// ==========================================
void jalankanSimulasiEtalase(TokoElektronik& toko) {
    cout << "\n=== SIMULASI PENGAMBILAN BARANG DI ETALASE ===\n";
    
    // Skenario 1: Pengambilan di indeks ke-1 (Harus Sukses)
    cout << "[Skenario 1] Mengambil barang di rak indeks ke-1...\n";
    try {
        string barang = toko.ambilProdukEtalase(1);
        cout << "Hasil: Berhasil mengambil -> " << barang << "\n\n";
    } 
    catch (const runtime_error& e) {
        cout << "Hasil: " << e.what() << "\n\n";
    }

    // Skenario 2: Pengambilan di indeks ke-5 (Harus Gagal & Menangkap Error Kustom)
    cout << "[Skenario 2] Mengambil barang di rak indeks ke-5...\n";
    try {
        string barang = toko.ambilProdukEtalase(5);
        cout << "Hasil: Berhasil mengambil -> " << barang << "\n\n";
    } 
    catch (const runtime_error& e) {
        // Menangkap error kustom yang dilemparkan oleh method objek
        cout << "Hasil Tangkapan Error: " << e.what() << "\n";
    }
    cout << "==============================================\n";
}

// ==========================================
// 4. PENGUJIAN PADA FUNGSI MAIN()
// ==========================================
int main() {
    TokoElektronik tokoGibran;
    int pilihanMenu;

    do {
        // Setiap kali menu utama terbuka, daftar barang dari file otomatis ditampilkan (Sesuai Poin 3 - Read)
        tampilkanGudang();

        cout << "\n--- MENU UTAMA TOKO ELEKTRONIK GIBRAN JAYA ---\n";
        cout << "1. Tambah Barang Gudang (Create)\n";
        cout << "2. Update Barang Gudang (Update)\n";
        cout << "3. Hapus Barang Gudang (Delete)\n";
        cout << "4. Jalankan Simulasi Etalase (Exception Handling)\n";
        cout << "5. Keluar Aplikasi\n";
        cout << "Pilih menu (1-5): ";
        cin >> pilihanMenu;

        switch (pilihanMenu) {
            case 1:
                tambahBarang();
                break;
            case 2:
                updateBarang();
                break;
            case 3:
                hapusBarang();
                break;
            case 4:
                jalankanSimulasiEtalase(tokoGibran);
                break;
            case 5:
                cout << "Terima kasih telah menggunakan sistem manajemen Gibran Jaya!\n";
                break;
            default:
                cout << "Pilihan tidak valid! Silakan masukkan angka 1-5.\n";
                break;
        }
        
        cout << "\n";
    } while (pilihanMenu != 5);

    return 0;
}