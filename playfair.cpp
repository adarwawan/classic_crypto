#include <bits/stdc++.h>

using namespace std;

string encryptdecrypt(vector<vector<char> > mc, vector<vector<int> > vc, char c1, char c2, bool encrypt){
    string hasil;
    int x1 = vc[c1 - 65][0];
    int y1 = vc[c1 - 65][1];
    int x2 = vc[c2 - 65][0];
    int y2 = vc[c2 - 65][1];
    if(x1 == x2) {
        if(encrypt == true){
            hasil.push_back(mc[x1][(y1 + 1) % 5]);
            hasil.push_back(mc[x2][(y2 + 1) % 5]);
        } else {
            int y1hasil = (y1 - 1) % 5;
            int y2hasil = (y2 - 1) % 5;
            y1hasil = y1hasil < 0 ? (5 + y1hasil) : y1hasil;
            y2hasil = y2hasil < 0 ? (5 + y2hasil) : y2hasil;
            hasil.push_back(mc[x1][y1hasil]);
            hasil.push_back(mc[x2][y2hasil]);
        }
    } else if (y1 == y2) {
        if(encrypt == true){
            hasil.push_back(mc[(x1 + 1) % 5][y1]);
            hasil.push_back(mc[(x2 + 1) % 5][y2]);
        } else {
            int x1hasil = (x1 - 1) % 5;
            int x2hasil = (x2 - 1) % 5;
            x1hasil = x1hasil < 0 ? (5 + x1hasil) : x1hasil;
            x2hasil = x2hasil < 0 ? (5 + x2hasil) : x2hasil;
            hasil.push_back(mc[x1hasil][y1]);
            hasil.push_back(mc[x2hasil][y2]);
        }
    } else {
        hasil.push_back(mc[x1][y2]);
        hasil.push_back(mc[x2][y1]);
    }
    /* cout << mc[x1][y1] << " " << mc[x2][y2] << " " << hasil << endl; */
    return hasil;
}

string konversipesan(vector<vector<char> > mc, vector<vector<int> > vc, string s, bool encrypt){
    string digram = "";
    char temp = 0;
    string temps = "";
    int i = 0;
    while(i < s.size()){
            char c = s[i];
        if(c >= 65 && c <= 90){
            c = c == 'J' ? 'I' : c;
            if(temp == 0) {
                temp = c;
            }
            else {
                if(s[i] == temp){
                    if(encrypt == true){
                        digram += encryptdecrypt(mc, vc, temp, 'Z', true);
                        digram += temps;
                        temps = "";
                    } else {
                        digram += encryptdecrypt(mc, vc, temp, 'Z', false);
                    }
                    temp = c;
                } else {
                    if(encrypt == true){
                        string tempdig = encryptdecrypt(mc, vc, temp, c, true);
                        digram += tempdig[0] + temps + tempdig[1];
                        temps = "";
                    } else {
                        digram += encryptdecrypt(mc, vc, temp, c, false);
                    }
                    temp = 0;
                }
            }
        } else {
            if(temp == 0){
                digram += s[i];
            } else {
                temps += c;
            }
        }
        ++i;
    }
    if(temp != 0) {
        if(encrypt == true){
            digram += encryptdecrypt(mc, vc, temp, 'Z', true);
        } else {
            digram += encryptdecrypt(mc, vc, temp, 'Z', false);
        }
    }
    return digram;
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

string encryptdecryptPlayFair(string s, string key, bool encrypt, int pilihan){
    int checkKey[26] = {0};
    checkKey[9] = 1; //huruf j tidak dimasukkan
    vector<vector<int> > vc; //vector yang merepresentasikan posisi karakter x,y dala matriks
    vector<vector<char> > mc; //matriks yang merepresentasikan posisi karakter
    string keytovector = "";
    for(int i = 0; i < key.size(); ++i){
        if(checkKey[key[i] - 65] == 0 && (key[i] >= 65 && key[i] <= 90)){
            keytovector.push_back(key[i]);
            checkKey[key[i] - 65] = 1;
        }
    }
    vector<int> v;
    for(int i = 0; i < 26; ++i) {
        vc.push_back(v); 
        if(checkKey[i] == 0) {
            keytovector.push_back(char(i + 65));
        }
    }
    int baris = 0, kolom = 0;
    vector<char> barischaracter;
    for(int i = 0; i < keytovector.size(); i++) {
        if(i % 5 == 0) barischaracter.clear();
        barischaracter.push_back(keytovector[i]);
        vector<int> temp;
        temp.push_back(baris);
        temp.push_back(kolom);
        vc[keytovector[i] - 65] = temp;
        kolom++;
        if(i % 5 == 4){
            mc.push_back(barischaracter);
            baris++;
            kolom = 0;
        } 
    }
    for(int i = 0; i < mc.size(); ++i){
        for(int j = 0; j < mc[i].size(); ++j){
            cout << mc[i][j] << " ";
        }
        cout << endl;
    }
    return tampilanString(konversipesan(mc, vc, s, encrypt), pilihan);
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

int main(){
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
    if(pilihanmasukkan == 2){
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
        ifstream fileinput(namafile);
        string text;
        pesan = "";
        while(getline(fileinput, text)){
            pesan += text;
            pesan += '\n';
        }
        fileinput.close();
    }
    if(pilihan == 1){
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
            ofstream fileoutput(namafile);
            fileoutput << encryptdecryptPlayFair(pesan, key, true, pilihankeluaran);
            fileoutput.close();
        } else {
            cout << encryptdecryptPlayFair(pesan, key, true, pilihankeluaran) << endl;
        }
    } else {
        int pilihanpenyimpanan = pilihanPenyimpanan();
        if(pilihanpenyimpanan == 2){
            cout << "Masukkan nama file: ";
            cin >> namafile;
            ofstream fileoutput(namafile);
            fileoutput << encryptdecryptPlayFair(pesan, key, false, 2);
            fileoutput.close();
        } else {
            cout << encryptdecryptPlayFair(pesan, key, false, 2) << endl;
        }
    }

    return 0;
}

