#include <bits/stdc++.h>

using namespace std;

string upperText(string s) {
    string hasil = "";
    char c;
    for (int i = 0; i < s.size(); ++i)
    {
        c = s[i];
        if( 97 <= c && c <= 122 ) {
            c = c - 32;
        }
        hasil.push_back(c);
    }
    return hasil;
}


string tampilanString(string s, int pilihan){
    string hasil = "";
    if(pilihan == 1) {
        return s;
    } else if(pilihan == 2 || pilihan == 3) {
        int count = 0;
        for(int i = 0; i < s.size(); ++i){
            char c = s[i];
            if(c >= 65 && c <= 90) {
                hasil.push_back(c);
                ++count;
                if(pilihan == 3 && count == 5){
                    hasil.push_back(' ');
                    count = 0;
                }
            }
        }
    }
    return hasil;
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

string encryptdecryptVigenere(string pesan, string key, bool encrypt, int pilihantampilan) {
    string keystring = "";
    for(int i = 0; i < key.size(); ++i) {
        char c = key[i];
        if(c >= 65 && c <= 90){
            keystring += c;
        }
    }
    string hasil = "";
    int panjangkey = keystring.size();
    int pos = 0; //count huruf besar alfabet pada pesan 
    for(int i = 0; i < pesan.size(); ++i){
        char c = pesan[i];
        if(c >= 65 && c <= 90){
            char p = c - 65;
            char k = keystring[pos % panjangkey] - 65;
            if(encrypt){
                char temp = ((p + k) % 26);
                hasil += temp + 65;
            } else {
                char temp = ((p - k) % 26);
                temp = temp < 0 ? (26 + temp) : temp;
                hasil += temp + 65;
            }
            ++pos;
        } else {
            hasil += c;
        }
    }
    return tampilanString(hasil, pilihantampilan);
}

int pilihanPenyimpanan(){
    int pilihanpenyimpanan;
    cout << "======== Penyimpanan chiper text ========" << endl;
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


int main(){
    string pesan, key, namafile;
    int pilihan, pilihankeluaran, pilihanmasukkan;
    cout << "======== Vigenere Standard ======== " << endl;
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
    if(pilihanmasukkan == 2){
        cout << "Masukkan nama file dengan ekstensi file (contoh: input.txt): ";
        cin >> namafile;
    }
    cout << endl;
    cout << "======== Pilihan ========" << endl;
    cout << "1. Enkripsi" << endl;
    cout << "2. Dekripsi" << endl;
    cout << "Masukkan pilihan: ";
    cin >> pilihan;
    while(pilihan < 1 || pilihan > 2) {
        cout << "Pilihan tidak diterima, pilih dengan angka 1 atau 2" << endl;
        cout << "Masukkan pilihan: ";
        cin >> pilihan;
    }
    cout << endl;
    cout << "======== Proses ========" << endl;
    cout << "Masukkan key: ";
    getline(cin, key);
    getline(cin, key);
    if(pilihanmasukkan == 1){
        cout << "Masukkan pesan: ";
        getline(cin, pesan);
    } else {
        ifstream fileinput(namafile.c_str());
        string text;
        pesan = "";
        while(getline(fileinput, text)){
            pesan += text;
            pesan += '\n';
        }
        fileinput.close();
    }
    pesan = upperText(pesan);
    key = upperText(key);
    cout << endl;
    if(pilihan == 1){
        cout << "======== Tampilan Keluaran ========" << endl;
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
            ofstream fileoutput(namafile.c_str());
            fileoutput << encryptdecryptVigenere(pesan, key, true, pilihankeluaran);
            fileoutput.close();
        } else {
            cout << "======== Hasil ========" << endl;
            cout << "Pesan : " << endl;
            cout << pesan << endl;
            cout << "Kunci : " << endl;
            cout << key << endl;
            cout << "Hasil : " << endl;
            cout << encryptdecryptVigenere(pesan, key, true, pilihankeluaran) << endl;
        }
    } else {
        int pilihanpenyimpanan = pilihanPenyimpanan();
        if(pilihanpenyimpanan == 2){
            cout << "Masukkan nama file: ";
            cin >> namafile;
            ofstream fileoutput(namafile.c_str());
            fileoutput << encryptdecryptVigenere(pesan, key, false, 1);
            fileoutput.close();
        } else {
            cout << "======== Hasil ========" << endl;
            cout << "Pesan : " << endl;
            cout << pesan << endl;
            cout << "Kunci : " << endl;
            cout << key << endl;
            cout << "Hasil : " << endl;
            cout << encryptdecryptVigenere(pesan, key, false, 1) << endl;
        }
    }
    string a;
    cin >> a;
    return 0;
}