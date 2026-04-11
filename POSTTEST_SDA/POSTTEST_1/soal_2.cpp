// Membuat untuk mengelompokkan data mahasiswa menggunakan struct dan menyimpannya dalam array lalu mencari ipk tertinggi

#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    int n = 5;
    Mahasiswa mhs [5];

    for(int i = 0; i < n; i++) {
        cout << "Data Mahasiswa ke-" << i+1 << endl;
        cout << "Nama: ";
        cin >> mhs[i].nama;
        cout << "NIM: ";
        cin >> mhs[i].nim;
        cout << "IPK: ";
        cin >> mhs[i].ipk;
        cout << endl;
    }

    int indeksMax = 0;
for (int i = 1; i < 5; i++) {
    if (mhs[i].ipk > mhs[indeksMax].ipk) {
        indeksMax = i;
    }
}

cout << "Mahasiswa IPK tertinggi: " << endl;
cout << "Nama : " << mhs[indeksMax].nama << endl;
cout << "NIM : " << mhs[indeksMax].nim << endl;
cout << "IPK : " <<mhs[indeksMax].ipk << endl;

return 0;
}

