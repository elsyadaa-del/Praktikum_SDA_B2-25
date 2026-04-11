#include <iostream>
#include <cmath>
using namespace std;

struct Kereta {
    int no;
    string nama;
    string asal;
    string tujuan;
    int harga;
};

void swap(Kereta *a, Kereta *b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tampil(Kereta *arr, int n) {
    cout << "\n=== DATA KERETA SARANJANA ===\n";
    for (int i = 0; i < n; i++) {
        cout << (arr + i)->no << " | "
             << (arr + i)->nama << " | "
             << (arr + i)->asal << " -> "
             << (arr + i)->tujuan << " | Rp"
             << (arr + i)->harga << endl;
    }
}

void tambah(Kereta *arr, int &n) {
    cout << "\nTambah Data Penumpang\n";
    cout << "No Kereta: "; cin >> (arr + n)->no;
    cout << "Nama: "; cin >> (arr + n)->nama;
    cout << "Asal: "; cin >> (arr + n)->asal;
    cout << "Tujuan: "; cin >> (arr + n)->tujuan;
    cout << "Harga: "; cin >> (arr + n)->harga;
    n++;
}

void linearSearch(Kereta *arr, int n, string asal, string tujuan) {
    bool ketemu = false;
    cout << "\nProses Pencarian Rute kereta :\n";
    for (int i = 0; i < n; i++) {
        cout << "Memeriksa data ke-" << i+1 << endl;

        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "Kereta ditemukan: " << (arr + i)->nama << endl;
            ketemu = true;
        }
    }
    if (!ketemu)
        cout << "Maaf, data  rute tidak ditemukan\n";
}

int jumpSearch(Kereta *arr, int n, int key) {
    int step = sqrt(n);
    int prev = 0;

    while ((arr + min(step, n) - 1)->no < key) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    for (int i = prev; i < min(step, n); i++) {
        if ((arr + i)->no == key)
            return i;
    }
    return -1;
}

void merge(Kereta *arr, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    Kereta L[100], R[100];

    for (int i = 0; i < n1; i++)
        L[i] = *(arr + l + i);

    for (int j = 0; j < n2; j++)
        R[j] = *(arr + m + 1 + j);

    int i = 0, j = 0, k = l;

    while (i < n1 && j < n2) {
        if (L[i].nama <= R[j].nama) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arr + k) = L[i];
        i++; k++;
    }

    while (j < n2) {
        *(arr + k) = R[j];
        j++; k++;
    }
}

void mergeSort(Kereta *arr, int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void selectionSort(Kereta *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if ((arr + j)->harga < (arr + minIdx)->harga) {
                minIdx = j;
            }
        }
        swap(arr + i, arr + minIdx);
    }
}

int main() {
    Kereta data[100];
    int n = 0, pilih;

    do {
        cout << "\n=== MENU KERETA API SARANJANA ===\n";
        cout << "1. Tambah Data\n";
        cout << "2. Tampilkan Data\n";
        cout << "3. Cari Rute\n";
        cout << "4. Cari No Kereta\n";
        cout << "5. Urutkan Nama\n";
        cout << "6. Urutkan Harga\n";
        cout << "0. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) {
            tambah(data, n);
        }
        else if (pilih == 2) {
            tampil(data, n);
        }
        else if (pilih == 3) {
            string asal, tujuan;
            cout << "Masukkan asal: "; cin >> asal;
            cout << "Masukkan tujuan: "; cin >> tujuan;
            linearSearch(data, n, asal, tujuan);
        }
        else if (pilih == 4) {
            int key;
            cout << "Masukkan No Kereta: ";
            cin >> key;

            int idx = jumpSearch(data, n, key);
            if (idx != -1)
                cout << "Ditemukan: " << (data + idx)->nama << endl;
            else
                cout << "Tidak ditemukan\n";
        }
        else if (pilih == 5) {
            mergeSort(data, 0, n - 1);
            cout << "Data berhasil diurutkan\n";
        }
        else if (pilih == 6) {
            selectionSort(data, n);
            cout << "Data berhasil diurutkan\n";
        }

    } while (pilih != 0);

    return 0;
}