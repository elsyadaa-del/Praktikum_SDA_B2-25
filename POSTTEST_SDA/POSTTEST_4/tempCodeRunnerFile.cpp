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
    NodeQueue* next;
};

struct NodeStack {
    string nama;
    string rute;
    NodeStack* next;
};

NodeQueue *frontLL = NULL, *rearLL = NULL;
NodeStack *topLL = NULL;

void push(string nama, string rute);

Tiket queueTiket[MAX];
int front = -1, rear = -1;

bool isQueueEmpty() {
    return front == -1 || front > rear;
}

bool isQueueFull() {
    return rear == MAX - 1;
}

void enqueue(string nama, string rute) {
    if (isQueueFull()) {
        cout << "Antrian penuh!\n";
        return;
    }
    if (front == -1) front = 0;

    rear++;
    queueTiket[rear] = {nama, rute};

    cout << "Penumpang masuk antrian\n";
}

void dequeue() {
    if (isQueueEmpty()) {
        cout << "Antrian kosong!\n";
        return;
    }

    Tiket t = queueTiket[front];
    cout << "\nMemproses tiket:\n";
    cout << "Nama  : " << t.nama << endl;
    cout << "Rute  : " << t.rute << endl;

    front++;

    if (front > rear) front = rear = -1;

    push(t.nama, t.rute);
}

void tampilQueue() {
    if (isQueueEmpty()) {
        cout << "Antrian kosong\n";
        return;
    }

    cout << "\n=== ANTRIAN ===\n";
    for (Tiket *p = queueTiket + front; p <= queueTiket + rear; p++) {
        cout << p->nama << " - " << p->rute << endl;
    }
}

void peekQueue() {
    if (isQueueEmpty()) {
        cout << "Antrian kosong\n";
        return;
    }
    cout << "Terdepan: " << queueTiket[front].nama << endl;
}

Tiket stackRiwayat[MAX];
int top = -1;

bool isStackEmpty() {
    return top == -1;
}

void push(string nama, string rute) {
    if (top == MAX - 1) {
        cout << "Stack penuh!\n";
        return;
    }

    top++;
    stackRiwayat[top] = {nama, rute};
}

void pop() {
    if (isStackEmpty()) {
        cout << "Riwayat kosong!\n";
        return;
    }

    cout << "Menghapus riwayat: " << stackRiwayat[top].nama << endl;
    top--;
}

void peekStack() {
    if (isStackEmpty()) {
        cout << "Riwayat kosong\n";
        return;
    }

    cout << "Transaksi terakhir: " << stackRiwayat[top].nama << endl;
}

void tampilStack() {
    if (isStackEmpty()) {
        cout << "Riwayat kosong\n";
        return;
    }

    cout << "\n=== RIWAYAT TRANSAKSI ===\n";
    for (Tiket *p = stackRiwayat; p <= stackRiwayat + top; p++) {
        cout << p->nama << " - " << p->rute << endl;
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

    for (int i = 0; i < n; i++) {
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "\nData ditemukan\n";
            swap(arr + i, arr);
            tampilDetail(arr);
            ketemu = true;
        }
    }

    if (!ketemu) cout << "Data tidak ditemukan\n";
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

void enqueueLL(string nama, string rute) {
    NodeQueue* baru = new NodeQueue{nama, rute, NULL};

    if (frontLL == NULL) {
        frontLL = rearLL = baru;
    } else {
        rearLL->next = baru;
        rearLL = baru;
    }

    cout << "Berhasil masuk ke antrian\n";
}

void dequeueLL() {
    if (frontLL == NULL) {
        cout << "Antrian kosong\n";
        return;
    }

    NodeQueue* hapus = frontLL;

    cout << "\nMemproses tiket:\n";
    cout << "Nama : " << hapus->nama << endl;
    cout << "Rute : " << hapus->rute << endl;

    frontLL = frontLL->next;

    push(hapus->nama, hapus->rute);

    delete hapus;

    if (frontLL == NULL) rearLL = NULL;
}

void tampilQueueLL() {
    if (frontLL == NULL) {
        cout << "Antrian kosong\n";
        return;
    }

    NodeQueue* temp = frontLL;
    while (temp != NULL) {
        cout << temp->nama << " - " << temp->rute << endl;
        temp = temp->next;
    }
}

void peekQueueLL() {
    if (frontLL == NULL) {
        cout << "Antrian kosong\n";
        return;
    }
    cout << "Terdepan: " << frontLL->nama << endl;
}

void pushLL(string nama, string rute) {
    NodeStack* baru = new NodeStack{nama, rute, NULL};
    baru->next = topLL;
    topLL = baru;
}

void popLL() {
    if (topLL == NULL) {
        cout << "Riwayat kosong\n";
        return;
    }

    NodeStack* hapus = topLL;
    cout << "Menghapus: " << hapus->nama << endl;

    topLL = topLL->next;
    delete hapus;
}

void tampilStackLL() {
    if (topLL == NULL) {
        cout << "Riwayat kosong\n";
        return;
    }

    NodeStack* temp = topLL;
    while (temp != NULL) {
        cout << temp->nama << " - " << temp->rute << endl;
        temp = temp->next;
    }
}

void peekStackLL() {
    if (topLL == NULL) {
        cout << "Riwayat kosong\n";
        return;
    }

    cout << "Terakhir: " << topLL->nama << endl;
}

int main() {
    Kereta data[100];
    int n = 0, pilih;

    isiDataAwal(data, n);

    do {
    cout << "\n+==========================================+\n";
    cout << "|            MENU KERETA API               |\n";
    cout << "+==========================================+\n";
    cout << "| 1. Data Kereta                          |\n";
    cout << "| 2. Pencarian                            |\n";
    cout << "| 3. Pengurutan                           |\n";
    cout << "| 4. Antrian (Array)                      |\n";
    cout << "| 5. Riwayat (Array)                      |\n";
    cout << "| 6. Antrian (Linked List)                |\n";
    cout << "| 7. Riwayat (Linked List)                |\n";
    cout << "| 8. Keluar                               |\n";
    cout << "+==========================================+\n";
    cout << " Pilih menu: ";
    cin >> pilih;

        switch(pilih) {
        case 1: {
            int p;
            cout << "\n+-----------------------------+\n";
            cout << "|        DATA KERETA          |\n";
            cout << "+-----------------------------+\n";
            cout << "| 1. Tambah Data              |\n";
            cout << "| 2. Tampilkan Jadwal         |\n";
            cout << "+-----------------------------+\n";
            cout << " Pilih: ";
            cin >> p;

            if (p == 1) tambah(data, n);
            else if (p == 2) tampil(data, n);
            break;
        }

        case 2: {
            int p;
            cout << "\n+-----------------------------+\n";
            cout << "|         PENCARIAN           |\n";
            cout << "+-----------------------------+\n";
            cout << "| 1. Cari Rute                |\n";
            cout << "| 2. Cari No Kereta           |\n";
            cout << "+-----------------------------+\n";
            cout << " Pilih: ";
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
                cout << "Masukkan No Kereta: ";
                cin >> key;

                int idx = jumpSearch(data, n, key);

                if (idx != -1) {
                    tampilDetail(&data[idx]);
                } 
                
                else {
                    cout << "Tidak ditemukan\n";
                }
            }

            else {
                cout << "Pilihan tidak valid\n";
            }

            break;
        }

        case 3: {
            int p;
            cout << "\n+-----------------------------+\n";
            cout << "|        PENGURUTAN           |\n";
            cout << "+-----------------------------+\n";
            cout << "| 1. Urutkan Nama             |\n";
            cout << "| 2. Urutkan Harga            |\n";
            cout << "+-----------------------------+\n";
            cout << " Pilih: ";
            cin >> p;

            if (p == 1) {
                mergeSort(data, 0, n - 1);
                cout << "Data berhasil diurutkan (Nama)\n";
            }
            else if (p == 2) {
                selectionSort(data, n);
                cout << "Data berhasil diurutkan (Harga)\n";
            }
            break;
        }

        case 4: {
            int p;
            cout << "\n+-----------------------------+\n";
            cout << "|      ANTRIAN (ARRAY)        |\n";
            cout << "+-----------------------------+\n";
            cout << "| 1. Tambah Antrian           |\n";
            cout << "| 2. Proses                   |\n";
            cout << "| 3. Lihat                    |\n";
            cout << "| 4. Cek Depan                |\n";
            cout << "+-----------------------------+\n";
            cout << " Pilih: ";
            cin >> p;

            if (p == 1) {
                string nama, rute;
                cin.ignore();
                getline(cin, nama);
                getline(cin, rute);
                enqueue(nama, rute);
            } 
            else if (p == 2) dequeue();
            else if (p == 3) tampilQueue();
            else if (p == 4) peekQueue();
            break;
        }

        case 5: {
            int p;
            cout << "\n+-----------------------------+\n";
            cout << "|      RIWAYAT (ARRAY)        |\n";
            cout << "+-----------------------------+\n";
            cout << "| 1. Hapus Terakhir           |\n";
            cout << "| 2. Lihat Riwayat            |\n";
            cout << "| 3. Cek Terakhir             |\n";
            cout << "+-----------------------------+\n";
            cout << " Pilih: ";
            cin >> p;

            if (p == 1) pop();
            else if (p == 2) tampilStack();
            else if (p == 3) peekStack();
            break;
        }

        case 6: {
            int p;
            cout << "\n+-----------------------------+\n";
            cout << "|   ANTRIAN (LINKED LIST)     |\n";
            cout << "+-----------------------------+\n";
            cout << "| 1. Tambah Antrian           |\n";
            cout << "| 2. Proses                   |\n";
            cout << "| 3. Lihat                    |\n";
            cout << "| 4. Cek Depan                |\n";
            cout << "+-----------------------------+\n";
            cout << " Pilih: ";
            cin >> p;

            if (p == 1) {
                string nama, rute;
                cin.ignore();
                getline(cin, nama);
                getline(cin, rute);
                enqueueLL(nama, rute);
            } 
            else if (p == 2) dequeueLL();
            else if (p == 3) tampilQueueLL();
            else if (p == 4) peekQueueLL();
            break;
        }

        case 7: {
            int p;
            cout << "\n+-----------------------------+\n";
            cout << "|   RIWAYAT (LINKED LIST)     |\n";
            cout << "+-----------------------------+\n";
            cout << "| 1. Hapus Terakhir           |\n";
            cout << "| 2. Lihat Riwayat            |\n";
            cout << "| 3. Cek Terakhir             |\n";
            cout << "+-----------------------------+\n";
            cout << " Pilih: ";
            cin >> p;

            if (p == 1) popLL();
            else if (p == 2) tampilStackLL();
            else if (p == 3) peekStackLL();
            break;
        }
    }

} while (pilih != 8);

    return 0;
}