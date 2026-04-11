#include <iostream>
#include <cmath>
using namespace std;

struct Kereta {
    int no;
    string nama;
    string asal;
    string tujuan;
    string jam; 
    int harga;
};

void swap(Kereta *a, Kereta *b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void inisialisasiPointer(Kereta *&arr) {
}


void isiDataAwal(Kereta *arr, int &n) {
    n = 3;

    arr[0] = {101, "Cakrawala Express", "Samarinda", "Balikpapan", "08:00", 35000};
    arr[1] = {202, "Samudra Jaya", "Balikpapan", "Sangatta", "09:30", 250000};
    arr[2] = {303, "Gajayana", "Penajam", "Balikpapan", "07:45", 50000};
}

void tampil(Kereta *arr, int n) {
    cout << "\n=== JADWAL & TIKET KERETA API SARANJANA ===\n";
    for (int i = 0; i < n; i++) {
        cout << "No            : " << (arr + i)->no << endl;
        cout << "Nama kereta   : " << (arr + i)->nama << endl;
        cout << "Rute          : " << (arr + i)->asal << " -> " << (arr + i)->tujuan << endl;
        cout << "Jam           : " << (arr + i)->jam << endl;
        cout << "Harga         : Rp" << (arr + i)->harga << endl;
        cout << "-------------------------\n";
    }
}

void tampilDetail(Kereta *k) {
    cout << "\n=== DETAIL JADWAL KERETA ===\n";
    cout << "No           : " << k->no << endl;
    cout << "Nama Kereta  : " << k->nama << endl;
    cout << "Rute         : " << k->asal << " -> " << k->tujuan << endl;
    cout << "Jam          : " << k->jam << endl;
    cout << "Harga        : Rp" << k->harga << endl;
}

void tambah(Kereta *arr, int &n) {
    cout << "\nTambah Data Kereta\n";
    cout << "No: "; cin >> (arr + n)->no;

    cin.ignore();
    cout << "Nama Kereta: "; getline(cin, (arr + n)->nama);
    cout << "Asal: "; getline(cin, (arr + n)->asal);
    cout << "Tujuan: "; getline(cin, (arr + n)->tujuan);
    cout << "Jam: "; getline(cin, (arr + n)->jam);
    cout << "Harga: "; cin >> (arr + n)->harga;
    n++;
}
void linearSearch(Kereta *arr, int n, string asal, string tujuan) {
    bool ketemu = false;
    cout << "\n=== PROSES PENCARIAN RUTE ===\n";

    for (int i = 0; i < n; i++) {
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "\nData berhasil ditemukan.\n";

            swap(arr + i, arr);
            tampilDetail(arr);

            ketemu = true;
        }
    }

    if (!ketemu) {
        cout << "\nData tidak ditemukan.\n";
    }
}
void sortByNo(Kereta *arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if ((arr + i)->no > (arr + j)->no) {
                swap(arr + i, arr + j);
            }
        }
    }
}

int jumpSearch(Kereta *arr, int n, int key) {
    int step = sqrt(n);
    int prev = 0;

    while ((arr + (step < n ? step : n) - 1)->no < key) {
        prev = step;
        step += sqrt(n);
        if (prev >= n)
            return -1;
    }

    for (int i = prev; i < (step < n ? step : n); i++) {
        if ((arr + i)->no == key)
            return i;
    }
    return -1;
}

void merge(Kereta *arr, int l, int m, int r) {
    Kereta temp[100];
    int i = l, j = m + 1, k = l;

    while (i <= m && j <= r) {
        if ((arr + i)->nama <= (arr + j)->nama)
            temp[k++] = *(arr + i++);
        else
            temp[k++] = *(arr + j++);
    }

    while (i <= m) temp[k++] = *(arr + i++);
    while (j <= r) temp[k++] = *(arr + j++);

    for (int x = l; x <= r; x++)
        *(arr + x) = temp[x];
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
            if ((arr + j)->harga < (arr + minIdx)->harga)
                minIdx = j;
        }
        swap(arr + i, arr + minIdx);
    }
}

// quick sort(double posttest)
int bagiDesc(Kereta *data, int awal, int akhir) {
    int patokan = (data + akhir)->harga;
    int indeksBesar = awal - 1;

    for (int i = awal; i < akhir; i++) {
        if ((data + i)->harga > patokan) {
            indeksBesar++;
            swap(data + indeksBesar, data + i);
        }
    }

    swap(data + indeksBesar + 1, data + akhir);
    return indeksBesar + 1;
}

void quickDesc(Kereta *data, int awal, int akhir) {
    if (awal < akhir) {
        int posisi = bagiDesc(data, awal, akhir);

        quickDesc(data, awal, posisi - 1);
        quickDesc(data, posisi + 1, akhir);
    }
}

// boyer moore (double posttest)
#define JUMLAH_CHAR 256

void buatTabelGeser(string pola, int panjang, int tabel[]) {
    for (int i = 0; i < JUMLAH_CHAR; i++)
        tabel[i] = -1;

    for (int i = 0; i < panjang; i++)
        tabel[(int)pola[i]] = i;
}

void cariNamaBM(Kereta *data, int jumlah, string keyword) {
    bool ditemukan = false;

    cout << "\n=== PENCARIAN NAMA KERETA ===\n";

    for (int x = 0; x < jumlah; x++) {
        string teks = (data + x)->nama;
        int panjangPola = keyword.length();
        int panjangTeks = teks.length();

        int tabel[JUMLAH_CHAR];
        buatTabelGeser(keyword, panjangPola, tabel);

        int geser = 0;

        while (geser <= (panjangTeks - panjangPola)) {
            int j = panjangPola - 1;

            while (j >= 0 && keyword[j] == teks[geser + j])
                j--;

            if (j < 0) {
                cout << "\nData ditemukan:\n";
                tampilDetail(data + x);
                ditemukan = true;
                break;
            } else {
                geser += max(1, j - tabel[teks[geser + j]]);
            }
        }
    }

    if (!ditemukan) {
        cout << "Data tidak ditemukan.\n";
    }
}

int main() {
    Kereta data[100];
    Kereta *ptr = data;
    int n = 0, pilih;

    inisialisasiPointer(ptr);
    isiDataAwal(data, n);

    do {
        cout << "\n=== MENU KERETA API ===\n";
        cout << "1. Tambah Data Kereta Baru\n";
        cout << "2. Tampilkan Jadwal\n";
        cout << "3. Cari Rute\n";
        cout << "4. Cari No Kereta\n";
        cout << "5. Urutkan Nama Kereta\n";
        cout << "6. Urutkan Harga Tiket Termurah\n";
        cout << "7. Urutkan Harga Tiket Termahal\n";
        cout << "8. Cari Nama Kereta\n";
        cout << "9. Keluar\n";
        cout << "Pilih: ";
        cin >> pilih;

        if (pilih == 1) tambah(data, n);
        else if (pilih == 2) tampil(data, n);
        else if (pilih == 3) {
            string asal, tujuan;
            cin.ignore();
            cout << "Asal: "; getline(cin, asal);
            cout << "Tujuan: "; getline(cin, tujuan);
            linearSearch(data, n, asal, tujuan);
        }
        else if (pilih == 4) {
            sortByNo(data, n);

            int key;
            cout << "Masukkan nomor kereta: ";
            cin >> key;

            int idx = jumpSearch(data, n, key);

            if (idx != -1) {
                swap(data + idx, data);
                tampilDetail(data);
            } else {
                cout << "Data tidak ditemukan.\n";
            }
        }
        else if (pilih == 5) {
            mergeSort(data, 0, n - 1);
            cout << "Berhasil diurutkan\n";
        }
        else if (pilih == 6) {
            selectionSort(data, n);
            cout << "Berhasil diurutkan\n";
        }
        else if (pilih == 7) {
            quickDesc(data, 0, n - 1);
            cout << "Berhasil diurutkan dari harga tertinggi ke terendah\n";
        }
        else if (pilih == 8) {
            string nama;
            cin.ignore();
            cout << "Masukkan nama kereta: ";
            getline(cin, nama);

            cariNamaBM(data, n, nama);
        }
        else if (pilih == 9) {
            cout << "Terima kasih telah menggunakan program ini!\n";
        }
        else {
            cout << "Pilihan tidak valid!\n";
        }
    } while (pilih != 9);

    return 0;
}