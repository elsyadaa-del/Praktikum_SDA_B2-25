#include <iostream>
#include <cmath>
using namespace std;

#define MAX 100

struct Tiket {
    string nama;
    string rute;
};

struct Kereta {
    int no;
    string nama;
    string asal;
    string tujuan;
    string jam;
    int harga;
};
struct NodeQueue {
    string nama;
    string rute;
    NodeQueue* prev;
    NodeQueue* next;
};

struct NodeStack {
    string nama;
    string rute;
    NodeStack* prev;
    NodeStack* next;
};

NodeQueue *frontLL = NULL, *rearLL = NULL;
NodeStack *topLL = NULL;

Tiket queueTiket[MAX];
Tiket stackRiwayat[MAX];

int front = -1, rear = -1;
int top = -1;

void push(string nama, string rute);
void pushLL(string nama, string rute);

void garis() {
    cout << "=======================================\n";
}

bool isQueueEmpty() {
    return front == -1 || front > rear;
}

bool isQueueFull() {
    return rear == MAX - 1;
}

bool isStackEmpty() {
    return top == -1;
}

void enqueue(string nama, string rute) {
    if (isQueueFull()) {
        cout << "\nAntrian penuh!\n";
        return;
    }
    if (front == -1)
        front = 0;
    rear++;
    queueTiket[rear] = {nama, rute};
    cout << "\nPenumpang berhasil masuk antrian!\n";
}

void dequeue() {
    if (isQueueEmpty()) {
        cout << "\nAntrian kosong!\n";
        return;
    }
    Tiket t = queueTiket[front];
    garis();
    cout << "        MEMPROSES TIKET\n";
    garis();
    cout << "Nama : " << t.nama << endl;
    cout << "Rute : " << t.rute << endl;
    front++;
    if (front > rear)
        front = rear = -1;
    push(t.nama, t.rute);
    cout << "\nTiket berhasil diproses!\n";
}

void tampilQueue() {
    if (isQueueEmpty()) {
        cout << "\nAntrian kosong!\n";
        return;
    }
    garis();
    cout << "           DAFTAR ANTRIAN\n";
    garis();
    int nomor = 1;
    for (Tiket *p = queueTiket + front;
         p <= queueTiket + rear;
         p++) {
        cout << nomor++ << ". ";
        cout << p->nama
             << " | "
             << p->rute << endl;
    }
}

void peekQueue() {
    if (isQueueEmpty()) {
        cout << "\nAntrian kosong!\n";
        return;
    }
    garis();
    cout << "        ANTRIAN TERDEPAN\n";
    garis();
    cout << "Nama : " << queueTiket[front].nama << endl;
    cout << "Rute : " << queueTiket[front].rute << endl;
}

void push(string nama, string rute) {
    if (top == MAX - 1) {
        cout << "\nRiwayat penuh!\n";
        return;
    }
    top++;
    stackRiwayat[top] = {nama, rute};
}

void pop() {
    if (isStackEmpty()) {
        cout << "\nRiwayat kosong!\n";
        return;
    }
    cout << "\nMenghapus riwayat : "
         << stackRiwayat[top].nama << endl;
    top--;
}

void peekStack() {
    if (isStackEmpty()) {
        cout << "\nRiwayat kosong!\n";
        return;
    }
    garis();
    cout << "      TRANSAKSI TERAKHIR\n";
    garis();
    cout << "Nama : " << stackRiwayat[top].nama << endl;
    cout << "Rute : " << stackRiwayat[top].rute << endl;
}

void tampilStack() {
    if (isStackEmpty()) {
        cout << "\nRiwayat kosong!\n";
        return;
    }
    garis();
    cout << "         RIWAYAT TRANSAKSI\n";
    garis();
    for (int i = top; i >= 0; i--) {
        cout << i + 1 << ". ";
        cout << stackRiwayat[i].nama
             << " | "
             << stackRiwayat[i].rute << endl;
    }
}

void swap(Kereta *a, Kereta *b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void isiDataAwal(Kereta *arr, int &n) {
    n = 3;
    arr[0] = {101, "Cakrawala Express", "Samarinda", "Balikpapan", "08:00", 35000};
    arr[1] = {202, "Samudra Jaya", "Balikpapan", "Sangatta", "09:30", 250000};
    arr[2] = {303, "Gajayana", "Penajam", "Balikpapan", "07:45", 50000};
}

void tampil(Kereta *arr, int n) {
    if (n == 0) {
        cout << "\nData kereta kosong!\n";
        return;
    }
    garis();
    cout << "      JADWAL KERETA API SARANJANA\n";
    garis();
    for (int i = 0; i < n; i++) {
        cout << "\nData Ke-" << i + 1 << endl;
        cout << "----------------------------------------------------\n";
        cout << "No Kereta   : " << (arr + i)->no << endl;
        cout << "Nama        : " << (arr + i)->nama << endl;
        cout << "Rute        : "
             << (arr + i)->asal
             << " -> "
             << (arr + i)->tujuan << endl;
        cout << "Jam         : " << (arr + i)->jam << endl;
        cout << "Harga       : Rp " << (arr + i)->harga << endl;
    }
    garis();
}

void tampilDetail(Kereta *k) {
    garis();
    cout << "         DETAIL KERETA\n";
    garis();
    cout << "No Kereta   : " << k->no << endl;
    cout << "Nama        : " << k->nama << endl;
    cout << "Rute        : "
         << k->asal
         << " -> "
         << k->tujuan << endl;
    cout << "Jam         : " << k->jam << endl;
    cout << "Harga       : Rp " << k->harga << endl;
    garis();
}

void tambah(Kereta *arr, int &n) {
    garis();
    cout << "        TAMBAH DATA KERETA\n";
    garis();
    cout << "No Kereta : ";
    cin >> (arr + n)->no;
    cin.ignore();
    cout << "Nama      : ";
    getline(cin, (arr + n)->nama);
    cout << "Asal      : ";
    getline(cin, (arr + n)->asal);
    cout << "Tujuan    : ";
    getline(cin, (arr + n)->tujuan);
    cout << "Jam       : ";
    getline(cin, (arr + n)->jam);
    cout << "Harga     : ";
    cin >> (arr + n)->harga;
    n++;
    cout << "\nData berhasil ditambahkan!\n";
}

void linearSearch(Kereta *arr, int n,
                  string asal,
                  string tujuan) {
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        if ((arr + i)->asal == asal &&
            (arr + i)->tujuan == tujuan) {
            cout << "\nData ditemukan!\n";
            tampilDetail(arr + i);
            ketemu = true;
        }
    }
    if (!ketemu)
        cout << "\nData tidak ditemukan!\n";
}

void cariById(Kereta *arr, int n, int id) {
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        if ((arr + i)->no == id) {
            tampilDetail(arr + i);
            ketemu = true;
            break;
        }
    }
    if (!ketemu)
        cout << "\nData tidak ditemukan!\n";
}

void cariByNama(Kereta *arr, int n, string nama) {
    bool ketemu = false;
    for (int i = 0; i < n; i++) {
        if ((arr + i)->nama == nama) {
            tampilDetail(arr + i);
            ketemu = true;
        }
    }
    if (!ketemu)
        cout << "\nData tidak ditemukan!\n";
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
    for (int i = prev;
         i < (step < n ? step : n);
         i++) {
        if ((arr + i)->no == key)
            return i;
    }
    return -1;
}

void merge(Kereta *arr, int l, int m, int r) {
    Kereta temp[100];
    int i = l;
    int j = m + 1;
    int k = l;
    while (i <= m && j <= r) {
        if ((arr + i)->nama <= (arr + j)->nama)
            temp[k++] = *(arr + i++);
        else
            temp[k++] = *(arr + j++);
    }
    while (i <= m)
        temp[k++] = *(arr + i++);
    while (j <= r)
        temp[k++] = *(arr + j++);
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
            if ((arr + j)->harga <
                (arr + minIdx)->harga)
                minIdx = j;
        }
        swap(arr + i, arr + minIdx);
    }
}

void enqueueLL(string nama, string rute) {
    NodeQueue* baru = new NodeQueue{
        nama,
        rute,
        NULL,
        NULL
    };
    if (frontLL == NULL) {
        frontLL = rearLL = baru;
    }
    else {
        baru->prev = rearLL;
        rearLL->next = baru;
        rearLL = baru;
    }
    cout << "\nBerhasil masuk antrian!\n";
}
void dequeueLL() {
    if (frontLL == NULL) {
        cout << "\nAntrian kosong!\n";
        return;
    }
    NodeQueue* hapus = frontLL;
    garis();
    cout << "      MEMPROSES ANTRIAN\n";
    garis();
    cout << "Nama : " << hapus->nama << endl;
    cout << "Rute : " << hapus->rute << endl;
    frontLL = frontLL->next;
    if (frontLL != NULL)
        frontLL->prev = NULL;
    else
        rearLL = NULL;
    pushLL(hapus->nama, hapus->rute);
    delete hapus;
    cout << "\nAntrian berhasil diproses!\n";
}
void tampilQueueLL() {
    if (frontLL == NULL) {
        cout << "\nAntrian kosong!\n";
        return;
    }
    garis();
    cout << "       ANTRIAN LINKED LIST\n";
    garis();
    NodeQueue* temp = frontLL;
    int nomor = 1;
    while (temp != NULL) {
        cout << nomor++ << ". ";
        cout << temp->nama
             << " | "
             << temp->rute << endl;
        temp = temp->next;
    }
}

void tampilBelakangQueueLL() {
    if (rearLL == NULL) {
        cout << "\nAntrian kosong!\n";
        return;
    }
    garis();
    cout << "    ANTRIAN DARI BELAKANG\n";
    garis();
    NodeQueue* temp = rearLL;
    int nomor = 1;
    while (temp != NULL) {
        cout << nomor++ << ". ";
        cout << temp->nama
             << " | "
             << temp->rute << endl;
        temp = temp->prev;
    }
}
void peekQueueLL() {
    if (frontLL == NULL) {
        cout << "\nAntrian kosong!\n";
        return;
    }
    garis();
    cout << "      ANTRIAN TERDEPAN\n";
    garis();
    cout << "Nama : " << frontLL->nama << endl;
    cout << "Rute : " << frontLL->rute << endl;
}

void pushLL(string nama, string rute) {
    NodeStack* baru = new NodeStack{
        nama,
        rute,
        NULL,
        NULL
    };
    if (topLL != NULL) {
        baru->next = topLL;
        topLL->prev = baru;
    }

    topLL = baru;
}
void popLL() {
    if (topLL == NULL) {
        cout << "\nRiwayat kosong!\n";
        return;
    }
    NodeStack* hapus = topLL;
    cout << "\nMenghapus : "
         << hapus->nama << endl;
    topLL = topLL->next;
    if (topLL != NULL)
        topLL->prev = NULL;
    delete hapus;
}

void tampilStackLL() {
    if (topLL == NULL) {
        cout << "\nRiwayat kosong!\n";
        return;
    }
    garis();
    cout << "      RIWAYAT LINKED LIST\n";
    garis();
    NodeStack* temp = topLL;
    int nomor = 1;
    while (temp != NULL) {
        cout << nomor++ << ". ";
        cout << temp->nama
             << " | "
             << temp->rute << endl;
        temp = temp->next;
    }
}

void peekStackLL() {
    if (topLL == NULL) {
        cout << "\nRiwayat kosong!\n";
        return;
    }
    garis();
    cout << "      RIWAYAT TERAKHIR\n";
    garis();
    cout << "Nama : " << topLL->nama << endl;
    cout << "Rute : " << topLL->rute << endl;
}

int main() {
    Kereta data[100];
    int n = 0;
    int pilih;
    isiDataAwal(data, n);
    do {
        garis();
        cout << "         MENU KERETA API\n";
        garis();
        cout << "1. Data Kereta\n";
        cout << "2. Pencarian\n";
        cout << "3. Pengurutan\n";
        cout << "4. Antrian (Array)\n";
        cout << "5. Riwayat (Array)\n";
        cout << "6. Antrian (Linked List)\n";
        cout << "7. Riwayat (Linked List)\n";
        cout << "8. Keluar\n";
        garis();
        cout << "Pilih Menu : ";
        cin >> pilih;
        switch (pilih) {

        case 1: {
            int p;
            garis();
            cout << "          DATA KERETA\n";
            garis();
            cout << "1. Tambah Data\n";
            cout << "2. Tampilkan Jadwal\n";
            garis();
            cout << "Pilih : ";
            cin >> p;
            if (p == 1)
                tambah(data, n);
            else if (p == 2)
                tampil(data, n);
            else
                cout << "\nMenu tidak tersedia!\n";
            break;
        }
        case 2: {
            int p;
            garis();
            cout << "            PENCARIAN\n";
            garis();
            cout << "1. Cari Rute\n";
            cout << "2. Cari No Kereta\n";
            cout << "3. Detail Berdasarkan ID\n";
            cout << "4. Detail Berdasarkan Nama\n";
            garis();
            cout << "Pilih : ";
            cin >> p;
            if (p == 1) {
                string asal, tujuan;
                cin.ignore();
                cout << "Masukkan Asal   : ";
                getline(cin, asal);
                cout << "Masukkan Tujuan : ";
                getline(cin, tujuan);
                linearSearch(data, n, asal, tujuan);
            }
            else if (p == 2) {
                sortByNo(data, n);
                int key;
                cout << "Masukkan No Kereta : ";
                cin >> key;
                int idx =
                jumpSearch(data, n, key);
                if (idx != -1)
                    tampilDetail(&data[idx]);
                else
                    cout << "\nData tidak ditemukan!\n";
            }
            else if (p == 3) {
                int id;
                cout << "Masukkan ID Kereta : ";
                cin >> id;
                cariById(data, n, id);
            }
            else if (p == 4) {
                string nama;
                cin.ignore();
                cout << "Masukkan Nama Kereta : ";
                getline(cin, nama);
                cariByNama(data, n, nama);
            }
            else {
                cout << "\nMenu tidak tersedia!\n";
            }
            break;
        }
        case 3: {
            int p;
            garis();
            cout << "           PENGURUTAN\n";
            garis();
            cout << "1. Urutkan Nama\n";
            cout << "2. Urutkan Harga\n";
            garis();
            cout << "Pilih : ";
            cin >> p;
            if (p == 1) {
                mergeSort(data, 0, n - 1);
                cout << "\nBerhasil diurutkan berdasarkan nama!\n";
                tampil(data, n);
            }
            else if (p == 2) {
                selectionSort(data, n);
                cout << "\nBerhasil diurutkan berdasarkan harga!\n";
                tampil(data, n);
            }
            else {
                cout << "\nMenu tidak tersedia!\n";
            }
            break;
        }
        case 4: {
            int p;
            garis();
            cout << "         ANTRIAN ARRAY\n";
            garis();
            cout << "1. Tambah Penumpang\n";
            cout << "2. Layani Antrian\n";
            cout << "3. Tampilkan Antrian\n";
            cout << "4. Lihat Antrian Terdepan\n";
            garis();
            cout << "Pilih : ";
            cin >> p;
            if (p == 1) {
                string nama, rute;
                cin.ignore();
                cout << "Masukkan Nama : ";
                getline(cin, nama);
                cout << "Masukkan Rute : ";
                getline(cin, rute);
                enqueue(nama, rute);
            }
            else if (p == 2)
                dequeue();
            else if (p == 3)
                tampilQueue();
            else if (p == 4)
                peekQueue();
            else
                cout << "\nMenu tidak tersedia!\n";
            break;
        }
        case 5: {
            int p;
            garis();
            cout << "         RIWAYAT ARRAY\n";
            garis();
            cout << "1. Hapus Terakhir\n";
            cout << "2. Lihat Riwayat\n";
            cout << "3. Cek Terakhir\n";
            garis();
            cout << "Pilih : ";
            cin >> p;
            if (p == 1)
                pop();
            else if (p == 2)
                tampilStack();
            else if (p == 3)
                peekStack();
            else
                cout << "\nMenu tidak tersedia!\n";
            break;
        }
        case 6: {
            int p;
            garis();
            cout << "      ANTRIAN LINKED LIST\n";
            garis();
            cout << "1. Tambah Antrian\n";
            cout << "2. Proses Antrian\n";
            cout << "3. Tampilkan Antrian\n";
            cout << "4. Cek Terdepan\n";
            cout << "5. Tampilkan dari Belakang\n";
            garis();
            cout << "Pilih : ";
            cin >> p;
            if (p == 1) {
                string nama, rute;
                cin.ignore();
                cout << "Masukkan Nama : ";
                getline(cin, nama);
                cout << "Masukkan Rute : ";
                getline(cin, rute);
                enqueueLL(nama, rute);
            }
            else if (p == 2)
                dequeueLL();
            else if (p == 3)
                tampilQueueLL();
            else if (p == 4)
                peekQueueLL();
            else if (p == 5)
                tampilBelakangQueueLL();
            else
                cout << "\nMenu tidak tersedia!\n";
            break;
        }
        case 7: {
            int p;
            garis();
            cout << "      RIWAYAT LINKED LIST\n";
            garis();
            cout << "1. Hapus Terakhir\n";
            cout << "2. Lihat Riwayat\n";
            cout << "3. Cek Terakhir\n";
            garis();
            cout << "Pilih : ";
            cin >> p;
            if (p == 1)
                popLL();
            else if (p == 2)
                tampilStackLL();
            else if (p == 3)
                peekStackLL();
            else
                cout << "\nMenu tidak tersedia!\n";
            break;
        }
        case 8:
            cout << "\nTerima kasih telah menggunakan program!\n";
            break;
        default:
            cout << "\nMenu tidak tersedia!\n";
        }
    } while (pilih != 8);
    return 0;
}