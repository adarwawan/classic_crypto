// Modifikasi Menggunakan Deret Jabat Tangan dengan modifikasi
// Deret Jabat Tangan Modifikasi => 1, -2, 3, -6, 10, -15, ....
// Formula Umum Jabat Tangan => Un = n (n + 1)
// Karakter Chiper ke-n = karakter pesan ke-n + karakter key vigenere ke-n + Un (-1^(n-1))

#include <bits/stdc++.h>

using namespace std;

int deretJabatTanganModf(int n) {
    int deret = n * (n+1) / 2 ;
    deret = (n % 2 == 0) ? (deret * -1) : deret;
    return deret;
}

string tampilkanString(string s, int pilihan) {
    string hasil = "";
    if (pilihan == 1) // Apa adanya
    {
        return s;
    }
    else if (pilihan == 2) { // Tanpa spasi
        for (int i = 0; i < s.size(); ++i)
        {
            char c = s[i];
            if (c != ' ')
            {
                hasil.push_back(c);
            }
        }
        return hasil;
    }
    else { // Kelompok 5-huruf
        for (int i = 0; i < s.size(); ++i)
        {
            char c = s[i];
            hasil.push_back(c);
            if ((i % 5) == 4)
            {
                hasil.push_back(' ');
            }
        }
        return hasil;
    }
}

void printInHex(string s) {
    char c;
    for (int i = 0; i < s.size(); ++i)
    {
        c = s[i];
        printf("%x ", c & 0xff);
    }
    printf("\n");
}

string bacaFileText(string filename) {
    string s;
    ifstream f(filename.c_str(), ios::in|ios::binary|ios::ate);
    if (f.good() && f.tellg()) {
        s.resize(f.tellg());
        f.seekg(0, ios::beg);
        f.read(&s[0], s.size());
        f.close();
    }
    else {
        cout << "File tidak dapat dibuka!\n";
    }
    return s;
}

string encryptDecryptVigExt(string pesan, string key, bool isEncrypt) {
    string hasil;
    int p_size = pesan.size();
    int k_size = key.size();
    hasil.resize(p_size);
    for (int i = 0; i < p_size; ++i)
    {
        char p = pesan[i];
        char k = key[i % k_size];
        if (isEncrypt)
        {
            char temp = p + k + deretJabatTanganModf(i+1);
            hasil[i] = temp;
        }
        else {
            char temp = p - k - deretJabatTanganModf(i+1);
            hasil[i] = temp;    
        }
    }
    return hasil;
}

int pilihanPenyimpanan(){
    int pilihanpenyimpanan;
    cout << "Penyimpanan chiper text :" << endl;
    cout << "1. Keluaran pada command prompt" << endl;
    cout << "2. Keluaran pada file" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihanpenyimpanan; 
    while(pilihanpenyimpanan < 1 || pilihanpenyimpanan > 2) {
        cout << "Pilihan tidak diterima, pilih dengan angka 1 atau 2" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanpenyimpanan;
    }
    return pilihanpenyimpanan;
}

int main()
{
    string pesan, key, namafile;
    int pilihan, pilihankeluaran, pilihanmasukkan;
    cout << "Pilihan Masukkan" << endl;
    cout << "1. Masukkan pengguna" << endl;
    cout << "2. File" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihanmasukkan;
    while(pilihanmasukkan < 1 || pilihanmasukkan > 2) {
        cout << "Pilihan tidak diterima, pilih dengan angka 1 atau 2" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihanmasukkan;
    }
    if (pilihanmasukkan == 2){
        cout << "Masukkan nama file dengan ekstensi file (contoh: input.txt): ";
        cin >> namafile;
    }
    cout << "Pilihan" << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    while(pilihan < 1 || pilihan > 2) {
        cout << "Pilihan tidak diterima, pilih dengan angka 1 atau 2" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
    }

    cout << "Masukkan key: ";
    getline(cin, key);
    getline(cin, key);
    if(pilihanmasukkan == 1){
        cout << "Masukkan pesan: ";
        getline(cin, pesan);
    } else {
        pesan = bacaFileText(namafile);       
    }

    if(pilihan == 1) { //Enkripsi
        string hasil = encryptDecryptVigExt(pesan, key, true);
        cout << "Tampilan Keluaran :" << endl;
        cout << "1. Apa adanya" << endl;
        cout << "2. Tanpa spasi" << endl;
        cout << "3. Kelompok 5 huruf" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihankeluaran;
        while(pilihankeluaran < 1 || pilihankeluaran > 3) {
            cout << "Pilihan tidak diterima, pilih dengan angka 1 atau 2" << endl;
            cout << "Masukkan pilihan: ";
            cin >> pilihankeluaran;
        }
        int pilihanpenyimpanan = pilihanPenyimpanan();
        if(pilihanpenyimpanan == 2){
            cout << "Masukkan nama file: ";
            cin >> namafile;
            ofstream f(namafile.c_str(), ios::out|ios::binary);
            f << tampilkanString(hasil, pilihanpenyimpanan);
            f.close();
        } else {
            cout << "==== Hasil ====" << endl;
            cout << "Pesan : " << endl;
            cout << pesan << endl;
            printInHex(pesan);
            cout << "Kunci : " << endl;
            cout << key << endl;
            printInHex(key);
            cout << "Hasil : " << endl;
            cout << tampilkanString(hasil, pilihanpenyimpanan) << endl;
            printInHex(tampilkanString(hasil, 1));
            cout << "===============" << endl;
        }
    } else { // Dekripsi
        string hasil = encryptDecryptVigExt(pesan, key, false);
        int pilihanpenyimpanan = pilihanPenyimpanan();
        if(pilihanpenyimpanan == 2){
            cout << "Masukkan nama file: ";
            cin >> namafile;
            ofstream f(namafile.c_str(), ios::out|ios::binary);
            f << tampilkanString(hasil, 1);
            f.close();
        } else {
            cout << "==== Hasil ====" << endl;
            cout << "Pesan : " << endl;
            cout << pesan << endl;
            printInHex(pesan);
            cout << "Kunci : " << endl;
            cout << key << endl;
            printInHex(key);
            cout << "Hasil : " << endl;
            cout << tampilkanString(hasil, 1) << endl;
            printInHex(tampilkanString(hasil, 1));
            cout << "===============" << endl;
        }
    }
    return 0;
}